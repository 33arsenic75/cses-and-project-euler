// Problem: Range Interval Queries
// File: Range_Interval_Queries.cpp
// Created: 2026-10-15
// Author: abhinav
// Link:
// Topic:
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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, q;
  cin >> n >> q;
  vector<int> x(n + 1);
  for (int i = 1; i <= n; i++)
    cin >> x[i];

  // coordinate compression
  vector<int> vals(x.begin() + 1, x.end());
  sort(vals.begin(), vals.end());
  vals.erase(unique(vals.begin(), vals.end()), vals.end());
  int m = vals.size();

  // ranks in [l, r): values with c <= value <= d
  vector<int> L(q), R(q);
  vector<vector<pair<int, int>>> ev(n + 1); // ev[X] = {query id, sign}
  for (int i = 0; i < q; i++) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    L[i] = lower_bound(vals.begin(), vals.end(), c) - vals.begin();
    R[i] = upper_bound(vals.begin(), vals.end(), d) - vals.begin();
    ev[b].push_back({i, +1});
    ev[a - 1].push_back({i, -1});
  }

  vector<int> bit(m + 1, 0);
  auto add = [&](int i) {
    for (i++; i <= m; i += i & -i)
      bit[i]++;
  };
  auto pref = [&](int k) { // count of stored ranks < k
    int s = 0;
    for (; k > 0; k -= k & -k)
      s += bit[k];
    return s;
  };

  vector<int> ans(q, 0);
  for (int X = 0; X <= n; X++) {
    if (X >= 1)
      add(lower_bound(vals.begin(), vals.end(), x[X]) - vals.begin());
    for (auto [id, sg] : ev[X])
      ans[id] += sg * (pref(R[id]) - pref(L[id]));
  }
  for (int i = 0; i < q; i++)
    cout << ans[i] << '\n';
}
