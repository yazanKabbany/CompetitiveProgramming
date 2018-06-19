/*
for every point (x0, y0)
find the maximum number of points (xi, yi) that have the values (y0 - yi)/(x0 - xi) equal
it can be done using a map
*/

#include <bits/stdc++.h>
#include<sstream>
using namespace std;

typedef long long ll;

ll x[1000];
ll y[1000];

pair<ll, ll> get_vec(int i, int j)
{
    ll dx = x[i] - x[j];
    ll dy = y[i] - y[j];
    bool neg = (dx < 0 )^(dy < 0);
    dx = abs(dx);
    dy = abs(dy);
    ll g = __gcd(dx, dy);
    dx /= g;
    dy /= g;
    if(neg)
    {
        if(dx)
            dx*=-1;
        else
            dy*=-1;
    }
    return {dx, dy};
}
int main()
{

    int TC;
    scanf("%d\n\n", &TC);
    while(TC--)
    {
        int n = 0;

        while(1)
        {
            string input;
            getline(cin, input);
            if(input.empty())
                break;
             istringstream str(input);

            int a, b;
            str>>a>>b;
            x[n] = a;
            y[n] = b;
            n++;
        }
        int ans = 0;
        for(int i=0;i<n;i++)
        {
            map<pair<ll, ll>, int> mp;
            int cur = 1;
            for(int j=0;j<n;j++)if(i != j)
            {
                auto vec = get_vec(i, j);
                mp[vec]++;
                cur = max(cur, mp[vec]+1);
            }
            ans = max(ans, cur);
        }
        printf("%d\n", ans);
        if(TC)
            puts("");
    }
    return 0;
}

