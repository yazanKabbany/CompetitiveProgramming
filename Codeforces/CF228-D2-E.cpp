/*
Firstly, note that every vertex should be switched-on no more than once. Then, consider every edge (x, y) of color c. 
We want to make its color 1. So, if c = 1 we should switch on vertices x and y or don’t switch them on simultaneously. 
If c = 0 we should switch on x or y.
we can solve this by using 2SAT algorithm
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 105 + 10;
#define pb push_back
vector<int>g[2*N];
vector<int>gr[2*N];
bool vis[2*N];
vector<int>order;
int comp[2*N],SCCcnt;
int ans[N];
int n;
int neg(int x) { return x>=n? x-n : x+n;}
void addor(int a,int b)
{
    g[neg(a)].pb(b);
    g[neg(b)].pb(a);
    gr[b].pb(neg(a));
    gr[a].pb(neg(b));
}
void dfs1(int v)
{
    vis[v] = true;
    for(auto u:g[v])if(!vis[u])
        dfs1(u);
    order.push_back(v);
}
void dfs2(int v, int c)
{
    comp[v] = c;
    for(auto u:gr[v])if(comp[u]==-1)
        dfs2(u,c);
}
bool sat()
{
    SCCcnt = 0;
    memset(vis,0,sizeof vis);
    for(int i=0;i<n;i++)
    {
        if(!vis[i])dfs1(i);
        if(!vis[neg(i)])dfs1(neg(i));
    }
    memset(comp, -1, sizeof comp);
    for(int i=0;i<2*n;i++)
    {
        int v = order[2*n-1-i];
        if(comp[v] == -1)
            dfs2(v, SCCcnt++);
    }
    for(int i=0;i<n;i++)
        if(comp[i] == comp[neg(i)])
            return false;
    for (int i = 0; i<n;i++)
        ans[i] = comp [i]> comp [neg(i)]? 1: 0;
    return true;
}

int main()
{
    int m;
    scanf("%d %d", &n, &m);
    for(int i=0;i<m;i++)
    {
        int x, y, c;
        scanf("%d %d %d", &x, &y, &c);
        x--, y--;
        if(c == 0)
        {
            addor(x, y);
            addor(neg(x), neg(y));
        }
        else
        {
            addor(neg(x), y);
            addor(x, neg(y));
        }
    }
    if(!sat())
    {
        puts("Impossible");
        return 0;
    }
    int x = 0;
    for(int i=0;i<n;i++)if(ans[i])
        x++;
    printf("%d\n", x);
    for(int i=0, j=0;i<n;i++)if(ans[i])
    {
        printf("%d%c",i+1," \n"[j==x-1]);
        j++;
    }
}
