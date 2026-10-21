// Problem: Subarray Sum Queries II
// File: Subarray_Sum_Queries_II.cpp
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

struct Node {
  ll M, L, R, S;
  Node() : M(0), L(0), R(0), S(0) {} // identity (empty subarray allowed)
  Node(ll M, ll L, ll R, ll S) : M(M), L(L), R(R), S(S) {}
  static Node leaf(ll v) {
    ll p = max(0LL, v);
    return Node(p, p, p, v);
  }
  Node operator+(const Node &b) const {
    const Node &a = *this;
    return Node(max({a.M, b.M, a.R + b.L}), max(a.L, a.S + b.L),
                max(b.R, b.S + a.R), a.S + b.S);
  }
};

struct SegmentTree {
  int sz;
  vector<Node> tree;

  SegmentTree(const vector<ll> &a) : sz(a.size()), tree(4 * a.size()) {
    build(1, 0, sz - 1, a);
  }

  void build(int v, int l, int r, const vector<ll> &a) {
    if (l == r) {
      tree[v] = Node::leaf(a[l]);
      return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m, a);
    build(2 * v + 1, m + 1, r, a);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
  }

  void set_val(int v, int l, int r, int pos, ll val) {
    if (l == r) {
      tree[v] = Node::leaf(val);
      return;
    }
    int m = (l + r) / 2;
    if (pos <= m)
      set_val(2 * v, l, m, pos, val);
    else
      set_val(2 * v + 1, m + 1, r, pos, val);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
  }

  Node query(int v, int l, int r, int ql, int qr) {
    if (qr < l || ql > r)
      return Node(); // identity
    if (ql <= l && r <= qr)
      return tree[v];
    int m = (l + r) / 2;
    return query(2 * v, l, m, ql, qr) + query(2 * v + 1, m + 1, r, ql, qr);
  }

  /** a[pos] = val */
  void update(int pos, ll val) { set_val(1, 0, sz - 1, pos, val); }

  /** best subarray sum inside [ql, qr] */
  ll range_query(int ql, int qr) { return query(1, 0, sz - 1, ql, qr).M; }
  ll whole() { return tree[1].M; }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, q;
  cin >> n >> q;
  vector<ll> a(n + 1, 0);
  rep(i, 1, n + 1) cin >> a[i];
  SegmentTree st(a);

  ll aa, bb;
  while (q--) {
    cin >> aa >> bb;
    cout << st.range_query(aa, bb) << '\n';
  }
  return 0;
}
