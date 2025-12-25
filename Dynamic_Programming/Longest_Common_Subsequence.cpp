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

    ll n, m;
    cin>>n>>m;
    vector<ll>a(n+1,0),b(m+1,0);
    fill(a,1,n+1);
    fill(b,1,m+1);
    vector<vector<ll>>dp(n+1,vector<ll>(m+1,0));
    rep(i,1,n+1){
        rep(j,1,m+1){
            dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            if(a[i]==b[j]){
                dp[i][j]=max(1+dp[i-1][j-1],dp[i][j]);
            }
        }
    }
    cout<<dp[n][m]<<"\n";
    int i = n, j = m;
    stack<ll>st;
    while(i>0 && j>0){
        if(dp[i][j] == 1 + dp[i-1][j-1] && a[i]==b[j]){
            st.push(a[i]);
            i--;
            j--;
        }
        else if(dp[i][j] == dp[i-1][j]){
            i--;
        }
        else{
            j--;
        }
    }
    while(!st.empty()){
        cout<<st.top()<<" ";
        st.pop();
    }
    return 0;
}
