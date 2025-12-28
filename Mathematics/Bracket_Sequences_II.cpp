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
    if(p==0) return 1ll;
    ll tmp = modpow(b, p/2, MOD);
    tmp = (tmp * tmp) % MOD;
    if(p & 1) tmp = (tmp * b) % MOD;
    return tmp;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll MOD = 1000000007;
    ll N;
    cin >> N;
    string s;
    cin >> s;
    
    // Validation
    bool valid = true;
    if(N & 1) valid = false;
    
    ll a = 0, b = 0;
    for(char c : s){
        if(c == '(') a++;
        else b++;
        if(a < b) valid = false;
    }
    
    ll n = N / 2;
    if(a > n || b > n) valid = false;
    
    if(!valid){
        cout << 0;
        return 0;
    }
    
    // Precompute factorials and inverse factorials
    ll L = 2 * n + 5;
    vector<ll> fac(L, 1ll);
    vector<ll> invfac(L, 1ll);
    
    rep(i, 1, L){
        fac[i] = (fac[i-1] * i) % MOD;
    }
    
    invfac[L-1] = modpow(fac[L-1], MOD-2, MOD);
    for(ll i = L-2; i >= 0; i--){
        invfac[i] = (invfac[i+1] * (i+1)) % MOD;
    }
    
    // Calculate answer using Catalan number formula
    ll remaining = 2 * n - a - b;
    ll open_needed = n - a;
    ll close_needed = n - b;
    
    // ans_1 = C(remaining, open_needed)
    ll ans_1 = fac[remaining];
    ans_1 = (ans_1 * invfac[open_needed]) % MOD;
    ans_1 = (ans_1 * invfac[close_needed]) % MOD;
    
    // ans_2 = C(remaining, open_needed - 1)
    ll ans_2 = 0;
    if(open_needed > 0){
        ans_2 = fac[remaining];
        ans_2 = (ans_2 * invfac[open_needed - 1]) % MOD;
        ans_2 = (ans_2 * invfac[close_needed + 1]) % MOD;
    }
    
    ll ans = ((ans_1 - ans_2) % MOD + MOD) % MOD;
    cout << ans ;
    
    return 0;
}
