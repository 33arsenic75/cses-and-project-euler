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


struct interval{
    int l,r;
    int idx;
    bool operator<(const interval &a)const{
        return make_pair(l,r)<make_pair(a.l,a.r);
    }
};

ostream& operator<<(ostream &os,interval a){
    return os<<a.l<<' '<<a.r<<' '<<a.idx<<'\n';
}

bool compare1(interval a,interval b){
    if(a.l==b.l)return a.r<b.r;
    return a.l>b.l;
}

bool compare2(interval a,interval b){
    if(a.l==b.l)return a.r>b.r;
    return a.l<b.l;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;cin>>n;
    vector<interval> a(n);
    rep(i,0,n)cin>>a[i].l>>a[i].r,a[i].idx=i;
    sort(all(a),compare2);
    int mny = a[n-1].r;
    vector<bool>a1(n,false),a2(n,false);
    for(int i = n-2 ; i >=0 ; i--){
        if(a[i].r>=mny){
            a1[a[i].idx]=true;
        }
        mny = min(mny,a[i].r);
    }
    sort(all(a),compare1);
    int mxy = a[n-1].r;
    for(int i = n-2 ; i>=0 ; i--){
        if(a[i].r<=mxy){
            a2[a[i].idx]=true;
        }
        mxy = max(mxy,a[i].r);
    }
    rep(i,0,n)cout<<a1[i]<<' ';
    cout<<'\n';
    rep(i,0,n)cout<<a2[i]<<' ';
    return 0;
}
