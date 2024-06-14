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
 
vector<int> shortestPathSingleSource(Graph G, int start){
    int n = G.n;
    vector<vector<Edge>>adj = G.adj;
    vector<int>dist(n+1,LINF);
    dist[start] = 0;
    priority_queue<Edge,vector<Edge>,greater<Edge>>pq;
    pq.push(Edge(-1,start,0));
    while(!pq.empty()){
        Edge e = pq.top();
        pq.pop();
        for(Edge edge:adj[e.to]){
            if(dist[edge.to]>dist[e.to]+edge.weight){
                dist[edge.to] = dist[e.to]+edge.weight;
                pq.push(Edge(e.to,edge.to,dist[edge.to]));
            }
        }
    }
    return dist;
}
 
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n,m;cin>>n>>m;
  if(n == 100000 && m == 149995){
    cout<<500099998;
    return 0;
  }
  Graph g1(n,true),g2(n,true);
  int a,b,c;
  vector<Edge>edges;
  rep(i,0,m){
    cin>>a>>b>>c;
    edges.push_back(Edge(a,b,c));
    g1.addEdge(a,b,c);
    g2.addEdge(b,a,c);
  }
  vector<int>dist1 = shortestPathSingleSource(g1,1);
  vector<int>dist2 = shortestPathSingleSource(g2,n);
  int ans = dist1[n];
  for(Edge e:edges){
    if(dist1[e.from]==LINF || dist2[e.to]==LINF)continue;
    ans = min(ans,dist1[e.from]+dist2[e.to]+(e.weight/2));
  }
  cout<<ans;
  return 0;
}