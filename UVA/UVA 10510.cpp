/*
	First check the graph is a single strongly connected component. Then draw the DFS tree - if the graph has any cross/forward edge, then it's not a cactus. If there exists a node who has more than one children with a back edge to the ancestor of the node, then the graph is not a cactus.
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=10009;
stack<int> s;
vector<int>adj[N];
int lw[N],idx[N],cmp[N],counter,SCCNum;

void tarjanSCC(int v)
{
    lw[v]=idx[v]=++counter;
    cmp[v]=-1;
    s.push(v);
    for(auto u:adj[v])if(!idx[u]||cmp[u]==-1){

        if(!idx[u])tarjanSCC(u);
        lw[v]=min(lw[v],lw[u]);
    }
    if(lw[v]==idx[v]){
        int x;
        do{
            x=s.top();
            s.pop();
            cmp[x]=SCCNum;
        }while(x!=v);

        SCCNum++;
    }
}

bool vis[N];
bool stk[N];
bool cac;
void dfs(int v)
{
    vis[v] =  1;
    stk[v] = 1;
    for(auto u:adj[v])
    {
        if(!vis[u])
            dfs(u);
        else if(!stk[u])
        {
             cac = false;
        }
    }
    stk[v] = 0;
}

int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        int n, m;
        scanf("%d %d", &n, &m);
        for(int i=0;i<n;i++)
            adj[i].clear(), idx[i] = 0, cmp[i] = -1, vis[i] = 0;
        SCCNum = counter = 0;
        for(int i=0;i<m;i++)
        {
            int x,y ;
            scanf("%d %d", &x, &y);
            adj[x].push_back(y);
        }
        tarjanSCC(0);
        for(int i=0;i<n;i++)if(!idx[i])SCCNum++;
        if(SCCNum > 1)
        {
            puts("NO");
            continue;
        }

        cac = true;
        dfs(0);
        if(cac)
            puts("YES");
        else
            puts("NO");

    }
}
