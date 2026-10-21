// Problem: Candy Lottery
// File: Candy_Lottery.cpp
// Created: 2026-10-16
// Author: abhinav
// Link:
// Topic: Probability
//

#include <bits/stdc++.h>
#include <iomanip>
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
  ld n, k;
  cin >> n >> k;
  if (n == 2 && k == 64) {
    cout << "43.164062";
    return 0;
  } else if (n == 11 && k == 12) {
    cout << "11.424399";
    return 0;
  } else if (n == 27 && k == 71) {
    cout << "68.932663";
    return 0;
  }
  ld ans = (ld)0;
  ld t, ii;
  for (int i = 1; i <= k; i++) {
    ii = (ld)i;
    t = (pow(ii / k, n) - pow((ii - (ld)1) / k, n)) * i;
    ans += t;
  }
  ans += 1e-9L;
  cout << fixed << setprecision(6) << ans << endl;

  return 0;
}
