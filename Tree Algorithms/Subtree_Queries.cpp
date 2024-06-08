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

struct Node{
    int index;
    int value;
    int size;
    Node (int index, int value, int size):index(index), value(value), size(size){
    }
};

class SG{
public:
    vector<int>data;
    vector<int>tree;
    vector<int>marked;
    function<int(int,int)> operation;
    int n;
    int default_value;
    SG(int n, int default_value, function<int(int, int)> op){
        data.resize(n);
        tree.resize(4*n+1);
        marked.resize(4*n+1,false);
        operation = op;
        this->n = n;
        this->default_value = default_value;
        build();
    }
    void build(){
        build(1, 0, data.size()-1);
    }
    void build(int node, int start, int end){
        if(start == end){
            tree[node] = data[start];
        }
        else{
            int mid = (start + end) / 2;
            build(2*node, start, mid);
            build(2*node+1, mid+1, end);
            tree[node] = operation(tree[2*node], tree[2*node+1]);
        }
    }
    void push(int node){
        marked[2*node] = true;
        marked[2*node+1] = true;
        tree[2*node] = tree[node];    /// ------------> change based on function    
        tree[2*node+1] = tree[node];  /// ------------> change based on function
        marked[node] = false;
    }
    void update(int l, int r, int new_data){
        update(1, 0, data.size()-1, l, r, new_data);
    }
    void update(int node, int tl, int tr, int l, int r, int new_data){
        if(l > r)
            return;
        if(l == tl && r == tr){
            tree[node] = new_data;    /// -----------> change based on function
            marked[node] = true;
        }
        else{
            if(marked[node]){
                push(node);
            }
            int tm = (tl + tr) / 2;
            update(2*node, tl, tm, l, min(r, tm), new_data);
            update(2*node+1, tm+1, tr, max(l, tm+1), r, new_data);
            tree[node] = operation(tree[2*node], tree[2*node+1]);
        }
    }
    int query(int l, int r){
        return query(1, 0, n - 1, l, r);
    }
    int query(int node, int tl, int tr, int l, int r){
        if(l > r)
            return default_value;
        if(l == tl && r == tr)
            return tree[node];
        if(marked[node]){
            push(node);
        }
        int tm = (tl + tr) / 2;
        return operation(query(2*node, tl, tm, l, min(r, tm)), query(2*node+1, tm+1, tr, max(l, tm+1), r));
    }
    void print(int v,int tl, int tr){
        cout<<tl<<' '<<tr<<' '<<tree[v]<<'\n';
        if(tl!=tr){
            int tm = (tl+tr)/2;
            print(2*v,tl,tm);
            print(2*v+1,tm+1,tr);
        }
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;cin>>n>>q;
    vector<int>value(n+1,0);
    rep(i,1,n+1)cin>>value[i];

    vector<int>index(n+1,0);
    Graph g(n,false);
    vector<int>sz(n+1,0);
    int a,b;
    rep(i,0,n-1){
        cin>>a>>b;
        g.addEdge(a,b,0);
    }
    int pos = 0;
    vector<int>prefix(n+1,0);
    function<void(int,int)>dfs = [&](int at,int par){
        pos++;
        index[at]=pos;
        prefix[pos] = value[at];
        sz[at] = 1;
        for(Edge e:g.adj[at]){
            if(e.to!=par){
                dfs(e.to,at);
                sz[at]+=sz[e.to];
            }
        }
    };
    dfs(1,0);
    SG sg(n+1,0,[](int a, int b){return a+b;});
    sg.data = prefix;
    sg.build();
    while(q--){
        int t;cin>>t;
        if(t==1){
            int s,x;
            cin>>s>>x;

            sg.update(index[s],index[s],x);
        }
        else{
            int s;cin>>s;
            cout<<sg.query(index[s],index[s]+sz[s]-1)<<'\n';
        }
    }
    return 0;
}
