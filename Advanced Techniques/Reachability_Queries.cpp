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
    bool visited;
    Edge(ll from, ll to, ll weight):from(from), to(to), weight(weight){
        visited=false;
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

/// O(V+E)
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

/// O(ElogE)
class UF {
public:
  ll *id, cnt, *sz;
  // Create an empty union find data structure with N isolated sets.
  UF(ll N) {
    cnt = N; id = new ll[N]; sz = new ll[N];
    for (ll i = 0; i<N; i++)  id[i] = i, sz[i] = 1; }
  ~UF() { delete[] id; delete[] sz; }
  // Return the id of component corresponding to object p.
  ll find(ll p) {
    ll root = p;
    while (root != id[root])    root = id[root];
    while (p != root) { ll newp = id[p]; id[p] = root; p = newp; }
    return root;
  }
  // Replace sets containing x and y with their union.
  void merge(ll x, ll y) {
    ll i = find(x); ll j = find(y); if (i == j) return;
    // make smaller root poll to larger one
    if (sz[i] < sz[j]) { id[i] = j, sz[j] += sz[i]; }
    else { id[j] = i, sz[i] += sz[j]; }
    cnt--;
  }
  // Are objects x and y in the same set?
  bool connected(ll x, ll y) { return find(x) == find(y); }
  // Return the number of disjoll sets.
    ll count() { return cnt; }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, m, q;
    cin>>n>>m>>q;
    Graph g(n, true);

    ll a,b;
    rep(i,0,m){
        cin>>a>>b;
        g.addEdge(a, b, 0);
    }

    vector<vector<ll>>sc = scc(g);
    map<ll,ll>rep;
    ll idx = 0;
    for(vector<ll>&v: sc){
        for(ll i: v)rep[i] = idx;
        idx ++;
    }

    ll num_comp = sc.size();
    ll M = (num_comp + 63)/64;

    vector<vector<ll>>adj(num_comp);
    for(Edge&e: g.edges){
        if(rep[e.from] != rep[e.to]){
            adj[rep[e.from]].pb(rep[e.to]);
        }
    }

    rep(i,0,num_comp){
        sort(all(adj[i]));
        adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
    }
    
    vector<vector<ll>>bt(num_comp, vector<ll>(M,0));
    vector<bool>call(num_comp,false);

    function<void(ll)> calc = [&](int at){
        if(call[at])return;
        for(ll to:adj[at]){
            calc(to);
            rep(idx,0,M)bt[at][idx] |= bt[to][idx];
        }
        call[at]=true;
    };

    rep(i,0,num_comp){
        ll idx1 = i >> 6;
        ll idx2 = i & 63;
        bt[i][idx1] |= (1ll << idx2);
    }
    rep(i,0,num_comp)calc(i);

    rep(i,0,q){
        cin>>a>>b;
        a = rep[a];
        b = rep[b];
        ll idx1 = b >> 6;
        ll idx2 = b & 63;

        if( (bt[a][idx1] >> idx2)&1 )py;
        else pn;
    }
    /// O(n+m) -> Total Algorithm
    return 0;
}
