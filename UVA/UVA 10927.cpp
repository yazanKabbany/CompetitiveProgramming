/*
add all the lights that lies on the same line segment that starts at 0, 0
sort them according to their distanceefrom the origin
for each light if their is a light that is closer to the origin and higher then this light is not visible
*/
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;


struct pole
{
    int x;
    int y;
    int z;
};
map< pair<int,int>, vector<pole> >mp;

int calc_g(int x,int y)
{
    x = abs(x);
    y = abs(y);
    return  __gcd(x, y);
}

bool cmp(pole &a, pole &b)
{
    return 1LL*a.x*a.x + a.y*a.y < 1LL*b.x*b.x + b.y*b.y;
}
int main()
{
    int T = 1;
    int n;
    while(scanf("%d", &n), n)
    {
        mp.clear();
        for(int i=0;i<n;i++)
        {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            int g = calc_g(x, y);
            int xx = x/g;
            int yy = y/g;
            mp[{xx, yy}].push_back({x, y, z});
        }
        vector<pair<int,int> >hidden;
        for(auto &p: mp)
        {
            sort(p.second.begin(), p.second.end(), cmp);
            int mx_len = -10;
            for(auto pol:p.second)
            {
                if(pol.z <= mx_len)
                    hidden.push_back({pol.x, pol.y});
                mx_len = max(mx_len, pol.z);
            }
        }
        printf("Data set %d:\n", T++);
        if(hidden.empty())
        {
            puts("All the lights are visible.");
        }
        else
        {
            sort(hidden.begin(), hidden.end());
            puts("Some lights are not visible:");
            for(int i=0;i<(int)hidden.size();i++)
            {
                printf("x = %d, y = %d%c\n", hidden[i].first, hidden[i].second,";."[i==(int)hidden.size()-1]);
            }
        }
    }

}

