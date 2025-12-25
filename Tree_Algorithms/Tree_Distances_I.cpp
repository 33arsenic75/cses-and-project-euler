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

struct str{
    int mx1 = 0, mx2 = 0;
    str(){
        mx1 = 0; mx2 = 0;
    }
    void push(int x){
        if(x>=mx1){
            mx2 = mx1;
            mx1 = x;
        }
        else if(x>mx2){
            mx2=x;
        }
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin>>n;
    Graph Gr(n,false);
    int a,b;
    rep(i,0,n-1){
        cin>>a>>b;
        Gr.addEdge(a,b,0);
    }
    // vector<str>d(n+1);
    vector<int>mx1(n+1,-1),mx2(n+1,-1);
    vector<int>f(n+1,0);
    vector<int>g(n+1,0);
    g[0] = -1;
    function<void(int,int)>bfs = [&](int at, int p){
        for(Edge&e : Gr.adj[at]){
            if(e.to==p)continue;
            bfs(e.to,at);
            f[at] = max(f[at],1+f[e.to]);
            int x = f[e.to];
            if(x>mx1[at]){
                mx2[at] = mx1[at];
                mx1[at] = x;
            }
            else if(x>mx2[at]){
                mx2[at] = x;
            }
        }
    };
    function<void(int,int)>bfs2 = [&](int at,int p){
        g[at] = max(1+g[p],g[at]);
        if(f[at]+1==f[p]){
            g[at] = max(g[at],2+mx2[p]);
        }
        else{
            g[at] = max(g[at],2+mx1[p]);
        }
        if(at==1)g[at] = 0;
        for(Edge e:Gr.adj[at]){
            if(e.to==p)continue;
            bfs2(e.to,at);
        }
    };
    bfs(1,0);
    bfs2(1,0);
    for(int i = 1; i <= n ; i++)cout<<max(g[i],f[i])<<" ";
    return 0;
}
