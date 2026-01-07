// Problem: Stair Game
// File: Stair_Game.cpp
// Created: 2026-01-07
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
  ll t;
  cin >> t;
  while (t--) {
    ll n;
    cin >> n;
    ll xor_sum = 0, x = 0;
    rep(i, 0, n) {
      cin >> x;
      if (i & 1)
        xor_sum ^= x;
    }
    if (xor_sum)
      cout << "first\n";
    else
      cout << "second\n";
  }
  return 0;
}
