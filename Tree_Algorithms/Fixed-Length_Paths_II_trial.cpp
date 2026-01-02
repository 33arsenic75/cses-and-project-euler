#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct CentroidDecomposition {
  ll n, k;
  vector<vector<ll>> graph;
  vector<ll> subtree;
  ll ans = 0, mx_depth = 0, subtree_depth = 0;
  vector<ll> cnt;
  vector<bool> processed;
  vector<ll> runsum;
  CentroidDecomposition(ll _n, ll _k, vector<vector<ll>> &g) {
    n = _n;
    k = _k;
    graph = g;
    subtree.assign(_n + 1, 0);
    ans = 0;
    mx_depth = 0;
    cnt.assign(_n + 1, 0);
    cnt[0] = 1;
    processed.assign(_n + 1, false);
    runsum.assign(_n + 1, 1);
  }
  ll get_subtree_sizes(ll node, ll parent = 0) {
    subtree[node] = 1;
    for (ll i : graph[node])
      if (!processed[i] && i != parent)
        subtree[node] += get_subtree_sizes(i, node);
    return subtree[node];
  }

  ll get_centroid(ll desired, ll node, ll parent = 0) {
    for (ll i : graph[node])
      if (!processed[i] && i != parent && subtree[i] >= desired)
        return get_centroid(desired, i, node);
    return node;
  }

  void get_cnt(ll node, ll parent, bool filling, ll depth = 1) {
    if (depth > k)
      return;
    subtree_depth = max(subtree_depth, depth);
    if (filling)
      cnt[depth]++;
    else
      ans += runsum[max(0ll, min(k - depth, mx_depth))];
    for (ll i : graph[node])
      if (!processed[i] && i != parent)
        get_cnt(i, node, filling, depth + 1);
  }

  void centroid_decomp(ll node = 1) {
    ll centroid = get_centroid(get_subtree_sizes(node) >> 1, node);
    processed[centroid] = true;
    mx_depth = 0;
    // cout << "Processing Centroid " << centroid << "\n";
    // for (ll i = 0; i <= n; i++)
    //   cout << cnt[i] << " ";
    // cout << "\n";
    // for (ll i = 0; i <= n; i++)
    //   cout << runsum[i] << " ";
    // cout << "\n";
    for (ll i : graph[centroid]) {
      if (!processed[i]) {
        subtree_depth = 0;
        get_cnt(i, centroid, false);
        get_cnt(i, centroid, true);
        // cout << "Proccesing child " << i << " " << ans << "\n";

        mx_depth = max(mx_depth, subtree_depth);
        ll carry_sum = 0;
        for (ll i = 1; i <= n; i++) {
          carry_sum += cnt[i];
          runsum[i] += carry_sum;
        }
        // for (ll i = 0; i <= n; i++)
        //   cout << cnt[i] << " ";
        // cout << "\n";
        // for (ll i = 0; i <= n; i++)
        //   cout << runsum[i] << " ";
        // cout << '\n';

        fill(cnt.begin() + 1, cnt.begin() + subtree_depth + 1, 0);
      }
    }
    // fill(cnt.begin() + 1, cnt.end(), 0);
    fill(runsum.begin(), runsum.begin() + mx_depth + 1, 1);

    for (ll i : graph[centroid])
      if (!processed[i])
        centroid_decomp(i);
  }
};
int main() {
  cin.tie(0)->sync_with_stdio(0);
  ll n, k1, k2;
  cin >> n >> k1 >> k2;
  vector<vector<ll>> g(n + 1);
  for (ll i = 1; i < n; i++) {
    ll u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  CentroidDecomposition cd1(n + 1, k1 - 1, g), cd2(n + 1, k2, g);
  cd1.centroid_decomp();
  cd2.centroid_decomp();
  // cout << (cd1.ans) << "\n";
  // cout << (cd2.ans) << "\n";
  cout << cd2.ans - cd1.ans;
  return 0;
}
