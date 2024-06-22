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
/// ordered sets support upperbound lowerbound too
#include <map>
#include <unordered_map>
#include <cstring>
#define len(v) (int)v.size()
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
using namespace std;
using ll = long long;
#define pb push_back
#define rep(i, a, b) for (int i = a; i < b; i++)
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
#define __gcd __algo_gcd
#else
#define debug(x)
#endif
const ll INF = 1e9;
const ll LINF = INF * INF;
 
// ------------------------------------------***--------------------------------------------------
 
 
const ll mod = 1000000007; 
 
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // freopen("input.txt","r",stdin);
    int n, m; cin >> n >> m;
    vector<vector<ll>>adj(n+1);
  	for(int i = 0; i < m; i++) {
	  	int a, b; cin >> a >> b;
		  adj[b].pb(a);
	  }
    vector<vector<ll>>dp((1<<20),vector<ll>(21));
  	dp[1][1] = 1; // there is one way to fly from 1 to itself
    for(int s = 2; s < (1<<n); s++) { // we start from the second city
      if((s & (1 << (n-1))) && s != ((1<<n) - 1)) continue;
      for(int d = 1; d <= n; d++) { // loop through each city
        if((s & (1 << (d-1))) == 0) continue;
        for(int v : adj[d]) {
          if(s & (1<<(v-1))) { // if v is in the mask
            dp[s][d] += dp[s-(1<<(d-1))][v];
            dp[s][d] %= mod;
          }
        }
      }
    }
    cout << dp[(1<<n)-1][n] % mod;
    return 0;
}