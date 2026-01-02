// Problem: Fixed_Length_Paths_I
// File: Fixed_Length_Paths_II.cpp
// Created: 2026-01-02
// Author: abhinav
//

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct CentroidDecomposition {
  ll n, k1, k2;
  vector<vector<ll>> graph;
  vector<ll> subtree;
  ll ans = 0, mx_depth = 0, subtree_depth = 0;
  vector<ll> cnt;
  vector<ll> total_cnt;
  vector<bool> processed;
  CentroidDecomposition(ll _n, ll _k1, ll _k2, vector<vector<ll>> &g) {
    n = _n;
    k1 = _k1;
    k2 = _k2;
    graph = g;
    subtree.assign(_n + 1, 0);
    ans = 0;
    mx_depth = 0;
    cnt.assign(_n + 1, 0);
    total_cnt.assign(_n + 1, 0);
    total_cnt[0] = 1;
    processed.assign(_n + 1, false);
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

  void get_cnt(ll node, ll parent, ll depth = 1) {
    if (depth > k2)
      return;
    subtree_depth = max(subtree_depth, depth);
    cnt[depth]++;
    for (ll i : graph[node])
      if (!processed[i] && i != parent)
        get_cnt(i, node, depth + 1);
  }

  void centroid_decomp(ll node = 1) {
    ll centroid = get_centroid(get_subtree_sizes(node) >> 1, node);
    processed[centroid] = true;
    mx_depth = 0;
    ll partial_sum_init = (k1 == 1 ? 1ll : 0ll);
    for (ll i : graph[centroid]) {
      if (!processed[i]) {
        subtree_depth = 0;
        get_cnt(i, centroid);
        ll partial_sum = partial_sum_init;
        for (int depth = 1; depth <= subtree_depth; depth++) {
          ans += partial_sum * cnt[depth];
          ll dremove = k2 - depth;
          if (dremove >= 0)
            partial_sum -= total_cnt[dremove];
          ll dadd = k1 - depth - 1;
          if (dadd >= 0)
            partial_sum += total_cnt[dadd];
        }
        for (int depth = k1 - 1; depth <= k2 - 1 && depth <= subtree_depth;
             depth++)
          partial_sum_init += cnt[depth];

        for (int depth = 1; depth <= subtree_depth; depth++)
          total_cnt[depth] += cnt[depth];
        mx_depth = max(mx_depth, subtree_depth);
        fill(cnt.begin(), cnt.begin() + subtree_depth + 1, 0);
      }
    }
    fill(total_cnt.begin() + 1, total_cnt.begin() + mx_depth + 1, 0);

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
  CentroidDecomposition cd(n + 1, k1, k2, g);
  cd.centroid_decomp();
  cout << cd.ans;
  return 0;
}
