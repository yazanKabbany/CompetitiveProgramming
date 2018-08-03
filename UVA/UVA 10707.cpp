/*
for each connected component find its 8 directions rotate(0, 90, 180, 270) then flip and rotate again
for each direction pull the points to the origin
add the 8 directions to a vector and sort them

if the vector for the first board is the equal to the vector of the second one the answer is YES
otherwise it's NO
*/

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 3e3 + 10;

int w, h;

int g1[105][105];
int g2[105][105];

vector<vector<pair<int,int> > >v1;
vector<vector<pair<int,int> > >v2;


vector<pair<int,int> >cur_vec[8];


int DX[]={0, 0, -1, 1};
int DY[]={1, -1, 0, 0};
void dfs(int x,int y, int g[][105])
{
    cur_vec[0].push_back({x, y});
    cur_vec[1].push_back({h-x-1, y});
    cur_vec[2].push_back({x, w-y-1});
    cur_vec[3].push_back({h-x-1, w-y-1});
    swap(x,y);
    swap(h, w);
    cur_vec[4].push_back({x, y});
    cur_vec[5].push_back({h-x-1, y});
    cur_vec[6].push_back({x, w-y-1});
    cur_vec[7].push_back({h-x-1, w-y-1});
    swap(x,y);
    swap(h,w);
    g[x][y] = 0;

            for(int i=0;i<4;i++)
            {
                int dx = DX[i];
                int dy = DY[i];
                int nx = x+dx;
                int ny = y+dy;
                if(nx < 0 || ny < 0 || nx >= h || ny >= w)
                    continue;
                if(g[nx][ny])
                    dfs(nx, ny , g);
            }
}
void fix_vec(vector<pair<int,int> > &v)
{
    int mn_x = 1e9;
    int mn_y = 1e9;
    for(auto c:v)
        mn_x = min(mn_x, c.first), mn_y = min(mn_y, c.second);
    for(auto &c:v)
        c.first -= mn_x, c.second-=mn_y;
    sort(v.begin(), v.end());
}
int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        v1.clear();
        v2.clear();
        scanf("%d %d", &w, &h);
        swap(h, w);
        int n;
        scanf("%d", &n);
        for(int i=0;i<n;i++)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            g1[x][y] = 1;
        }
        for(int i=0;i<n;i++)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            g2[x][y] = 1;
        }

        for(int i=0;i<h;i++)
            for(int j=0;j<w;j++)
                if(g1[i][j])
                {
                    for(int k=0;k<8;k++)
                        cur_vec[k].clear();
                    dfs(i, j, g1);
                    for(int k=0;k<8;k++)
                    {
                        fix_vec(cur_vec[k]);
                        v1.push_back(cur_vec[k]);
                    }
                }
        for(int i=0;i<h;i++)
            for(int j=0;j<w;j++)
                if(g2[i][j])
                {
                    for(int k=0;k<8;k++)
                        cur_vec[k].clear();
                    dfs(i, j, g2);
                    for(int k=0;k<8;k++)
                    {
                        fix_vec(cur_vec[k]);
                        v2.push_back(cur_vec[k]);
                    }
                }
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        if(v1 == v2)
        {
            puts("YES");
        }
        else
            puts("NO");
    }
    return 0;
}
