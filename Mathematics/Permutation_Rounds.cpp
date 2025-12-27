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
    if(p==0)return 1ll;
    ll tmp = modpow(b, p/2, MOD);
    tmp *= tmp;
    tmp %= MOD;
    if(p&1)tmp*=b;
    tmp %= MOD;
    return tmp;
}

vector<ll> sieve(ll n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (ll i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }

    vector<ll> primes;
    for (ll i = 2; i <= n; i++) {
        if (is_prime[i]) primes.push_back(i);
    }

    return primes;
}

#include <cassert>
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll MOD = (1e9)+7;
    ll n;
    cin>>n;

    vector<ll>prm = sieve(2*(1e5));
    
    vector<ll>perm(n+1,0);
    rep(i,1,n+1)cin>>perm[i];
    vector<bool>vis(n+1,false);
    map<ll,ll>prmfac;
    ll ans = 1;
    ll sum_len = 0;
    function<void(ll)>cycle_length = [&](ll start){
        ll node = start;
        ll c_len = 1;
        while(perm[node]!=start){
            vis[node]=true;
            node = perm[node];
            c_len++;
        }
        vis[node]=true;
        // debug(start);
        for(ll p: prm){
            if(c_len == 1)break;
            ll cnt = 0;
            while(c_len%p==0){
                c_len/=p;
                cnt++;
            }
            if(prmfac.count(p))prmfac[p] = max(prmfac[p], cnt);
            else prmfac[p] = cnt;
        }
    };
    // debug(sum_len);
    rep(i,1,n+1){
        if(!vis[i])cycle_length(i);
    }
    for(auto&[k,v]: prmfac){
        ans *= modpow(k, v, MOD);
        ans %= MOD;
    }
    cout<<ans;
    return 0;
}
