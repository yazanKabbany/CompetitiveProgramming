#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 5e5 + 10;
bool composite[N];

void init()
{
    int n = 474747;
    for(ll i = 2;i*i<=n;i++)
        if(!composite[i])
            for(ll j = i*i; j<=n;j+=i)
                composite[j] = 1;

}
int n, k;
struct STATE
{
    STATE()
    {
        type = 0;
        x = 0;
    }
    STATE(int type, int x)
    {
        this->type = type;
        this->x = x;
    }
    int type;
    int x;
    bool operator <(const STATE& other)const
    {
        if(type == other.type)
        {
            if(type == 0)
                return x < other.x;
            else ///if(type == 1)
                return x>other.x;
        }
        return type < other.type;
    }
};
STATE dpme[N];
STATE dphim[N];

STATE solve()
{
    multiset<STATE>me;
    multiset<STATE>him;
    me.insert(STATE{1, -1});
    him.insert(STATE{1, -1});

    dpme[1] = dphim[1] = {1, -1};

    k++;
    for(int i=2;i<=n;i++)
    {
        if(i-k>=1)
        {
            me.erase(me.find(STATE{dpme[i-k]}));
            him.erase(him.find(STATE{dphim[i-k]}));
        }
        if(i == n)
        {
            STATE got = *him.begin();
            dpme[i] = STATE{!got.type, got.x+1};
            return dpme[i];
        }
        if(!composite[i])
        {
            STATE got = *me.begin();
            dpme[i] = {1, -1};
            dphim[i] = STATE{!got.type, got.x+1};
        }
        else
        {
            STATE got = *him.begin();
            dpme[i] = STATE{!got.type, got.x+1};
            dphim[i] = {1, -1};
        }
        me.insert(STATE{dpme[i]});
        him.insert(STATE{dphim[i]});
    }
    return STATE{0, 0};
}

class PrimeCompositeGame
{
public:
    int theOutcome(int n, int k)
    {
        init();
        ::n = n;
        ::k = k;
        STATE res = solve();
        int x = res.x;
        if(!res.type)
            x*=-1;

        return x;
    }
};
