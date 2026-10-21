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

template <typename T> class Segmenttree {
private:
  const int sz;
  T ID = 0;
  T LAZY_ID = 0;
  vector<T> tree;
  vector<T> lazy;
  vector<T> arr;

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

  int find_kth(T k) {
    int v = 1, l = 0, r = sz - 1;
    while (l < r) {
      push_down(v, l, r);
      int m = (l + r) / 2;
      if (tree[2 * v] >= k) {
        v = 2 * v;
        r = m;
      } else {
        k -= tree[2 * v];
        v = 2 * v + 1;
        l = m + 1;
      }
    }
    return l;
  }
};

ll gcd(ll a, ll b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

int32_t main() {
  // ios_base::sync_with_stdio(false);
  // cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> pos(n + 1, 1);
  pos[0] = 0;
  Segmenttree<int> sg(pos);
  vector<int> v(n + 1);
  rep(i, 1, n + 1) cin >> v[i];
  int p, idx;
  rep(i, 0, n) {
    cin >> p;
    idx = sg.find_kth(p);
    cout << v[idx] << ' ';
    sg.range_update(idx, idx, -1);
  }

  return 0;
}
