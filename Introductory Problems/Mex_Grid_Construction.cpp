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

void solve() {
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;cin>>n;
    vector<vector<ll>>a(n,vector<ll>(n,0));
    rep(i,0,n)a[i][0]=i, a[0][i]=i;

    // vector<vector<vector<int>>>cnt(n, vector<vector<int>>(n, vector<int>(2*n, 0)));
    vector<vector<int>>row_cnt(n, vector<int>(2*n, 0));
    vector<vector<int>>col_cnt(n, vector<int>(2*n, 0));
    rep(i,0,n){
        /// i, 0 -> i
        row_cnt[i][i]++;
        col_cnt[0][i]++;
        /// 0, i -> i
        row_cnt[0][i]++;
        col_cnt[i][i]++;
    }

    for(int i = 1 ; i < n ; i++){
        for(int j = 1 ; j < n ; j++){
            int mex = 0;
            rep(num,0,2*n){
                if(row_cnt[i][num] + col_cnt[j][num]== 0){
                    mex = num;
                    break;
                }
            }
            a[i][j] = mex;
            row_cnt[i][mex]++;
            col_cnt[j][mex]++;
        }
    }
    rep(i,0,n){
        rep(j,0,n)cout<<a[i][j]<<" ";
        cout<<"\n";
    }

    return 0;
}
