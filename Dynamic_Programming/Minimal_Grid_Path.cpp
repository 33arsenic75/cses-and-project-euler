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


int32_t main(){
    ll n;
    cin >> n;
    vector<string> a(n);
    rep(i,0,n) cin >> a[i];

    queue<pair<ll,ll>> f, tf;
    f.push({0,0});

    string ans;
    ans.push_back(a[0][0]);

    vector<ll> dx = {0,1};
    vector<ll> dy = {1,0};

    auto inrange = [&](ll i, ll j){
        return (0 <= i && i < n && 0 <= j && j < n);
    };

    vector<vector<int>> used(n, vector<int>(n, -1));
    int iter = 0;

    while (ans.size() < 2*n - 1) {
        int best = 27;
        iter++;

        while (!f.empty()) {
            auto [x,y] = f.front(); f.pop();

            rep(d,0,2) {
                ll nx = x + dx[d];
                ll ny = y + dy[d];
                if (!inrange(nx,ny)) continue;

                int c = a[nx][ny] - 'A';

                if (c < best) {
                    best = c;
                    while (!tf.empty()) tf.pop();
                    iter++;
                }

                if (c == best && used[nx][ny] != iter) {
                    used[nx][ny] = iter;
                    tf.push({nx,ny});
                }
            }
        }

        ans.push_back(best + 'A');
        swap(f, tf);
    }

    cout << ans;

    return 0;
}
