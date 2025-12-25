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
    ll n,m;cin>>n>>m;
    Graph g(n,false);
    ll a,b;
    rep(i,0,n-1){
        cin>>a>>b;
        g.addEdge(a,b,0);
    }
    vector<vector<ll>>p(n+1,vector<ll>(20,0));/// p[i][j] 2^jth ancestor of i 
    vector<ll>depth(n+1,0ll);
    function<void(ll,ll)>bfs = [&](ll at, ll par){
        for(Edge&e:g.adj[at]){
            if(e.to == par)continue;
            p[e.to][0] = at;
            depth[e.to] = 1 + depth[at];
            bfs(e.to,at);
        }
    };
    bfs(1,0);
    for(int j = 1 ; j < 20 ; j++){
        for(int i = 1 ; i <= n ; i++){
            p[i][j] = p[p[i][j-1]][j-1];
        }
    }
    function<ll(ll,ll)>up = [&](ll at,ll ht){
        int ans = at;
        for(int i = 0; i < 20; i++){
            if((ht>>i)&1){
                ans = p[ans][i];
            }
        }
        return ans;
    };
    // for(int i = 1; i <= n ; i++){
        // for(int j = 0 ; j < 20 ; j++)cout<<p[i][j]<<" ";
        // cout<<"\n";
    // }
    function<ll(ll,ll)>lca = [&](ll a,ll b){
        // cout<<a<<" "<<b<<" "<<depth[a]<<" "<<depth[b]<<" ";
        if(depth[a] > depth[b]){
            a = up(a,depth[a]-depth[b]);
        }
        else{
            b = up(b,depth[b]-depth[a]);
        }
        // cout<<a<<" "<<b<<" ";
        while(a!=b){
            for(int i = 19; i >= 0; i--){
                if(p[a][i] != p[b][i]){
                    a = p[a][i];
                    b = p[b][i];
                }
            }
            a = p[a][0];
            b = p[b][0];
        }
        if(a == 0)a = 1;
        // cout<<a<<'\n';
        return a;
    };
    vector<ll>ans(n+1,0);
    // vector<ll>ans2(n+1,0);
    while(m--){
        cin>>a>>b;
        ans[a]++;ans[b]++;
        int ancestor = lca(a,b);
        ans[ancestor]--;
        // ans2[ancestor]+=1;
        ans[p[ancestor][0]]--;
    }
    // show(ans);
    function<void(ll,ll)>bfs2 = [&](ll at, ll par){
        for(Edge&e:g.adj[at]){
            if(e.to==par)continue;
            bfs2(e.to,at);
            ans[at] += ans[e.to];
        }
    };
    bfs2(1,0);
    for(int i = 1 ; i <= n ; i++)cout<<ans[i]<<" ";
    return 0;
}
