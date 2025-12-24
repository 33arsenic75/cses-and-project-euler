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
ll mod_pow(ll b, ll p, ll M){
    if(p==0)return 1ll;
    ll tmp = mod_pow(b, p/2, M);
    tmp *= tmp;
    tmp %= M;
    if(p&1)tmp*=b;
    return tmp%M;
}


int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s; 
    cin>>s;
    ll n = s.size();
    ll MOD = (1e9) + 7;
    vector<ll>cnt(26,0);
    for(char c: s)cnt[c-'a']++;
    vector<ll>fac(n+1,1);
    rep(i,2,n+1){
        fac[i] = fac[i-1]*i;
        fac[i] %= MOD;
    }
    ll ans = fac[n];
    for(ll c: cnt){
        ans *= mod_pow(fac[c], MOD-2, MOD);
        ans %= MOD;
    }
    cout<<ans<<'\n';
    return 0;
}
