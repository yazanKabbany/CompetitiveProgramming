/*
https://codeforces.com/blog/entry/5251
*/
#include<bits/stdc++.h>


using namespace std;

typedef long long ll;
const ll mod = 1e9 + 7;

int m;
struct MAT
{
    ll a[55][55];
    MAT()
    {
        memset(a, 0, sizeof a);
    }

    MAT mult(const MAT &other)
    {
        MAT res;
        for(int i=0;i<m;i++)
            for(int j=0;j<m;j++)
                for(int k=0;k<m;k++)
                    res.a[i][j] += a[i][k] * other.a[k][j]%mod, res.a[i][j]%=mod;
        return res;
    }
};
MAT eye, base;
int forbids[55][55];
void init()
{
    for(int i=0;i<m;i++)
        eye.a[i][i] = 1;

    for(int i=0;i<m;i++)
        for(int j=0;j<m;j++)
        {
            base.a[i][j] = 1-forbids[i][j];
        }
}

MAT power(ll n)
{
    if(!n)
        return eye;
    if(n&1)
        return base.mult(power(n-1));
    auto res = power(n/2);
    return res.mult(res);

}
int c_to_int(char x)
{
    if(islower(x))
        return x-'a';
    else
        return x-'A' + 'z'-'a'+1;
}
int main()
{
    int  k;
    ll n;
    scanf("%I64d %d %d", &n, &m, &k);
    char s[10];
    for(int i=0;i<k;i++)
    {
        scanf("%s",s);
        forbids[c_to_int(s[0])][c_to_int(s[1])] = 1;
    }
    init();
    MAT mat = power(n-1);
    ll res = 0;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<m;j++)
        {
            res += mat.a[i][j];
            res %= mod;
        }
    }
    cout<<res<<'\n';
}
