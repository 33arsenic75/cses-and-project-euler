// Problem: Salary Queries
// File: Salary_Queries.cpp
// Created: 2026-10-15
// Author: abhinav
// Link:
// Topic: Ordered Set
//

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef pair<int, int> pii;
typedef tree<pii, null_type, less<pii>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_multiset;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, q;
  cin >> n >> q;

  vector<int> a(n + 1);
  ordered_multiset ms;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    ms.insert({a[i], i}); // index i makes each pair unique
  }

  while (q--) {
    char t;
    int x, y;
    cin >> t >> x >> y;
    if (t == '!') {
      // employee x now has salary y
      ms.erase({a[x], x}); // erase by exact key
      a[x] = y;
      ms.insert({a[x], x});
    } else {
      // count salaries in [x, y]
      int hi = ms.order_of_key({y, INT_MAX}); // elements with salary <= y
      int lo = ms.order_of_key({x, 0});       // elements with salary <  x
      cout << hi - lo << '\n';
    }
  }
  return 0;
}
