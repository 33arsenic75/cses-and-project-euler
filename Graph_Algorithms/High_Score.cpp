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
    int n,m; cin>>n>>m;
    Graph g(n,true);
    int a,b,w;
    rep(i,0,m){
        cin>>a>>b>>w;
        g.addEdge(a,b,-w);
    }
    if(n==1){
        for(Edge e: g.edges){
            if(e.weight<0){
                cout<<-1<<'\n';
                return 0;
            }
        }
        cout<<0<<'\n';
        return 0;
    }
    vector<int> dist(n+1, LINF);
    vector<int>par(n+1,-1);
    vector<bool>reachable1(n+1,false);
    vector<bool>reachable2(n+1,false);
    reachable1[1] = true;
    reachable2[n] = true;
    function<void()> bellman_ford = [&](){
        dist[1] = 0;
        rep(i,0,n-1){
            for(Edge e: g.edges){
                if(dist[e.from] + e.weight < dist[e.to]){
                    dist[e.to] = dist[e.from] + e.weight;
                    par[e.to] = e.from;
                }
                if(reachable2[e.to])reachable2[e.from]=true;
                if(reachable1[e.from])reachable1[e.to]=true;
            }
        }
    };
    bellman_ford();
    // show(reachable);
    vector<int>initial = dist;
    for(Edge e: g.edges){
        if(dist[e.from] + e.weight < dist[e.to]){
            dist[e.to] = dist[e.from] + e.weight;
            par[e.to] = e.from;
        }
    }
    vector<int>final = dist;
    bool isneg = false;
    // show(initial);
    // show(final);
    // show(reachable1);
    // show(reachable2);
    rep(i,1,n+1){
        if(reachable1[i] && reachable2[i] && (initial[i]!=final[i]))isneg=true;
    }
    if(isneg){
        cout<<-1<<'\n';
    }
    else cout<<-initial[n]<<'\n';
    return 0;
}
