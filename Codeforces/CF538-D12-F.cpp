/*
each node's childern are represented as a subsegment of the array
the sum of lengthes of these subsegments is at most (n*log(n))
to calculate the number of elements in a subsegment that are smaller than the parnet we use a a BIT:
we iterate on the array numbers in increasing order
for each element we count the number of its invalid children in each segment and add 1 to its position in the BIT
*/
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
ll mod = 1e9 + 7;

const int N = 2e5 + 10;

int fen[N];
int n;
void update(int p,int val){
    for(int i = p;i <= n;i += i & -i)
        fen[i] += val;
}
int sum(int p){
    int ans = 0;
    for(int i = p;i;i -= i & -i)
        ans += fen[i];
    return ans;
}
int query(int l,int r)
{
    r = min(r, n);
    int res = sum(r);
    res -= sum(l-1);
    return res;
}



bool cmp(pair<int,int> a, pair<int,int> b)
{
    if(a.first == b.first)
        return a.second < b.second;
    return a.first < b.first;
}
pair<int,int>a[N];

ll ans[N];
int main()
{
    scanf("%d", &n);
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d", &x);
        a[i] = {x, i};
    }
    sort(a+1,a+n+1, cmp);
    for(int i=1;i<=n;i++)
    {
        int v = a[i].second;
        for(int k = 1;k<n;k++)
        {
            int lef = k*(v-1)+2;
            if(lef > n)
                break;
            int rit = k*v+1;
            int cur = query(lef, rit);
            ans[k] += cur;
        }
        update(v, 1);
    }
    for(int i=1;i<n;i++)
    {
        printf("%I64d%c",ans[i], " \n"[i==n-1]);
    }
}
