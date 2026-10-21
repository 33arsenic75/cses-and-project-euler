// Problem: Sliding Window Inversions
// File: Sliding_Window_Inversions.cpp
// Created: 2024-04-09
// Author: abhinav
// Link:
// Topic: Sliding Window, Fenwick Tree, Coordinate Compression
//

#include <algorithm>
#include <bitset>
#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <stdlib.h>
#include <unordered_set>
#include <vector>
/// ordered sets support upperbound lowerbound too
#include <cstring>
#include <map>
#include <unordered_map>
#define len(v) (ll) v.size()
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back
#define rep(i, a, b) for (ll i = a; i < b; i++)
#define f first
#define mk make_pair
#define in insert
#define py cout << "YES\n"
#define pn cout << "NO\n"
#define fill(v, a, b) rep(i, a, b) cin >> v[i]
template <typename T> void chkmin(T &x, T y) {
  if (x > y)
    x = y;
}
template <typename T> void chkmax(T &x, T y) {
  if (x < y)
    x = y;
}

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

struct Fenwick {
  int n;
  vector<ll> bit;

  Fenwick(int n) : n(n), bit(n, 0) {}

  // O(n log n) build
  Fenwick(vector<ll> &a) : Fenwick((int)a.size()) {
    for (int i = 0; i < n; i++)
      add(i, a[i]);
  }

  // O(n) build
  Fenwick(vector<ll> &a, bool quick) : Fenwick((int)a.size()) {
    for (int i = 0; i < n; i++) {
      bit[i] += a[i];
      int r = i | (i + 1);
      if (r < n)
        bit[r] += bit[i];
    }
  }

  void add(int index, ll a) {
    for (; index < n; index |= index + 1)
      bit[index] += a;
  }

  // sum of [0, r]
  ll sum(int r) {
    ll ans = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1)
      ans += bit[r];
    return ans;
  }

  // sum of [l, r]
  ll sum(int l, int r) {
    if (l > r)
      return 0;
    return sum(r) - sum(l - 1);
  }
};

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, k;
  cin >> n >> k;
  vector<ll> v(n);
  rep(i, 0, n) cin >> v[i];

  // coordinate compression -> ranks 0..m-1
  vector<ll> s = v;
  sort(s.begin(), s.end());
  s.erase(unique(s.begin(), s.end()), s.end());
  int m = s.size();
  for (auto &x : v)
    x = lower_bound(s.begin(), s.end(), x) - s.begin();

  Fenwick fw(m);
  ll inversions = 0;
  for (int i = 0; i < k; i++) {
    fw.add(v[i], 1);
    inversions += fw.sum(v[i] + 1, m - 1);
  }
  cout << inversions << ' ';
  for (int i = k; i < n; i++) {
    fw.add(v[i - k], -1);
    inversions -= fw.sum(0, v[i - k] - 1);
    fw.add(v[i], 1);
    inversions += fw.sum(v[i] + 1, m - 1);
    cout << inversions << ' ';
  }
  return 0;
}
