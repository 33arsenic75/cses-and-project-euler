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
#define len(v) (int)v.size()
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
using namespace std;
#define int long long
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
const int INF = 1e9;
const int LINF = INF * INF;

// ------------------------------------------***--------------------------------------------------



int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int a,b;cin>>a>>b;
    vector<vector<int>>dp(a+1,vector<int>(b+1,INF));
    for(int i = 1 ; i <= min(a,b) ; i++){
        dp[i][i]=0;
    }
    for(int i = 1 ; i <= a ; i++){
        for(int j = 1 ; j <= b ; j++){
            for(int k = 1 ; k <= i-1 ; k++){
                dp[i][j] = min(dp[i][j], 1 + dp[k][j] + dp[i-k][j]);
            }
            for(int k = 1; k <= j-1 ; k++){
                dp[i][j] = min(dp[i][j], 1 + dp[i][k] + dp[i][j-k]);
            }
        }
    }
    cout<<dp[a][b];
    return 0;
}
