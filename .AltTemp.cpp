#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
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
void solve() {}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  ll t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
