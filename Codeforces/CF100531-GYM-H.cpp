/*
the main idea is to only walk on the vertces of the triangles
then this problem is turned to a graph problem
use binary search to find the minimum possible z
use BFS to find the path between A and B
*/


#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


const int N = 6009;
int tr[N][5][5];
int a[5];
int b[5];

map<pair<int,int>, int> mp;
int cntr=1;
int get_idx(int a, int b)
{
    auto p = make_pair(a, b);
    auto it = mp.find(p);
    if(it != mp.end())
        return it->second;
    return mp[p] = cntr++;
}
vector<int>adj[N];
int z[N];

struct point
{
    ll x;
    ll y;
};

ll sign (point p1, point p2, point p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool PointInTriangle (point pt, point v1, point v2, point v3)
{
    bool b1, b2, b3;

    b1 = sign(pt, v1, v2) < 0;
    b2 = sign(pt, v2, v3) < 0;
    b3 = sign(pt, v3, v1) < 0;

    return ((b1 == b2) && (b2 == b3));
}
struct XXX
{
    int x, y, z;
}nodes[N];
int d[N];
int prv[N];
int inf = (int)1e8;
int source;
int dist;
bool bfs(int mx_z)
{
    fill(d,d+cntr+1,inf);
    queue<int>q;
    int s = source;
    q.push(s);
    d[s] = 0;
    prv[s] = -1;
    while(!q.empty())
    {
        int v = q.front();
        q.pop();
        if(v == dist)
            return 1;

        for(int u:adj[v])if(d[u] == inf && z[u] <= mx_z)
        {
            prv[u] = v;
            d[u] = d[v]+1;
            q.push(u);
        }
    }
    return 0;
}

int BS()
{
    int lo = max(z[source], z[dist]);
    int hi = 1e6;
    int ans = hi;
    while(lo <= hi)
    {
        int mid = (lo + hi)/2;
        if(bfs(mid))
            ans = mid, hi = mid -1;
        else
            lo = mid+1;
    }
    return ans;
}
int main()
{
    freopen("hiking.in","r",stdin);
    freopen("hiking.out","w",stdout);

    int n;
    scanf("%d", &n);
    for(int i=0;i<n;i++)
    {
        vector<int>idxes;
        idxes.reserve(3);
        for(int j=0;j<3;j++)
        {
            for(int k=0;k<3;k++)
                scanf("%d", &tr[i][j][k]);
            int idx = get_idx(tr[i][j][0], tr[i][j][1]);
            z[idx] = tr[i][j][2];
            idxes.push_back(idx);
            nodes[idx] = {tr[i][j][0], tr[i][j][1],tr[i][j][2]};
        }
        for(auto x:idxes)
            for(auto y:idxes)if(x!= y)
                adj[x].push_back(y);
    }
     for(int i=0;i<3;i++)
        scanf("%d", a+i);
     for(int i=0;i<3;i++)
        scanf("%d", b+i);

    source=get_idx(a[0], a[1]);
    dist=get_idx(b[0], b[1]);

    for(int i=0;i<n;i++)
    {
        point p1={tr[i][0][0], tr[i][0][1]};
        point p2={tr[i][1][0], tr[i][1][1]};
        point p3={tr[i][2][0], tr[i][2][1]};
        point q={a[0], a[1]};
        point w={b[0], b[1]};
        if(PointInTriangle(q, p1, p2, p3))
        {
            int cur = get_idx(q.x, q.y);
            nodes[cur] = {a[0], a[1], a[2]};
            z[cur] = a[2];
            for(int j=0;j<3;j++)
            {
                int idx = get_idx(tr[i][j][0], tr[i][j][1]);
                adj[idx].push_back(cur);
                adj[cur].push_back(idx);
            }
        }
        if(PointInTriangle(w, p1, p2, p3))
        {
            int cur = get_idx(w.x, w.y);
            nodes[cur] = {b[0], b[1], b[2]};

            z[cur] = b[2];
            for(int j=0;j<3;j++)
            {
                int idx = get_idx(tr[i][j][0], tr[i][j][1]);
                adj[idx].push_back(cur);
                adj[cur].push_back(idx);
            }
        }
    }
    int mx_h = BS();
    bfs(mx_h);
    vector<XXX>res;
    res.reserve(5*n);
    int idx = get_idx(b[0], b[1]);
    while(idx != -1)
    {
        res.push_back(nodes[idx]);
        idx = prv[idx];
    }
    printf("%d\n", (int)res.size());
    for(int i=(int)res.size()-1;i>=0;i--)
    {
        printf("%d %d %d\n", res[i].x, res[i].y, res[i].z);
    }
    return 0;
}
