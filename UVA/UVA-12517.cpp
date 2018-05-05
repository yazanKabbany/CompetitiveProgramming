#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


ll sum(ll x)
{
    return x*(x+1)/2;
}
ll dig_sum(ll x)
{
    ll  res = 0;
    while(x)
    {
        res += x%10;
        x /= 10;
    }
    return res;
}
ll f(ll x)
{
    if(!x)
        return 0;
    if(x%10 == 0)
        return  dig_sum(x)+f(x-1);
    if(x%10 == 9)
    {
        ll got = f(x/10)*10 + 45*(x/10+1);
        return got;
    }
    else
    {
        ll res = sum(x%10) + f(x - (x%10)) + dig_sum(x/10)*(x%10);
        return res;
    }
}
ll calc(int s, int t)
{
    ll res = f(t);
    res -= f(s-1);
    return res;
}
ll test(ll s, ll t)
{
    ll res= 0;
    for(int i = s;i<=t;i++)
    {
        int x=  i;
        while(x)
            res += x%10, x/=10;
    }
    return res;
}
int main()
{
    int s, t;
    while(scanf("%d %d", &s, &t) , s && t)
    {
        ll res = calc(s, t);
        printf("%lld\n", res);
//        cerr<<test(s, t)<<'\n';
    }
}
