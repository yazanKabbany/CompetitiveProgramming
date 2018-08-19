/*
calculate the distance of each node from node 1 and from node c
for every edge calculate the best time to reach the end by fixing that edge
this can be done with ternary search
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int M = 600;
const int N = 109;
int st[M];
int en[M];
double v[M];
double a[M];

vector<pair<int,double> >adj[N];
double d[N];
double r_d[N];
bool mark[N];
double inf = 1e7;
int n;
void dijkstra(int v, double *d){
    fill(d,d + n, inf);
    fill(mark, mark + n, false);
    d[v] = 0;
    int u;
    priority_queue<pair<int,double>,vector<pair<int,double> >, greater<pair<int,double> > > pq;
    pq.push({d[v], v});
    while(!pq.empty()){
        u = pq.top().second;
        pq.pop();
        if(mark[u])
            continue;
        mark[u] = true;
        for(auto p : adj[u]) //adj[v][i] = pair(vertex, weight)
            if(d[p.first] > d[u] + p.second){
                d[p.first] = d[u] + p.second;
                pq.push({d[p.first], p.first});
            }
    }
}

double calc_min(double v, double a, double p)
{
    double lo = 0, hi = 60;
    for(int i=0;i<60;i++)
    {
        double x1 = lo + (hi-lo)/3;
        double x2 = lo + 2*(hi-lo)/3;

        double f1 = v/pow(a, p+x1)+x1;
        double f2 = v/pow(a, p+x2)+x2;

        if(f2 > f1)
            hi = x2;
        else if(f1 > f2)
            lo = x1;
    }
    return v/pow(a, p+lo)+lo;
}

double calc(int v, int u, int i)
{
    double res = d[v] + r_d[u];
    double added = calc_min(::v[i],::a[i], d[v]);
    return res + added;

}
int main()
{

    int m;
    while(scanf("%d %d", &n, &m), n||m)
    {
        for(int i=0;i<n;i++)
            adj[i].clear();
        for(int i=0;i<m;i++)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            x--, y--;
            scanf("%lf %lf",v+i, a+i);
            adj[x].push_back({y, v[i]});
            adj[y].push_back({x, v[i]});
            st[i] = x;
            en[i] = y;
        }
        dijkstra(0, d);
        dijkstra(n-1, r_d);
        double res = inf;
        for(int i=0;i<m;i++)
        {
            double cur = calc(st[i], en[i], i);
            res = min(res, cur);
            cur = calc(en[i], st[i], i);
            res = min(res, cur);
        }
        printf("%.3f\n", res);
    }
}
