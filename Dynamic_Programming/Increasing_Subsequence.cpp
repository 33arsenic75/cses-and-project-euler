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
const ll INF= 1e9;
const ll LINF = INF * INF;

// ------------------------------------------***--------------------------------------------------






int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;cin>>n;
    vector<ll>a(n);
    rep(i,0,n)cin>>a[i];
    vector<ll>d(n+1,LINF);
    d[0] = -INF;
    for(int i: a){
        int low = 0, high = n , mid = 0, ans = 0;
        while(low <= high){
            mid = low + (high - low)/2;
            if(d[mid] >= i){
                ans = mid;
                high = mid - 1;
            }
            else{
                low = mid + 1;
            }
        }
        d[ans] = i;
    }
    int ans = 0;
    for(int i = 1 ; i <= n ; i++){
        if(d[i]!=LINF)ans = i;
    }
    cout<<ans;
    return 0;
}
