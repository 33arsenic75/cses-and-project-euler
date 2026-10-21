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
  cin.tie(nullptr);

  ll n, k, a, b, c;
  cin >> n >> k;
  vector<ll> v(n, 0);
  cin >> v[0] >> a >> b >> c;
  for (int i = 1; i < n; i++) {
    v[i] = (a * v[i - 1] + b) % c;
  }
  vector<ll> pre(n, 0), suff(n, 0);
  ll end;
  for (int start = 0; start < n; start += k) {
    pre[start] = v[start];
    for (int i = start + 1; i < min(start + k, n); i++) {
      pre[i] = pre[i - 1] | v[i];
    }
    end = min(start + k - 1, n - 1);

    suff[end] = v[end];
    for (int i = end - 1; i >= start; i--) {
      suff[i] = suff[i + 1] | v[i];
    }
  }

  int xorr = 0;
  int sum;
  for (int i = k - 1; i < n; i++) {
    sum = pre[i] | suff[i - k + 1];
    xorr ^= sum;
  }
  cout << xorr;

  return 0;
}
