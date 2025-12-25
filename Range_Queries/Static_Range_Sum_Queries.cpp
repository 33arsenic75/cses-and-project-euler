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
#define __gcd __algo_gcd
#else
#define debug(x)
#endif


// ------------------------------------------***--------------------------------------------------





int32_t main() {
    int n,q;cin>>n>>q;
    vector<int>a(n+1,0);
    int x;
    rep(i,1,n+1){
        cin>>x;
        a[i]=a[i-1]+x;
    }
    int l,r;
    while(q--){
        cin>>l>>r;
        cout<<a[r]-a[l-1]<<'\n';
    }
  return 0;
}

// struct Fenwick
// {
//     int n;

//     vector<int>bit;
//     Fenwick(int sz){
//         n = sz;
//         bit.resize(n,0);
//     }
//     Fenwick(vector<int>&a):Fenwick(a.size()){
//         for(int i = 0 ; i < n ; i++){
//             add(i,a[i]);
//         }
//     }
//     void add(int index, int a){
//         for(;index<n ; index = index | (index+1) ){
//             bit[index] += a;
//         }
//     }
//     Fenwick(vector<int>&a,bool quick) : Fenwick(a.size()){
//         for(int i = 0 ; i < n ; i++){
//             bit[i] += a[i];

//             int r = i|(i+1);
//             if(r<n)bit[r]+=bit[i];
//         }
//     }

//     int sum(int r){
//         int ans = 0;
//         for(;r>=0 ; r = ((r&(r+1)) - 1)){
//             ans += bit[r];
//         }
//         return ans;
//     }
//     int sum(int l, int r){
//         return sum(r) - sum(l-1);
//     }
// };


// int32_t main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     int n,q;cin>>n>>q;
//     vector<int>a(n+1);
//     rep(i,1,n+1)cin>>a[i];
//     Fenwick f(a,true);
//     // cout<<f.sum(0,n-1);
//     while(q--){
//         int l,r;
//         cin>>l>>r;
//         cout<<f.sum(l,r)<<'\n';
//     }
//     return 0;
// }
