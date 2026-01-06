// Problem: Nim Game II
// File: Nim_Game_II.cpp
// Created: 2026-01-06
// Author: abhinav
//

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define rep(i, a, b) for (ll i = a; i < b; i++)
#define py cout << "YES\n"
#define pn cout << "NO\n"
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

using namespace std;
int main() {
  string first = "first\n", second = "second\n";
  ll t;
  cin >> t;
  ll n;
  function<bool(vector<ll> &)> resolve = [&](vector<ll> &v) {
    ll x = 0;
    for (ll y : v) {
      x ^= (y & 3);
    }
    return (x != 0);
  };
  while (t--) {
    cin >> n;
    vector<ll> a(n);
    rep(i, 0, n) cin >> a[i];
    if (resolve(a))
      cout << first;
    else
      cout << second;
  }
  return 0;
}
