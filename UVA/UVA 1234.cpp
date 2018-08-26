/*
put a camera on every edge that is not on the naximum spanning tree
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



const int N = 1e6+10;
pair<int,pair<int,int> > edges[N];
int par[N];

int root(int v){return par[v] < 0 ? v : (par[v] = root(par[v]));}
void merge(int x,int y){
        if((x = root(x)) == (y = root(y)))     return ;
    if(par[y] < par[x])
        swap(x, y);
    par[x] += par[y];
    par[y] = x;
}

int main()
{
//   freopen("out.txt","w",stdout);
    int t;
    scanf("%d", &t);
    while(t--)
    {
        int n, m;
        scanf("%d %d", &n, &m);
        for(int i=0;i<n;i++)
            par[i] = -1;
        for(int i=0;i<m;i++)
        {
            int x, y, z;
            scanf("%d %d %d", &x, &y,&z);
            x--, y--;
            edges[i] = {z,{x,y}};
        }
        sort(edges,edges+m, greater<pair<int,pair<int,int> > >());
        ll cost = 0;
        for(int i=0;i<m;i++)
        {
            int x = edges[i].second.first;
            int y = edges[i].second.second;
            x = root(x);
            y = root(y);
            if(x == y)
                cost += edges[i].first;
            else
                merge(x, y);
        }
        printf("%lld\n", cost);
    }
    scanf("%d",&t);
    return 0;
}
