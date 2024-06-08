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

/// dp
// int32_t main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     int n;cin>>n;
//     int a,b;
//     Graph G(n,false);
//     vector<int>deg(n+1,0);
//     rep(i,0,n-1){
//         cin>>a>>b;
//         G.addEdge(min(a,b),max(a,b),1);
//         deg[a]++;deg[b]++;
//     }
//     vector<int>includeself(n+1,0);
//     vector<int>notinclude(n+1,0);
//     function<void(int,int)>dp = [&](int at,int par){
//         int total = 0;
//         for(Edge &e:G.adj[at]){
//             if(e.to == par)continue;
//             dp(e.to,at);
//             total += max(includeself[e.to],notinclude[e.to]);
//         }
//         notinclude[at] = total;
//         for(Edge &e:G.adj[at]){
//             if(e.to == par)continue;
//             else if(notinclude[e.to]>=includeself[e.to]){
//                 chkmax(includeself[at],total+1);
//             }
//             else{
//                 chkmax(includeself[at],total-includeself[e.to]+notinclude[e.to]+1);
//             }
//         }
//     };
//     dp(1,-1);
//     cout<<max(*max_element(all(includeself)),*max_element(all(notinclude)));
//     return 0;
// }



// /// greedy
// int32_t main(){
//     int n;cin>>n;
//     Graph g(n,false);
//     int a,b;
//     rep(i,0,n-1){
//         cin>>a>>b;
//         g.addEdge(a,b,0);
//     }
//     int ans = 0;
//     vector<bool>vis(n+1,false);
//     function<void(int,int)>bfs = [&](int at,int par){
//         for(Edge e:g.adj[at]){
//             if(e.to == par)continue;
//             bfs(e.to,at);
//             if(!vis[e.to] && !vis[at])vis[e.to]=vis[at]=true,ans++;
//         }
//     };
//     bfs(1,-1);
//     cout<<ans;
//     return 0;
// }