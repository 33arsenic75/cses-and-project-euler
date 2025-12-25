#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include<functional>
using namespace std;
using ll = long long;

// ------------------------------------------***--------------------------------------------------

#include <cstring>

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll a,b;cin>>a>>b;

    function<ll(ll)>count = [](ll num){
        if(num<0)return 0ll;
        string s = to_string(num);
        ll n = s.size();
        ll dp[n][10][2];
        memset(dp,-1,sizeof(dp));
        function<ll(ll)>exp = [&](int pow){
            if(pow==0)return 1ll;
            else if(pow==1)return 9ll;
            ll ans = exp(pow/2);
            ans *= ans;
            if(pow%2)ans*=9ll;
            return ans;
        };
        function<ll(ll,ll,ll)>memo = [&](ll i,ll lastdig, ll istight){
            if(i==n)return 1ll;
            else if(lastdig!=-2){
                if(dp[i][lastdig][istight]!=-1)return dp[i][lastdig][istight];
            }
            ll ans = 0;
            if(istight){
                for(ll j = 0 ; j < s[i]-'0'; j++){
                    if(lastdig==j)continue;
                    ans += memo(i+1,j,0);
                }
                ll j = s[i]-'0';
                if(j!=lastdig)ans += memo(i+1,j,1);
            }
            else{
                for(ll j = 0 ; j <= 9 ; j++){
                    if(lastdig==j)continue;
                    ans += memo(i+1,j,0);
                }
            }
            dp[i][lastdig][istight] = ans;
            // cout<<i<<" "<<lastdig<<" "<<istight<<" "<<dp[i][lastdig][istight]<<"\n";
            return ans;
        };
        ll ans = memo(1,s[0]-'0',1);
        // cout<<s<<" "<<ans<<' ';
        ll length = s.size() - 1;
        ans += (s[0]-'0')*exp(length);
        ans += (exp(length) - 1ll)/8ll;
        // cout<<ans<<'\n';
        return ans;
    };
    // count(b);
    // count(a-1);
    ll ans = count(b) - count(a - 1);
    cout<<max(0ll,ans);
    return 0;
}
