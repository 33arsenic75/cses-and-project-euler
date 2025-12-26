#include <algorithm>
#include <climits>
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
/// ordered sets support upperbound lowerbound too
#include <map>
#include <unordered_map>
#define len(v) (ll)v.size()
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
using namespace std;
#define ll long long
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
#define __gcd __algo_gcd
#else
#define debug(x)
#endif

// ------------------------------------------***--------------------------------------------------

const ll INF = 1e9;
const ll LINF = INF * INF;

int n;
int mask;
vector<vector<int>> adj;
vector<int> ans;

void dfs(int u) {
    while (!adj[u].empty()) {
        int bit = adj[u].back();
        adj[u].pop_back();
        int v = ((u << 1) & mask) | bit;
        dfs(v);
        ans.push_back(bit);
    }
}

int main() {
    cin >> n;
    if(n==1){
        cout<<"01";
        return 0;
    }
    int nodes = 1 << (n - 1);
    mask = nodes - 1;
    adj.assign(nodes, {});

    // build graph
    for (int u = 0; u < nodes; u++) {
        adj[u].push_back(0);
        adj[u].push_back(1);
    }

    dfs(0);

    // print first (n-1) bits
    for (int i = n - 2; i >= 0; i--) {
        cout << ((0 >> i) & 1);
    }

    // print edge labels
    for (int i = ans.size() - 1; i >= 0; i--) {
        cout << ans[i];
    }
    cout << '\n';
}
