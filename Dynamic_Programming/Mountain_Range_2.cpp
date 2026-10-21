#include <bits/stdc++.h>
using namespace std;

// Point-assign, range-max segment tree (iterative, no lazy needed).
struct MaxSegTree {
  int n;
  vector<int> t;
  MaxSegTree(int n) : n(n), t(2 * n, 0) {}
  void set(int p, int v) {
    for (t[p += n] = v; p > 1; p >>= 1)
      t[p >> 1] = max(t[p], t[p ^ 1]);
  }
  int query(int l, int r) { // inclusive [l, r]; empty range -> 0
    int res = 0;
    if (l > r)
      return res;
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        res = max(res, t[l++]);
      if (r & 1)
        res = max(res, t[--r]);
    }
    return res;
  }
};

template <typename T, typename Compare> class MonotonicStack {
  stack<T> st;
  Compare cmp;

public:
  explicit MonotonicStack(Compare comp = Compare()) : cmp(comp) {}
  // Pops while cmp(top, value) is true, then pushes value.
  void push(const T &value) {
    while (!st.empty() && cmp(st.top(), value))
      st.pop();
    st.push(value);
  }
  void prune(const T &value) {
    while (!st.empty() && cmp(st.top(), value))
      st.pop();
  }
  bool empty() const { return st.empty(); }
  T &top() { return st.top(); }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> h(n);
  for (auto &x : h)
    cin >> x;

  using P = pair<int, int>; // (height, index)
  auto cmp = [](const P &a, const P &b) { return a.first < b.first; };
  // Pop strictly smaller heights only, so the remaining top has height >=
  // current.
  MonotonicStack<P, decltype(cmp)> msl(cmp), msr(cmp);

  vector<int> L(n, -1), R(n, n);
  for (int i = 0; i < n; i++) {
    msl.prune({h[i], i});
    L[i] = msl.empty() ? -1 : msl.top().second;
    msl.push({h[i], i});
  }
  for (int i = n - 1; i >= 0; i--) {
    msr.prune({h[i], i});
    R[i] = msr.empty() ? n : msr.top().second;
    msr.push({h[i], i});
  }

  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int a, int b) { return h[a] < h[b]; });

  MaxSegTree sg(n);
  int ans = 0;
  for (int i : order) {
    int val = 1 + sg.query(L[i] + 1, R[i] - 1);
    sg.set(i, val);
    ans = max(ans, val);
  }
  cout << ans;
  return 0;
}
