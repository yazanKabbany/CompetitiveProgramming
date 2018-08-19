#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll>cur;
vector<ll>a[2][30];
ll fact[30];

int k;
ll target;
int cur_idx;
void build(int i, int taken, ll sum)
{
    if(taken > k || sum > target)
        return;
    if(i == (int)cur.size())
    {
        a[cur_idx][taken].push_back(sum);
        return;
    }
    build(i+1, taken, sum);
    build(i+1, taken,sum+cur[i]);
    if(cur[i]<19)
    {
        build(i+1, taken+1, sum+fact[cur[i]]);
    }
}
int main()
{
    fact[0] = 1;
    for(int i=1;i<19;i++)
        fact[i] = fact[i-1]*i;
    int n;
    scanf("%d %d %lld", &n, &k, &target);
    vector<ll>nums[2];
    for(int i=0;i<n;i++)
    {
        int x;
        scanf("%d", &x);
        nums[i&1].push_back(x);
    }
    cur = nums[0];
    cur_idx = 0;
    build(0, 0, 0);
    cur = nums[1];
    cur_idx = 1;
    build(0, 0, 0);
    for(int i=0;i<=k;i++)
        for(int j=0;j<2;j++)
        {
            sort(a[j][i].begin(), a[j][i].end());
        }
    ll ans = 0;
    for(int i=0;i<=k;i++)
        for(int j=0;j<(int)a[0][i].size();)
        {
            auto r = equal_range(a[0][i].begin()+j,a[0][i].end(), a[0][i][j]);
            ll len_r = r.second - r.first;
            for(int k2=k-i;k2>=0;k2--)
            {
                auto r2 = equal_range(a[1][k2].begin(), a[1][k2].end(), target - a[0][i][j]);
                ll len_r2 = r2.second - r2.first;
                ans += len_r*len_r2;
            }
            j = r.second - a[0][i].begin();
        }
    cout<<ans<<'\n';
}
