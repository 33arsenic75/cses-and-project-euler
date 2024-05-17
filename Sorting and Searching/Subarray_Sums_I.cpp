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
    int n, x;cin>>n>>x;
    vector<int> arr(n);
    rep(i,0,n)cin>>arr[i];
    int sum = 0;
    int start = 0, end = -1;
    int cnt = 0;
    while (end < n) {
        while (end < n && sum < x) {
            end += 1;
            sum += arr[end];
        }
        while (start <= end && sum > x) {
            sum -= arr[start];
            start += 1;
        }
        if (sum == x) {
            cnt += 1;
            sum -= arr[start];
            start += 1;
        }
    }
    cout<<cnt;
  return 0;
}
