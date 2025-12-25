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






const int MOD = 1000'000'007;
int32_t main() {
    ios_base::sync_with_stdio(false);
    // freopen("input.txt","r",stdin);
    cin.tie(NULL);
    int n,m;cin>>n>>m;
    vector<int>a(n+1);
    rep(i,1,n+1)cin>>a[i];
    vector<vector<int>>dp(n+1,vector<int>(m+2,0));
    if(a[1]==0){
        for(int i = 1 ; i <= m ; i++)dp[1][i] = 1;
    }
    else{
        dp[1][a[1]]=1;
    }
    for(int i = 2 ; i <=n ; i++){
        if(a[i]!=0){
            int j = a[i];
            dp[i][j] = dp[i-1][j-1] + dp[i-1][j] + dp[i-1][j+1];
            dp[i][j]%=MOD;
            continue;
        }
        for(int j = 1 ; j <= m ; j++){
            dp[i][j] = dp[i-1][j-1] + dp[i-1][j] + dp[i-1][j+1];
            dp[i][j]%=MOD;
        }
    }
    int ans = 0;
    for(int i = 1 ; i <= m ; i++){
        ans += dp[n][i];
        ans%=MOD;
    }
    cout<<ans;
    return 0;
}
