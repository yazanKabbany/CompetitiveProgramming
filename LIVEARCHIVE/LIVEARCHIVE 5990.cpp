/*
subsets:
if min(a) != max(a)
  2^n - (2^(n-mx_count) + 2^(n-mx_count) - 2^(n-mx_count-mn_count))
else 
  2^n - 1
substrings:
if min(a) != max(a)
  n*(n+1)/2
else
  for each i calculate the number of substring that ends with a[i] and satisfies the conditions
*/

#include <bits/stdc++.h>
#include<sstream>
using namespace std;

typedef long long ll;

const int N = 1e5 + 10;
const ll mod = 1e9 + 7;

ll po[N];
void init()
{
    po[0] = 1;
    for(int i=1;i<=100000;i++)
    {
        po[i] = po[i-1]*2%mod;
    }
}

int a[N];
int n;
ll calc_substr()
{
    int mn = *min_element(a,a+n);
    int mx = *max_element(a,a+n);
    if(mn == mx)
    {
        ll res = 1LL*(n)*(n+1)/2;
        res %= mod;
        return res;
    }
    int lst_mn = -1;
    int lst_mx = -1;
    ll res = 0;
    for(int i=0;i<n;i++)
    {
        if(a[i] == mn)
            lst_mn = i;
        if(a[i] == mx)
            lst_mx = i;
        ll rit = min(lst_mx, lst_mn);
        res += rit+1;
        res %= mod;
    }
    return res;
}

ll calc_subsets()
{
    int mn = *min_element(a,a+n);
    int mx = *max_element(a,a+n);
    if(mn == mx)
    {
        ll res = po[n] - 1+mod;
        res %= mod;
        return res;
    }
    int mn_cnt = count(a,a+n, mx);
    int mx_cnt = count(a,a+n, mn);
    ll res = po[n - mn_cnt] + po[n - mx_cnt] - po[n-mn_cnt-mx_cnt];
    res += mod;
    res %= mod;
    res = po[n] - res + mod;
    res %= mod;
    return res;
}
int main()
{
    init();
    int t;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        for(int i=0;i<n;i++)
            scanf("%d", a+i);
        ll ans_str = calc_substr();
        ll ans_set = calc_subsets();
        cout<<ans_str<<' '<<ans_set<<'\n';
    }
    return 0;
}

