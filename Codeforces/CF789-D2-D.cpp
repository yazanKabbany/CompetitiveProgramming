/*
same as tutorial
https://codeforces.com/blog/entry/51312
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e6 + 10;

vector<int>adj[N];
bool has_loop[N];
bool vis[N];
int dfs(int v)
{
    vis[v] = 1;
    int res = 1;
    for(auto u:adj[v])if(!vis[u])
        res += dfs(u);
    return res;
}
int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    ll loops= 0;
    for(int i=0;i<m;i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        x--, y--;
        if(x == y)
        {
            has_loop[x] = 1;
            loops++;
        }
        else
        {
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
    }
    ll res = 0;
    bool got_comp=false;
    for(int i=0;i<n;i++)if(!vis[i])
    {
        int sz = dfs(i);
        if(sz > 1 || has_loop[i])
        {
            if(got_comp)
                return puts("0"), 0;
            got_comp = 1;
        }
    }
    for(int i=0;i<n;i++)
        {
            ll num = adj[i].size();
            ll cur = num*(num-1)/2;
            res += cur;
        }
    ll one_loop = loops*(m-loops);
    res += one_loop;
    res += loops*(loops-1)/2;
    cout<<res<<'\n';
}
