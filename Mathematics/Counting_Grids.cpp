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

ll modpow(ll b, ll p, ll MOD){
    if(p==0)return 1;
    ll tmp = modpow(b, p/2, MOD);
    tmp *= tmp;
    tmp %= MOD;
    if(p&1)tmp*=b;
    return (tmp%MOD);
}


int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll MOD = (1e9)+7;
    ll n;
    cin>>n;

    function<ll(ll)>r1 = [&](ll s){
        if(s&1){
            ll m = s/2;
            return (m+1)*m+ 1;
        }
        return (s/2)*(s/2);
    };
    function<ll(ll)>r2 = [&](ll s){
        if(s&1){
            ll m = s/2;
            return 2*m*(m+1)+1;
        }
        return 2*(s/2)*(s/2);
    };

    ll ans = 0;
    // debug(r1(n));
    // debug(r2(n));
    ans += modpow(2, n*n, MOD);
    ans += modpow(2, r1(n), MOD);
    ans %= MOD;
    ans += modpow(2, r1(n), MOD);
    ans %= MOD;
    ans += modpow(2, r2(n), MOD);
    ans %= MOD;
    ans *= modpow(4, MOD-2, MOD);
    ans %= MOD;
    cout<<ans;
    return 0;
}
