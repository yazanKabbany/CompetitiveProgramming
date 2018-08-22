/*
each shape has a unique number of holes inside it
for each connected component count the number of halls in it to determine what shape it is
this can be done using dfs
but first of all mark th 'outside' area so we wont consider it as a hole
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int g[205][205];
char s[100];

int dx[]={1, -1, 0, 0};
int dy[]={0, 0, -1, 1};
int n, m;
void zeros_to_m1(int x, int y)
{
    g[x][y] = -1;
    for(int i=0;i<4;i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx < 0 || ny < 0 || nx > n || ny > m || g[nx][ny] != 0)
            continue;
        zeros_to_m1(nx, ny);
    }
}

int cnt_halls(int x, int y)
{
    g[x][y] = 2;
    int res=  0;
     for(int i=0;i<4;i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx < 0 || ny < 0 || nx > n || ny > m)
            continue;
        if(g[nx][ny] == 0)
        {
            res++;
            zeros_to_m1(nx, ny);
        }
        else if(g[nx][ny] == 1)
        {
            res += cnt_halls(nx, ny);
        }
    }
    return res;
}
char code[]={'W', 'A', 'K', 'J', 'S', 'D'};
int main()
{
    int T = 1;
    while(scanf("%d %d", &n, &m),n||m)
    {
        memset(g, 0, sizeof g);
        m*=4;
        for(int i=1;i<=n;i++)
        {
            scanf("%s",s);
            for(int j=0,k=1;s[j];j++)
            {
                int num = 0;
                if(s[j]>='a')
                    num = s[j]-'a'+10;
                else
                    num = s[j]-'0';
                for(int x=3;x>=0;x--)
                    g[i][k++] = (num>>x)&1;
            }
        }
        n++, m++;
        zeros_to_m1(n,m);
        zeros_to_m1(0,0);
        string ans;
        for(int i=0;i<=n;i++)
            for(int j=0;j<=m;j++)if(g[i][j] == 1)
            {
                int cnt = cnt_halls(i, j);
                ans.push_back(code[cnt]);
            }
        sort(ans.begin(), ans.end());
        printf("Case %d: %s\n", T++,ans.c_str());
    }
}
