#include <algorithm>
#include <bitset>
#include <deque>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <stdlib.h>
#include <unordered_set>
#include <vector>
/// ordered sets support upperbound lowerbound too
#include <map>
#include <unordered_map>
#define len(v) (int)v.size()
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
using namespace std;
#define int long long
#define pb push_back
#define rep(i, a, b) for (int i = a; i < b; i++)
#define f first
#define mk make_pair
#define in insert
#define py cout << "YES" << endl
#define pn cout << "NO" << endl
#define show1(v)                                                               \
  for (auto i : v)                                                             \
  cout << i << ' '
#define show(v)                                                                \
  show1(v);                                                                    \
  cout << '\n'
template <int MOD=998244353>
struct Modular {
  int value;
  static const int MOD_value = MOD;

  Modular(long long v = 0) { value = v % MOD; if (value < 0) value += MOD;}
  Modular(long long a, long long b) : value(0){ *this += a; *this /= b;}

  Modular& operator+=(Modular const& b) {value += b.value; if (value >= MOD) value -= MOD; return *this;}
  Modular& operator-=(Modular const& b) {value -= b.value; if (value < 0) value += MOD;return *this;}
  Modular& operator*=(Modular const& b) {value = (long long)value * b.value % MOD;return *this;}

  friend Modular mexp(Modular a, long long e) {
    Modular res = 1; while (e) { if (e&1) res *= a; a *= a; e >>= 1; }
    return res;
  }
  friend Modular inverse(Modular a) { return mexp(a, MOD - 2); }

  Modular& operator/=(Modular const& b) { return *this *= inverse(b); }
  friend Modular operator+(Modular a, Modular const b) { return a += b; }
  friend Modular operator-(Modular a, Modular const b) { return a -= b; }
  friend Modular operator-(Modular const a) { return 0 - a; }
  friend Modular operator*(Modular a, Modular const b) { return a *= b; }
  friend Modular operator/(Modular a, Modular const b) { return a /= b; }
  friend std::ostream& operator<<(std::ostream& os, Modular const& a) {return os << a.value;}
  friend bool operator==(Modular const& a, Modular const& b) {return a.value == b.value;}
  friend bool operator!=(Modular const& a, Modular const& b) {return a.value != b.value;}
};
template <typename T> void chkmin(T &x, T y) {
  if (x > y)
    x = y;
}
template <typename T> void chkmax(T &x, T y) {
  if (x < y)
    x = y;
}
void sigsev(int n, vector<int> &prime) {
  vector<bool> is_prime(n + 1, true);
  is_prime[0] = is_prime[1] = false;
  int i;
  for (i = 2; i * i <= n; i += 2) {
    if (is_prime[i]) {
      prime.push_back(i);
      for (int j = i * i; j <= n; j += i)
        is_prime[j] = false;
    }
  }
  for (i = i; i <= n; i++) {
    if (is_prime[i])
      prime.push_back(i);
  }
}
#ifndef ONLINE_JUDGE
#define debug(x) cout << #x << " = " << x << endl
#else
#define debug(x)
#endif


// ------------------------------------------***--------------------------------------------------



int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n,x;cin>>n>>x;
  vector<int>a(n);
  rep(i,0,n)cin>>a[i];
  sort(all(a));
  int ans = 0;
  int i = 0, j = n-1;
  int sum = 0;
  while(i<j){
    sum = a[i] + a[j];
    if(sum<=x){
        ans++;
        i++;j--;
    }
    else{
        ans++;
        j--;
    }
  }
  if(i==j)ans++;
  cout<<ans;
  return 0;
}
