// Problem: Counting Tilings
// File: Counting_Tilings.cpp
// Created: 2026-10-13
// Author: abhinav
// Link:
// Topic: Dynamic Programming, Bitmask DP
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
// void print(__int128 x) {
//   if (x < 0) {
//     cout << "-";
//     x = -x;
//   }
//   if (x > 9)
//     print(x / 10);
//   cout << char('0' + x % 10);
// }
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
int n, m;
vector<vector<int>> trans; // trans[cur] = all reachable nxt masks
vector<vector<Mint>> dp;
vector<vector<char>> vis;

// fill column cells row..n-1; cur = prefilled cells, nxt = cells pushed into
// next column
void gen(int row, int cur, int nxt, int start) {
  if (row >= n) {
    trans[start].push_back(nxt);
    return;
  }
  if ((cur >> row) & 1) { // already covered
    gen(row + 1, cur, nxt, start);
    return;
  }
  gen(row + 1, cur, nxt | (1 << row), start); // horizontal
  if (row + 1 < n && !((cur >> (row + 1)) & 1))
    gen(row + 2, cur, nxt, start); // vertical (covers row, row+1)
}

// h columns remaining including the current one; mask = prefilled cells of
// current column
Mint f(int h, int mask) {
  if (h == 0)
    return mask == 0 ? Mint(1) : Mint(0);
  if (vis[h][mask])
    return dp[h][mask];
  vis[h][mask] = 1;
  Mint res = 0;
  for (int nxt : trans[mask])
    res += f(h - 1, nxt);
  return dp[h][mask] = res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n >> m;
  if (n > m)
    swap(n, m); // mask over the smaller side (n <= 10)

  trans.assign(1 << n, {});
  for (int mask = 0; mask < (1 << n); mask++)
    gen(0, mask, 0, mask);

  dp = make_vec<Mint>(m + 1, 1 << n, (Mint)0);
  vis = make_vec<char>(m + 1, 1 << n, (char)0);

  cout << f(m, 0);
  return 0;
}
