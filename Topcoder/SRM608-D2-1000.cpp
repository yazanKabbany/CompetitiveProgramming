/*
the answer is unbounded if and only if there exist node X such that:
2 or more adjacent nodes to X can reach X
this can be checked using Floyd-warshall algorithm
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 55;
int d[N][N];

class BigOEasy
{
public:
    string isBounded(vector <string> graph)
    {
        int n = graph.size();
        for(int i=0;i<n;i++)
        {
            for(int j=0;j < n;j++)
            {
                if(graph[i][j] == 'Y')
                    d[i][j] = 1;
            }
        }
        for(int k=0;k<n;k++)
            for(int i=0;i<n;i++)
                for(int j=0;j<n;j++)
                    d[i][j] |= d[i][k]&d[k][j];

        bool bounded = true;
        for(int k=0;k<n;k++)
            for(int i=0;i<n;i++)
                for(int j=0;j<n;j++)if(i != j)
                {
                    if(graph[k][i]=='Y' && graph[k][j]=='Y' && d[j][k] && d[i][k])
                        bounded = false;
                }
        if(bounded)
            return "Bounded";
        else
            return "Unbounded";

    }
};

int main()
{

}
