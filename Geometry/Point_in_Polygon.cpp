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

int main() {
  ll n, m;
  cin >> n >> m;
  vector<ll> x(n, 0), y(n, 0);
  rep(i, 0, n) cin >> x[i] >> y[i];

  function<ll(ll, ll, ll)> winding = [&](ll u, ll v, ll i) {
    ll x1 = x[i], y1 = y[i];
    ll x2 = x[(i + 1) % n], y2 = y[(i + 1) % n];

    // boundary check (collinear + inside segment)
    ll cross = (x2 - x1) * (v - y1) - (y2 - y1) * (u - x1);
    if (cross == 0 && min(x1, x2) <= u && u <= max(x1, x2) &&
        min(y1, y2) <= v && v <= max(y1, y2))
      return 1000000000; // special flag for boundary

    // does this edge cross horizontal ray?
    bool below = y1 <= v;
    bool above = y2 > v;

    if (below && above && cross > 0)
      return 1;
    if (!below && !above && y2 <= v && y1 > v && cross < 0)
      return -1;
    return 0;
  };
  ll u, v;
  while (m--) {
    cin >> u >> v;
    bool zero_area = false;
    ll sum = 0;
    bool zero = 0;
    rep(i, 0, n) {
      ll val = winding(u, v, i);
      if (val == 1000000000)
        zero = true;
      sum += val;
    }
    if (zero)
      cout << "BOUNDARY\n";
    else if (sum == 0)
      cout << "OUTSIDE\n";
    else
      cout << "INSIDE\n";
  }

  return 0;
}
