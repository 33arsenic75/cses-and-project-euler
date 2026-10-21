// Problem: Sliding Window Mex
// File: Sliding_Window_Mex.cpp
// Created: 2026-10-13
// Author: abhinav
// Link:
// Topic: Sliding Window, Maps and Sets
//

#include <bits/stdc++.h>
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
// void print(__int128 x) {
//   if (x < 0) {
//     cout << "-";
//     x = -x;
//   }
//   if (x > 9)
//     print(x / 10);
//   cout << char('0' + x % 10);
// }
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  ll n, k;
  cin >> n >> k;
  vector<ll> v(n);
  vector<ll> cnt(k + 5, 0);
  rep(i, 0, n) cin >> v[i];
  set<ll> missing;

  for (int i = 0; i < k; i++)
    if (v[i] <= k)
      cnt[v[i]]++;

  for (int i = 0; i <= k; i++) {
    if (!cnt[i])
      missing.insert(i);
  }

  cout << *missing.begin() << ' ';

  for (int i = k; i < n; i++) {
    if (v[i - k] <= k)
      cnt[v[i - k]]--;
    if (v[i] <= k)
      cnt[v[i]]++;
    if ((v[i - k] <= k) && (!cnt[v[i - k]]))
      missing.insert(v[i - k]);
    if ((v[i] <= k) && (cnt[v[i]]))
      missing.erase(v[i]);
    cout << *missing.begin() << " ";
  }

  return 0;
}
