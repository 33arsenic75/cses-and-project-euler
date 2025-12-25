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


int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin>>n;
    vector<vector<ll>>a(n,vector<ll>(n,INT32_MAX));
    a[0][0]=0;
    function<bool(ll,ll)>isvalid=[&](ll x,ll y){
        if(x<0||y<0||x>=n||y>=n)return false;
        return true;
    };
    vector<ll>dx={2,2,-2,-2,1,1,-1,-1};
    vector<ll>dy={1,-1,1,-1,2,-2,2,-2};
    queue<pair<ll,ll>>q;
    q.push({0,0});
    while(!q.empty()){
        pair<ll,ll> cur=q.front();
        q.pop();
        ll x=cur.first,y=cur.second;
        rep(i,0,8){
            ll newx=x+dx[i],newy=y+dy[i];
            if(isvalid(newx,newy) && a[newx][newy]==INT32_MAX){
                a[newx][newy]=a[x][y]+1;
                q.push({newx,newy});
            }
        }
    }
    rep(i,0,n){
        rep(j,0,n)cout<<a[i][j]<<" ";
        cout<<"\n";
    }
    return 0;
}
