#include<bits/stdc++.h>
typedef long long ll;
using namespace std;


const int N = 2e5  + 10;
ll dp[N];
ll a[N];
ll sum[N];


int main()
{
    int n;
    scanf("%d", &n);
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    sum[0] = a[0];
    for(int i=1;i<n;i++)
    {
        sum[i] = a[i] + sum[i-1];
    }
    ll mx = sum[n-1];
    dp[n-1] = 0;

    for(int i=n-2;i>=0;i--)
    {
        dp[i] = mx;
        if(i)
            mx = max(mx, -dp[i] + sum[i]);
    }
    ll res = dp[0];
    cout<<res<<'\n';
}
