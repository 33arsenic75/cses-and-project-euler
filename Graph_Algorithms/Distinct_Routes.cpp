#include <algorithm>
#include <climits>
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
#define len(v) (ll)v.size()
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
using namespace std;
#define ll long long
#define pb push_back
#define rep(i, a, b) for (ll i = a; i < b; i++)
#define f first
#define mk make_pair
#define in insert
#define py cout << "YES\n"
#define pn cout << "NO\n"
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

// ------------------------------------------***--------------------------------------------------

const ll INF = 1e9;
const ll LINF = INF * INF;

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

/// O(V+E)
vector<ll> toposort(Graph G){
    ll n = G.n;
    vector<vector<Edge>>adj = G.adj;
    vector<ll>indegree(n+1,0);
    for(ll i = 0; i <= n; i++){
        for(Edge e:adj[i]){
            indegree[e.to]++;
        }
    }
    queue<ll>q;
    vector<ll>par(n+1);
    for(ll i = 0; i <= n; i++){
        if(indegree[i]==0)q.push(i),par[i] = -1;
    }
    vector<ll>ans;
    while(!q.empty()){
        ll at = q.front();
        q.pop();
        ans.push_back(at);
        for(Edge e:adj[at]){
            indegree[e.to]--;
            if(indegree[e.to]==0)q.push(e.to),par[e.to]=at;
        }
    }
    return ans;
}

/// O(V + ElogV)
vector<ll> shortestPathSingleSource(Graph G, ll start){
    ll n = G.n;
    vector<vector<Edge>>adj = G.adj;
    vector<ll>dist(n+1,LINF);
    dist[start] = 0;
    priority_queue<Edge,vector<Edge>,greater<Edge>>pq;
    pq.push(Edge(-1,start,0));
    vector<ll>par(n+1,-1);
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
    return dist;
}

/// O(V^3)
vector<vector<ll>> shortestPathAllPairs(Graph G){
    ll n = G.n;
    vector<vector<Edge>>adj = G.adj;
    vector<vector<ll>>dist(n+1,vector<ll>(n+1,INF));
    for(ll i = 0; i <= n; i++){
        dist[i][i] = 0;
    }
    for(ll i = 0; i <= n; i++){
        for(Edge e:adj[i]){
            dist[e.from][e.to] = e.weight;
        }
    }
    for(ll k = 0; k <= n; k++){
        for(ll i = 0; i <= n; i++){
            for(ll j = 0; j <= n; j++){
                if(dist[i][k]<INF && dist[k][j]<INF){
                    dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);
                }
            }
        }
    }
    return dist;
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
vector<Edge> mst(Graph G){
    ll n = G.n;
    vector<Edge>edges = G.edges;
    vector<bool>vis(n+1,false);
    vector<Edge>ans;
    priority_queue<Edge,vector<Edge>,greater<Edge>>pq(all(edges));
    UF uf(n+1);
    ll mincost = 0;
    while(!pq.empty()){
        Edge e = pq.top();
        pq.pop();
        if(!uf.connected(e.from,e.to)){
            uf.merge(e.from,e.to);
            ans.push_back(e);
            mincost+=e.weight;
        }
    }
    bool mstexist = (ans.size()==n-1);
    return ans;
}

void bfs(Graph G,ll start,vector<bool>&vis,vector<ll>&par,vector<ll>&dist){
    if(vis[start])return;
    vis[start] = true;
    for(Edge e:G.adj[start]){
        if(!vis[e.to]){
            par[e.to] = start;
            dist[e.to] = dist[start]+1;
            bfs(G,e.to,vis,par,dist);
        }
    }
}

void eulertour(Graph G,vector<ll>&start,vector<ll>&end){
    ll time = 0;
    function<void(ll,ll)>euler = [&](ll at, ll parent){
        start[at] = time++;
        for(Edge e:G.adj[at]){
            if(e.to!=parent){
                euler(e.to,at);
            }
        }
        end[at] = time;
    };
    euler(1,0);
}


struct Dinic {
    struct Edge {
        ll to;
        ll cap;
        ll flow;
        int rev;
    };

    ll n;
    vector<vector<Edge>> adj;
    vector<ll> level, it;
    
    struct NormalEdges {
        ll from;
        ll to;
        ll cap;
    };

    vector<NormalEdges>originalEdges;

    Dinic(ll n) : n(n) {
        adj.resize(n + 1);
        level.resize(n + 1);
        it.resize(n + 1);
    }

    void addEdge(ll u, ll v, ll cap) {
        Edge a = {v, cap, 0, (int)adj[v].size()};
        Edge b = {u, 0,   0, (int)adj[u].size()};
        adj[u].push_back(a);
        adj[v].push_back(b);
        NormalEdges e = {u, v, cap};
        originalEdges.push_back(e);
    }

    bool bfs(ll s, ll t) {
        fill(level.begin(), level.end(), -1);
        queue<ll> q;
        level[s] = 0;
        q.push(s);

        while (!q.empty()) {
            ll u = q.front(); q.pop();
            for (auto &e : adj[u]) {
                if (level[e.to] < 0 && e.flow < e.cap) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] >= 0;
    }

    ll dfs(ll u, ll t, ll f) {
        if (u == t) return f;
        for (ll &i = it[u]; i < (ll)adj[u].size(); i++) {
            Edge &e = adj[u][i];
            if (e.flow < e.cap && level[e.to] == level[u] + 1) {
                ll pushed = dfs(e.to, t, min(f, e.cap - e.flow));
                if (pushed > 0) {
                    e.flow += pushed;
                    adj[e.to][e.rev].flow -= pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    ll maxFlow(ll s, ll t) {
        ll flow = 0;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            while (ll pushed = dfs(s, t, LLONG_MAX)) {
                flow += pushed;
            }
        }
        return flow;
    }

    // -------- MIN CUT COMPONENTS --------
    vector<vector<ll>> minCutComponents(ll s) {
        vector<bool> vis(n + 1, false);
        queue<ll> q;
        q.push(s);
        vis[s] = true;

        // reachable from s in residual graph
        while (!q.empty()) {
            ll u = q.front(); q.pop();
            for (auto &e : adj[u]) {
                if (!vis[e.to] && e.flow < e.cap) {
                    vis[e.to] = true;
                    q.push(e.to);
                }
            }
        }

        vector<ll> S, T;
        for (ll i = 1; i <= n; i++) {
            if (vis[i]) S.push_back(i);
            else T.push_back(i);
        }

        return {S, T};
    }
};

int main(){
    ll n, m;
    cin>>n>>m;
    
    Dinic d(n);
    ll a, b;
    rep(i,0,m){
        cin>>a>>b;
        d.addEdge(a, b, 1);
    }
    cout<<d.maxFlow(1, n)<<'\n';


    vector<vector<ll>> flowAdj(n + 1);

    // Build graph of used flow edges
    for (ll i = 1; i <= n; i++) {
        for (auto &e : d.adj[i]) {
            if (e.cap > 0 && e.flow > 0) {
                flowAdj[i].push_back(e.to);
            }
        }
    }

    vector<vector<ll>> paths;
    vector<ll> cur;

    // DFS to extract one path
    function<bool(ll)> dfs = [&](ll u) -> bool {
        cur.push_back(u);
        if (u == n) return true;

        for (int i = 0; i < (int)flowAdj[u].size(); i++) {
            ll v = flowAdj[u][i];
            flowAdj[u].erase(flowAdj[u].begin() + i);  // consume edge
            if (dfs(v)) return true;
            flowAdj[u].insert(flowAdj[u].begin() + i, v); // backtrack
        }

        cur.pop_back();
        return false;
    };

    // Extract all paths
    while (true) {
        cur.clear();
        if (!dfs(1)) break;
        paths.push_back(cur);
    }
    for (auto &p : paths) {
        cout<<p.size()<<"\n";
        for (ll x : p) cout << x << " ";
        cout << "\n";
    }

    return 0;
}
