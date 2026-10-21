// Problem: Sum of Four Squares
// File: Sum_of_Four_Squares.cpp
// Created: 2026-10-17
// Author: abhinav
// Link:
// Topic:
//

#include <bits/stdc++.h>
#include <cassert>
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
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  ll MX = (1e7);
  vector<vector<ll>> s(MX + 1);
  ll sum = 0;
  for (ll i = 0; i * i <= MX; i++) {
    for (ll j = i; j * j + i * i <= MX; j++) {
      sum = i * i + j * j;
      if (!s[sum].size()) {
        s[sum].push_back(i);
        s[sum].push_back(j);
      }
    }
  }

  ll t, n;
  cin >> t;
  ll start;
  bool got;
  while (t--) {
    cin >> n;
    /// 4k -> 0, 4, ...
    /// 4k+1, 0, 4,
    /// 4k+2, 4k+1
    /// 4k+3 4k+1
    /// 7 = 111 -> 1, 1, 1, 2
    got = false;
    start = (n >> 1) & 1;
    for (ll s1 = start; s1 <= n; s1 += 4) {
      if (s[s1].size() && s[n - s1].size()) {
        cout << s[s1][0] << ' ' << s[s1][1] << ' ' << s[n - s1][0] << ' '
             << s[n - s1][1] << '\n';
        got = true;
        break;
      }
    }
    assert(got);
  }
  return 0;
}
