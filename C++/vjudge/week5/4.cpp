#include <iostream>
#include <math.h>
using namespace std;

const double pi = acos(-1);
const int MAXN = 10005;
double n, x, y, theta, a, b, r;

struct point
{
    double x, y;
    point(double _x, double _y) : x(_x), y(_y) {}
    inline double operator*(const point &p2) const
    {
        return x * p2.y - y * p2.x;
    }
    inline point operator+(const point &p2) const
    {
        return (x + p2.x, y + p2.y);
    }
    inline point operator-(const point &p2) const
    {
        return (x - p2.x, y - p2.y);
    }
} p[MAXN * 4];

bool cmp(const point p1, const point p2)
{
    return (p1.x > p2.x ? true : p1.y > p2.y ? true
                                             : false);
}

bool cmpv(const point p1, const point p2)
{
    return (p1 * p2 > 0) || equal(p1 * p2, 0);
}

inline double dis(const point p1, const point p2)
{
    return (p1.x - p2.x)
}

void caculate_point(const double &x, const double &y, const double &theta)
{
}

void tubao(point *p)
{
}

int main()
{
    scanf("%d%lf%lf%lf", &n, &a, &b, &r);
    a -= 2 * r;
    b -= 2 * r;
    double l = sqrt(a * a + b * b) / 2;
    double phi = atan(a / b);
    for (int i = 0; i < n; i++)
    {
        scanf("%lf%lf%lf", &x, &y, &theta);
        double dx = cos(theta + phi) * l;
        double dy = sin(theta + phi) * l;
        p[4 * i] = point(x + dx, y + dy);
        p[4 * i + 1] = point(x - dx, y - dy);
        double dx = cos(theta - phi) * l;
        double dy = sin(theta - phi) * l;
        p[4 * i + 2] = point(x + dx, y + dy);
        p[4 * i + 3] = point(x - dx, y - dy);
    }
    return 0;
}