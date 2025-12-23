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
using ll = unsigned long long;
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


int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    cin>>n;
    

    ll m = (n+63)/64;

    vector<vector<ll>>a(n, vector<ll>(m,0));

    string s;
    rep(i,0,n){
        cin>>s;
        rep(j,0,n){
            if(s[j]=='0')continue;
            ll idx_1 = j >> 6;
            ll idx_2 = j & 63;
            a[i][idx_1] |= (1LL<<idx_2);
        }
    }
    ll ans = 0; 
    rep(r1,0,n){
        rep(r2,r1+1,n){
            ll cnt = 0;
            rep(idx,0,m)cnt += __builtin_popcountll(a[r1][idx] & a[r2][idx]);
            ans += cnt*(cnt-1)/2;
        }
    }

    cout<<ans;
    return 0;
}

