/*
build a graph of 51X51 nodes
representing the state of the student (the practical skills and the theoratical skills)
we build an edge between state A and state B if there is a course that changes the srudents state from A to B
run BFS over the graph to get a shortest path DAG
run DFS over the shortest path DAG tp build the required path
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 60;


int d[N][N];
int vis[N][N];
int inf = 1e6;

class CsCourses
{
public:
    vector <int> tv;
    vector <int> pv;
    vector <int> ex;
    vector <int> ans;
    int n, target;
    void bfs()
    {
        for(int i=0;i<=50;i++)
            for(int j=0;j<=50;j++)
                d[i][j] = inf;
        d[0][0] = 0;
        queue<pair<int,int> >q;
        q.push({0,0});
        while(!q.empty())
        {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();
            if(x>=target && y >= target)
                continue;
            for(int i=0;i<n;i++)
            {
                if(ex[i] > d[x][y] && tv[i] <= x+1 && pv[i] <= y+1)
                {
                    int nx = max(x, tv[i]);
                    int ny = max(y, pv[i]);
                    if(d[nx][ny] == inf)
                    {
                        d[nx][ny] = d[x][y]+1;
                        q.push({nx, ny});
                    }

                }
            }
        }

    }
    bool build_ans(int x, int y)
    {
        if(x >= target && y >= target)
            return 1;
        bool res = false;
        vis[x][y] = 1;
        for(int i=0;i<n && !res;i++)
            {
                if(ex[i] > d[x][y] && tv[i] <= x+1 && pv[i] <= y+1)
                {
                    int nx = max(x, tv[i]);
                    int ny = max(y, pv[i]);
                    if(d[nx][ny] == d[x][y]+1 && !vis[nx][ny])
                    {
                        ans.push_back(i);
                        res = res || build_ans(nx, ny);
                        if(!res)
                            ans.pop_back();
                    }
                }
            }
        return res;
    }
    vector <int> getOrder(vector <int> theoreticalValue, vector <int> practicalValue, vector <int> expire, int skillBound)
    {
        n = theoreticalValue.size();
        target = skillBound;
        tv = theoreticalValue;
        pv = practicalValue;
        ex = expire;
        bfs();
        bool can = build_ans(0, 0);
        if(!can)
            return vector<int>();
        else
            return ans;

    }
};
