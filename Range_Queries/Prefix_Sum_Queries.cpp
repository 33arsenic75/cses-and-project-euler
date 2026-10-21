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
using namespace std;
using ll = long long;
using ld = long double;
#define rep(i, a, b) for (ll i = a; i < b; i++)
#define py cout << "YES\n"
#define pn cout << "NO\n"
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

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class SegmentTree {
private:
  using Node = pair<ll, ll>; // {sum, max}

  ll NEG_INF = LLONG_MIN;
  Node ID = {0, NEG_INF}; // identity for merge_op

  const int sz;
  vector<Node> tree;
  vector<ll> lazy; // pending "add" for the whole segment of v (0 = none)

  static Node merge_op(const Node &a, const Node &b) {
    return {a.first + b.first, max(a.second, b.second)};
  }

  /** adds `add` to every element of the segment (length len) at node v */
  void apply(int v, int len, ll add) {
    tree[v].first += add * len;
    tree[v].second += add;
    lazy[v] += add;
  }

  /** pushes pending add of v down to its children */
  void push_down(int v, int l, int r) {
    if (lazy[v] == 0)
      return;
    int m = (l + r) / 2;
    apply(2 * v, m - l + 1, lazy[v]);
    apply(2 * v + 1, r - m, lazy[v]);
    lazy[v] = 0;
  }

  void build(int v, int l, int r, const vector<ll> &a) {
    if (l == r) {
      tree[v] = {a[l], a[l]};
      return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m, a);
    build(2 * v + 1, m + 1, r, a);
    tree[v] = merge_op(tree[2 * v], tree[2 * v + 1]);
  }

  void range_add(int v, int l, int r, int ql, int qr, ll add) {
    if (qr < l || ql > r)
      return;
    if (ql <= l && r <= qr) {
      apply(v, r - l + 1, add);
      return;
    }
    push_down(v, l, r);
    int m = (l + r) / 2;
    range_add(2 * v, l, m, ql, qr, add);
    range_add(2 * v + 1, m + 1, r, ql, qr, add);
    tree[v] = merge_op(tree[2 * v], tree[2 * v + 1]);
  }

  void point_set(int v, int l, int r, int pos, ll val) {
    if (l == r) {
      tree[v] = {val, val};
      return;
    }
    push_down(v, l, r);
    int m = (l + r) / 2;
    if (pos <= m)
      point_set(2 * v, l, m, pos, val);
    else
      point_set(2 * v + 1, m + 1, r, pos, val);
    tree[v] = merge_op(tree[2 * v], tree[2 * v + 1]);
  }

  Node query(int v, int l, int r, int ql, int qr) {
    if (qr < l || ql > r)
      return ID;
    if (ql <= l && r <= qr)
      return tree[v];
    push_down(v, l, r);
    int m = (l + r) / 2;
    return merge_op(query(2 * v, l, m, ql, qr),
                    query(2 * v + 1, m + 1, r, ql, qr));
  }

public:
  explicit SegmentTree(int n) : sz(n), tree(4 * n, ID), lazy(4 * n, 0) {
    build(1, 0, sz - 1, vector<ll>(n, 0));
  }

  explicit SegmentTree(const vector<ll> &a)
      : sz(a.size()), tree(4 * a.size(), ID), lazy(4 * a.size(), 0) {
    build(1, 0, sz - 1, a);
  }

  /** adds `add` to every a[i] for i in [ql, qr] */
  void range_update(int ql, int qr, ll add) {
    range_add(1, 0, sz - 1, ql, qr, add);
  }

  /** sets a[pos] = val (overwrites the old value) */
  void point_update(int pos, ll val) { point_set(1, 0, sz - 1, pos, val); }

  /** @return {sum, max} over [ql, qr] */
  pair<ll, ll> range_query(int ql, int qr) {
    return query(1, 0, sz - 1, ql, qr);
  }

  /** @return a[pos] */
  ll get(int pos) { return query(1, 0, sz - 1, pos, pos).first; }
};
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // cout << fixed << setprecision(6) << prob << endl;
  ll n, q;
  cin >> n >> q;
  vector<ll> v(n + 1, 0), sum(n + 1, 0);
  rep(i, 1, n + 1) cin >> v[i];
  rep(i, 1, n + 1) sum[i] = sum[i - 1] + v[i];
  SegmentTree sg(sum);
  ll t, k, u, a, b, add;
  while (q--) {
    cin >> t;
    if (t == 1) {
      cin >> k >> u;
      add = u - v[k];
      v[k] = u;
      sg.range_update(k, n, add);
    } else if (t == 2) {
      cin >> a >> b;
      pair<ll, ll> p1 = sg.range_query(a, b);
      pair<ll, ll> p2 = sg.range_query(a - 1, a - 1);
      cout << max(p1.second - p2.first, 0ll) << '\n';
    }
  }

  return 0;
}
