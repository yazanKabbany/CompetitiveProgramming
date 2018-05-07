/*
find the centroid of the polygon
for every query of type 1 find the transformation matrix that rotates the polygon around the pin point
for every query of type 2 multiply transformation matrices with the query point to get its current position
*/
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <complex>
#include <iostream>
#include <cstdio>
#include<set>
using namespace std;

typedef complex<long double> point;
#define sz(a) ((int)(a).size())
#define all(n) (n).begin(),(n).end()
#define EPS (1e-7)
#define OO 1e9
#define X real()
#define Y imag()
#define angle(v) (atan2((v).Y,(v).X))

point find_centroid(vector<point> &vertices)
{

        long double signedArea = 0.0;
        long double x0 = 0.0; // Current vertex X
        long double y0 = 0.0; // Current vertex Y
        long double x1 = 0.0; // Next vertex X
        long double y1 = 0.0; // Next vertex Y
        long double a = 0.0;  // Partial signed area
        long double c_x = 0;
        long double c_y = 0;
    for (int i=0; i<(int)vertices.size(); ++i)
    {
        int j = (i+1) % vertices.size();
        x0 = vertices[i].X;
        y0 = vertices[i].Y;
        x1 = vertices[j].X;
        y1 = vertices[j].Y;
        a = x0*y1 - x1*y0;
        signedArea += a;
        c_x += (x0 + x1)*a;
        c_y += (y0 + y1)*a;
    }
    signedArea *= 0.5;
    c_x /= (6.0*signedArea);
    c_y /= (6.0*signedArea);
    return point(c_x, c_y);
}


struct transformation
{
    long double a[4][4];
    transformation()
    {
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
        {
                a[i][j] = 0;
                if(i == j)
                    a[i][j] = 1;
        }
    }
    void add_transformation(const transformation &other)
    {
        transformation t;
        t.a[0][0] = t.a[1][1] = t.a[2][2] = 0;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                for(int k=0;k<3;k++)
                    t.a[i][j] += other.a[i][k] * a[k][j];
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                a[i][j] = t.a[i][j];
    }
    point calc_pos(point p)
    {
        point res ;
        res.real(a[0][0]*p.X + p.Y *a[0][1]+ a[0][2]);
        res.imag(a[1][0]*p.X + p.Y *a[1][1]+ a[1][2]);
        return res;
    }
}total_trans;

transformation movemoent(long double dx, long double dy)
{
    transformation t;
    t.a[0][2] = dx;
    t.a[1][2] = dy;
    return t;
}
transformation rotation(long double theta)
{
    transformation t;
    long double c = cos(theta);
    long double s = sin(theta);
    t.a[0][0] = t.a[1][1] = c;
    t.a[0][1] = -s;
    t.a[1][0] = s;
    return t;
}
vector<point> poly;
point centroid;
long double PI = acos(-1);
void stabilize(point pin)
{
    point cur_pin = total_trans.calc_pos(pin);

    transformation a = movemoent(-cur_pin.X, -cur_pin.Y);
    total_trans.add_transformation(a);
    point cur_centroid = total_trans.calc_pos(centroid);

    point vec_a = cur_centroid;
    point vec_b = point{0, -1};
    long double Angle_b = angle(vec_b) + 2*PI;
    long double Angle_a = angle(vec_a);
    long double theta =  Angle_b- Angle_a;

    transformation b = rotation(theta);
    total_trans.add_transformation(b);

    transformation c = movemoent(cur_pin.X, cur_pin.Y);
    total_trans.add_transformation(c);
}
int main()
{
    int n, q;
    scanf("%d %d", &n, &q);
    for(int i=0;i<n;i++)
    {
        int x,y;
        scanf("%d %d", &x, &y);
        poly.push_back(point{x,y});
    }
    point del = poly[0];
    for(auto &p:poly)
        p -= del;
    centroid = find_centroid(poly);
    multiset<int>pins{0, 1};
    while(q--)
    {
        int type;
        scanf("%d", &type);
        if(type == 1)
        {
            int f, t;
            scanf("%d %d", &f, &t);
            f--, t--;
            pins.erase(pins.find(f));
            stabilize(poly[*pins.begin()]);

            pins.insert(t);
        }
        else
        {
            int v;
            scanf("%d", &v);
            v--;
            point new_pos = total_trans.calc_pos(poly[v]);
            new_pos += del;
            printf("%.8f %.8f\n",(double) new_pos.X, (double)new_pos.Y);
        }
    }
}
