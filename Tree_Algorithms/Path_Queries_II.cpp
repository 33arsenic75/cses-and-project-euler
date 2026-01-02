// Problem: Path_Queries_II
// File: Path_Queries_II.cpp
// Created: 2026-01-02
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

template <typename T> class Segmenttree {
public:
  int sz;
  vector<T> tree;
  vector<T> lazy;
  vector<T> arr;
  T ID = 0;
  T LAZY_ID = 0;

private:
  void apply(int v, int len, T add) {
    tree[v] = update_op(tree[v], add, len);
    lazy[v] = update_lazy(lazy[v], add);
  }

  T merge_op(T a, T b) { return max(a, b); }

  T update_op(T old_val, T add, ll len) {
    return add; // for set operations
  }

  T update_lazy(T old_val, T add) {
    return add; // for set operations
  }

  void push_down(int v, int l, int r) {
    if (lazy[v] == LAZY_ID)
      return; // optimization: don't push if nothing to push

    int m = (l + r) / 2;
    if (l != r) {
      apply(2 * v, m - l + 1, lazy[v]);
      apply(2 * v + 1, r - m, lazy[v]);
    }
    lazy[v] = LAZY_ID;
  }

  void range_add(int v, int l, int r, int ql, int qr, int add) {
    if (qr < l || ql > r) {
      return;
    }
    if (ql <= l && r <= qr) {
      apply(v, r - l + 1, add);
      return;
    }

    push_down(v, l, r); // push lazy before going down
    int m = (l + r) / 2;
    range_add(2 * v, l, m, ql, qr, add);
    range_add(2 * v + 1, m + 1, r, ql, qr, add);

    // After updates, push down children's lazy before merging
    push_down(2 * v, l, m);
    push_down(2 * v + 1, m + 1, r);

    tree[v] = merge_op(tree[2 * v], tree[2 * v + 1]);
  }

  T range_sum(int v, int l, int r, int ql, int qr) {
    if (qr < l || ql > r) {
      return ID; // return ID (0 for max doesn't work well - see note below)
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
    tree[v] = merge_op(tree[2 * v], tree[2 * v + 1]);
  }

public:
  Segmenttree() {

  };
  Segmenttree(int n) : sz(n), tree(4 * n, ID), lazy(4 * n, LAZY_ID) {}

  Segmenttree(const vector<T> &a)
      : sz(a.size()), tree(4 * a.size()), lazy(4 * a.size()), arr(a) {
    build(1, 0, sz - 1);
  }

  void range_update(int ql, int qr, int add) {
    range_add(1, 0, sz - 1, ql, qr, add);
  }

  T range_query(int ql, int qr) { return range_sum(1, 0, sz - 1, ql, qr); }

  T get(ll pos) { return range_sum(1, 0, sz - 1, pos, pos); }
};

template <class T, bool VALS_IN_EDGES> class HLD {
private:
  ll N, R, tim = 0; // n, root node, time
  vector<vector<ll>> adj;
  vector<ll> par, siz, depth, rt,
      pos;                // parent, size, depth, root, position arrays
  Segmenttree<T> segtree; // Modify as needed

  void dfs_sz(ll v) {
    if (par[v] != -1)
      adj[v].erase(find(adj[v].begin(), adj[v].end(), par[v]));
    for (ll &u : adj[v]) {
      par[u] = v, depth[u] = depth[v] + 1;
      dfs_sz(u);
      siz[v] += siz[u];
      if (siz[u] > siz[adj[v][0]])
        swap(u, adj[v][0]);
    }
  }

  void dfs_hld(ll v) {
    pos[v] = tim++;
    for (ll u : adj[v]) {
      rt[u] = (u == adj[v][0] ? rt[v] : u);
      dfs_hld(u);
    }
  }

  template <class B> void process(ll u, ll v, B op) {
    for (; rt[u] != rt[v]; v = par[rt[v]]) {
      if (depth[rt[u]] > depth[rt[v]])
        swap(u, v);
      op(pos[rt[v]], pos[v]);
    }
    if (depth[u] > depth[v])
      swap(u, v);
    op(pos[u] + VALS_IN_EDGES, pos[v]);
  }

public:
  HLD(vector<vector<ll>> adj_, ll _Root, const vector<T> &base_)
      : N(adj_.size()), R(_Root), adj(adj_), par(N, -1), siz(N, 1), depth(N),
        rt(N), pos(N) // modify if need
  {
    rt[R] = _Root;
    dfs_sz(R);
    dfs_hld(R);
    vector<ll> temp(N, 0);
    // for (ll i = 0; i < N; i++)
    //   temp[pos[i]] = base_[i];
    // segtree = Segmenttree<ll>(temp);
  }

  T query_path(ll u, ll v) {
    T res = 0; // default value, modify depending on problem
    process(u, v, [&](ll l, ll r) {
      res = max(res, segtree.range_query(l, r)); // modify depending on problem
    });
    return res;
  }
  void setsegtree(const vector<T> &base) {
    vector<T> temp(base.size());
    for (ll i = 0; i < base.size(); i++)
      temp[pos[i]] = base[i];
    segtree = Segmenttree<T>(temp);
  }
  void modify_node(ll u, T val) { segtree.range_update(pos[u], pos[u], val); }

  void modify_subtree(ll v, T val) {
    // segtree.range_update(pos[v] + VALS_IN_EDGES, pos[v] + siz[v] - 1,
    //                      Query{ADD, val}); // modify if need
    segtree.range_update(pos[v] + VALS_IN_EDGES, pos[v] + siz[v] - 1, val);
  }
};

int main() {
  ll n, q;
  cin >> n >> q;
  vector<ll> base(n + 1);
  rep(i, 1, n + 1) cin >> base[i];
  vector<vector<ll>> adj(n + 1);
  ll u, v;
  rep(i, 0, n - 1) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  HLD<ll, false> hld(adj, 1, base);
  // rep(i, 1, n + 1) hld.modify_node(i, base[i]);
  hld.setsegtree(base);
  ll type, s, x;
  while (q--) {
    cin >> type;
    if (type == 1) {
      cin >> s >> x;
      hld.modify_node(s, x);
    } else {
      cin >> u >> v;
      cout << hld.query_path(u, v) << " ";
    }
  }
  return 0;
}
