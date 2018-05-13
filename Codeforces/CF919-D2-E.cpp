/*
solved using baby step giant step algorithm
*/

#include<bits/stdc++.h>
typedef long long ll;
using namespace std;



ll a,b,p,x;
ll power(ll b, ll n)
{
    if(!n)
        return 1;
    if(n & 1)
        return b*power(b, n-1)%p;
    ll res = power(b, n/2);
    return res * res % p;
}
ll inv(ll x)
{
    return power(x, p-2);
}
ll mp[10000000];
ll calc_p_1(ll cnt, ll &b, ll mx = p)
{
//    map<ll, ll>mp;
    memset(mp, 0, sizeof mp);
    ll power = a;
    for(int i=1;i<=mx;i++)
    {
        mp[power*i%p]++;
        power *= a;
        power%=p;
    }
    ll res = 0;
    ll inv_a = inv(a);
    while(cnt > 0)
    {
        res += mp[b];
        b = b*inv_a%p;
        cnt -= p;
    }
    return res;
}
int main()
{
    cin>>a>>b>>p>>x;
    ll res = 0;
    if(x > p*(p-1))
    {
        ll t = b;
        ll cur = calc_p_1(p*(p-1), t);
        res += cur*(x/(p*(p-1)));
        x %= p*(p-1);
    }
    ll final_b = b;
    if(x > p)
    {
        ll cur = calc_p_1((x/(p))*(p), final_b);
        res += cur;
        x %= (p);
    }
    if(x)
    {
        ll cur = calc_p_1(x, final_b, x);
        res += cur;
    }
    cout<<res<<'\n';
    return 0;
}
