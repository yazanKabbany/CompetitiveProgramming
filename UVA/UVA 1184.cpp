/*
max-flow problem:

split every node to an (in) node and (out) node
connect all out nodes with the source
connect all int nodes with the sink

for every edge S-E in the original graph:
  connect out(S) with in(E) in the new graph
run dinic algorithm on the new bipartite 
the answer is n - MAX_FLOW 

*/

#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAXN = 500;
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
    return x + n;
}
int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        int m;
        scanf("%d %d", &n, &m);
        flow.reset();
        flow.n = n*2 +2;
        while(m--)
        {
            int s, e;
            scanf("%d %d", &s, &e);
            s--, e--;
            flow.add_edge(out(s), in(e),1);
        }
        flow.s = 2*n;
        flow.t = flow.s + 1;
        for(int i=0;i<n;i++)
            flow.add_edge(flow.s, out(i), 1), flow.add_edge(in(i), flow.t, 1);
        int mx_flow = flow.dinic();
        int res = n - mx_flow;
        printf("%d\n", res);
    }
}
