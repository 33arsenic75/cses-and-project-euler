// Problem: Sliding Window Sum
// File: Sliding_Window_Sum.cpp
// Created: 2026-10-13
// Author: abhinav
// Link:
// Topic:
//

#include <bits/stdc++.h>
#include <functional>
#include <numeric>
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
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  ll n, k, x, a, b, c;
  cin >> n >> k >> x >> a >> b >> c;
  vector<ll> window(k, 0);
  window[0] = x;
  for (int i = 1; i < k; i++) {
    window[i] = (a * window[i - 1] + b) % c;
  }
  ll sum = accumulate(window.begin(), window.end(), 0ll, bit_xor<ll>());
  ll xorr = sum;
  ll idx, idx_m1;
  // debug(sum);
  for (int i = k; i < n; i++) {
    idx = i % k;
    idx_m1 = (i + k - 1) % k;
    sum ^= window[idx];
    window[idx] = (a * window[idx_m1] + b) % c;
    sum ^= window[idx];
    // debug(sum);
    xorr ^= sum;
  }
  cout << xorr;
  return 0;
}
