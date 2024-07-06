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
#include<cmath>
#include<numeric>
/// ordered sets support upperbound lowerbound too
#include <map>
#include <unordered_map>
#include <cstring>
#define len(v) (ll)v.size()
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back
#define rep(i, a, b) for (ll i = a; i < b; i++)
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
#else
#define debug(x)
#endif
const ll INF = 1e9;
const ll LINF = INF * INF;

// ------------------------------------------***--------------------------------------------------

ll gcd(ll a, ll b){
    if(b==0)return a;
    return gcd(b,a%b);
}

struct  Edge{
    ll from; ll to;
    ll weight;
    Edge(ll from, ll to, ll weight):from(from), to(to), weight(weight){
    }
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
    bool operator>(const Edge& other) const {
        return weight > other.weight;
    }
};

struct Graph{
    ll n;
    vector<vector<Edge>> adj;
    vector<Edge> edges;
    bool directed;
    Graph(ll n, bool directed):n(n),directed(directed){
        adj.resize(n+1);
    }
    void addEdge(ll from, ll to, ll weight){
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

vector<vector<ll>> scc(Graph G){
    ll n = G.n;
    vector<ll>ids(n+1,-1);
    vector<ll>lowlink(n+1,-1);
    vector<bool>onstack(n+1,false);
    vector<vector<ll>>ans;
    vector<vector<Edge>>adj = G.adj;
    ll id = 0;
    stack<ll>stk;
    vector<bool>vis(n+1,false);
    function<void(ll)>sccdfs = [&](ll at){
        id++;
        lowlink[at] = id;
        ids[at] = id;
        onstack[at] = true;
        stk.push(at);
        vis[at] = true;
        for(Edge e:adj[at]){
           if(ids[e.to]==-1)sccdfs(e.to);
           if(onstack[e.to])lowlink[at] = min(lowlink[at],lowlink[e.to]);
        }
        if(ids[at]==lowlink[at]){
            vector<ll>curr;
            while(stk.top() != at){
                ll node = stk.top();
                stk.pop();
                onstack[node] = false;
                lowlink[node] = ids[at];
                curr.push_back(node);
            }
            stk.pop();
            onstack[at] = false;
            curr.push_back(at);
            ans.push_back(curr);
        }
    };
    for(ll i = 0; i <= n ; i++){
        if(!vis[i])sccdfs(i);
    }
    return ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;cin>>n;
    Graph g(n,true);
    ll to;
    rep(i,1,n+1){
        cin>>to;
        g.addEdge(i,to,0);
    }
    vector<vector<ll>>component = scc(g);
    vector<ll>ans(n+1);
    vector<bool>incycle(n+1,false);
    vector<bool>vis(n+1,false);
    for(vector<ll>&v:component){
        if(v.size()>1){
            for(ll at:v){
                ans[at]=v.size();
                incycle[at]=true;
                vis[at]=true;
            }
        }
    }
    function<void(ll,ll)>dfs = [&](ll at, ll p){
        vis[at]=true;
        ll to = g.adj[at][0].to;
        if(!vis[to])dfs(to,at);
        ans[at] = 1 + ans[to];
    };
    rep(i,1,n+1){
        if(!vis[i])dfs(i,0);
    }
    rep(i,1,n+1)cout<<ans[i]<<" ";
    return 0;
}
