#include <algorithm>
#include <complex>
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
#include <map>
#include <unordered_map>
#include <cstring>

using namespace std;
using ll = long long;
using ld = long double;
using cd = complex<ld>;
#define len(v) (ll)v.size()
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
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



const ld PI = acos(-1);

/* ================= FFT ================= */

void fft(vector<cd> &a, bool invert) {
    int n = a.size();
    static vector<int> rev;
    static vector<cd> roots{{0,0}, {1,0}};

    if ((int)rev.size() != n) {
        int k = __builtin_ctz(n);
        rev.assign(n, 0);
        for (int i = 0; i < n; i++)
            rev[i] = (rev[i>>1] >> 1) | ((i&1) << (k-1));
    }

    if ((int)roots.size() < n) {
        int k = __builtin_ctz(roots.size());
        roots.resize(n);
        while ((1 << k) < n) {
            ld angle = 2 * PI / (1 << (k+1));
            for (int i = 1 << (k-1); i < (1 << k); i++) {
                roots[2*i] = roots[i];
                ld ang = angle * (2*i + 1 - (1<<k));
                roots[2*i+1] = cd(cos(ang), sin(ang));
            }
            k++;
        }
    }

    for (int i = 0; i < n; i++)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);

    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += 2*len) {
            for (int j = 0; j < len; j++) {
                cd u = a[i+j];
                cd v = a[i+j+len] * roots[len+j];
                a[i+j] = u + v;
                a[i+j+len] = u - v;
            }
        }
    }

    if (invert) {
        reverse(a.begin() + 1, a.end());
        for (cd &x : a) x /= n;
    }
}

/* ========== REAL (FLOAT) CONVOLUTION ========== */

template<typename T>
vector<T> convolution_real(const vector<T> &a, const vector<T> &b) {
    int n = 1;
    while (n < (int)a.size() + (int)b.size())
        n <<= 1;

    vector<cd> fa(n), fb(n);
    for (int i = 0; i < (int)a.size(); i++) fa[i] = (ld)a[i];
    for (int i = 0; i < (int)b.size(); i++) fb[i] = (ld)b[i];

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);

    vector<T> res(n);
    for (int i = 0; i < n; i++)
        res[i] = (T)fa[i].real();

    return res;
}

/* ========== INTEGER (NO MOD) CONVOLUTION ========== */

template<typename T>
vector<ll> convolution_ll(const vector<T> &a, const vector<T> &b) {
    int n = 1;
    while (n < (int)a.size() + (int)b.size())
        n <<= 1;

    vector<cd> fa(n), fb(n);
    for (int i = 0; i < (int)a.size(); i++) fa[i] = (ld)a[i];
    for (int i = 0; i < (int)b.size(); i++) fb[i] = (ld)b[i];

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);

    vector<ll> res(n);
    for (int i = 0; i < n; i++)
        res[i] = (ll)(fa[i].real() + 0.5);

    return res;
}

/* ========== MOD CONVOLUTION ========== */

template<typename T>
vector<ll> convolution_mod(const vector<T> &a, const vector<T> &b, ll MOD) {
    vector<ll> A(a.begin(), a.end()), B(b.begin(), b.end());
    int n = 1;
    while (n < (int)A.size() + (int)B.size())
        n <<= 1;

    vector<cd> fa(n), fb(n);
    for (int i = 0; i < (int)A.size(); i++)
        fa[i] = cd(A[i] & 32767, A[i] >> 15);
    for (int i = 0; i < (int)B.size(); i++)
        fb[i] = cd(B[i] & 32767, B[i] >> 15);

    fft(fa, false);
    fft(fb, false);

    vector<cd> fa_fb(n), fa_conj_fb(n);
    for (int i = 0; i < n; i++) {
        int j = (n - i) & (n - 1);
        cd a1 = (fa[i] + conj(fa[j])) * cd(0.5, 0);
        cd a2 = (fa[i] - conj(fa[j])) * cd(0, -0.5);
        cd b1 = (fb[i] + conj(fb[j])) * cd(0.5, 0);
        cd b2 = (fb[i] - conj(fb[j])) * cd(0, -0.5);

        fa_fb[i] = a1 * b1 + cd(0,1) * a2 * b2;
        fa_conj_fb[i] = a1 * b2 + a2 * b1;
    }

    fft(fa_fb, true);
    fft(fa_conj_fb, true);

    vector<ll> res(n);
    for (int i = 0; i < n; i++) {
        ll x = (ll)(fa_fb[i].real() + 0.5) % MOD;
        ll y = (ll)(fa_conj_fb[i].real() + 0.5) % MOD;
        ll z = (ll)(fa_fb[i].imag() + 0.5) % MOD;
        res[i] = (x + (y << 15) + (z << 30)) % MOD;
    }
    return res;
}

/* ========== UNIFIED INTERFACE ========== */
#include <cassert>
template<typename T>
auto multiply(const vector<T> &a,
                 const vector<T> &b,
                 ll MOD = -1)
{
    if constexpr (is_floating_point_v<T>) {
        assert(MOD == -1 && "MOD convolution not supported for floating-point types");
        return convolution_real(a, b);      // vector<T>
    } else {
        if (MOD == -1)
            return convolution_ll(a, b);    // vector<ll>
        else
            return convolution_mod(a, b, MOD);
    }
}

int main(){
    ll n, m;
    cin>>n>>m;
    vector<ll>a(n,0), b(m,0);
    rep(i,0,n)cin>>a[i];
    rep(i,0,m)cin>>b[m-1-i];

    vector<ll>prd = convolution_ll(a, b);
    rep(i,0,n+m-1)cout<<prd[i]<<" ";
    return 0;   
}
