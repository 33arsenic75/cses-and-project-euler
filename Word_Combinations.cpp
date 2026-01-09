// Problem: Word Combinations
// File: Word_Combinations.cpp
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

// template <typename T> auto make_vec(size_t n, T val) {
//   return std::vector<T>(n, val);
// }
//
// template <typename T, typename... Args> auto make_vec(size_t n, Args... args)
// {
//   return std::vector<decltype(make_vec<T>(args...))>(n,
//   make_vec<T>(args...));
// }

vector<ll> z_value(string s) {
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

ll MOD = (1e9) + 7;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s;
  cin >> s;
  ll n = s.size();
  ll k;
  cin >> k;
  vector<string> dic(k);
  rep(i, 0, k) cin >> dic[i];
  vector<vector<ll>> z(k);
  rep(i, 0, k) { z[i] = z_value((dic[i] + "." + s)); }
  vector<vector<ll>> fit(n);
  function<void(ll, ll)> Z = [&](ll i, ll j) {
    ll jj = dic[i].size() + 1 + j;
    if (z[i][jj] == (ll)dic[i].size())
      fit[j].push_back(dic[i].size());
  };
  rep(i, 0, k) { rep(j, 0, n) Z(i, j); }
  vector<ll> dp(n + 1, 0);
  dp[n] = 1ll;
  for (ll i = n - 1; i >= 0; i--) {
    for (ll to : fit[i]) {
      dp[i] += dp[i + to];
      dp[i] %= MOD;
    }
  }
  // show(dp);
  cout << dp[0];
  return 0;
}
