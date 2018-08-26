/*
dp[i][j] is the longest palindrome starting at i and ending at j
after calculating the dp
we can build the answer using some modification of BFS
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 55;
int n;
char g[N][N];
int dp[N][N];
int inf = 1e7;
int calc(int i, int j)
{
    if(i == j)
        return 0;
    if(i > j)
        return -inf;
    int &res = dp[i][j];
    if(res != -1)
        return res;
    res = 1;
    for(int i_to = i+1; i_to <n; i_to++)
        for(int j_from = j-1;j_from>=0; j_from--)if(g[i][i_to] == g[j_from][j])
        {
            int got = calc(i_to, j_from);
            res = max(res, got+2);
        }
    return res;
}
bool vis[N][N];
int main()
{
//   freopen("out.txt","w",stdout);
    int t;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        for(int i=0;i<n;i++)
            scanf("%s",g[i]);
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                dp[i][j] = -1, vis[i][j] = 0;
        int len = calc(0, n-1);
        string ans1, ans2;
        queue<pair<int,int> >q;
        q.push({0, n-1});
        int i, j;
        while(!q.empty())
        {
            int sz = q.size();
            queue<pair<int,int > >q2;
            char letter = 'z';
            while(sz--)
            {
                i = q.front().first;
                j = q.front().second;
                q2.push({i,j});
                q.pop();
                int res = calc(i, j);
                if(res == 1)
                {
                    letter = min(letter, g[i][j]);
                    continue;
                }
                if(!res)
                    continue;
                for(int i_to = i+1; i_to <n; i_to++)
                for(int j_from = j-1;j_from>=0; j_from--)if(g[i][i_to] == g[j_from][j])
                {
                    int got = calc(i_to, j_from);
                    if(res == got+2 )
                    {
                        letter = min(letter, g[i][i_to]);
                    }
                }
            }
            if(letter !='z')
                ans1.push_back(letter);
            while(!q2.empty())
            {
                i = q2.front().first;
                j = q2.front().second;
                q2.pop();
                int res = calc(i, j);
                if(res < 2)
                    continue;
                for(int i_to = i+1; i_to <n; i_to++)
                    for(int j_from = j-1;j_from>=0; j_from--)if(g[i][i_to] == g[j_from][j])
                    {
                        int got = calc(i_to, j_from);
                        if(res == got+2 && g[i][i_to] == letter && !vis[i_to][j_from])
                        {
                            vis[i_to][j_from] = 1;
                            q.push({i_to, j_from});
                        }
                    }
            }
        }
            ans2 = ans1;
            if(len&1)
                ans2.pop_back();
            reverse(ans2.begin(), ans2.end());
            ans1 += ans2;
            printf("%s\n", ans1.c_str());
    }
    return 0;
}
