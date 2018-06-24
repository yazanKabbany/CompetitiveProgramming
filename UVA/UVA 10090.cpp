/*
  find a and b such that (a*n1 + b*n2) == n and (a*c1 + b*c2) is minimum
  try every a from 0 to sqrt(n) and calculate b
  try every b from 0 to sqrt(b) and calculate a
  output the best a, b
*/
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
ll mod = 1e9 + 7;

ll inf = 1e17;
ll n;

ll calc(ll a, ll n1, ll c1, ll n2, ll c2)
{
    ll took = a*n1;
    ll b = (n - took)/n2;
    if(a*n1 + b*n2 != n ||b<0)
        return inf;
    ll res = a*c1 + b*c2;
    return res;
}

pair<ll, ll> get_ans(ll n1, ll c1, ll n2, ll c2)
{
    ll res = inf;
    ll a = -1, b= -1;
    for(ll i = 0; (i*i)<=4*n;i++)
    {
        ll cur = calc(i, n1, c1, n2, c2);
        if(cur < res)
        {
            a = i;
            b = (n - a*n1)/n2;
            res = min(res, cur);
        }
        ll cur2 = calc(i, n2, c2, n1, c1);
        if(cur2 < res)
        {
            b = i;
            a = (n - b*n2)/n1;
            res = min(res, cur2);
        }
    }
//    cerr<<"cost "<<res<<'\n';
    return {a,b};
}

int main()
{
    while(scanf("%lld", &n), n)
    {
        ll n1, c1, n2, c2;
        scanf("%lld %lld %lld %lld", &n1, &c1, &n2, &c2);
        auto res = get_ans(c1, n1, c2, n2);
        if(res.first==-1)
        {
            puts("failed");
            continue;
        }
        printf("%lld %lld\n",res.first, res.second);
    }

}
