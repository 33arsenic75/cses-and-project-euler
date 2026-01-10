// Problem: Polygon Lattice Points
// File: Polygon_Lattice_Points.cpp
// Created: 2026-01-10
// Author: abhinav
// Link:
//

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
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

template <typename T> struct geometry {
  T x, y;

  geometry() : x(0), y(0) {}
  geometry(T a, T b) : x(a), y(b) {}

  T real() const { return x; }
  T imag() const { return y; }

  geometry operator+(const geometry &other) const {
    return {x + other.x, y + other.y};
  }

  geometry operator-(const geometry &other) const {
    return {x - other.x, y - other.y};
  }

  geometry operator*(T k) const { return {x * k, y * k}; }

  bool operator==(const geometry &other) const {
    return (x == other.x) && (y == other.y);
  }
};

template <typename T> T dot(const geometry<T> &a, const geometry<T> &b) {
  return a.x * b.x + a.y * b.y;
}

template <typename T> T cross(const geometry<T> &a, const geometry<T> &b) {
  return a.x * b.y - a.y * b.x;
}

template <typename T> double arg(const geometry<T> &a) {
  return atan2((double)a.y, (double)a.x); // already in [-pi, pi]
}

template <typename T>
double signedAngleABC(const geometry<T> &A, const geometry<T> &B,
                      const geometry<T> &C) {
  auto BA = A - B;
  auto BC = C - B;
  return atan2((double)cross(BC, BA), (double)dot(BC, BA));
}

template <typename T> T dist2(const geometry<T> &a, const geometry<T> &b) {
  T dx = a.x - b.x;
  T dy = a.y - b.y;
  return dx * dx + dy * dy;
}

template <typename T> double dist(const geometry<T> &a, const geometry<T> &b) {
  return sqrt((double)dist2(a, b));
}

template <typename T>
int orientation(const geometry<T> &a, const geometry<T> &b,
                const geometry<T> &c) {
  auto v1 = b - a;
  auto v2 = c - a;
  T v = cross(v1, v2);
  if (v > 0)
    return 1; // left turn
  if (v < 0)
    return -1; // right turn
  return 0;    // collinear
}

template <typename T>
double pointLineDistance(const geometry<T> &A, const geometry<T> &B,
                         const geometry<T> &P) {
  auto AB = B - A;
  auto AP = P - A;
  double area2 = abs((double)cross(AB, AP));
  double base = sqrt((double)dot(AB, AB));
  return area2 / base;
}

template <typename T> T doublepolygonArea(const vector<geometry<T>> &p) {
  int n = p.size();
  T s = 0;
  for (int i = 0; i < n; i++) {
    int j = (i + 1) % n;
    s += p[i].x * p[j].y - p[i].y * p[j].x;
  }
  return abs((T)s);
}

template <typename T>
bool onSegment(geometry<T> A, geometry<T> B, geometry<T> C) {
  /// C lie on AB segment
  return cross(A - C, B - C) == 0 && dot(A - C, B - C) <= 0;
}

template <typename T> ll numPointonSegment(geometry<T> a, geometry<T> b) {
  if (a == b)
    return 0ll;
  geometry<T> c(abs(a.x - b.x), abs(a.y - b.y));
  return gcd(c.x, c.y);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  ll n;
  cin >> n;
  vector<geometry<ll>> p(n);
  rep(i, 0, n) cin >> p[i].x >> p[i].y;
  ll area2 = doublepolygonArea(p);
  ll b = 0;
  rep(i, 0, n) { b += numPointonSegment(p[i], p[(i + 1) % n]); }
  cout << ((area2 - b + 2) / 2) << " " << b;
  return 0;
}
