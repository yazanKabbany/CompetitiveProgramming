/*
  build a network
  connect s with plant with capacity d^2
  connect plant with base that it support with capacity INF
  connect base with capacity d^2
  where d^2 is the squared distance
  
  the solution is the  value if max-flow/min-cut
*/
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

#define pb push_back
#define sz(x) x.size()

int nodes;
const int MAXN = 1000 ;
const int INF = 100000000 ;

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


int c,b,p;
class GreenWarfare
{
    public:
    int minimumEnergyCost(vector <int> canonX, vector <int> canonY, vector <int> baseX, vector <int> baseY, vector <int> plantX, vector <int> plantY, ll energySupplyRadius)
    {
        energySupplyRadius*=energySupplyRadius;
        c = canonX.size();
        b = baseX.size();
        p = plantX.size();
        nodes = b + p;
        int s = nodes++;
        int t = nodes++;
        flow.n = nodes;
        flow.s = s;
        flow.t = t;
        vector<int>baseCost(b);
        for(int i=0;i<(int)baseX.size();i++)
        {
            ll cost = INF;
            for(int j=0;j<(int)canonX.size(); j++)
            {
                ll cur = (canonX[j] - baseX[i])*(canonX[j] - baseX[i]) + (canonY[j] - baseY[i])*(canonY[j] - baseY[i]);
                cost = min(cost, cur);
            }
            baseCost[i] = cost;

        }

        for(int i=0;i<(int)plantX.size();i++)
        {
            ll cost = INF;
            for(int j=0;j<(int)canonX.size();j++)
            {
                ll cur = (canonX[j] - plantX[i])*(canonX[j] - plantX[i]) + (canonY[j] - plantY[i])*(canonY[j] - plantY[i]);
                cost = min(cost, cur);
            }
            flow.add_edge(s,i,cost);

            for(int j =0 ; j < (int)baseX.size(); j++)
            {
                ll cur = (plantX[i] - baseX[j])*(plantX[i] - baseX[j]) + (plantY[i] - baseY[j])*(plantY[i] - baseY[j]);
                if(cur <= energySupplyRadius)
                    flow.add_edge(i, p+j,INF);
            }
        }
        for(int i=0;i<(int)baseX.size();i++)
        {
//            addEdge(p+i,t,1,baseCost[i]);
            flow.add_edge(p+i,t,baseCost[i]);
//            addEdge(s,p+i,1,baseCost[i]);
        }
        ll res  = flow.dinic();
        return res;
    }
};
