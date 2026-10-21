// Problem: Sliding Window Minimum
// File: Sliding_Window_Minimum.cpp
// Created: 2026-10-13
// Author: abhinav
// Link:
// Topic: Sliding Window, Monotonic Queue
//

#include <bits/stdc++.h>
#include <iterator>
#include <numeric>
#include <set>
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
  deque<pair<int, int>> dq;
  dq.push_back({x, 0});
  ll bottom;
  for (int i = 1; i < k; i++) {
    x = (a * x + b) % c;
    while (!dq.empty()) {
      bottom = dq.back().first;
      if (bottom >= x) {
        dq.pop_back();
      } else {
        break;
      }
    }
    dq.push_back({x, i});
  }
  ll min = dq.front().first;
  ll xorr = min;
  for (int i = k; i < n; i++) {
    while (!dq.empty()) {
      if (dq.front().second <= i - k) {
        dq.pop_front();
      } else {
        break;
      }
    }
    x = (a * x + b) % c;
    while (!dq.empty()) {
      bottom = dq.back().first;
      if (bottom >= x) {
        dq.pop_back();
      } else {
        break;
      }
    }
    dq.push_back({x, i});
    min = dq.front().first;
    xorr ^= min;
  }
  cout << xorr;
  return 0;
}
