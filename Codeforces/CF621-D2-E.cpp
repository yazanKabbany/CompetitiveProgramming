/*
standard dp solution implemented using matrix exponentiation 
https://codeforces.com/blog/entry/23196
*/

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 105;
const ll mod = 1e9 + 7;

int cnt[12];

int x;

struct MATR
{
    ll a[N][N];
    MATR()
    {
        memset(a,0,sizeof a);
    }

    MATR mult(MATR other)
    {
        MATR res;
        for(int i=0;i<x;i++)
        {
            for(int j=0;j<x;j++)
            {
                for(int k=0;k<x;k++)
                {
                    res.a[i][j] += (a[i][k] * other.a[k][j]);
                    res.a[i][j] %= mod;
                }
            }
        }
        return res;
    }
};
MATR eye;

MATR power(MATR b, int n)
{
    if(!n)
        return eye;
    if(n & 1)
        return b.mult(power(b, n-1));
    MATR res = power(b, n/2);
    return res.mult(res);
}

MATR base;
void init()
{
    for(int i=0;i<x;i++)
        eye.a[i][i] = 1;

    for(int x=0;x<::x;x++)
    {
        for(int i=1;i<=9;i++)
        {
            base.a[x][(x*10 + i)%(::x)] += cnt[i];
        }
    }
}
int main()
{
    int n, b, k;
    scanf("%d %d %d %d", &n, &b, &k, &x);

    for(int i=0;i<n;i++)
    {
        int t;scanf("%d", &t);
        cnt[t]++;
    }
    init();
    MATR res = power(base, b);
    ll ans = 0;
    for(int i=0;i<x;i++)
        ans += res.a[i][k] * (i == 0);
    printf("%I64d\n", ans);
    return 0;
}
