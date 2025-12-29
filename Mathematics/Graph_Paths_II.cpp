#include <algorithm>
#include <bitset>
#include <cassert>
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

/* Matrix structure */
struct Matrix {
    int n;
    vector<vector<ll>> a;
    ll MOD;
    Matrix(int n_, bool ident = false, ll MOD_ = LINF + INF ): n(n_) {
        a.assign(n, vector<ll>(n, MOD_));
        MOD = MOD_;
        if (ident) {
            for (int i = 0; i < n; i++){
                a[i][i] = 0;
            }
        }
    }
};

/* Matrix multiplication */
Matrix operator*(const Matrix &A, const Matrix &B) {
    int n = A.n;
    Matrix C(n, false, A.MOD);
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                C.a[i][j] = min(C.a[i][j], A.a[i][k] + B.a[k][j]);
            }
        }
    }
    return C;
}

/* Matrix exponentiation */
Matrix mpow(Matrix base, long long exp) {
    if(exp==0){
        Matrix M(base.n, true);
        return M;
    }
    Matrix M = mpow(base, exp/2);
    // cout<<"Partial M: \n";
    // rep(i,0,M.n){
    //     rep(j,0,M.n)cout<<M.a[i][j]<<" ";
    //     cout<<'\n';
    // }
    M = M*M;
    // cout<<"Partial M: \n";
    // rep(i,0,M.n){
    //     rep(j,0,M.n)cout<<M.a[i][j]<<" ";
    //     cout<<'\n';
    // }

    if(exp&1)M = M*base;
    // cout<<"Partial M: \n";
    // rep(i,0,M.n){
    //     rep(j,0,M.n)cout<<M.a[i][j]<<" ";
    //     cout<<'\n';
    // }

    return M;
}

/*
  Computes A[n] given:
  - recurrence coefficients C[1..K]
  - initial values A[0..K-1]
*/
ll linear_recurrence(
    vector<ll> C,        // size K
    vector<ll> A,        // size K
    long long n,
    long long MOD = (1e9+7)
) {
    int K = C.size();

    if (n < K)
        return A[n] % MOD;

    // Build transition matrix
    Matrix T(K, false, MOD);

    // First row
    for (int i = 0; i < K; i++)
        T.a[0][i] = C[i] % MOD;

    // Subdiagonal
    for (int i = 1; i < K; i++)
        T.a[i][i - 1] = 1;

    // Exponentiate
    T = mpow(T, n - K + 1);

    // Base vector
    ll ans = 0;
    for (int i = 0; i < K; i++) {
        ans = (ans + T.a[0][i] * A[K - 1 - i]) % MOD;
    }

    return ans;
}


int main(){
    ll n, m, k;
    cin >> n >> m >> k;
    ll MOD = LINF + INF;

    Matrix M(n, false, MOD);

    ll u, v, c;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> c;
        M.a[u-1][v-1] = min(M.a[u-1][v-1], c);  // directed
    }
    // rep(i,0,n){
    //     rep(j,0,n)cout<<M.a[i][j]<<" ";
    //     cout<<'\n';
    // }
    M = mpow(M, k);
    // rep(i,0,n){
    //     rep(j,0,n)cout<<M.a[i][j]<<" ";
    //     cout<<'\n';
    // }
    if(M.a[0][n-1] >= MOD)M.a[0][n-1]=-1;
    cout << M.a[0][n-1];
}
