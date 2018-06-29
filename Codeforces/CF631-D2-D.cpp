/*
same as the editorial
https://codeforces.com/blog/entry/43551

*/

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

typedef pair<ll,char> cmprsd;

vector<cmprsd>a;
vector<cmprsd>b;

vector<cmprsd>fix(const vector<cmprsd> &a)
{
    vector<cmprsd> res;
    for(auto c:a)
    {
        if(!res.empty() && res.back().second == c.second)
        {
            res[(int)res.size()-1].first += c.first;
        }
        else
            res.push_back(c);
    }
    return res;
}


vector<int> PrefixFunction(vector<cmprsd> S) {//s=pattern+"#"+text
    vector<int> p(S.size());
    int j = 0;
    for (int i = 1; i < (int)S.size(); i++) {
        while (j > 0 && S[j] != S[i])
            j = p[j-1];

        if (S[j] == S[i])
            j++;
        p[i] = j;
    }
    return p;
}

bool contains(cmprsd a, cmprsd b)
{
    return a.second == b.second && a.first >= b.first;
}
int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i=0;i<n;i++)
    {
        char s[5];
        int cnt;
        scanf("%d-%s", &cnt, s);
        a.push_back({cnt, s[0]});
    }
    for(int i=0;i<m;i++)
    {
        char s[5];
        int cnt;
        scanf("%d-%s", &cnt, s);
        b.push_back({cnt, s[0]});
    }
    a=fix(a);
    b=fix(b);
    swap(a, b);
    if((int)a.size() <3)
    {
        ll ans = 0;
        if((int)a.size() == 1)
        {
            for(auto x:b)
            {
                if(contains(x, a[0]))
                {
                    ans += x.first - a[0].first + 1;
                }
            }
        }
        else
        {
            for(int i=0;i+1<(int)b.size();i++)
            {
                if(contains(b[i], a[0]) && contains(b[i+1], a[1]))
                    ans++;
            }
        }
        cout<<ans<<'\n';
        return 0;
    }
    vector<cmprsd> c (a.begin()+1, a.end()-1);
    c.push_back({-1, 'A'});
    for(auto x:b)
        c.push_back(x);

    vector<int>p = PrefixFunction(c);
    int pat_len = (int)a.size()-2;
    ll ans = 0;
    for(int i=0;i<(int)p.size();i++)if(p[i] == pat_len)
    {
        int bef = i - pat_len ;
        int aft = i + 1;
        if(aft >= (int)p.size())
            continue;
        if(bef < 0)
            continue;
        if(contains(c[bef], a[0]) && contains(c[aft], a.back()))
            ans++;
    }
    cout<<ans<<'\n';
}
