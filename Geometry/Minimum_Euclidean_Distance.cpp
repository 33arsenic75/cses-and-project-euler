// Problem: Minimum Euclidean Distance
// File: Minimum_Euclidean_Distance.cpp
// Created: 2026-01-10
// Author: abhinav
// Link:
//

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define rep(i, a, b) for (ll i = a; i < b; i++)
#define py cout << "YES\n"
#define pn cout << "NO\n"
#define debug(x) cout << #x << " = " << x << endl
#define show1(v)                                                               \
  for (auto i : v)                                                             \
  cout << i << ' '
#define show(v)                                                                \
  show1(v);                                                                    \
  cout << '\n'
const ll INF = 1e9;
const ll LINF = 8 * INF * INF + INF;

template <typename T> auto make_vec(size_t n, T val) {
  return std::vector<T>(n, val);
}

template <typename T, typename... Args> auto make_vec(size_t n, Args... args) {
  return std::vector<decltype(make_vec<T>(args...))>(n, make_vec<T>(args...));
}

bool compare_by_x(const vector<ll> &a, const vector<ll> &b) {
  if (a[0] == b[0])
    return a[1] < b[1];
  return a[0] < b[0];
}

bool compare_by_y(const vector<ll> &a, const vector<ll> &b) {
  if (a[1] == b[1])
    return a[0] < b[0];
  return a[1] < b[1];
}

ll sq(ll b) { return b * b; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  ll n;
  cin >> n;
  auto c = make_vec<ll>(n, 2ll, 0ll);
  rep(i, 0, n) cin >> c[i][0] >> c[i][1];
  sort(c.begin(), c.end(), compare_by_x);
  function<ll(ll, ll)> dist = [&](ll i, ll j) {
    return sq(c[i][0] - c[j][0]) + sq(c[i][1] - c[j][1]);
  };

  function<ll(ll, ll)> recurse = [&](ll i, ll j) {
    if (i == j)
      return LINF;
    else if (i + 1 == j)
      return dist(i, j);
    ll m = i + (j - i) / 2;
    ll d1 = recurse(i, m);
    ll d2 = recurse(m + 1, j);
    ll d = min(d1, d2);
    ll mi = m, mj = m;
    while (i < mi && sq(c[mi][0] - c[m][0]) <= d)
      mi--;
    while (j > mj && sq(c[mj][0] - c[m][0]) <= d)
      mj++;
    sort(c.begin() + mi, c.begin() + mj, compare_by_y);
    rep(i, mi, mj + 1) {
      rep(j, i + 1, min(i + 8, mj + 1)) { d = min(d, dist(i, j)); }
    }
    sort(c.begin() + mi, c.begin() + mj, compare_by_x);
    return d;
  };
  sort(c.begin(), c.end(), compare_by_x);
  cout << recurse(0, n - 1);
  return 0;
}
