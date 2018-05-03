#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int N = 2e5 + 10;
const int mod = 1e9 + 7;

struct SEG
{
    ll s, t;
}seg[N];

bool cmp_seg(const SEG &a,const SEG &b)
{
   if(a.t == b.t)
    return a.s > b.s;
   return a.t < b.t;

}
ll sum[N];
ll p_sum(int l,int r)
{
    if(l > r)
        return 0;
    ll res = sum[r] - (l > 0? sum[l-1]:0);
    res += mod;
    res %=mod;
    return res;
}
int main()
{
    int n, m;
    scanf("%d %d",&n, &m);
    seg[0] = {0, 0};
    for(int i=1;i<=m;i++)
    {
        int s, t;
        scanf("%d %d",&s,&t);
        seg[i] = {s, t};
    }
    sort(seg+1, seg+m+1, cmp_seg);
    sum[0] = 1;
    int rit = 0;
    for(int i=1;i<=m;i++)
    {
        sum[i] = sum[i-1];
        ll inf = mod;
        const SEG t = {inf, seg[i].s};
        int lef = lower_bound(seg, seg+m+1, t, cmp_seg) - seg;
        if(seg[i].t != seg[i-1].t)
            rit = i-1;

        sum[i] += p_sum(lef, rit);
        sum[i] %= mod;

    }
    ll ans = 0;
    for(int i=0;i<=m;i++)
    {
        if(seg[i].t == n)
            ans += p_sum(i, i), ans %= mod;
    }
    printf("%I64d\n", ans);
}
