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
    if(b==0 && p==0)return 1;
    if(p==0)return 1;
    ll tmp = mod_pow(b, p/2, M);
    tmp *= tmp;
    tmp %= M;
    if(p&1)tmp *= b;
    tmp %= M;
    return tmp;
}


int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll MOD = (1e9) + 7;
    ll MOD1 = MOD-1;
    ll n; cin>>n; 
    vector<ll>p(n,0), alpha(n, 0);
    rep(i,0,n)cin>>p[i]>>alpha[i];

    ll num_divisiors = 1;
    ll num_divisiors_1 = 1;
    for(ll ap: alpha){
        num_divisiors *= (1+ap);
        num_divisiors_1 *= (1+ap);
        num_divisiors %= MOD;
        num_divisiors_1 %= (2*MOD1);
    }
    
    ll sum_divisors = 1;
    rep(i,0,n){
        sum_divisors *= (mod_pow(p[i], alpha[i]+1, MOD) + MOD - 1);
        sum_divisors %= MOD;
        sum_divisors *= mod_pow(p[i]-1, MOD-2, MOD);
        sum_divisors %= MOD;
    }
    ll prd_divisors = 1;
    rep(i,0,n){
        // prd_divisors *= mod_pow(p[i], ((alpha[i]*num_divisiors_1)/2ll), MOD);
        if(alpha[i]&1){
            ll tmp = mod_pow(p[i], alpha[i], MOD);
            tmp = mod_pow(tmp, (num_divisiors_1/2LL), MOD);
            prd_divisors *= tmp;
            prd_divisors %= MOD;
        }
        else{
            ll tmp = mod_pow(p[i], (alpha[i]/2LL), MOD);
            tmp = mod_pow(tmp, num_divisiors_1, MOD);
            prd_divisors *= tmp;
            prd_divisors %= MOD;
        }
    }

    cout<<num_divisiors<<" "<<sum_divisors<<" "<<prd_divisors;
    // 689682945 950748992 115729452
    return 0;
}

