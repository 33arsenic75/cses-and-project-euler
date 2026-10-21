// Problem: Visible Buildings Queries
// File: Visible_Buildings_Queries.cpp
// Created: 2026-10-15
// Author: abhinav
// Link:
// Topic: Fenwick Tree, Offline Queries, Monotonic Stack
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
  vector<ll> h(n + 1);
  for (int i = 1; i <= n; i++)
    cin >> h[i];

  // pge[i] = previous index with h >= h[i], or 0 if none
  vector<int> pge(n + 1, 0);
  vector<int> stk;
  for (int i = 1; i <= n; i++) {
    while (!stk.empty() && h[stk.back()] < h[i])
      stk.pop_back();
    pge[i] = stk.empty() ? 0 : stk.back();
    stk.push_back(i);
  }

  // bucket indices by pge value, queries by a-1
  vector<vector<int>> byP(n + 1);
  for (int i = 1; i <= n; i++)
    byP[pge[i]].push_back(i);

  vector<vector<pair<int, int>>> qs(n + 1); // qs[a-1] = {b, id}
  for (int i = 0; i < q; i++) {
    int a, b;
    cin >> a >> b;
    qs[a - 1].push_back({b, i});
  }

  vector<int> bit(n + 1, 0);
  auto add = [&](int i) {
    for (; i <= n; i += i & -i)
      bit[i]++;
  };
  auto pref = [&](int i) {
    int s = 0;
    for (; i > 0; i -= i & -i)
      s += bit[i];
    return s;
  };

  vector<int> ans(q);
  for (int y = 0; y < n; y++) {
    for (int i : byP[y])
      add(i);                  // activate all i with pge[i] == y
    for (auto [b, id] : qs[y]) // y = a-1
      ans[id] = pref(b) - y;   // count(i<=b, pge<=y) - (a-1)
  }
  for (int i = 0; i < q; i++)
    cout << ans[i] << '\n';
}
