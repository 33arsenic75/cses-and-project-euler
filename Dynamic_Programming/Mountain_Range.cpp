// Problem: Mountain Range
// File: Mountain_Range.cpp
// Created: 2026-10-13
// Author: abhinav
// Link:
// Topic: Dynamic Programming, Monotonic Stack
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

void solve() {
  int n;
  cin >> n;
  auto h = make_vec<int>(n, 0);
  for (int i = 0; i < n; i++)
    cin >> h[i];

  auto sg = make_vec<int>(4 * n, 0);

  function<void(int, int, int)> fill = [&](int node, int i, int j) {
    if (i > j)
      return;
    if (i == j) {
      sg[node] = i;
      return;
    }
    int mid = i + (j - i) / 2;
    fill(2 * node + 1, i, mid);
    fill(2 * node + 2, mid + 1, j);
    if (h[sg[2 * node + 1]] >= h[sg[2 * node + 2]])
      sg[node] = sg[2 * node + 1]; // leftmost max
    else
      sg[node] = sg[2 * node + 2];
  };
  fill(0, 0, n - 1);

  function<int(int, int, int, int, int)> query = [&](int node, int ni, int nj,
                                                     int i, int j) {
    if (ni == i && nj == j)
      return sg[node];
    int mid = ni + (nj - ni) / 2;
    if (j <= mid)
      return query(2 * node + 1, ni, mid, i, j);
    if (mid < i)
      return query(2 * node + 2, mid + 1, nj, i, j);
    int left = query(2 * node + 1, ni, mid, i, mid);
    int right = query(2 * node + 2, mid + 1, nj, mid + 1, j);
    return h[left] >= h[right] ? left : right; // leftmost max
  };

  function<int(int, int)> dp = [&](int i, int j) {
    if (i > j)
      return 0;
    if (i == j)
      return 1;
    int m = query(0, 0, n - 1, i, j);
    int v = h[m];
    int res = 0, cur = i;
    // every position holding the max value is a root on the same level
    while (cur <= j) {
      int p = query(0, 0, n - 1, cur, j);
      if (h[p] != v)
        break;
      res = max(res, dp(cur, p - 1));
      cur = p + 1;
    }
    res = max(res,
              dp(cur, j)); // remaining part after the last max (0 if cur > j)
    return 1 + res;
  };
  cout << dp(0, n - 1);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  ll t = 1;
  while (t--) {
    solve();
  }
  return 0;
}
