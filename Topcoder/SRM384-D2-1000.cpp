/*
for a single pile:
let dp[i] be a pair of int 
the first int is 1 if the first player can win if the pile contains i sticks
it is 0 otherwise 
the second int is the minimum number of steps to win if the first player can win
ot the maximum number of steps to lose if the first player can't win

for 2 piles:
the player that can win one of the piles before the other player is the winner
*/

#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
int inf = 1e6;
class PowerGame
{
    char temp[1000];
public:
    vector<int>squares;
    pair<int,int>dp[10009];
    string winner(int s0, int s1)
    {
        int mx = max(s0, s1);
        for(int i=1;i*i<=mx;i++)
            squares.push_back(i*i);
        dp[0]={0, 0};
        for(int i=1; i<= mx; i++)
        {
            int longest_lose = 0;
            int fastest_win = inf;
            for(auto s:squares)
            {
                if(s > i)
                    break;
                int got = dp[i-s].first;
                if(!got)
                {
                    fastest_win = min(fastest_win, dp[i-s].second+1);
                }
                else
                {
                    longest_lose= max(longest_lose,dp[i-s].second+1);
                }
            }
            if(fastest_win != inf)
                dp[i] = {1, fastest_win};
            else
                dp[i] = {0, longest_lose};
        }
        int win = 0;
        int turns = 0;
        turns = min(dp[s0].second, dp[s1].second);
        if(dp[s0].first && dp[s1].second)
        {
        }
        if(!dp[s0].first && !dp[s1].first)
        {
            win = 1;
        }
        else if(dp[s0].second < dp[s1].second)
        {
            win =  !dp[s0].first;
        }
        else if(dp[s0].second > dp[s1].second)
        {
            win = !dp[s1].first;
        }
        sprintf(temp,"%s will win after %d moves", (win?"Bob":"Alan"), turns);
        string res = temp;
        return res;
    }
};
