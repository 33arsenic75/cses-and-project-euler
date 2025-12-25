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
#ifndef ONLINE_JUDGE
#define debug(x) cout << #x << " = " << x << endl
#define __gcd __algo_gcd
#else
#define debug(x)
#endif


// ------------------------------------------***--------------------------------------------------

/// https://www.youtube.com/watch?v=dm70QwzBsMc

vector<vector<bool>>ava;

int ans = 0;
set<int>cl1;
set<int>cl2;
set<int>col;
set<int>row;

bool help(int column, int i){
    return cl1.find(column+i)==cl1.end() && cl2.find(column-i)==cl2.end() && col.find(column)==col.end() && row.find(i)==row.end();
}

void help1(int column, int i){
    cl1.insert(column+i);
    cl2.insert(column-i);
    col.insert(column);
    row.insert(i);
}

void help2(int column, int i){
    cl1.erase(column+i);
    cl2.erase(column-i);
    col.erase(column);
    row.erase(i);
}

void solve(int column){
    if(column==8){ans++;return;}
    for(int i = 0; i < 8 ; i++){
        if(ava[column][i] && help(column,i)){
            help1(column,i);
            solve(column+1);
            help2(column,i);
        }
    }
}


int32_t main() {
  ava = vector<vector<bool>>(8,vector<bool>(8,true));
  vector<string>brd(8);
  ans = 0;
  rep(i,0,8)cin>>brd[i];
  rep(i,0,8){
    rep(j,0,8)ava[i][j]=(brd[i][j]=='.');
  }
    solve(0);
    cout<<ans;
  return 0;
}
