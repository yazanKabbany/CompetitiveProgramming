#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


const int N = 1e5 + 10;
ll a[N];
int main()
{
    ll d, l, n;
    cin>>d>>l>>n;
    for(int i=0;i<n;i++)
    {
        int x;
        scanf("%d", &x);
        a[i] = x;
    }
    a[n++] = 0;
    a[n++] = d;
    sort(a,a+n);
    ll res = 0;
    for(int i=1;i<n;i++)if(a[i] - a[i-1] > l)
    {
        ll base = 2*(a[i] - a[i-1] - l);
        ll h = base/2;
        ll cur = base * h;
        res += cur;

    }
    printf("%.7f\n", res/(8.0*d));
}
