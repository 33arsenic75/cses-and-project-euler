// Problem: Convex Hull
// File: Convex_Hull.cpp
// Created: 2026-01-11
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

  bool operator<(const geometry &other) const {
    if (x == other.x)
      return y < other.y;
    return x < other.x;
  }
  bool operator>(const geometry &other) const {
    if (x == other.x)
      return y > other.y;
    return x > other.x;
  }
};

template <typename T>
bool compare_by_x(const geometry<T> &a, const geometry<T> &b) {
  if (a.x == b.x)
    return a.y < b.y;
  return a.x < b.x;
}

template <typename T>
bool compare_by_y(const geometry<T> &a, const geometry<T> &b) {
  if (a.y == b.y)
    return a.x < b.x;
  return a.y < b.y;
}

template <typename T> T dot(const geometry<T> &a, const geometry<T> &b) {
  return a.x * b.x + a.y * b.y;
}

template <typename T> T cross(const geometry<T> &a, const geometry<T> &b) {
  return a.x * b.y - a.y * b.x;
}

template <typename T>
T cross(const geometry<T> &a, const geometry<T> &b, const geometry<T> &c) {
  // (b - a) × (c - a)
  return cross(b - a, c - a);
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

template <typename T> T minimumDistance(vector<geometry<T>> &p) {
  ll n = p.size();

  function<T(T)> sq = [](T b) { return b * b; };
  function<ll(ll, ll)> recurse = [&](ll i, ll j) {
    if (i == j)
      return 8 * INF * INF + INF;
    else if (i + 1 == j)
      return dist2(p[i], p[j]);
    ll m = i + (j - i) / 2;
    T d1 = recurse(i, m);
    T d2 = recurse(m + 1, j);
    T d = min(d1, d2);
    ll mi = m, mj = m;
    while (i < mi && sq(p[mi].x - p[m].x) <= d)
      mi--;
    while (j > mj && sq(p[mj].x - p[m].x) <= d)
      mj++;
    sort(p.begin() + mi, p.begin() + mj, compare_by_y<ll>);
    rep(i, mi, mj + 1) {
      rep(j, i + 1, min(i + 8, mj + 1)) { d = min(d, dist2(p[i], p[j])); }
    }
    sort(p.begin() + mi, p.begin() + mj, compare_by_x<ll>);
    return d;
  };
  sort(p.begin(), p.end(), compare_by_x<ll>);
  return recurse(0, n - 1);
}

template <typename T> int rightmost(const vector<geometry<T>> &P) {
  int idx = 0;
  for (int i = 1; i < (int)P.size(); i++)
    if (P[i].x > P[idx].x)
      idx = i;
  return idx;
}

template <typename T> int leftmost(const vector<geometry<T>> &P) {
  int idx = 0;
  for (int i = 1; i < (int)P.size(); i++)
    if (P[i].x < P[idx].x)
      idx = i;
  return idx;
}

template <typename T>
pair<geometry<T>, geometry<T>> upperTangent(const vector<geometry<T>> &P,
                                            const vector<geometry<T>> &Q) {
  int n = P.size(), m = Q.size();

  int i = rightmost(P);
  int j = leftmost(Q);

  bool done = false;
  while (!done) {
    done = true;

    // move i on P
    while (orientation(Q[j], P[i], P[(i + 1) % n]) >= 0)
      i = (i + 1) % n;

    // move j on Q
    while (orientation(P[i], Q[j], Q[(j - 1 + m) % m]) <= 0) {
      j = (j - 1 + m) % m;
      done = false;
    }
  }
  return {P[i], Q[j]};
}

template <typename T>
pair<geometry<T>, geometry<T>> lowerTangent(const vector<geometry<T>> &P,
                                            const vector<geometry<T>> &Q) {
  int n = P.size(), m = Q.size();

  int i = rightmost(P);
  int j = leftmost(Q);

  bool done = false;
  while (!done) {
    done = true;

    // move i on P
    while (orientation(Q[j], P[i], P[(i - 1 + n) % n]) <= 0)
      i = (i - 1 + n) % n;

    // move j on Q
    while (orientation(P[i], Q[j], Q[(j + 1) % m]) >= 0) {
      j = (j + 1) % m;
      done = false;
    }
  }
  return {P[i], Q[j]};
}

template <typename T>
vector<geometry<T>> convexHull_noBoundary(vector<geometry<T>> p) {
  int n = p.size();
  if (n <= 1)
    return p;

  sort(p.begin(), p.end());

  vector<geometry<T>> lower, upper;

  // Build lower hull
  for (auto &pt : p) {
    while (lower.size() >= 2 &&
           cross(lower[lower.size() - 2], lower.back(), pt) <= 0) {
      lower.pop_back();
    }
    lower.push_back(pt);
  }

  // Build upper hull
  for (int i = n - 1; i >= 0; i--) {
    auto &pt = p[i];
    while (upper.size() >= 2 &&
           cross(upper[upper.size() - 2], upper.back(), pt) <= 0) {
      upper.pop_back();
    }
    upper.push_back(pt);
  }

  // Remove last element of each (it is the starting point of the other)
  lower.pop_back();
  upper.pop_back();

  lower.insert(lower.end(), upper.begin(), upper.end());
  return lower; // CCW convex hull
}

template <typename T>
vector<geometry<T>> convexHull_Boundary(vector<geometry<T>> p) {
  int n = p.size();
  if (n <= 1)
    return p;

  sort(p.begin(), p.end());

  vector<geometry<T>> lower, upper;

  // Build lower hull
  for (auto &pt : p) {
    while (lower.size() >= 2 &&
           cross(lower[lower.size() - 2], lower.back(), pt) < 0) {
      lower.pop_back();
    }
    lower.push_back(pt);
  }

  // Build upper hull
  for (int i = n - 1; i >= 0; i--) {
    auto &pt = p[i];
    while (upper.size() >= 2 &&
           cross(upper[upper.size() - 2], upper.back(), pt) < 0) {
      upper.pop_back();
    }
    upper.push_back(pt);
  }

  // Remove last element of each (it is the starting point of the other)
  lower.pop_back();
  upper.pop_back();

  lower.insert(lower.end(), upper.begin(), upper.end());
  return lower; // CCW convex hull
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  ll n;
  cin >> n;
  vector<geometry<ll>> p(n);
  rep(i, 0, n) cin >> p[i].x >> p[i].y;

  vector<geometry<ll>> hull = convexHull_Boundary(p);
  cout << hull.size() << '\n';
  rep(i, 0, hull.size()) cout << hull[i].x << " " << hull[i].y << '\n';
  return 0;
}
