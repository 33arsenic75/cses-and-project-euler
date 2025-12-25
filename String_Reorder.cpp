// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC target("popcnt")
// #pragma GCC target("avx,avx2,fma")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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

void solve() {
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s; cin>>s;
    ll n = s.size();

    vector<ll>cnt(26,0);
    for(char c: s)cnt[c-'A']++;
    ll last_insert = -1;
    string ans(n,' ');
    
    rep(i,0,n){
        rep(j,0,26){
            if(cnt[j] && (j!=last_insert)){
                cnt[j]--;
                ans[i] = (char)('A'+j);
                last_insert=j;
                break;
            }
        }
    }

    if(ans.size()!=n){
        cout<<-1;
        return 0;
    }
    rep(i,1,n){
        if(ans[i]==ans[i-1]){
            cout<<-1;return 0;
        }
    }
    cout<<ans;
    /// AHA IT IT VT -> MY Ans
    /// AHA TI TI TVT -> Correct Anc
    return 0;
}
