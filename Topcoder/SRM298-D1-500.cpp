/*
make a graph with 1000 vertex 
consider each matrix as an edge from Ni to Mi
if there is no eulerian path the answer is -1
if there is an eulerian cycle the answer is the square of the maximum vertex
otherwise the answer is the starting vertex multipied with ending vertex of the eulerian path
*/

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e3 + 10;
class OrderDoesMatter
{
public:
    vector<int>adj[N];
    bool exist[N];
    bool vis[N];
    int deg[N];
    void dfs(int x)
    {
        vis[x] = true;
        for(auto y:adj[x])if(!vis[y])
            dfs(y);
    }
    int getOrder(vector <int> n, vector <int> m)
    {
        memset(exist, 0, sizeof exist);
        memset(vis, 0, sizeof vis);
        memset(deg, 0, sizeof deg);
        for(int i=0;i<(int)n.size();i++)
        {
            deg[n[i]]--;
            deg[m[i]]++;
            exist[n[i]] = exist[m[i]] = 1;
            adj[n[i]].push_back(m[i]);
        }

        int pos = 0;
        int neg = 0;
        ll a= 1;
        ll b = 1;
        ll mx = 1;
        for(int i=0;i<=1000;i++)
        {
            if(deg[i] > 0)
                pos += deg[i], a = i;
            else if(deg[i] < 0)
                neg -= deg[i], b = i;

            if(exist[i])
                mx = i;
        }
        if(pos > 1 || neg > 1)
            return -1;
        if(pos != neg)
            return -1;
        if(pos || neg)
        {
            dfs(b);
            for(int i=0;i<(int)n.size();i++)
            {
                if(!vis[n[i]] || !vis[m[i]])
                    return -1;
            }
            return a*b;
        }
        dfs(n[0]);
        for(int i=0;i<(int)n.size();i++)
        {
            if(!vis[n[i]] || !vis[m[i]])
                return -1;
        }
        return mx*mx;

    }
};

int main()
{
    int n;
    scanf("%d", &n);
    vector<int>a;
    vector<int>b;
    for(int i=0;i<n;i++)
    {
        int x;
        scanf("%d",&x);
        a.push_back(x);
    }

    for(int i=0;i<n;i++)
    {
        int x;
        scanf("%d",&x);
        b.push_back(x);
    }
    OrderDoesMatter obj;
    cout<<obj.getOrder(a, b)<<'\n';
}

