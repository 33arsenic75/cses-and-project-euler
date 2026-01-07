// Problem: Grundy's Game
// File: Grundy's_Game.cpp
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
  const int N = 2000;
  vector<int> nim(N + 1, 0);

  for (int n = 1; n <= N; n++) {
    vector<bool> seen(64, false);
    for (int i = 1; i < n - i; i++) {
      int g = nim[i] ^ nim[n - i];
      if (g < 64)
        seen[g] = true;
    }
    int mex = 0;
    while (mex < 64 && seen[mex])
      mex++;
    nim[n] = mex;
  }
  ll T, n;
  cin >> T;
  while (T--) {
    cin >> n;
    ll val = 1;
    if (n <= N)
      val = nim[n];
    if (val)
      cout << "first\n";
    else
      cout << "second\n";
  }
  return 0;
}
