#include <iostream>
#include <math.h>
#define sq(x) (x) * (x)

using namespace std;

int n = 0, cnt;
double a, b, r, x, y, theta;

struct node
{
    double x, y;
} p[400040], s[400040];

double check(node a1, node a2, node b1, node b2)
{
    return (a2.x - a1.x) * (b2.y - b1.y) - (a2.y - a1.y) * (b2.x - b1.x);
}
double dis(node a, node b)
{
    return sqrt(sq(a.x - b.x) + sq(a.y - b.y));
}
bool cmp(node p1, node p2)
{
    double tmp = check(p1, p[1], p2, p[1]);
    if (tmp > 0)
        return 1;
    else if (tmp == 0 && dis(p[0], p1) < dis(p[0], p2))
        return 1;
    return 0;
}
void add(double x, double y)
{
    n++;
    p[n].x = x, p[n].y = y;
    if (p[n].y < p[1].y)
        swap(p[n], p[1]);
}
void deal()
{
    sort(p + 2, p + 1 + n, cmp);
    s[1] = p[1];
    cnt = 1;
    for (int i = 2; i <= n; i++)
    {
        while (cnt > 1 && check(s[cnt - 1], s[cnt], s[cnt], p[i]) <= 0)
            cnt--;
        s[++cnt] = p[i];
    }
    s[cnt + 1] = p[1];
}

double caculate()
{
    double ans = 0;
    for (int i = 1; i <= cnt; i++)
        ans += dis(s[i], s[i + 1]);
    return ans;
};

int main()
{
    scanf("%d%lf%lf%lf", &n, &a, &b, &r);
    a -= 2 * r;
    b -= 2 * r;
    double l = sqrt(a * a + b * b) / 2;
    double phi = atan(a / b);
    while (n--)
    {
        scanf("%lf%lf%lf", &x, &y, &theta);
        double dx = cos(theta + phi) * l;
        double dy = sin(theta + phi) * l;
        add(x + dx, y + dy);
        add(x - dx, y - dy);
        dx = cos(theta - phi) * l;
        dy = sin(theta - phi) * l;
        add(x + dx, y + dy);
        add(x - dx, y - dy);
    }
    deal();
    printf("%.2lf", caculate() + acos(-1) * 2 * r);
    return 0;
}