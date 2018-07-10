/*
https://codeforces.com/blog/entry/52742
*/
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 2e5 + 10;
const ll inf = 1e16;
ll mod = 1e9 + 7;



ll power(ll b, int n)
{
    if(!n)
        return 1;
    if(n&1)
        return b*power(b,n-1)%mod;
    ll res = power(b,n/2);
    return res * res % mod;
}
ll inv(ll x)
{
    ll res = power(x, mod-2);
    return res;
}
ll fact[N];
ll inv_fact[N];
void init(int n)
{
    fact[0] = 1;
    inv_fact[0] = 1;
    for(int i=1;i<=n;i++)
    {
        fact[i] = (fact[i-1]*i)%mod;
        inv_fact[i] = inv(fact[i]);
    }
}
ll choose(ll n, ll k)
{
    ll res = fact[n];
    ll den = inv_fact[k] * inv_fact[n-k]%mod;
    res = res*den%mod;
    return res;
}

ll sum_all(vector<int>&v)
{
    ll res = 0;
    int n = v.size();
    for(int i=0;i<n;i++)
    {
        ll a = choose(n-1, i);
        res += a*v[i]%mod;
        res %= mod;
    }
    return res;
}
int main()
{
    int n;
    scanf("%d", &n);
    init(n);
    vector<int>vals(n);
    for(int i=0;i<n;i++)
    {
        int x;
        scanf("%d",&x);
        vals[i] = x;
    }
    if(n == 1)
    {
        printf("%d\n", vals[0]);
        return 0;
    }
    if(n &1)
    {
        vector<int>v;
        for(int i=1;i<n;i++)
        {
            int x;
            if(i&1)
                x = vals[i]+ vals[i-1];
            else
                x = vals[i-1]- vals[i]+mod;
            x%=mod;
            v.push_back(x);
        }
        vals = v;
    }
    ll res = 0;
    if((int)vals.size() == 2)
    {
        printf("%d\n",( vals[0] + vals[1])%mod);
        return 0;
    }

    vector<int>evens;
    vector<int>odds;
    for(int i=0;i<(int)vals.size();i++)
    {
        if(i&1)
            odds.push_back(vals[i]);
        else
            evens.push_back(vals[i]);
    }
    ll a = sum_all(evens);
    ll b = sum_all(odds);
    n = vals.size();
    if(n % 4 == 0)
        res = a-b+mod;
    else
        res = a + b;
    res %= mod;
    printf("%I64d\n", res);
}
