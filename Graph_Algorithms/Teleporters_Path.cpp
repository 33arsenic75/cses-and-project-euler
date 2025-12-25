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

void eulertour(vector<multiset<ll>>&adj, vector<ll>& euler_path) {
    vector<ll> deg(adj.size()+1);
    ll n = adj.size()-1;
    rep(i,1,n+1){
        deg[i]=adj[i].size();
    }
    function<void(ll)> dfs = [&](ll at) {
        while (deg[at] != 0) {
            ll to = *adj[at].begin();
            adj[at].erase(adj[at].find(to));
            deg[at]--;
            dfs(to);
        }
        euler_path.push_back(at);
    };

    dfs(1); // Assuming the Euler tour starts at node 1
    reverse(all(euler_path));
}


int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n,m;cin>>n>>m;
    vector<multiset<ll>>adj(n+1);
    ll a,b;
    vector<ll>indeg(n+1),outdeg(n+1);
    rep(i,0,m){
        cin>>a>>b;
        adj[a].insert(b);
        // g.addEdge(a,b,0);
        outdeg[a]++;indeg[b]++;
    }
    rep(i,2,n){
        if(indeg[i]!=outdeg[i]){
            cout<<"IMPOSSIBLE";
            return 0;
        }
    }
    if((outdeg[1]-indeg[1])!=1){
        cout<<"IMPOSSIBLE";
        return 0;
    }
    if((indeg[n]-outdeg[n])!=1){
        cout<<"IMPOSSIBLE";
        return 0;      
    }
    vector<ll>path;
    eulertour(adj,path);
    if(path.size()!=m+1){
        cout<<"IMPOSSIBLE";
        return 0;
    }
    for(ll at:path)cout<<at<<" ";
    return 0;
}
