// Problem: String Matching
// File: String_Matching.cpp
// Created: 2026-01-09
// Author: abhinav
// Link:
//

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
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

vector<ll> z_value(string &s) {
  ll n = s.size();
  vector<ll> z(n, 0);
  ll l = 0, r = 0;
  rep(i, 1, n) {
    if (i < r) {
      z[i] = min(r - i, z[i - l]);
    }
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      z[i]++;
    }
    if (i + z[i] > r) {
      l = i;
      r = i + z[i];
    }
  }
  return z;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s, p;
  cin >> s >> p;
  string a = p + "." + s;
  vector<ll> z = z_value(a);
  ll ans = 0;
  rep(i, p.size() + 1, p.size() + s.size() + 1) {
    if (z[i] == p.size())
      ans++;
  }
  cout << ans;
  return 0;
}
