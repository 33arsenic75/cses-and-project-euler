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
    int n,m;cin>>n>>m;
    vector<int>color(n+1,-1);
    vector<vector<int>>adj(n+1);
    rep(i,0,m){
        int a,b;cin>>a>>b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vector<bool>vis(n+1,false);
    function<bool(int,int,int)>dfs = [&](int node,int par,int col){
        if(color[node]!=-1 && color[node]!=col)return false;
        else if(vis[node])return true;
        color[node] = col;
        vis[node] = true;
        bool f = true;
        for(int&to:adj[node]){
            if(to==par)continue;
            f &= dfs(to,node,3-col);
        }
        return f;
    };
    bool ans = true;
    for(int i = 1 ; i <= n ; i++){
        if(!vis[i]){
            ans&=dfs(i,-1,1);
        }
    }
    if(!ans)cout<<"IMPOSSIBLE";
    else{
        rep(i,1,n+1)cout<<color[i]<<' ';
    }
    return 0;
}
