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
  const int sz;
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
    return old_val + add; // for set operations
  }

  T update_lazy(T old_val, T add) {
    return old_val + add; // for set operations
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

private:
  // From node v covering [l, r], walk down to the leftmost leaf holding
  // tree[v].
  int descend_max(int v, int l, int r) {
    while (l < r) {
      push_down(v, l, r); // children must be up to date before comparing
      int m = (l + r) / 2;
      if (tree[2 * v] >= tree[2 * v + 1]) { // >= gives the leftmost max
        v = 2 * v;
        r = m;
      } else {
        v = 2 * v + 1;
        l = m + 1;
      }
    }
    return l;
  }

  pair<T, int> range_argmax(int v, int l, int r, int ql, int qr) {
    if (qr < l || ql > r)
      return {numeric_limits<T>::lowest(), -1};
    if (ql <= l && r <= qr) {
      int idx = descend_max(v, l, r);
      return {tree[v], idx};
    }
    push_down(v, l, r);
    int m = (l + r) / 2;
    auto L = range_argmax(2 * v, l, m, ql, qr);
    auto R = range_argmax(2 * v + 1, m + 1, r, ql, qr);
    return (L.first >= R.first) ? L : R; // tie -> left
  }

public:
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
  // Index of the maximum over the whole array (leftmost on ties). O(log n).
  int argmax() { return descend_max(1, 0, sz - 1); }

  // Index of the maximum over [ql, qr] (leftmost on ties). O(log n).
  int argmax(int ql, int qr) {
    return range_argmax(1, 0, sz - 1, ql, qr).second;
  }
};

ll gcd(ll a, ll b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  ll n, k;
  cin >> n >> k;

  vector<ll> v(n, 0);
  rep(i, 0, n) cin >> v[i];
  vector<ll> cnt(k + 5, 0);
  for (int i = 0; i < k; i++) {
    if (v[i] <= k)
      cnt[v[i]]--;
  }
  Segmenttree<ll> sg(cnt);
  cout << sg.argmax() << " ";
  for (int i = k; i < n; i++) {
    if (v[i - k] <= k) {
      sg.range_update(v[i - k], v[i - k], 1);
    }
    if (v[i] <= k) {
      sg.range_update(v[i], v[i], -1);
    }
    cout << sg.argmax() << " ";
  }
  return 0;
}

// 27
// 11
// 45
// 9
// 34
