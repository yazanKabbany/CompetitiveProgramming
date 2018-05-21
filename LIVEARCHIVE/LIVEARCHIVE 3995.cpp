/*
dp with bitmask solution

dp[i][mask] is:
the answer to the problem for the first i row while choosing from the ith row cells similar a sub set of (mask)
*/

#include<bits/stdc++.h>
typedef long long ll;
using namespace std;


vector<int>masks;
int allowed[(1<<15) + 10];
vector<int>sub_bit[(1<<15) + 10];
int n;
int init_allowed(int msk)
{
    int res = msk;
    for(int i=0; i<n; i++)
    {
        if(msk & (1<<i))
        {
            if(i>0)
                res |= (1<<(i-1));
            if(i+1 < n)
                res |= (1<<(i+1));
        }
    }
    return ((1<<n)-1) ^ res;
}
bool valid_mask(int i)
{
    for(int j=0; j+1<n; j++)
        if((i & (1<<j)) && (i & (1<<(j+1))))
        {
            return false;
        }
    return true;
}
void init()
{

    for(int i=0; i<(1<<n); i++)
    {
        int msk = i;
        while(msk)
        {
            int bit = (msk & (msk-1))^msk;
            msk ^= bit;
            sub_bit[i].push_back(i ^ bit);
        }
    }

}
int dp[2][(1<<15) + 10];
int a[20][20];
int input[500];
int main()
{
    do
    {
        n = 0;
        do
        {
            if(scanf("%d", &a[0][n++]) == EOF)
                return 0;
        }
        while(getchar() != '\n');
        for(int i=1; i<n; i++)
            for(int j=0; j<n; j++)
                scanf("%d", &a[i][j]);
        getchar();
        init();
        for(int msk = 0; msk<(1<<n); msk++)
            {
                dp[0][msk] = 0;
                dp[1][msk] = 0;
            }
        for(int i=0; i<n; i++)
        {
            int cur = i & 1;
            for(int msk = 0; msk<(1<<n); msk++)
            {
                dp[cur][msk] = 0;
            }
            for(int msk=0; msk<(1<<n) ; msk++)
            {
                if(!valid_mask(msk))
                    continue;

                for(int j=0; j<n; j++)if(msk & (1<<j))
                        dp[cur][msk] += a[i][j];
                dp[cur][msk] += dp[!cur][allowed[msk]];
            }
            for(int msk = 0; msk<(1<<n); msk++)
            {
                for(auto sub_mask:sub_bit[msk])
                {
                    dp[cur][msk] = max(dp[cur][msk], dp[cur][sub_mask]);
                }
            }
        }
        int res = 0;
        for(int msk=0; msk<(1<<n) ; msk++)
        {
            if(!valid_mask(msk))
                continue;
            res = max(res, dp[!(n&1)][msk]);
        }
        printf("%d\n", res);

    }
    while(true);

    return 0;
}

