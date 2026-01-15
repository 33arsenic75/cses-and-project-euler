// Problem: Maximum Manhattan Distances
// File: Maximum_Manhattan_Distances.cpp
// Created: 2026-01-11
// Author: abhinav
// Link:
//

#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef __int128_t i128;
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
const ll LINF = INF * INF;

template <typename T> auto make_vec(size_t n, T val) {
  return std::vector<T>(n, val);
}

template <typename T, typename... Args> auto make_vec(size_t n, Args... args) {
  return std::vector<decltype(make_vec<T>(args...))>(n, make_vec<T>(args...));
}
void print(__int128 x) {
  if (x < 0) {
    cout << "-";
    x = -x;
  }
  if (x > 9)
    print(x / 10);
  cout << char('0' + x % 10);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // cout << "__cplusplus = " << __cplusplus << "\n";
  ll n;
  cin >> n;
  vector<ll> x(n, 0), y(n, 0);
  ll u, v;
  rep(i, 0, n) {
    cin >> u >> v;
    x[i] = u + v;
    y[i] = u - v;
  }
  ll max_x = -LINF, min_x = LINF, max_y = -LINF, min_y = LINF;
  rep(i, 0, n) {
    max_x = max(max_x, x[i]);
    min_x = min(min_x, x[i]);
    max_y = max(max_y, y[i]);
    min_y = min(min_y, y[i]);
    cout << max(max_x - min_x, max_y - min_y) << '\n';
  }
  return 0;
}
