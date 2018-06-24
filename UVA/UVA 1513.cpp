/*
simulate the stack with a fenwick tree
initially each pos contains 1
after each removal we substract 1 from its position
and add 1 after the last element
thus th querys can be answerd as a range sum by fewick tree
*/
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
ll mod = 1e9 + 7;

const int N = 2e5 + 20;

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
    if(l > r)
        return 0;
    int res = sum(r);
    res -= sum(l-1);
    return res;
}
int pos[N];

int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        int n,m;
        scanf("%d %d", &n, &m);
        ::n = n+m+10;
        memset(fen, 0, sizeof fen);
        int top = n+1;
        for(int i=1;i<=n;i++)
        {
            update(i, 1);
            pos[i] = n-i+1;
        }
        for(int i=0;i<m;i++)
        {
            int x;
            scanf("%d", &x);
            int cur = pos[x];
            int ans = query(cur+1, ::n);
            printf("%d%c",ans, " \n"[i==m-1]);
            update(cur, -1);
            pos[x] = top;
            update(top, 1);
            top++;
        }
    }
}
