#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int N = 2e5 + 10;
map<ll, ll>mp;
map<pair<ll,ll>, ll>same;
int main()
{
    int n;
    ll a, b;
    cin>>n>>a>>b;
    for(int i=0;i<n;i++)
    {
        int x, vx, vy;
        scanf("%d %d %d", &x, &vx, &vy);
        mp[a*vx - vy]++;
        same[{vx,vy}]++;
    }
    ll res = 0;
    for(auto p:mp)
    {
        res += p.second*(p.second-1);
    }
    for(auto p:same)
    {
        res -= p.second*(p.second-1);
    }
    printf("%I64d\n", res);
}
