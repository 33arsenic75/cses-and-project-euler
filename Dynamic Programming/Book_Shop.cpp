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
template <typename T> void chkmin(T &x, T y) {
  if (x > y)
    x = y;
}
template <typename T> void chkmax(T &x, T y) {
  if (x < y)
    x = y;
}
using namespace std;
// ------------------------------------------***--------------------------------------------------






int32_t main() {
    // freopen("input.txt","r",stdin);
    int n,W;cin>>n>>W;
    vector<int>w(n+1),v(n+1);
    for(int i=1; i <=n ; i++)cin>>w[i];
    for(int i=1; i <=n ; i++)cin>>v[i];
    vector<vector<int>>dp(n+1,vector<int>(W+1,0));
    for(int i = 1 ; i <=n ; i++){
        for(int wgt = 0 ; wgt <= W ; wgt++){
            dp[i][wgt] = dp[i-1][wgt];
            if(wgt>=w[i]){
                dp[i][wgt] = max(dp[i][wgt],v[i] + dp[i-1][wgt-w[i]]);
            }
        }
    }
    int ans = 0;
    for(int i = 0 ; i <= n ; i++){
        for(int j = 0 ; j <= W ; j++)chkmax(ans,dp[i][j]);
    }
    cout<<ans<<'\n';
    return 0;
}
