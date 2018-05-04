/*
turn the graph to a DAG using BFS 
split evey node to in node and out node
use dinic algorithm to calculate the maximum number of paths that don't share a node(which is the answer to the problem

*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int N = 1009;
const int MAXN = 4*N;
const int INF = 1e6;



struct MAXFLOW
{
    struct edge
    {
        int a, b, cap, flow;
    };

    int n, s, t, d[MAXN], ptr[MAXN], q[MAXN];
    vector<edge> e;
    vector<int> g[MAXN];

    void add_edge (int a, int b, int cap)
    {
        edge e1 = { a, b, cap, 0 };
        edge e2 = { b, a, 0, 0 };
        g[a].push_back ((int) e.size());
        e.push_back (e1);
        g[b].push_back ((int) e.size());
        e.push_back (e2);
    }

    bool bfs()
    {
        int qh=0, qt=0;
        q[qt++] = s;
        memset (d, -1, n * sizeof d[0]);
        d[s] = 0;
        while (qh < qt && d[t] == -1)
        {
            int v = q[qh++];
            for (size_t i=0; i<g[v].size(); ++i)
            {
                int id = g[v][i],
                    to = e[id].b;
                if (d[to] == -1 && e[id].flow < e[id].cap)
                {
                    q[qt++] = to;
                    d[to] = d[v] + 1;
                }
            }
        }
        return d[t] != -1;
    }

    int dfs (int v, int flow)
    {
        if (!flow)  return 0;
        if (v == t)  return flow;
        for (; ptr[v]<(int)g[v].size(); ++ptr[v])
        {
            int id = g[v][ptr[v]],
                to = e[id].b;
            if (d[to] != d[v] + 1)  continue;
            int pushed = dfs (to, min (flow, e[id].cap - e[id].flow));
            if (pushed)
            {
                e[id].flow += pushed;
                e[id^1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

    int dinic()
    {
        int flow = 0;
        for (;;)
        {
            if (!bfs())  break;
            memset (ptr, 0, n * sizeof ptr[0]);
            while (int pushed = dfs (s, INF))
                flow += pushed;
        }
        return flow;
    }
    void reset()
    {
        e.clear();
        memset (d, -1, n * sizeof d[0]);
        memset (ptr, 0, n * sizeof ptr[0]);
        memset (q, 0, n * sizeof q[0]);
        for(int i=0;i<n;i++)
            g[i].clear();
    }

}flow;

int n;
int in(int x)
{
    return x;
}
int out(int x)
{
    if(x == flow.s)
        return x;
    return x + n;
}
vector<int>adj[N];
int lev[N];

void bfs(int s,int t)
{
    memset(lev, -1, sizeof lev);
    lev[s] = 0;
    lev[t] = n*10;
    queue<int>q;
    q.push(s);
    while(!q.empty())
    {
        int v = q.front();
        q.pop();
        for(auto u:adj[v])
        {
            if(lev[u] == -1 || lev[u] >= lev[v])
                flow.add_edge(out(v), in(u), 1);
            if(lev[u] == -1)
                lev[u] = lev[v] + 1, q.push(u);
        }
    }
}
int main()
{
    int m;
    scanf("%d %d", &n, &m);
    flow.n = 2*n;
    scanf("%d %d", &flow.s, &flow.t);
    flow.s--;
    flow.t--;
    for(int i=0;i<m;i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    bfs(flow.s, flow.t);
    for(int i=0;i<n;i++)
    {
        flow.add_edge(in(i), out(i), 1);
    }
    int mx_flow = flow.dinic();
    int ans = mx_flow;
    printf("%d\n", ans);
}
