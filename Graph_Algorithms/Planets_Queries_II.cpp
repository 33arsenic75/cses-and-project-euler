// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC target("popcnt")
// #pragma GCC target("avx,avx2,fma")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <algorithm>
#include <bitset>
#include <deque>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <stdlib.h>
#include <unordered_set>
#include <vector>
#include<functional>
#include<cmath>
#include<numeric>
/// ordered sets support upperbound lowerbound too
#include <map>
#include <unordered_map>
#include <cstring>
#define len(v) (ll)v.size()
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back
#define rep(i, a, b) for (ll i = a; i < b; i++)
#define f first
#define mk make_pair
#define in insert
#define py cout << "YES\n"
#define pn cout << "NO\n"
template <typename T> void chkmin(T &x, T y) {
  if (x > y)
    x = y;
}
template <typename T> void chkmax(T &x, T y) {
  if (x < y)
    x = y;
}

#ifndef ONLINE_JUDGE
#define debug(x) cout << #x << " = " << x << endl
#define show1(v)                                                               \
  for (auto i : v)                                                             \
  cout << i << ' '
#define show(v)                                                                \
  show1(v);                                                                    \
  cout << '\n'
#else
#define debug(x)
#endif
const ll INF = 1e9;
const ll LINF = INF * INF;

// ------------------------------------------***--------------------------------------------------

ll gcd(ll a, ll b){
    if(b==0)return a;
    return gcd(b,a%b);
}

int main() {
	int planet_num;
	int query_num;
	std::cin >> planet_num >> query_num;
	vector<int> next(planet_num);
	vector<vector<int>> before(planet_num);
	for (int p = 0; p < planet_num; p++) {
		std::cin >> next[p];
		next[p]--;
		before[next[p]].push_back(p);
	}

	/*
	 * -2 = We haven't even got to processing this planet yet.
	 * -1 = This node is part of a tree.
	 * >= 0: the ID of the cycle the planet belongs to.
	 */
	vector<int> cycle_id(planet_num, -2);
	// Each map, given a planet #, returns the index of that planet in the
	// cycle.
	vector<std::map<int, int>> cycles;
	for (int p = 0; p < planet_num; p++) {
		if (cycle_id[p] != -2) { continue; }
		vector<int> path{p};
		int at = p;
		while (cycle_id[next[at]] == -2) {
			at = next[at];
			cycle_id[at] = -3;  // Leave breadcrumbs for this iteration
			path.push_back(at);
		}

		std::map<int, int> cycle;
		bool in_cycle = false;
		for (int i : path) {
			in_cycle = in_cycle || i == next[at];
			if (in_cycle) { cycle[i] = cycle.size(); }
			cycle_id[i] = in_cycle ? cycles.size() : -1;
		}
		cycles.push_back(cycle);
	}

	/*
	 * Precalculate the distance from each planet to its cycle with BFS.
	 * (cyc_dist[p] = 0) if p is part of a cycle.
	 */
	vector<int> cyc_dist(planet_num);
	for (int p = 0; p < planet_num; p++) {
		// Check if this planet is part of a cycle.
		if (cycle_id[next[p]] == -1 || cycle_id[p] != -1) { continue; }
		cyc_dist[p] = 1;
		vector<int> stack(before[p]);
		while (!stack.empty()) {
			int curr = stack.back();
			stack.pop_back();
			cyc_dist[curr] = cyc_dist[next[curr]] + 1;
			stack.insert(stack.end(), before[curr].begin(), before[curr].end());
		}
	}

	// Initialize the binary jumping arrays.
	int log2 = std::ceil(std::log2(planet_num));
	vector<vector<int>> pow2_ends(planet_num, vector<int>(log2 + 1));
	for (int p = 0; p < planet_num; p++) { pow2_ends[p][0] = next[p]; }
	for (int i = 1; i <= log2; i++) {
		for (int p = 0; p < planet_num; p++) {
			pow2_ends[p][i] = pow2_ends[pow2_ends[p][i - 1]][i - 1];
		}
	}

	/*
	 * Given a starting planet & dist, returns the planet we end up at
	 * if we use the teleporter dist times.
	 */
	auto advance = [&](int pos, int dist) {
		for (int pow = log2; pow >= 0; pow--) {
			if ((dist & (1 << pow)) != 0) { pos = pow2_ends[pos][pow]; }
		}
		return pos;
	};
	for (int q = 0; q < query_num; q++) {
		int u, v;  // going from u to v
		std::cin >> u >> v;
		u--;
		v--;
		if (cycle_id[pow2_ends[u][log2]] != cycle_id[pow2_ends[v][log2]]) {
			cout << -1 << '\n';
			continue;
		}
		if (cycle_id[u] != -1 || cycle_id[v] != -1) {
			if (cycle_id[v] == -1 && cycle_id[u] != -1) {
				cout << -1 << '\n';
				continue;
			}
			// Handle the 2nd & 3rd cases at the same time.
			int dist = cyc_dist[u];
			int u_cyc = advance(u, cyc_dist[u]);  // The root of u's tree

			std::map<int, int> &cyc = cycles[cycle_id[u_cyc]];  // u and v's cycle
			int u_ind = cyc[u_cyc];
			int v_ind = cyc[v];
			int diff = u_ind <= v_ind ? v_ind - u_ind : cyc.size() - (u_ind - v_ind);
			cout << dist + diff << '\n';
		} else {
			if (cyc_dist[v] > cyc_dist[u]) {
				cout << -1 << '\n';
				continue;
			}
			int diff = cyc_dist[u] - cyc_dist[v];
			cout << (advance(u, diff) == v ? diff : -1) << '\n';
		}
	}
}
