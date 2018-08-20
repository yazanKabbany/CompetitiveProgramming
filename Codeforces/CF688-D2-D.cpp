/*
https://codeforces.com/blog/entry/45770
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e6 + 10;
int a[N];

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    for(int i=0;i<n;i++)
        scanf("%d", a+i);

    vector<int>to_div;
    for(int i=2;i*i<=k;i++)if(k%i == 0)
    {
        int num = 1;
        while(k%i == 0)
        {
            k/=i;
            num*=i;
        }
        to_div.push_back(num);
    }
    if(k > 1)
        to_div.push_back(k);
    for(auto num:to_div)
    {
        bool ok = false;
        for(int i=0;!ok &&i<n;i++)
            ok = ok || (a[i]%num == 0);
        if(!ok)
            return puts("No"), 0;
    }
    puts("Yes");
}
