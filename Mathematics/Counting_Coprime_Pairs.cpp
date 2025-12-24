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

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin>>n;
    vector<ll>a(n);
    rep(i,0,n)cin>>a[i];
    sort(all(a));
    vector<ll>mu(a[n-1]+1,1),d(a[n-1]+1,0);

    vector<ll>prms = sieve(a[n-1]);


    // function<vector<ll>(ll)>fact = [&](ll x){
    //     vector<ll>ans = {1};
    //     for(ll p: prms){
    //         vector<ll>t1 = {1};
    //         ll last = 1;
    //         while(x%p == 0){
    //             t1.push_back(last*p);
    //             x /= p;
    //             last *= p;
    //         }
    //         if(last==1)continue;
    //         vector<ll>t2;
    //         for(ll f1:ans){
    //             for(ll f2: t1)t2.push_back(f1*f2);
    //         }
    //         ans = t2;
    //     }
    //     return ans;
    // };

    for(int p : prms){
        for(ll d = p ; d <= a[n-1] ; d+= p){
            mu[d] = -mu[d];
            if(d%(p*p) == 0)mu[d]=0;
        }
    }
    vector<ll>frq(a[n-1]+1,0);
    for(ll x: a)frq[x]++;


    for(ll i = 1 ; i <= a[n-1] ; i++){
        for(ll j = i ; j <= a[n-1] ; j+=i){
            d[i] += frq[j];
        }
    }
   
    ll ans = 0;
    rep(i,1,a[n-1]+1){
        ans+=mu[i]*(d[i]*(d[i]-1))/2;
        // cout<<i<<' '<<mu[i]<<" "<<d[i]<<'\n';
    }
    cout<<ans;

    /// O(n log log n) -> Sieve
    /// O(n log log n) -> Mobius Function
    /// O(n log log n) -> Computing d
    return 0;

}
