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

struct node{
    int index;
    int val;
    int depth;
    node(int index, int val, int depth):index(index),val(val),depth(depth){}
    bool operator<(const node& other) const {
        return depth < other.depth;
    }
    bool operator>(const node& other) const {
        return depth > other.depth;
    }
    std::string toString() const {
        string s = "index: " + to_string(index) + " val: " + to_string(val) + " depth: " + to_string(depth);
        return s;
    }

};

// int32_t main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     int n,q;
//     cin>>n>>q;
//     Graph g(n, true);
//     int p;
//     vector<int>par(n+1);
//     rep(i,2,n+1){
//         cin>>p;
//         par[i] = p;
//         g.addEdge(p,i,0);
//     }
//     vector<node>nodes(2*n-1, node(0,0,0));
//     int index = 0;
//     vector<int>depth(n+1,0);
//     vector<vector<int>>where(n+1);
//     function<void(int)>dfs = [&](int at){
//         nodes[index] = node(index,at,depth[at]);
//         where[at].pb(index);
//         index++;
//         for(Edge e:g.adj[at]){
//             depth[e.to] = depth[at] + 1;
//         }
//         for(Edge e:g.adj[at]){
//             dfs(e.to);
//             nodes[index] = node(index,at,depth[at]);
//             where[at].pb(index);
//             index++;
//         }
//     };
//     dfs(1);
//     vector<vector<node>>st(2*n-1, vector<node>(20, node(0,0,0)));  
//     rep(i,0,2*n-1)st[i][0] = nodes[i];
//     rep(j,1,20){
//         rep(i,0,2*n-1){
//             if(i+(1<<j) < 2*n-1){
//                 st[i][j] = min(st[i][j-1], st[i+(1<<(j-1))][j-1]);
//             }
//             else{
//                 st[i][j] = st[i][j-1];
//             }
//         }
//     }
//     function<node(int,int)>query = [&](int l, int r){
//         int j = 63 - __builtin_clzll(r-l+1);
//         return min(st[l][j], st[r-(1<<j)+1][j]);
//     };
//     while(q--){
//         int u,v;
//         cin>>u>>v;
//         int l = where[u][0];
//         int r = where[v][0];
//         if(l > r)swap(l,r);
//         cout<<query(l,r).val<<'\n';
//     }
//     return 0;
// }

// int32_t main(){
//     int n,q;cin>>n>>q;
//     vector<vector<int>>par(n+1,vector<int>(20,0));
//     vector<int>depth(n+1,0);
//     rep(i,2,n+1)cin>>par[i][0];
//     rep(j,1,20){
//         rep(i,2,n+1){
//             par[i][j] = par[par[i][j-1]][j-1];
//         }
//     }
//     function<void()>depthcalc = [&](){
//         vector<bool>vis(n+1,false);
//         function<void(int)>help = [&](int at){
//             if(vis[par[at][0]]){
//                 depth[at] = depth[par[at][0]] + 1;
//             }
//             else{
//                 help(par[at][0]);
//                 depth[at] = depth[par[at][0]] + 1;
//             }
//             vis[at]=true;
//         };
//         depth[1] = 0;
//         vis[1]=true;
//         rep(i,2,n+1){
//             if(!vis[i])help(i);
//         }
//     };
//     depthcalc();
//     function<int(int,int)>jump = [&](int at,int jump){
//         int ans = at;
//         for(int i = 0; i < 20; i++){
//             if((jump>>i)&1){
//                 ans = par[ans][i];
//             }
//         }
//         return ans;
//     };
//     while(q--){
//         int a,b;
//         cin>>a>>b;
//         if(depth[a] < depth[b])swap(a,b);
//         a = jump(a,depth[a]-depth[b]);
//         while(a!=b){
//             for(int i = 19; i >= 0; i--){
//                 if(par[a][i] != par[b][i]){
//                     a = par[a][i];
//                     b = par[b][i];
//                 }
//             }
//             a = par[a][0];
//             b = par[b][0];
//         }
//         cout<<a<<'\n';
//     }
//     return 0;
// }