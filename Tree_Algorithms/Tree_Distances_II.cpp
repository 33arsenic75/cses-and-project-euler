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
#include <cstring>
#define len(v) (int)v.size()
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
using namespace std;
using ll = long long;
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
const ll INF = 1e9;
const ll LINF = INF * INF;

// ------------------------------------------***--------------------------------------------------

struct  Edge{
    int from; int to;
    int weight;
    Edge(int from, int to, int weight):from(from), to(to), weight(weight){
    }
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
    bool operator>(const Edge& other) const {
        return weight > other.weight;
    }
};

struct Graph{
    int n;
    vector<vector<Edge>> adj;
    vector<Edge> edges;
    bool directed;
    Graph(int n, bool directed):n(n),directed(directed){
        adj.resize(n+1);
    }
    void addEdge(int from, int to, int weight){
        Edge e1(from, to, weight);
        adj[from].push_back(e1);
        edges.push_back(e1);
        if(!directed){
            Edge e2(to, from, weight);
            adj[to].push_back(e2);
            edges.push_back(e2);
        }
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;cin>>n;
    Graph gr(n,false);
    ll a,b;
    rep(i,0,n-1){
        cin>>a>>b;
        gr.addEdge(a,b,0);
    }
    vector<ll>f(n+1,0);
    vector<ll>g(n+1,0);
    vector<ll>child(n+1,0);
    function<void(ll,ll)>bfs = [&](ll at, ll p){
        for(Edge&e:gr.adj[at]){
            if(e.to==p)continue;
            bfs(e.to,at);
            f[at] += 1 + child[e.to] + f[e.to];
            child[at] += 1 + child[e.to];
        }
    };

    function<void(ll,ll)>bfs2 = [&](ll at, ll p){
        if(at!=1){
            g[at] = f[p] + g[p] - f[at] - child[at] - 1 + (n-1-child[at]);
        }
        // cout<<"Done "<<at<<" "<<g[at]<<"\n"; 
        for(Edge&e:gr.adj[at]){
            if(e.to==p)continue;
            bfs2(e.to,at);
        }
    };
    bfs(1,0);
    // show(f);show(child);
    bfs2(1,0);
    rep(i,1,n+1)cout<<f[i]+g[i]<<" ";
    return 0;
}
