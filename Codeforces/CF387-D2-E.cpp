*/
https://codeforces.com/blog/entry/10583
*/
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

set<int>borders;
const int N = 1e6 + 10;
int a[N];
int pos[N];
int to_del[N];

int t[2*N];
int n;
void build()
{
        for(int i=0;i<n;i++)
            t[i+n] = 1;
        for(int i=n-1;i>0;i--)
            t[i] = t[i<<1] + t[i<<1|1];
}
int query(int l,int r)
{
    int res = 0;
    for(l += n, r+=n; l < r ; l>>=1, r>>=1)
    {
        if(l&1)res += t[l++];
        if(r&1)res += t[--r];
    }
    return res;
}
void update(int p, int v)
{
    for(t[p+=n] = v;p>1;p>>=1)
    {
        t[p>>1] = t[p] + t[p^1];
    }
}
int main()
{
    int k;
    scanf("%d %d", &n, &k);
    borders.insert(-1);
    borders.insert(n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",a+i);
        a[i]--;
        pos[a[i]] = i;
    }
    memset(to_del, 1, sizeof to_del);
    for(int i=0;i<k;i++)
    {
        int x;
        scanf("%d", &x);
        x--;
        to_del[x] = 0;
    }
    build();
    ll ans = 0;
    for(int i=0; i<n;i++)
    {
        if(!to_del[i])
        {
            borders.insert(pos[i]);
        }
        else
        {
            auto itr = borders.lower_bound(pos[i]);
            int r_border = *itr;
            itr--;
            int l_border = *itr;
            int cur = query(l_border+1, r_border);
            ans+=cur;
            update(pos[i], 0);
        }
    }
    cout<<ans<<'\n';
}
