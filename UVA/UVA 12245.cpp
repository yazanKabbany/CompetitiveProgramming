/*
0 1 dp
we can take a range if doesn't cover another taken range and is not coverd by it
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll mod = 1e8;
const int N = 109;
pair<int,int>a[N];
ll dp[N][2*N][2*N];

int n, m;
ll calc(int i, int lst_rit, int bef_lst_rit)
{
    if(i == n)
        return lst_rit == m;
    ll &res = dp[i][lst_rit+1][bef_lst_rit+1];
    if(res != -1)
        return res;
    res= 0;
    if(bef_lst_rit<a[i].first && lst_rit < a[i].second&& lst_rit >= a[i].first)
    {
        ll cur = calc(i+1,a[i].second,lst_rit);
        res += cur;
        res %= mod;
    }
    res += calc(i+1, lst_rit, bef_lst_rit);
    res %= mod;
    return res;
}
int main()
{
    while(scanf("%d %d", &m, &n), n||m)
    {
        vector<int>vals;
//        vals.push_back(-1);
//        vals.push_back(1e9);
        for(int i=0;i<n;i++)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            a[i] = {x, y};
            vals.push_back(x);
            vals.push_back(y);
        }
        sort(vals.begin(), vals.end());
        vals.resize(unique(vals.begin(), vals.end())-vals.begin());
        sort(a,a+n);
        bool has_zero = false;
        for(int i=0;i<n;i++)
        {
            has_zero = has_zero || !a[i].first;
            a[i].first = lower_bound(vals.begin(), vals.end(), a[i].first)-vals.begin();
            a[i].second = lower_bound(vals.begin(), vals.end(), a[i].second)-vals.begin();
        }
        m = lower_bound(vals.begin(), vals.end(), m)-vals.begin();
        memset(dp, -1, sizeof dp);
        ll res = 0;
        if(has_zero)
            res = calc(0, 0, -1);
        printf("%lld\n", res);
    }

}
