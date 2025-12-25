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
    ll n,m;cin>>n>>m;
    vector<ll>par(n+1),sz(n+1,1ll);
    rep(i,1,n+1)par[i]=i;

    function<ll(ll)>head = [&](ll at){
        while(at!=par[at])at=par[at];
        return at;
    };
    function<ll(ll,ll)>merge = [&](ll i,ll j){
        ll h1 = head(i),h2 = head(j);
        if(h1==h2)return 0;
        else if(sz[h2]>sz[h1])swap(h1,h2);
        par[h2]=h1;
        sz[h1]+=sz[h2];
        ll next = 0;
        while(j!=h1){
            next = par[j];
            par[j]=h1;
            j = next;
        }
        while(i!=h1){
            next = par[i];
            par[i] = h1;
            i = next;
        }
        return 1;
    };
    ll total = n, mxsize = 1;
    while(m--){
        ll i,j;cin>>i>>j;
        total -= merge(i,j);
        ll siz = max(sz[head(i)],sz[head(j)]);
        if(siz>mxsize)mxsize=siz;
        cout<<total<<" "<<mxsize<<'\n';
    }
    return 0;
}
