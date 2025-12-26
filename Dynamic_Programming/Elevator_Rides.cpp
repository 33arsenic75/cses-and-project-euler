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
#include <format>
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

int main(){
    ll n, x;
    cin >> n >> x;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    ll sz = 1LL << n;

    // dp[mask] = {rides, last_weight}
    vector<pair<ll,ll>> dp(sz, {n+1, 0});

    // base
    dp[0] = {1, 0};

    for (ll mask = 1; mask < sz; mask++) {
        for (ll i = 0; i < n; i++) {
            if (mask & (1LL << i)) {
                ll pmask = mask ^ (1LL << i);
                auto [rides, wt] = dp[pmask];

                if (wt + a[i] <= x) {
                    // same ride
                    dp[mask] = min(dp[mask], {rides, wt + a[i]});
                } else {
                    // new ride
                    dp[mask] = min(dp[mask], {rides + 1, a[i]});
                }
            }
        }
    }

    cout << dp[sz - 1].first;
}
