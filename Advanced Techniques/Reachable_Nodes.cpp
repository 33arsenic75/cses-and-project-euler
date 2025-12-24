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

void solve() {
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin>>n>>m;
    int M = (n+63)/64;

    vector<vector<ll>>adj(n+1);
    ll a,b;
    rep(i,0,m){
        cin>>a>>b;
        adj[a].push_back(b);
    }

    vector<vector<ll>>bt(n+1,vector<ll>(M,0));
    
    vector<bool>call(n+1,false);
    function<void(int)>calc = [&](int at){
        if(call[at])return;
        for(int to: adj[at]){
            calc(to);
            for(int idx = 0 ; idx < M ; idx++){
                bt[at][idx] |= bt[to][idx];
            }
        }
        call[at]=true;
        return;
    };

    rep(i,1,n+1){
        ll idx1 = i >> 6;
        ll idx2 = i & 63;
        bt[i][idx1] |= (1ll<<idx2);
    }
    rep(i,1,n+1)calc(i);
    rep(i,1,n+1){
        ll ans = 0;
        rep(idx,0,M)ans+=__builtin_popcountll(bt[i][idx]);
        cout<<ans<<' ';
    }
    return 0;
}
