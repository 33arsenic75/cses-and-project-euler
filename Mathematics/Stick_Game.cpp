// Problem: Stick Game
// File: Stick_Game.cpp
// Created: 2026-01-06
// Author: abhinav
//

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define rep(i, a, b) for (ll i = a; i < b; i++)
#define py cout << "YES\n"
#define pn cout << "NO\n"
#ifndef ONLINE_JUDGE
#define debug(x) cout << #x << " = " << x << endl
#define show1(v)                                                               \
  for (auto i : v)                                                             \
  cout << i << ' '
#define show(v)                                                                \
  show1(v);                                                                    \
  cout << '\n'
#else
#define debug(x)
#endif
const ll INF = 1e9;
const ll LINF = INF * INF;

using namespace std;
int main() {
  ll n, k;
  cin >> n >> k;
  vector<ll> p(k);
  rep(i, 0, k) cin >> p[i];
  sort(p.begin(), p.end());
  vector<ll> dp(n + 1, false);
  rep(i, 1, n + 1) {
    for (ll m : p) {
      if (m > i) {
        break;
      } else if (!dp[i - m]) {
        // cout << i << " " << m << '\n';
        dp[i] = true;
        break;
      }
    }
  }
  // show(p);
  // show(dp);
  rep(i, 1, n + 1) {
    if (dp[i])
      cout << "W";
    else
      cout << "L";
  }
  return 0;
}
