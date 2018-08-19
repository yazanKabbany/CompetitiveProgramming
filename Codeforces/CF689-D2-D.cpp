/*
https://codeforces.com/blog/entry/45912
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 2e5 + 10;
int a[N];
int first_big[N];
int b[N];
int first_small[N];

int main()
{
    int n;
    scanf("%d", &n);
    for(int i=0;i<n;i++)
        scanf("%d", a+i);
    for(int i=0;i<n;i++)
        scanf("%d", b+i);
    a[n] = 2e9;
    b[n] = -2e9;
    stack<int>mxs;
    mxs.push(n);
    stack<int>mns;
    mns.push(n);
    for(int i=n-1;i>=0;i--)
    {
        while(a[i] >= a[mxs.top()])
            mxs.pop();
        first_big[i] = mxs.top();
        mxs.push(i);

        while(b[i] <= b[mns.top()])
            mns.pop();
        first_small[i] = mns.top();
        mns.push(i);
    }

    set<pair<int, int > >mx;
    set<pair<int, int > >mn;
    ll ans = 0;
    for(int i=0, j=-1;i<n;i++)
    {
        if(j < i)
        {
            j = i;
            mx.insert({a[i], i});
            mn.insert({b[i], i});
        }
        while(j < n && mx.rbegin()->first <  mn.begin()->first)
        {
            j++;
            mx.insert({a[j], j});
            mn.insert({b[j], j});
        }
        if(mx.rbegin()->first == mn.begin()->first)
        {
            int ra = first_big[mx.rbegin()->second];
            int rb = first_small[mn.begin()->second];
            int r = min(ra, rb);
            ans += r-j;
        }
        mx.erase({a[i], i});
        mn.erase({b[i], i});
    }
    printf("%lld\n", ans);
}
