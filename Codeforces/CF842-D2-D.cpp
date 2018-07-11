/*
https://codeforces.com/blog/entry/54179
*/

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 6e6 + 10;
const int LOG = 19;


int x[N][2];
int cnt[N];
int flipped[N];
int nex = 1;

void build(int s)
{
    int i=LOG-1, v = 0;
    while(i >=0 )
    {
        cnt[v]++;
        int to = (s>>i)&1;
        if(x[v][to] != -1)
            v = x[v][to];
        else
            v = x[v][to]=nex++;
        i--;
    }
    cnt[v]++;
}

int mex()
{
    int res = 0;
    int i=LOG-1, v = 0;
    int choosen = 0;
    while(i>=0)
    {
        int lef = 0, rit = 1;
        if(flipped[i])
            swap(lef, rit);
        if(x[v][lef] == -1)
            return res;
        int expected_left = 1<<(LOG-choosen-1);
        if(cnt[x[v][lef]] < expected_left)
        {
            v = x[v][lef];
        }
        else
        {
            res |= (1<<(i));
            v = x[v][rit];
            if(v == -1)
                return res;
        }
        i--;
        choosen++;
    }
    return res;
}

int main()
{
    memset(x, -1, sizeof x);
    int n, m;
    scanf("%d %d", &n, &m);
    set<int>s;
    for(int i=0;i<n;i++)
    {
        int x;
        scanf("%d", &x);
        s.insert(x);
    }
    for(auto x:s)
    {
        build(x);
    }
    for(int i=0;i<m;i++)
    {
        int x;
        scanf("%d",&x);
        for(int j=0;j<LOG;j++)
        {
            if((1<<j)&x)
                flipped[j]^=1;
        }
        int res = mex();
        printf("%d\n", res);
    }
}
