// Problem: Fixed_Length_Paths_I
// File: Fixed_Length_Paths_I.cpp
// Created: 2026-01-02
// Author: abhinav
//

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct CentroidDecomposition {
  ll n, k;
  // vector<ll> graph[200001];
  vector<vector<ll>> graph;
  // ll subtree[200001];
  vector<ll> subtree;
  ll ans = 0, mx_depth = 0;
  vector<ll> cnt;
  vector<bool> processed;
  // ll cnt[200001]{1}, mx_depth;
  // bool processed[200001];

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
    mx_depth = max(mx_depth, depth);
    if (filling)
      cnt[depth]++;
    else
      ans += cnt[k - depth];
    for (ll i : graph[node])
      if (!processed[i] && i != parent)
        get_cnt(i, node, filling, depth + 1);
  }

  void centroid_decomp(ll node = 1) {
    ll centroid = get_centroid(get_subtree_sizes(node) >> 1, node);
    processed[centroid] = true;
    mx_depth = 0;
    for (ll i : graph[centroid])
      if (!processed[i]) {
        get_cnt(i, centroid, false);
        get_cnt(i, centroid, true);
      }
    fill(cnt.begin() + 1, cnt.begin() + mx_depth + 1, 0);
    for (ll i : graph[centroid])
      if (!processed[i])
        centroid_decomp(i);
  }
};
int main() {
  cin.tie(0)->sync_with_stdio(0);
  ll n, k;
  cin >> n >> k;
  vector<vector<ll>> g(n + 1);
  for (ll i = 1; i < n; i++) {
    ll u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  CentroidDecomposition cd(n + 1, k, g);
  cd.centroid_decomp();
  cout << cd.ans;
  return 0;
}
