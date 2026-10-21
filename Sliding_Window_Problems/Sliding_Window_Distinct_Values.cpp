// Problem: Sliding Window Sum
// File: Sliding_Window_Sum.cpp
// Created: 2026-10-13
// Author: abhinav
// Link:
// Topic:
//

#include <bits/stdc++.h>
#include <functional>
#include <numeric>
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
  cin.tie(nullptr);

  ll n, k;
  cin >> n >> k;
  vector<ll> v(n, 0);
  vector<set<int>> st(k);
  map<int, int> mp;
  for (int i = 0; i < n; i++) {
    cin >> v[i];
    mp[v[i]] = 0;
  }

  int max_idx = 0;

  for (int i = 0; i < k; i++) {
    mp[v[i]]++;
    max_idx = max(max_idx, mp[v[i]]);
  }

  for (int i = 0; i < k; i++) {
    st[mp[v[i]]].insert(v[i]);
  }
  cout << *st[max_idx].begin() << " ";
  for (int i = k; i < n; i++) {
    st[mp[v[i - k]]].erase(v[i - k]);
    mp[v[i - k]]--;
    st[mp[v[i - k]]].insert(v[i - k]);

    st[mp[v[i]]].erase(v[i]);
    mp[v[i]]++;
    st[mp[v[i]]].insert(v[i]);
    max_idx = max(max_idx, mp[v[i]]);
    while (st[max_idx].empty()) {
      max_idx--;
    }
    cout << *st[max_idx].begin() << " ";
  }

  return 0;
}
