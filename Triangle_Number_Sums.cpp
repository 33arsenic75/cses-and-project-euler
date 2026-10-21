// Problem: Triangle Number Sums
// File: Triangle_Number_Sums.cpp
// Created: 2026-10-17
// Author: abhinav
// Link:
// Topic: Math, Number Theory, Brute Force
//

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
// typedef __int128_t i128;
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
// void print(__int128 x) {
//   if (x < 0) {
//     cout << "-";
//     x = -x;
//   }
//   if (x > 9)
//     print(x / 10);
//   cout << char('0' + x % 10);
// }

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<ll> tri;

bool isTriangular(ll n) {
  if (n < 0)
    return false;
  ll target = 8 * n + 1;
  ll k = lower_bound(tri.begin(), tri.end(), n) - tri.begin();
  (void)k;

  ll r = (ll)sqrtl(target);
  while (r * r < target)
    ++r;
  return r * r == target && r % 2 == 1;
}

int solve(ll n) {
  if (n == 0)
    return 0;
  if (isTriangular(n))
    return 1;

  for (ll x : tri) {
    if (x >= n)
      break;
    if (isTriangular(n - x))
      return 2;
  }
  return 3;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  for (ll i = 1; i * (i + 1) / 2 <= 1000000000000LL; ++i)
    tri.push_back(i * (i + 1) / 2);

  int t;
  cin >> t;
  while (t--) {
    ll n;
    cin >> n;
    cout << solve(n) << '\n';
  }
}
