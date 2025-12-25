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
    int n,q;
    cin>>n>>q;
    Graph g(n, false);
    int a,b;
    rep(i,0,n-1){
        cin>>a>>b;
        g.addEdge(a,b,1);
    }
    vector<int>depth(n+1,0);
    vector<vector<int>>par(n+1,vector<int>(20,0));
    function<void(int,int,int)>dfs = [&](int node, int p, int d){
        par[node][0] = p;
        depth[node] = d;
        for(Edge i : g.adj[node]){
            if(i.to != p){
                dfs(i.to, node, d+1);
            }
        }
    };
    dfs(1,0,0);
    rep(j,1,20){
        rep(i,2,n+1){
            par[i][j] = par[par[i][j-1]][j-1];
        }
    }
    function<int(int,int)>jump = [&](int at,int jump){
        int ans = at;
        for(int i = 0; i < 20; i++){
            if((jump>>i)&1){
                ans = par[ans][i];
            }
        }
        return ans;
    };
    function<int(int,int)>ancestor = [&](int a, int b){
       if(depth[a] < depth[b])swap(a,b);
        a = jump(a,depth[a]-depth[b]);
        while(a!=b){
            for(int i = 19; i >= 0; i--){
                if(par[a][i] != par[b][i]){
                    a = par[a][i];
                    b = par[b][i];
                }
            }
            a = par[a][0];
            b = par[b][0];
        }
        return a;
    };
    while(q--){
        int a,b,c;
        cin>>a>>b;
        c = ancestor(a,b);
        cout<<depth[a]+depth[b]-2*depth[c]<<'\n';
    }
    return 0;
}
