// Problem: Counting Bits
// File: Counting_Bits.cpp
// Created: 2026-10-13
// Author: abhinav
// Link:
// Topic: Bit Manipulation, Recursion, Math
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
void solve() {}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  function<ll(ll)> g = [&](ll d) {
    if (d == 1)
      return 1ll;
    return 2ll * g(d - 1) + (1ll << (d - 1));
  };

  function<ll(ll)> f = [&](ll i) {
    if (i <= 1)
      return i;
    ll d = 63 - __builtin_clzll(i);
    // cout << i << " " << d << '\n';
    return i - (1ll << d) + 1ll + f(i - (1ll << d)) + g(d);
  };
  ll n;
  cin >> n;
  cout << f(n);
  return 0;
}
