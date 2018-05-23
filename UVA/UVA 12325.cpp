/*
First of all if the box size is a multiple of lcm(s1, s2) then we can fill it with only one type of treasure (the one with 
the biggest v/s) 
for a size less than lcm(s1, s2) we can fill the box with a combination of the 2 treasures using a for loop

the solution goes like this:
we fill a size less than lcm(s1, s2) with a combination of the 2 treasures and the rest of the box with the treasure of 
v/s

why not TLE?
because we'll only do [(n%lcm(s1, s2))/max(s1, s2)] iteration  
*/


#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int main()
{
//    freopen("out.txt", "w", stdout);
    int t;
    scanf("%d", &t);
    int CASE = 1;
    while(t--)
    {
        ll n, s1, v1, s2, v2;
        scanf("%lld %lld %lld %lld %lld",&n, &s1, &v1, &s2, &v2);

        ll lcm = s1*s2/__gcd(s1, s2);
        ll res = 0;
        if(n >= 2*lcm)
        {
            ll cnt_lcm = n/lcm;
            cnt_lcm --;
            res = cnt_lcm*max((lcm/s1)*v1, (lcm/s2)*v2);
            n -= cnt_lcm*lcm;
        }
        if(s1 < s2)
            swap(s1, s2), swap(v1 , v2);

        ll added = 0;
        for(ll i=0;i*s1 <= n; i++)
        {
            ll cur = i*v1;
            ll rem = n-i*s1;
            ll other_cnt = rem/s2;
            cur += other_cnt*v2;
            added = max(added, cur);
        }
        printf("Case #%d: %lld\n", CASE++,res + added);
    }
}

