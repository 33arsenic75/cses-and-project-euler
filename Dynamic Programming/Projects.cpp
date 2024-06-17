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


bool compare(vector<ll>&a,vector<ll>&b){
    return a[1] < b[1];
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;cin>>n;
    vector<vector<ll>>a(n+1,vector<ll>(3,0ll));
    rep(i,1,n+1)cin>>a[i][0]>>a[i][1]>>a[i][2];
    sort(all(a),compare);
    // for(int i = 0 ; i <=n ; i++)cout<<a[i][0]<<" "<<a[i][1]<<" "<<a[i][2]<<"\n";
    vector<ll>dp(n+1,0ll);
    vector<ll>mx(n+1,0ll);
    for(int i = 1; i <= n ; i++){
        ll low = 0, high = i-1 , ans = 0, mid = 0;
        while(low<=high){
            mid = low + (high - low)/2;
            if(a[mid][1] < a[i][0]){
                ans = mid;
                low = mid + 1;
            }
            else{
                high = mid - 1;
            }
        }
        dp[i] = mx[ans] + a[i][2];
        mx[i] = max(dp[i],mx[i-1]);
    }
    ll ans = 0;
    for(ll i:dp)chkmax(ans,i);
    cout<<ans;
    return 0;
}
