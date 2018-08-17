/*
modified version of floyd algorithm to calculate all pairs shortest path and second shortest path
Complexity: O(N*N*N + Q) for every test case.
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 105;

ll d[N][N][2];
ll inf = 1e12;
int main()
{
    int T = 1;
    int n, m;
    while(scanf("%d %d", &n, &m)!=EOF)
    {
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
            {
                d[i][j][0] = d[i][j][1] = inf;
                if(i ==  j)
                    d[i][j][0] = 0;
            }
        for(int i=0;i<m;i++)
        {
            int x,y,c;
            scanf("%d %d %d", &x, &y, &c);
            d[x][y][0] = d[y][x][0] = c;
            d[x][y][1] = d[y][x][1] = 3*c;
        }

        for(int k=0;k<n;k++)
            for(int i=0;i<n;i++)
                for(int j=0;j<n;j++)
                {
                    vector<ll>paths;
                    paths.push_back(d[i][j][0]);
                    paths.push_back(d[i][j][1]);
                    for(int x=0;x<2;x++)
                        for(int y=0;y<2;y++)
                            for(int z=0;z<2;z++)
                            {
                                ll val = min(inf, d[i][k][x] + d[k][j][y]+d[k][k][z]);
                                paths.push_back(val);
                            }
                    sort(paths.begin(), paths.end());
                    unique(paths.begin(), paths.end());
                    d[i][j][0] = paths[0];
                    d[i][j][1] = paths[1];
                }
        int q;
        scanf("%d", &q);
        printf("Set #%d\n",T++);
        while(q--)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            ll res = d[x][y][1];
            if(res >= inf)
                puts("?");
            else
                printf("%lld\n", res);
        }
    }

}
