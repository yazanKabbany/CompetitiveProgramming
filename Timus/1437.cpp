/*
dfs all possible states
and calculate the answer
*/

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int cap[4];

set<vector<int> >visited;
set<int>vals;

vector<vector<int> > adjs(vector<int> &v)
{
    vector<vector<int> >res;
    for(int i=0;i<3;i++)
    {
        vector<int>cur(3);
        for(int j=0;j<3;j++)
        {
            if(i != j)
                cur[j] = v[j];
            else
                cur[j] = cap[j];
        }
        res.push_back(cur);
    }

   for(int i=0;i<3;i++)
   {
       for(int j=0;j<3;j++)if(i != j && v[j] <= cap[j])
       {
           vector<int>cur(3);
           int got = min(cap[j], v[i] + v[j]);
           int rem = v[i] + v[j] - got;
           for(int k=0;k<3;k++)
           {
                if(k == j)
                    cur[k] = got;
                else if(k == i)
                    cur[k] = rem;
                else
                    cur[k] = v[k];
           }
           res.push_back(cur);

       }
   }
   return res;
}
void add_ans(vector<int> &v)
{
    for(auto a:v)if(a)
        vals.insert(a);
    if(v[0] + v[1] + v[2])
        vals.insert(v[0] + v[1] + v[2]);
    for(int i=0;i<3;i++)
    {
        for(int j=i+1;j<3 ;j++)if(v[i] + v[j])
            vals.insert(v[i] + v[j]);
    }
}
void dfs(vector<int> v)
{
    visited.insert(v);
    add_ans(v);
    for(auto u:adjs(v))if(visited.find(u) == visited.end())
    {
        dfs(u);
    }
}
int main()
{
    scanf("%d %d %d",cap, cap+1, cap+2);
    dfs({0, 0, 0});
    int ans = vals.size();
    printf("%d\n", ans);
}
