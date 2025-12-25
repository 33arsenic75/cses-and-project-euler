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
    int n,m;cin>>n>>m;
    Graph g(n,false);
    int a,b;
    rep(i,0,m){
        cin>>a>>b;
        g.addEdge(a,b,0);
    }
    vector<int>par(n+1,-1);
    vector<bool>vis(n+1,false);
    vector<int>ans;
    int start = -1;
    int end = -1;
    function<void(int,int)>dfs = [&](int at,int p){
        vis[at] = true;
        for(Edge e:g.adj[at]){
            if(e.to==p)continue;
            if(vis[e.to]){
                start = e.to;
                end = at;
                par[e.to] = at;
                return;
            }
            par[e.to] = at;
            dfs(e.to,at);
            if(start!=-1)return;
        }
    };
    rep(i,1,n+1){
        if(!vis[i]){
           dfs(i,-1);
           if(start!=-1)break;
       }
    }
    if(start==-1)cout<<"IMPOSSIBLE";
    else{
        while(end!=start){
            ans.push_back(end);
            end = par[end];
        }
        ans.push_back(start);
        reverse(all(ans));
        ans.push_back(ans[0]);
        cout<<len(ans)<<'\n';
        for(int i:ans)cout<<i<<' ';
    }
    return 0;
}
