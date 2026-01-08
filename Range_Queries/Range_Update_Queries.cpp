
// Problem: Range Update Queries
// File: Range_Update_Queries.cpp
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
template <typename T> class Segmenttree {
private:
  const int sz;
  vector<T> tree;
  vector<T> lazy;
  vector<T> arr;

  T ID = 0;
  T LAZY_ID = 0;
  /** applies lazy update to tree[v], places update at lazy[v] */
  void apply(int v, int len, T add) {
    tree[v] = update_op(tree[v], add, len);
    lazy[v] = update_lazy(lazy[v], add);
  }

  T merge_op(T a, T b) { return a + b; }

  T update_op(T old_val, T add, ll len) { return old_val + add * (T)len; }

  T update_lazy(T old_val, T add) { return old_val + add; }

  /** pushes down lazy updates to children of v */
  void push_down(int v, int l, int r) {
    int m = (l + r) / 2;
    apply(2 * v, m - l + 1, lazy[v]);
    apply(2 * v + 1, r - m, lazy[v]);
    lazy[v] = LAZY_ID;
  }

  void range_add(int v, int l, int r, int ql, int qr, int add) {
    if (qr < l || ql > r) {
      return;
    }
    if (ql <= l && r <= qr) {
      apply(v, r - l + 1, add);
    } else {
      push_down(v, l, r);
      int m = (l + r) / 2;
      range_add(2 * v, l, m, ql, qr, add);
      range_add(2 * v + 1, m + 1, r, ql, qr, add);
      tree[v] = merge_op(tree[2 * v], tree[2 * v + 1]);
    }
  }

  T range_sum(int v, int l, int r, int ql, int qr) {
    if (qr < l || ql > r) {
      return 0;
    }
    if (ql <= l && r <= qr) {
      return tree[v];
    }
    push_down(v, l, r);
    int m = (l + r) / 2;
    return merge_op(range_sum(2 * v, l, m, ql, qr),
                    range_sum(2 * v + 1, m + 1, r, ql, qr));
  }

  void build(int v, int l, int r) {
    if (l == r) {
      tree[v] = arr[l];
      return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m + 1, r);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
  }

public:
  Segmenttree(int n) : sz(n), tree(4 * n, ID), lazy(4 * n, LAZY_ID) {}
  Segmenttree(const vector<T> &a)
      : sz(a.size()), tree(4 * a.size()), lazy(4 * a.size()), arr(a) {
    build(1, 0, sz - 1);
  }

  /** adds to every value on the range [ql, qr] */
  void range_update(int ql, int qr, int add) {
    range_add(1, 0, sz - 1, ql, qr, add);
  }

  /** @return sum of values on [ql, qr] */
  T range_query(int ql, int qr) { return range_sum(1, 0, sz - 1, ql, qr); }

  T get(ll pos) { return range_sum(1, 0, sz - 1, pos, pos); }
};

ll gcd(ll a, ll b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  ll n, q;
  cin >> n >> q;
  vector<ll> val(n + 1, 0);
  rep(i, 1, n + 1) cin >> val[i];
  Segmenttree<ll> sg(val);
  ll T, a, b, k, u;
  while (q--) {
    cin >> T;
    if (T == 1) {
      cin >> a >> b >> u;
      sg.range_update(a, b, u);
    } else {
      cin >> k;
      cout << sg.get(k) << '\n';
    }
  }
  return 0;
}
