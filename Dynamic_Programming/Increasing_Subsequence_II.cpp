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
public:
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

  void range_add(int v, int l, int r, int ql, int qr, T add) {
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
      return ID;
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
  void range_update(int ql, int qr, T add) {
    range_add(1, 0, sz - 1, ql, qr, add);
  }

  /** @return sum of values on [ql, qr] */
  T range_query(int ql, int qr) { return range_sum(1, 0, sz - 1, ql, qr); }

  T get(ll pos) { return range_sum(1, 0, sz - 1, pos, pos); }
};
template <typename T> auto make_vec(size_t n, T val) {
  return std::vector<T>(n, val);
}

template <typename T, typename... Args> auto make_vec(size_t n, Args... args) {
  return std::vector<decltype(make_vec<T>(args...))>(n, make_vec<T>(args...));
}

ll gcd(ll a, ll b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

template <ll MOD = (ll)(1e9) + 7> struct Modular {
  int value;
  static const int MOD_value = MOD;

  Modular(long long v = 0) {
    value = v % MOD;
    if (value < 0)
      value += MOD;
  }
  Modular(long long a, long long b) : value(0) {
    *this += a;
    *this /= b;
  }

  Modular &operator+=(Modular const &b) {
    value += b.value;
    if (value >= MOD)
      value -= MOD;
    return *this;
  }
  Modular &operator-=(Modular const &b) {
    value -= b.value;
    if (value < 0)
      value += MOD;
    return *this;
  }
  Modular &operator*=(Modular const &b) {
    value = (long long)value * b.value % MOD;
    return *this;
  }

  friend Modular mexp(Modular a, long long e) {
    Modular res = 1;
    while (e) {
      if (e & 1)
        res *= a;
      a *= a;
      e >>= 1;
    }
    return res;
  }
  friend Modular inverse(Modular a) { return mexp(a, MOD - 2); }

  Modular &operator/=(Modular const &b) { return *this *= inverse(b); }
  friend Modular operator+(Modular a, Modular const b) { return a += b; }
  friend Modular operator-(Modular a, Modular const b) { return a -= b; }
  friend Modular operator-(Modular const a) { return 0 - a; }
  friend Modular operator*(Modular a, Modular const b) { return a *= b; }
  friend Modular operator/(Modular a, Modular const b) { return a /= b; }
  friend std::ostream &operator<<(std::ostream &os, Modular const &a) {
    return os << a.value;
  }
  friend bool operator==(Modular const &a, Modular const &b) {
    return a.value == b.value;
  }
  friend bool operator!=(Modular const &a, Modular const &b) {
    return a.value != b.value;
  }
};
using Mint = Modular<>;

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // cout << fixed << setprecision(6) << prob << endl;
  int n;
  cin >> n;
  auto h = make_vec<int>(n, 0);
  auto idx = make_vec<int>(n, 2, 0);
  for (int i = 0; i < n; i++) {
    cin >> h[i];
    idx[i][0] = h[i];
    idx[i][1] = i;
  }

  sort(idx.begin(), idx.end());

  auto rank1 = make_vec<int>(n, -1);
  map<int, int> rank2;

  for (int i = 0; i < n; i++) {
    rank1[idx[i][1]] = i;
    if (rank2.find(idx[i][0]) == rank2.end())
      rank2[idx[i][0]] = i;
    else
      rank2[idx[i][0]] = min(rank2[idx[i][0]], i);
  }

  Segmenttree<Mint> sg(n + 5);
  // show(sg.tree);

  for (int i = 0; i < n; i++) {
    int dp_idx = rank1[i];
    int range_idx = rank2[h[i]];
    // cout << i << " " << dp_idx << " " << range_idx << '\n';
    Mint val = sg.range_query(0, range_idx - 1);
    val += 1;
    sg.range_update(dp_idx, dp_idx, val);
  }
  // show(sg.tree);
  cout << sg.range_query(0, n - 1);
  return 0;
}
