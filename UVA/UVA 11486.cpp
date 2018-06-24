/*
there are 35 valid state
make a transition matrix between states
use matrix matrix exponentiation to find the transition after n steps
*/
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
ll mod = 1e9 + 7;

struct MAT
{
    ll a[40][40];
    MAT()
    {
        memset(a, 0, sizeof a);
    }
    MAT mult(MAT other)
    {
        MAT res;
        for(int i=0;i<35;i++)
            for(int j=0;j<35;j++)
                for(int k=0;k<35;k++)
                    res.a[i][j] += a[i][k]*other.a[k][j]%mod, res.a[i][j] %= mod;
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

int state_number[400];
void init()
{
    vector<int>states;
    memset(state_number, -1, sizeof state_number);
    int cntr = 0;
    for(int i=0;i<7;i++)
        for(int j=i+1;j<7;j++)
            for(int k=j+1;k<7;k++)
                for(int l=k+1;l<7;l++)
                {
                    int state = 0;
                    state |= (1<<i);
                    state |= (1<<j);
                    state |= (1<<k);
                    state |= (1<<l);
                    state_number[state]=cntr++;
                    states.push_back(state);
                }
    for(auto state:states)
    {
        for(int msk = 0; msk < (1<<4);msk++)
        {
            int to = 0;
            for(int i=0, pos = 0;i<7;i++)if(state &(1<<i))
            {
                if((msk & (1<<pos)) && i<6)
                    to |= (1<<(i+1));
                else if(i)
                    to |= (1<<(i-1));
                pos++;
            }
            if(state_number[to] ==-1)
                continue;
            base.a[state_number[state]][state_number[to]] = 1;
        }
    }

    for(int i=0;i<35;i++)
        eye.a[i][i] = 1;
}
int main()
{


    init();
    int t;
    scanf("%d", &t);
    while(t--)
    {
        int n;
        scanf("%d", &n);
        int start_state = 0;
        for(int i=0;i<7;i++)
        {
            int x;
            scanf("%d", &x);
            if(x)
                start_state |= (1<<i);
        }
        int start_num = state_number[start_state];
        MAT mat = power(n-1);
        ll res = 0;
        for(int i=0;i<35;i++)
        {
            res += mat.a[start_num][i];
            res %= mod;
        }
        cout<<res<<'\n';
    }
}
