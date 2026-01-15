#include <bits/stdc++.h>
#include <cstdlib>
#include <cstdlib> // rand()
#include <fstream>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef __int128_t i128;
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
void print(__int128 x) {
  if (x < 0) {
    cout << "-";
    x = -x;
  }
  if (x > 9)
    print(x / 10);
  cout << char('0' + x % 10);
}

void testcase() {
  ll n = rand();
  n = (n % 50) + 1;
  cout << n << '\n';
  rep(i, 0, n) cout << rand() % (ll)(500) << " " << rand() % (ll)(500) << '\n';
}

int main(int argc, char *argv[]) {
  // Default filenames
  srand(time(nullptr));
  string filename = ".input";
  // If user provided a filename, use it
  if (argc >= 2) {
    filename = argv[1];
  }
  // Open file for writing
  ofstream fout(filename);
  if (!fout.is_open()) {
    cerr << "Failed to open file: " << filename << "\n";
    return 1;
  }
  // Redirect cout to the file
  streambuf *old_buf = cout.rdbuf(fout.rdbuf());

  testcase();

  // Restore cout back to terminal (optional)
  cout.rdbuf(old_buf);
  fout.close();

  cout << "Testcase created in " << filename;
  return 0;
}
