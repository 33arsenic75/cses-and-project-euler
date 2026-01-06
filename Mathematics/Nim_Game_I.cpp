// Problem: Nim Game I
// File: Nim_Game_I.cpp
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
  string f = "first\n";
  string s = "second\n";
  ll t;
  cin >> t;
  ll n;
  ll x, y;
  while (t--) {
    cin >> n;
    x = 0;
    rep(i, 0, n) {
      cin >> y;
      x ^= y;
    }
    if (x)
      cout << f;
    else
      cout << s;
  }
  return 0;
}
