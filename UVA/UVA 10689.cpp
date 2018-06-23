/*
used fibonacci numbers matrix method
*/

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int n = 2;
int mod = 10000;
struct MAT
{
    int a[3][3];
    MAT()
    {
        memset(a, 0, sizeof a);
    }
    MAT mult(const MAT &other)
    {
        MAT res;
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                for(int k=0;k<n;k++)
                    res.a[i][j] += a[i][k] * other.a[k][j]%mod, res.a[i][j]%=mod;
        return res;
    }
};
MAT base;
MAT eye;



MAT power(int n)
{
    if(!n)
        return eye;
    if(n&1)
        return base.mult(power(n-1));
    MAT res = power(n/2);
    return res.mult(res);
}

void init()
{
    eye.a[0][0] = 1;
    eye.a[1][1] = 1;
    base.a[0][1] = 1;
    base.a[1][1] = 1;
    base.a[1][0] = 1;
}
int main()
{
    init();
    MAT x = base.mult(base);
    int t;
    scanf("%d", &t);
    while(t--)
    {
        int a,b , n, m;
        scanf("%d %d %d %d", &a, &b, &n, &m);
        if(m == 1)
            mod=10;
        else if(m == 2)
            mod=100;
        else if(m == 3)
            mod = 1000;
        else
            mod = 10000;
        MAT res = power(n);
        int ans = (a*res.a[0][0]%mod)+(b*res.a[1][0]%mod);
        ans %= mod;
        printf("%d\n", ans);
    }
}
