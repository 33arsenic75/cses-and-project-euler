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
#include <iomanip>
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
#define fill(v,a,b) rep(i,a,b)cin>>v[i]
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


int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;

    const int N = 8;
    const int CELLS = 64;

    // prob[start][end] = probability that robot starting at `start`
    // ends at `end` after k moves
    vector<vector<long double>> prob(CELLS, vector<long double>(CELLS, 0.0L));

    for (int sx = 0; sx < N; sx++) {
        for (int sy = 0; sy < N; sy++) {

            vector<vector<long double>> dp(N, vector<long double>(N, 0.0L));
            dp[sx][sy] = 1.0L;

            for (int step = 1; step <= k; step++) {
                vector<vector<long double>> ndp(N, vector<long double>(N, 0.0L));

                for (int x = 0; x < N; x++) {
                    for (int y = 0; y < N; y++) {
                        if (dp[x][y] == 0) continue;

                        int cnt = 0;
                        for (int d = 0; d < 4; d++) {
                            int nx = x + dx[d];
                            int ny = y + dy[d];
                            if (nx >= 0 && nx < N && ny >= 0 && ny < N)
                                cnt++;
                        }

                        for (int d = 0; d < 4; d++) {
                            int nx = x + dx[d];
                            int ny = y + dy[d];
                            if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                                ndp[nx][ny] += dp[x][y] / cnt;
                            }
                        }
                    }
                }
                dp.swap(ndp);
            }

            int start_id = sx * N + sy;
            for (int x = 0; x < N; x++)
                for (int y = 0; y < N; y++)
                    prob[start_id][x * N + y] = dp[x][y];
        }
    }

    long double expected_empty = 0.0L;

    for (int cell = 0; cell < CELLS; cell++) {
        long double p_empty = 1.0L;
        for (int start = 0; start < CELLS; start++) {
            p_empty *= (1.0L - prob[start][cell]);
        }
        expected_empty += p_empty;
    }

    cout << fixed << setprecision(6) << expected_empty << "\n";
    return 0;
}
