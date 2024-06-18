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
    vector<string>a(n);
    rep(i,0,n)cin>>a[i];
    ll dx[4] = {0,0,1,-1}, dy[4] = {1,-1,0,0};
    function<bool(ll,ll)>valid = [&](ll i,ll j){
        return (i>=0) && (i<n) && (j<m) && (j>=0) && ( (a[i][j]=='.') || (a[i][j]=='A') );
    };

    vector<bool>visA(n*m+1,false),visM(n*m+1,false);
    vector<ll>disA(n*m+1,LINF),parA(n*m+1,0);
    vector<ll>disM(n*m+1,LINF),parM(n*m+1,0);
    ll x = -1,y = -1;
    function<void(void)>bfsA =[&](){
        queue<ll>q;
        rep(i,0,n){
            rep(j,0,m){
                if(a[i][j]=='A'){
                    q.push(i*m+j);
                    x = i, y = j;
                    disA[i*m+j] = 0;
                }
            }
        }
        while(!q.empty()){
            ll at = q.front(); q.pop();
            rep(k,0,4){
                int newy = at%m;
                int newx = (at - newy)/m;
                newy += dy[k], newx +=dx[k];
                // debug(newx),debug(newy);
                if(valid(newx,newy) && disA[newx*m + newy] > 1 + disA[at]){
                    parA[newx*m+newy] = at;
                    disA[newx*m+newy] = 1 + disA[at];
                    q.push(newx*m+newy);
                }
            }
        }
    };
    function<void(void)>bfsM =[&](){
        queue<ll>q;
        rep(i,0,n){
            rep(j,0,m){
                if(a[i][j]=='M'){
                    q.push(i*m+j);
                    disM[i*m+j] = 0;
                }
            }
        }
        while(!q.empty()){
            ll at = q.front(); q.pop();
            rep(k,0,4){
                int newy = at%m;
                int newx = (at - newy)/m;
                newy += dy[k], newx +=dx[k];
                if(valid(newx,newy) && disM[newx*m + newy] > 1 + disM[at]){
                    disM[newx*m+newy] = 1 + disM[at];
                    parM[newx*m+newy] = at;
                    q.push(newx*m+newy);
                }
            }
        }
    };
    bfsA();bfsM();
    // for(int i = 0 ; i < n ; i++){
        // for(int j = 0  ; j < m ; j++){
            // if(disA[i*m+j]==LINF)cout<<"INF ";
            // else cout<<disA[i*m+j]<<"   ";
        // }
        // cout<<'\n';
    // }
    // cout<<"\n";
    // for(int i = 0 ; i < n ; i++){
        // for(int j = 0  ; j < m ; j++){
            // if(disM[i*m+j]==LINF)cout<<"INF ";
            // else cout<<disM[i*m+j]<<"   ";
        // }
        // cout<<'\n';
    // }
    int target = -1;
    for(int i = 0; i < m ; i++){
        if(disA[i] < disM[i])target = i;
    }
    for(int i = 0; i < m ; i++){
        if(disA[(n-1)*m + i] < disM[(n-1)*m + i])target = (n-1)*m + i;
    }    
    for(int i = 0; i < n ; i++){
       if(disA[i*m] < disM[i*m])target = i*m;
    }
    for(int i = 0; i < n ; i++){
       if(disA[i*m + m - 1] < disM[i*m + m - 1])target = i*m + m - 1;
    }
    if(target == -1 ){
        pn;return 0;
    }
    vector<ll>path;
    while(target != x*m + y){
        path.push_back(target);
        target = parA[target];
    }
    path.push_back(x*m+y);
    reverse(all(path));
    py;
    ll length = path.size() - 1;
    cout<<length<<'\n';
    for(ll i = 0 ; i < length ; i++){
        ll dist = path[i+1]-path[i];
        if(dist==1)cout<<"R";
        else if(dist==-1)cout<<"L";
        else if(dist==m)cout<<"D";
        else if(dist==-m)cout<<"U";
    }
    return 0;
}
