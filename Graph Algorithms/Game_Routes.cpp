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
#include<functional>
#include<cmath>
#include<numeric>
/// ordered sets support upperbound lowerbound too
#include <map>
#include <unordered_map>
#include <cstring>
#define len(v) (ll)v.size()
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back
#define rep(i, a, b) for (ll i = a; i < b; i++)
#define f first
#define mk make_pair
#define in insert
#define py cout << "YES\n"
#define pn cout << "NO\n"
#define fill(v,a,b) rep(i,a,b)cin>>v[i]
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
#define show1(v)                                                               \
  for (auto i : v)                                                             \
  cout << i << ' '
#define show(v)                                                                \
  show1(v);                                                                    \
  cout << '\n'
#else
#define debug(x)
#endif
const ll INF = 1e9;
const ll LINF = INF * INF;

// ------------------------------------------***--------------------------------------------------

ll gcd(ll a, ll b){
    if(b==0)return a;
    return gcd(b,a%b);
}

template <ll MOD=1000'000'007>
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
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n,m;cin>>n>>m;
    vector<vector<ll>>adj(n+1);
    ll a,b;
    rep(i,0,m){
        cin>>a>>b;
        adj[a].push_back(b);
    }
    vector<Modular<>>dp(n+1);
    dp[n]=1;
    vector<ll>topo;
    function<void()>toposort = [&](){
        vector<ll>indeg(n+1);
        rep(i,1,n+1){
            for(ll to:adj[i])indeg[to]++;
        }
        queue<ll>q;
        rep(i,1,n+1){
            if(indeg[i]==0)q.push(i);
        }
        while(!q.empty()){
            ll at = q.front();q.pop();
            topo.push_back(at);
            for(ll to:adj[at]){
                indeg[to]--;
                if(indeg[to]==0)q.push(to);
            }
        }
    };
    toposort();
    // show(topo);
    dp[n]=1;
    for(ll i = n-1 ; i >=0 ; i--){
        ll at = topo[i];
        for(ll to:adj[at]){
            dp[at]+=dp[to];
        }
    }
    cout<<dp[1];
    return 0;
}
