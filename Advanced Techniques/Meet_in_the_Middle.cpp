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

void solve() {
}

unordered_map<ll,ll> allsums(vector<ll>&a){
    ll n = a.size();
    vector<ll>ans;
    unordered_map<ll,ll>mp;
    for(ll i = 0 ; i < (1<<n) ; i++){
        ll sum = 0;
        for(ll j = 0 ; j < n ; j++){
            if( (i>>j)&1 )sum+=a[j];
        } 
        ans.pb(sum);
    }
    for(ll num: ans)mp[num]+=1;
    return mp;
}

vector<ll> allsumsv(vector<ll>&a){
    ll n = a.size();
    vector<ll>ans;
    unordered_map<ll,ll>mp;
    for(ll i = 0 ; i < (1<<n) ; i++){
        ll sum = 0;
        for(ll j = 0 ; j < n ; j++){
            if( (i>>j)&1 )sum+=a[j];
        } 
        ans.pb(sum);
    }
    sort(all(ans));
    return ans;
}


int32_t main() {
    ios_base::sync_with_stdio(false);
    
    ll n, t;
    cin>>n>>t; 
    ll n1 = n/2;
    ll n2 = n - n1;
    ll mx = 0;
    vector<ll>v1(n1,0),v2(n2,0);
    
    rep(i,0,n1){
        cin>>v1[i];
        mx = max(mx, v1[i]);
    }
    rep(i,0,n2){
        cin>>v2[i];
        mx = max(mx, v2[i]);
    }

    vector<ll>a = allsumsv(v1);
    vector<ll>b = allsumsv(v2);

    ll ans = 0;
    
    for(ll s1 : a) {
        ll s2 = t - s1;
        // count number of times s2 appears in b
        auto low = lower_bound(b.begin(), b.end(), s2);
        auto high = upper_bound(b.begin(), b.end(), s2);
        ans += high - low; // number of occurrences
    }
    cout<<ans;
    return 0;
}
