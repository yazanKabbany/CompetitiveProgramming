#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


const int N = 50 + 10;

ll dp[N][4][4];
inline int f(int x)
{
    return x+1;
}
map<pair<int,int> ,int>mp;
pair<int,int> state[15];

vector<pair<int,int> >to[N];
void init()
{
    mp[{0, 0}] = 1;
    mp[{1, 1}] = 2;
    mp[{-1, -1}] = 3;
    mp[{0, 1}] = 4;

    state[1] = {0, 0};
    state[2] = {1, 1};
    state[3] = {-1, -1};
    state[4] = {0, 1};

    to[1] = {{2, 1}, {0, 2}, {1, 4}};
    to[2] = {{2, 3}};
    to[3] = {{0, 1}, {0, 2}};
    to[4] = {{1, 1}, {2, 4}};
}
int main()
{
    init();
    int n = 30;
    dp[0][f(0)][f(0)] = 1;
    for(int i=0;i<=n;i++)
    {
        for(int a = -1;a<=1;a++)
            for(int b = -1; b<=1; b++)
            {
                if(mp.find({a,b}) == mp.end())
                    continue;
                int cur = mp[{a,b}];
                for(auto p: to[cur])
                {
                    int added = p.first;
                    int na = state[p.second].first;
                    int nb = state[p.second].second;
                    dp[i+added][f(na)][f(nb)] += dp[i][f(a)][f(b)];
                }
            }
    }
    while(scanf("%d", &n), n != -1)
    {
        ll res = dp[n][f(0)][f(0)];
        printf("%lld\n", res);
    }
}
