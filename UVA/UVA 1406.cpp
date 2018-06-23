/*
pre-calculate all possible query
each type 2 query is dfined as a the number that needs to be added and the bit to check it's state

make a frequency array of the numbers
1) the first (2^15) element have the MSB 0, the last (2^15) element have the MSB 1
2) adding a number to all the array elements is the same as rotating the frequency array 

repeat 1 & 2 (2^16) times

after that delete the MSB from all the numbers and resolve the problem just like above
*/

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 2*(1<<16)+10;

int freq[N];

ll a[N];

ll ans[20][N];
int main()
{
    int n;
    int TC = 1;
    while (scanf("%d", &n), n != -1)
    {
        memset(freq, 0, sizeof freq);
        for(int i=0;i<n;i++)
        {
            int x;
            scanf("%d", &x);
            freq[x]++;
        }

        for(int bit = 15;bit>=0; bit--)
        {
            int msk = (1<<(bit+1))-1;
            memset(a,0, sizeof a);
            for(int i=0;i<(1<<16);i++)
            {
                a[msk&i] += freq[i];
            }
            int len = msk+1;
            for(int i=0;i<len;i++)
                a[i+len] = a[i];
            for(int i=1;i<2*len;i++)
            {
                a[i] += a[i-1];
            }

            for(int lef = 0, added = 0;lef<len;lef++, added--)
            {
                int rit = lef + len/2 - 1;
                ll cur = a[rit] - (lef>0?a[lef-1]:0);
                ans[bit][(len+added)%len] = a[len-1] - cur;
            }
        }

        ll res = 0;
        ll added = 0;
        while(1)
        {

            char s[4];
            scanf("%s", s);
            if(s[0]=='E')
                break;
            if(s[0] == 'C')
            {
                int x;
                scanf("%d", &x);
                added += x;
                added%=(1<<16);
            }
            else ///'Q'
            {
                int bit ;
                scanf("%d", &bit);
                int msk = (1<<(bit+1))-1;
                int q_added = added&msk;
                ll cur = ans[bit][q_added];
                res += cur;
            }
        }
        printf("Case %d: %lld\n",TC++ ,res);
    }
}
