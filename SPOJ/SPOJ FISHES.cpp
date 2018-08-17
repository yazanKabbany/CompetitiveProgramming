/*
same solution as
https://github.com/yelghareeb/problem_solving/blob/master/SPOJ/SPOJ%20FISHES.cpp
but using O(n*n*n) algorithm to find sub rectangle with the maximum sum
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 105;
ll a[N][N];
ll sum[N][N];
ll vec[600];
int main()
{
    int s, T = 1;
    scanf("%d", &s);
    while(s--)
    {
        int r,c,h,k,t;
        scanf("%d %d %d %d %d", &r, &c, &h, &k, &t);
        for(int i=1;i<=r;i++)
            for(int j=1;j<=c;j++)
                scanf("%lld",&a[i][j]);
        for(int i=0;i<=k;i++)
            vec[i] = 0;
        for(int i=0;i<t;i++)
        {
            int x;
            scanf("%d", &x);
            for(int j=0;j<k;j++)
            {
                int y;
                scanf("%d", &y);
                vec[j] += 1LL*x*y;
            }
        }
        for(int i=1;i<=r;i++)
            for(int j=1;j<=c;j++)
                a[i][j] = vec[a[i][j]-1];
        for(int i=1;i<=r;i++)
            for(int j=1;j<=c;j++)
            {
                sum[i][j] = a[i][j] + sum[i-1][j];
            }
        ll mx = -1e12;
        for(int r1=1;r1<=r;r1++)
            for(int r2=r1;r2<=r;r2++)
            {
                ll cur = 0;
                for(int j=1;j<=c;j++)
                {
                    ll thi_col = sum[r2][j] - sum[r1-1][j];
                    cur += thi_col;
                    mx = max(cur, mx);
                    if(cur < 0)
                        cur = 0;
                }
            }
        mx += h;
        printf("Case #%d: %lld\n",T++, mx);
    }
}
