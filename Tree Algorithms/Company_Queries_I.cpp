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
#define __gcd __algo_gcd
#else
#define debug(x)
#endif
const int INF = 1e9;
const int LINF = INF * INF;

// ------------------------------------------***--------------------------------------------------

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,q;cin>>n>>q;
    vector<vector<int>>par(n+1,vector<int>(20,0));// par[i][j] -> ancestor of i at 2^j distance
    rep(i,2,n+1)cin>>par[i][0];
    rep(j,1,20){
        rep(i,1,n+1){
            par[i][j] = par[par[i][j-1]][j-1];
        }
    }
    while(q>0){
        int k,x;cin>>k>>x;
        int ans = k;
        while(x>0 && ans>0){
            int setbit = 63 - __builtin_clzll(x);
            ans = par[ans][setbit];
            x ^=(1<<setbit);
        }
        if(ans==0)ans=-1;
        cout<<ans<<'\n';
        q--;
    }


    return 0;
}
