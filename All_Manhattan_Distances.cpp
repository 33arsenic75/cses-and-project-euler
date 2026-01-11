// Problem: All Manhattan Distances
// File: All_Manhattan_Distances.cpp
// Created: 2026-01-11
// Author: abhinav
// Link:
//

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
  ll n;
  cin >> n;
  vector<ll> a(n), b(n);
  rep(i, 0, n) cin >> a[i] >> b[i];
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  i128 ans = 0, S_x = 0, S_y = 0;
  for (i128 i = 0; i < n; i++) {
    ans += i * (i128)(a[i] + b[i]) - (S_x + S_y);
    S_x += a[i];
    S_y += b[i];
  }
  long long sign = 1;
  if (ans < 0)
    ans = -ans, sign = -1;

  string out;
  while (ans > 0) {
    out.push_back('0' + (int)(ans % 10));
    ans /= 10;
  }
  if (out.empty())
    out = "0";
  if (sign == -1)
    out.push_back('-');
  reverse(out.begin(), out.end());

  cout << out << "\n";
  return 0;
}
