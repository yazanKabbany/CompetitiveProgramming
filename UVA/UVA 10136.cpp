/*
try every cicle that toches 2 points 
the answer is the circle that contains the maximum number of Chocolate Chip
Complexity O(n*n*n)
*/


#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const double EPS = 1e-11;
typedef complex<double> point;

#define X real()
#define Y imag()
#define vec(a,b) ((b) - (a))
#define dot(a,b) ((conj(a)*(b)).real())
#define cross(a,b) ((conj(a)*(b)).imag())
#define length(a)  ((double)hypot((a).Y, (a).X))
#define normalize(v) ((v) / length((v)))
#define lengthSqr(v) (dot(v,v))
#define same(a,b) (lengthSqr(vec(a,b))<EPS)
#define polar(r,t) ((r)*exp(point(0,(t))))
#define rotate(v,t) (polar(v,t))
const double R = 2.5;
long double cosRule(long double a, long double b, long double c) {
        // Handle denom = 0
        long double res = (b * b + c * c - a * a) / (2 * b * c);
        if ( fabs(res-1)<EPS)
                res = 1;
        if ( fabs(res+1)<EPS)
                res = -1;
        return acos(res);
}
int circleCircleIntersection(const point &c1, const double&r1,
                const point &c2, const double&r2, point &res1, point &res2) {
        if (same(c1,c2) && fabs(r1 - r2) < EPS) {
                res1 = res2 = c1;
                return fabs(r1) < EPS ? 1 : -1;
        }
        double len = length(vec(c1,c2));
        if (fabs(len - (r1 + r2)) < EPS || fabs(fabs(r1 - r2) - len) < EPS) {
                point d, c;
                double r;
                if (r1 > r2)
                        d = vec(c1,c2), c = c1, r = r1;
                else
                        d = vec(c2,c1), c = c2, r = r2;
                res1 = res2 = normalize(d) * r + c;
                return 1;
        }
        if (len > r1 + r2 || len < fabs(r1 - r2))
                return 0;
        double a = cosRule(r2, r1, len);
        point c1c2 = normalize(vec(c1,c2)) * r1;
        res1 = rotate(c1c2,a) + c1;
        res2 = rotate(c1c2,-a) + c1;
        return 2;
}

vector<point>pts;
int calc_cir_at(point p1)
{
    int ans = 0;
    for(auto p:pts)
    {
        double d = length(vec(p1, p));
        if(d <= R+EPS)
            ans++;
    }
    return ans;
}
int main()
{
//   freopen("out.txt","w",stdout);
    int t;
    cin>>t;
    cin.ignore();
    cin.ignore();
    while(t--)
    {
        int n=0;
        pts.clear();
        for(int i=0;;i++)
        {
            double x, y;
            string input;
            getline(cin, input);
            if(input.empty())
                break;
            istringstream in(input);
            in>>x;
            in>>y;
            n++;
            pts.push_back(point(x, y));
        }
        int ans = 1;
        for(int i=0;i<(int)pts.size();i++)
            for(int j=i+1;j<(int)pts.size();j++)
            {
                    point p1, p2;
                    int got = circleCircleIntersection(pts[i], R, pts[j],R,p1, p2);
                    if(got>0)
                    {
                        int cur = calc_cir_at(p1);
                        ans = max(cur, ans);
                        cur = calc_cir_at(p2);
                        ans = max(cur, ans);
                    }
            }
        cout<<ans<<'\n';
        if(t)
            cout<<'\n';
    }
    return 0;
}
