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
#define py cout << "YES" << endl
#define pn cout << "NO" << endl
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
#define gcd __algo_gcd
#else
#define debug(x)
#endif


// ------------------------------------------***--------------------------------------------------





int32_t main() {
    int n,q;cin>>n>>q;
    vector<int>a(n+1,0);
    vector<int>pos(n+2,0);
    pos[0] = n+2;
    pos[n+1] = n+2;
    rep(i,1,n+1){
        cin>>a[i];
        pos[a[i]]=i;
    }
    int ans = 0;
    rep(i,0,n){
        if(pos[i]>pos[i+1])ans++;
    }
    int u,v;int x,y;
    set<int>st;
    while(q--){
        cin>>u>>v;
        x = a[u];y = a[v];
        st.clear();
        st.insert(x);st.insert(x+1);
        st.insert(y);st.insert(y+1);
        for(int z:st){
            if(pos[z-1]>pos[z])ans--;
        }
        swap(pos[x],pos[y]);
        swap(a[u],a[v]);
        for(int z:st){
            if(pos[z-1]>pos[z])ans++;
        }
        cout<<ans<<endl;
    }
    return 0;
}
       

