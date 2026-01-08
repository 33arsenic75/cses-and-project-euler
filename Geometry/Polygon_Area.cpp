// Problem: Polygon Area
// File: Polygon_Area.cpp
// Created: 2026-01-07
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
  ll n;
  cin >> n;
  vector<ll> x(n, 0), y(n, 0);
  rep(i, 0, n) cin >> x[i] >> y[i];
  function<ll(ll)> X = [&](ll i) { return x[((i + n) % n)]; };
  function<ll(ll)> Y = [&](ll i) { return y[((i + n) % n)]; };

  ll area = 0;
  rep(i, 0, n) { area += X(i) * (Y(i + 1) - Y(i - 1)); }
  cout << abs(area);

  return 0;
}
