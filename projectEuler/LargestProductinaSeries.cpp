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
  for (i = 2; i <= sqrt(n); i++) {
    if (is_prime[i]) {
      prime.push_back(i);
      for (int j = i * i; j <= n; j += i)
        is_prime[j] = false;
    }
  }
  for (; i <= n; i++) {
    if (is_prime[i])
      prime.push_back(i);
  }
}
#ifndef ONLINE_JUDGE
#define debug(x) cout << #x << " = " << x << endl
#define __gcd __algo_gcd
#else
#define debug(x)
#endif


// ------------------------------------------***--------------------------------------------------



/// a = 2mn, b = m2-n2 c = m2 + n2 , m>n
/// a+b+c = 2m2 + 2mn
string s = "7316717653133062491922511967442657474235534919493496983520312774506326239578318016984801869478851843858615607891129494954595017379583319528532088055111254069874715852386305071569329096329522744304355766896648950445244523161731856403098711121722383113622298934233803081353362766142828064444866452387493035890729629049156044077239071381051585930796086670172427121883998797908792274921901699720888093776657273330010533678812202354218097512545405947522435258490771167055601360483958644670632441572215539753697817977846174064955149290862569321978468622482839722413756570560574902614079729686524145351004748216637048440319989000889524345065854122758866688116427171479924442928230863465674813919123162824586178664583591245665294765456828489128831426076900422421902267105562632111110937054421750694165896040807198403850962455444362981230987879927244284909188845801561660979191338754992005240636899125607176060588611646710940507754100225698315520005593572972571636269561882670428252483600823257530420752963450";
int N = 13;
int sz = len(s);
int help(char c){return c-'0';}
int ans = 0;
inline void help2(int j){
    int init = 1;
    for(int i = j ; i < N+j ; i++){
        init*=help(s[i]);
    }
    ans = max(ans,init);
}
int32_t main() {
    rep(i,0,sz-N)help2(i);
    cout<<ans;
  return 0;
}
