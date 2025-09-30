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
 
void countingSort(vector<tuple<ll,ll,ll,ll>>& arr, int pos, ll exp) {
    int n = arr.size();
    vector<tuple<ll,ll,ll,ll>> output(n);
    vector<int> count(10, 0);

    auto getDigit = [&](ll num) {
        return (num / exp) % 10;
    };

    // Count digits at given position
    for (int i = 0; i < n; i++) {
        ll val;
        if (pos == 0) val = get<0>(arr[i]);
        else if (pos == 1) val = get<1>(arr[i]);
        else if (pos == 2) val = get<2>(arr[i]);
        else val = get<3>(arr[i]);

        int digit = getDigit(val);
        count[digit]++;
    }

    // Prefix sums
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Stable placement
    for (int i = n - 1; i >= 0; i--) {
        ll val;
        if (pos == 0) val = get<0>(arr[i]);
        else if (pos == 1) val = get<1>(arr[i]);
        else if (pos == 2) val = get<2>(arr[i]);
        else val = get<3>(arr[i]);

        int digit = getDigit(val);
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Copy back
    arr = output;
}

// Radix sort for one component of the tuple
void radixSortComponent(vector<tuple<ll,ll,ll,ll>>& arr, int pos) {
    ll maxVal = 0;
    for (auto &t : arr) {
        ll v = (pos==0? get<0>(t) : pos==1? get<1>(t) : pos==2? get<2>(t) : get<3>(t));
        maxVal = max(maxVal, v);
    }

    for (ll exp = 1; maxVal / exp > 0; exp *= 10)
        countingSort(arr, pos, exp);
}

// Full radix sort (lexicographic order)
void radixSortTuples(vector<tuple<ll,ll,ll,ll>>& arr) {
    // Sort starting from last to first component
    for (int pos = 3; pos >= 0; pos--) {
        radixSortComponent(arr, pos);
    }
}
 
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin>>n;
    vector<string>a(n);
    rep(i,0,n)cin>>a[i];
    function<ll(ll,ll)>isvalid = [&](ll x,ll y){
        return x>=0 && y>=0 && x<n && y<n;
    };
    vector<vector<ll>>dp(n,vector<ll>(n,LINF));
    vector<vector<ll>>rank(n,vector<ll>(n,LINF));
    rank[n-1][n-1] = 0;
    dp[n-1][n-1] = 0;
    // down = 1, right = 0
    for(ll k = 2 * n - 2 ; k >= 0 ; k--){
        vector<vector<tuple<ll,ll,ll,ll>>>v(26);
        for(int i = min(k, n - 1); i >= max(k - n, 0ll); i--){
            int j = k - i;
            if(!isvalid(i,j))continue;
            ll best = LINF, dir_ = -1;
            if(isvalid(i, j + 1)){
                if(rank[i][j+1]<best){
                    best = rank[i][j+1];
                    dir_ = 0;
                }
            }
            if(isvalid(i + 1, j)){
                if(rank[i+1][j]<best){
                    best = rank[i+1][j];
                    dir_ = 1;
                }
            }
            if(best==LINF)continue;
            v[(int)(a[i][j]-'A')].push_back({best,i,j,dir_});
        }
        int idx = 0;
        for(int i = 0 ; i < 26 ; i++){
            // sort(all(v[i]));
            radixSortTuples(v[i]);
            for(tuple<ll,ll,ll,ll> t: v[i]){
                int x = get<1>(t);
                int y = get<2>(t);
                int dir = get<3>(t);
                rank[x][y] = idx;
                dp[x][y] = dir;
                idx++;
            }
        }
    }
    int i = 0, j = 0;
    while(i<n && j<n){
        cout<<a[i][j];
        if(dp[i][j]==0)j++;
        else i++;
    }
    return 0;
}