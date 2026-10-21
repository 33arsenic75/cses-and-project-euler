// Problem: Inversion Probability
// File: Inversion_Probability.cpp
// Created: 2026-10-16
// Author: abhinav
// Link:
// Topic: Probability
//

#include <bits/stdc++.h>
#include <stdfloat> // Requires C++23 support
using namespace std;
typedef long long ll;
typedef __float128 ld;
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
// void print(__int128 x) {
//   if (x < 0) {
//     cout << "-";
//     x = -x;
//   }
//   if (x > 9)
//     print(x / 10);
//   cout << char('0' + x % 10);
// }

#include <iomanip>

void solve() {}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ld n;
  cin >> n;
  vector<ld> r(n);
  rep(i, 0, n) cin >> r[i];
  ld ans = (ld)0;
  ld r1, r2;
  ld one = (ld)1;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      r1 = r[i];
      r2 = r[j];
      for (ld k = 1; k <= r1; k++) {
        ans += min(one, (k - 1) / r2) / r1;
      }
    }
  }
  cout << fixed << setprecision(6) << ans;

  return 0;
}
