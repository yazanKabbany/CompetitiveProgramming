#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

double EPS = 1e-9;
const int N = 6;

double dp[(1<<N) + 10][N+10];
bool calced[(1<<N) + 10][N+10];

double p[N];
int n;

double calc(int msk, int pos)
{
    vector<int>v;
    for(int i=0;i<n;i++)if((1<<i)&msk)
        v.push_back(i);
    if((int)v.size() <= 1)
        return 0;
    pos = lower_bound(v.begin(), v.end(), pos)-v.begin();
    if(pos==v.size())
        pos = 0;

    if(calced[msk][pos])
        return dp[msk][pos];
    calced[msk][pos] = 1;
    double &res = dp[msk][pos];
    res = 0;
    double fail = 1;
    int cnt = 1;

    for(int i=pos;;i=(i+1)%(int)v.size())
    {
        double mx = 1e10;
        for(int j=0;j<(int)v.size();j++)if(j != i)
        {
            double got = calc(msk ^ (1<<v[j]), v[i]+1);
            mx = min(got, mx);
        }
        double cur = fail*p[v[i]]*(cnt + mx);
        res += cur;

        cnt++;
        fail*=(1-p[v[i]]);

        if((i+1)%(int)v.size() == pos)
            break;
    }
    res += fail*v.size();
    res /= (1-fail);
    return res;
}

class SchoolTrip
{
public:

    double duration(vector <int> probability)
    {
        n = probability.size();
        for(int i=0;i<n;i++)
            p[i] = probability[i]/100.0;
        double res = calc((1<<n)-1, 0);
        return res;
    }
};
int main()
{
    SchoolTrip obj;
    cout<<obj.duration({25,50,75})<<'\n';
}
