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
    int n;
    queue<int> q;
    set<int> st;
    cin >> n;
    int x;
    int curr = 0; 
    int ans = 0;
    while (n--) {
        cin >> x;
        if (st.find(x) == st.end()) {
            st.insert(x);
            q.push(x);
            curr++;
        } else {
            while(st.find(x) != st.end()) {
                st.erase(q.front());
                q.pop();
                curr--;
            }
            q.push(x);
            st.insert(x);
            curr++;
        }
        ans = max(ans, curr);
    }
    cout << ans;
    return 0;
}