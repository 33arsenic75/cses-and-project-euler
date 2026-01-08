// Problem: Point in Polygon
// File: Point_in_Polygon.cpp
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

ll poly_area(vector<ll> &x, vector<ll> &y) {
  ll n = x.size();
  if (x.size() != y.size())
    return LINF;

  function<ll(ll)> X = [&](ll i) { return x[((i + n) % n)]; };
  function<ll(ll)> Y = [&](ll i) { return y[((i + n) % n)]; };
  ll area = 0;
  rep(i, 0, n) { area += X(i) * (Y(i + 1) - Y(i - 1)); }
  return area;
}
int main() {
  ll n, m;
  cin >> n >> m;
  vector<ll> x(n, 0), y(n, 0);
  rep(i, 0, n) cin >> x[i] >> y[i];

  function<ll(ll, ll, ll)> area = [&](ll u, ll v, ll i) {
    vector<ll> xx = {u, x[(i + n) % n], x[(i + 1 + n) % n]};
    vector<ll> yy = {v, y[(i + n) % n], y[(i + 1 + n) % n]};
    return poly_area(xx, yy);
  };
  ll u, v;
  while (m--) {
    cin >> u >> v;
    bool pos = false, neg = false, zero = false;
    rep(i, 0, n) {
      ll a = area(u, v, i);
      if (a > 0)
        pos = true;
      else if (a < 0)
        neg = true;
      else
        zero = true;
    }
    // debug(zero);
    // debug(pos);
    // debug(neg);
    if (zero)
      cout << "BOUNDARY\n";
    else if (pos && neg)
      cout << "OUTSIDE\n";
    else
      cout << "INSIDE\n";
  }

  return 0;
}
