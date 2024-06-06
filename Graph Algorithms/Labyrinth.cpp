#pragma GCC optimize("Ofast")
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


const int INF = INT64_MAX;
/// O(V + ElogV)
vector<int> shortestPathSingleSource(Graph G, int start){
    int n = G.n;
    vector<vector<Edge>>adj = G.adj;
    vector<int>dist(n+1,INF);
    dist[start] = 0;
    priority_queue<Edge,vector<Edge>,greater<Edge>>pq;
    pq.push(Edge(-1,start,0));
    vector<int>par(n+1,-1);
    while(!pq.empty()){
        Edge e = pq.top();
        pq.pop();
        for(Edge edge:adj[e.to]){
            if(dist[edge.to]>dist[e.to]+edge.weight){
                dist[edge.to] = dist[e.to]+edge.weight;
                pq.push(Edge(e.to,edge.to,dist[edge.to]));
                par[edge.to] = edge.from;
            }
        }
    }
    return par;
}



int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
//   freopen("test_input.txt","r",stdin);
  int n,m;cin>>n>>m;
  Graph G(n*m+1,false);
  vector<string>grid(n);
  rep(i,0,n)cin>>grid[i];
  function<bool(int,int)>inrange = [&](int i,int j){
        return i>=0 && i<n && j>=0 && j<m;
  };
  function<bool(char)>isvalid = [&](char c){
        return c=='.' || c=='A' || c=='B';
  };
  int dx[2]={1,0};
  int dy[2]={0,1};
  int start = 0,end = 0;
  for(int i = 0 ; i < n ; i++){
    for(int j = 0 ; j < m ; j++){
        for(int k = 0 ; k < 2; k++){
            if(inrange(i+dx[k],j+dy[k]) && isvalid(grid[i][j]) && isvalid(grid[i+dx[k]][j+dy[k]])){
                G.addEdge(i*m+j,(i+dx[k])*m+j+dy[k],1);
            }
            if(grid[i][j]=='A')start = i*m+j;
            if(grid[i][j]=='B')end = i*m+j;
        }
    }
  }
  vector<int>par = shortestPathSingleSource(G,start);
  if(par[end]==-1){
    cout<<"NO\n";return 0;
  }
  cout<<"YES\n";
  vector<int>ans;
  while(end!=-1){
    ans.push_back(end);
    end = par[end];
  }
  reverse(all(ans));
  cout<<len(ans)-1<<'\n';
  for(int i = 1 ; i < len(ans); i++){
    int diff = ans[i]-ans[i-1];
    if(diff==1)cout<<"R";
    else if(diff==-1)cout<<"L";
    else if(diff==m)cout<<"D";
    else cout<<"U";
  }

  return 0;
}
