/*
same as the tutorial
https://codeforces.com/blog/entry/47890
*/

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 4e5 + 10;

struct EDGE
{
    int e, type, idx;
};
pair<int,int> edges[N];
int ans[N];
vector<EDGE>adj[N];
vector<EDGE>tree[N];

stack<int> s;

int lw[N],idx[N],cmp[N],counter,SCCNum;
int cmp_sz[N];
void tarjanSCC(int v, int p)
{
    lw[v]=idx[v]=++counter;
    cmp[v]=-1;
    s.push(v);
    for(auto e:adj[v])
    {
        int u = e.e;
        if(u == p)
            continue;
        if(!idx[u]||cmp[u]==-1)
        {
            if(!idx[u])tarjanSCC(u, v);
            lw[v]=min(lw[v],lw[u]);
        }

    }
    if(lw[v]==idx[v]){
        int x;
        do{
            x=s.top();
            s.pop();
            cmp[x]=SCCNum;
            cmp_sz[SCCNum]++;
        }while(x!=v);

        SCCNum++;
    }
}

bool vis[N];
void dfs(int v,int p)
{
    vis[v] = true;
    for(auto e:adj[v])
    {
        int u = e.e;
        if(cmp[u] != cmp[v])
            continue;
        if(u == p)
            continue;
        if(ans[e.idx] == -1)
            ans[e.idx] = e.type;
        if(!vis[u])
            dfs(u, v);
    }
}

void orient_tree(int v, int p)
{
    for(auto e:tree[v])
    {
        int u = e.e;
        if(u == p)
            continue;
        orient_tree(u, v);
        ans[e.idx] = !e.type;
    }
}

int main()
{
    memset(cmp,-1,sizeof cmp);
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i=0;i<m;i++)
    {
        int x,y ;
        scanf("%d %d", &x, &y);
        x--, y--;
        adj[x].push_back(EDGE{
                            y, 0, i
                         });
        adj[y].push_back(EDGE{
                            x, 1, i
                         });
         edges[i] = {x, y};
    }
    tarjanSCC(0, -1);
    memset(ans, -1, sizeof ans);
    for(int i=0;i<n;i++)
        if(!vis[i])
        dfs(i, -1);
    for(int i=0;i<m;i++)
    {
        int x = cmp[edges[i].first],y = cmp[edges[i].second];
        if(x == y)
            continue;
        tree[x].push_back({
                          y, 0, i
                          });
        tree[y].push_back({
                          x, 1, i
                          });
    }
    int mx_idx = 0;
    for(int i=1;i<SCCNum;i++)
        if(cmp_sz[i] > cmp_sz[mx_idx])
            mx_idx = i;
    orient_tree(mx_idx, -1);
    int res = cmp_sz[mx_idx];
    printf("%d\n", res);
    for(int i=0;i<m;i++)
    {
        if(ans[i] == 1)
            swap(edges[i].first, edges[i].second);
        printf("%d %d\n", edges[i].first+1, edges[i].second+1);
    }

    return 0;
}
