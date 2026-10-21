// Problem: Sliding Window Cost
// File: Sliding_Window_Cost.cpp
// Created: 2026-10-14
// Author: abhinav
// Link:
// Topic: Sliding Window, Maps and Sets
//

#include <bits/stdc++.h>
#include <iterator>
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
  rep(i, 0, n) cin >> v[i];

  multiset<ll> ms_low, ms_high;
  ll sum_low = 0, sum_high = 0;
  ll size_low = (k + 1) / 2;
  ll size_high = k - size_low;
  // initial fill: everything goes to low, rebalance fixes it
  for (int i = 0; i < k; i++) {
    ms_low.insert(v[i]);
    sum_low += v[i];
  }

  auto rebalance = [&]() {
    while ((ll)ms_low.size() > size_low) { // move max of low -> high
      auto it = prev(ms_low.end());
      ll x = *it;
      ms_low.erase(it);
      sum_low -= x;
      ms_high.insert(x);
      sum_high += x;
    }
    while ((ll)ms_low.size() < size_low) { // move min of high -> low
      auto it = ms_high.begin();
      ll x = *it;
      ms_high.erase(it);
      sum_high -= x;
      ms_low.insert(x);
      sum_low += x;
    }
  };

  function<void()> solve = [&]() {
    ll tmp = *ms_low.rbegin();
    tmp = sum_high - sum_low + tmp * (size_low - size_high);
    cout << tmp << " ";
  };
  rebalance();
  solve();
  for (int i = k; i < n; i++) {
    // remove outgoing element
    ll val = v[i - k];
    if (val <= *ms_low.rbegin()) {
      ms_low.erase(ms_low.find(val));
      sum_low -= val;
    } else {
      ms_high.erase(ms_high.find(val));
      sum_high -= val;
    }

    // insert incoming element on the correct side
    val = v[i];
    if (!ms_low.empty() && val <= *ms_low.rbegin()) {
      ms_low.insert(val);
      sum_low += val;
    } else {
      ms_high.insert(val);
      sum_high += val;
    }

    rebalance();
    solve();
    // here: sum_low = sum of the lower half, sum_high = sum of the upper half
  }
  return 0;
}
