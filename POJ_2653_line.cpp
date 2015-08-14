#include <cmath>
#include <cstdio>
#include <queue>
#include <iomanip>
using namespace std;

const double pi = acos(-1.0);
inline double sqr(double x)
{
    return x * x;
}

const double eps = 1e-8;
int cmp(double x)
{
    if (fabs(x) < eps) return 0;
    if (x > 0) return 1;
    return -1;
}

struct point
{
    double x, y;
    point(){}
    point(double a, double b):x(a), y(b){}
    void input()
    {
        scanf("%lf%lf", &x, &y);
    }

    friend point operator + (const point &a, const point &b)
    {
        return point(a.x + b.x, a.y + b.y);
    }

    friend point operator - (const point &a, const point &b)
    {
        return point(a.x - b.x, a.y - b.y);
    }

    friend bool operator == (const point &a, const point &b)
    {
        return cmp(a.x - b.x) == 0 && cmp(a.y - b.y) == 0;
    }

    friend point operator * (const point &a, const double &b)
    {
        return point(a.x * b, a.y * b);
    }

    friend point operator * (const double &a, const point &b)
    {
        return point(a * b.x, a * b.y);
    }

    friend point operator / (const point &a, const double &b)
    {
        return point(a.x / b, a.y / b);
    }

    double norm()
    {
        return sqrt(sqr(x) + sqr(y));
    }
};

double det(const point &a, const point &b)
{
    return a.x * b.y - a.y * b.x;
}

double dot(const point &a, const point &b)
{
    return a.x * b.x + a.y * b.y;
}

double dist(const point &a, const point &b)
{
    return (a - b).norm();
}

point rotate_point(const point &p, double A)
{
    double tx = p.x, ty = p.y;
    return point(tx * cos(A) - ty * sin(A), tx * sin(A) + ty * cos(A));
}

struct line
{
    point a, b;
    line(){}
    line(point x, point y): a(x), b(y) {}
};

line point_make_line(const point a, const point b)
{
    return line(a, b);
}

bool PointOnSegment(point p, point s, point t)
{
    return cmp(det(p - s, t - s)) == 0 && cmp(dot(p - s, p - t)) <= 0;
}

bool parallel(line a, line b)
{
    return !cmp(det(a.a - a.b, b.a - b.b));
}

bool line_make_point(line a, line b, point &res)
{
    if (parallel(a, b)) return false;
    double s1 = det(a.a - b.a, b.b - b.a);
    double s2 = det(a.b - b.a, b.b - b.a);
    res = (s1 * a.b - s2 * a.a) / (s1 - s2);
    return true;
}

queue<pair<line, int> > q;
int main()
{
    int n, t;
    int size;
    line x;
    point p;
    pair<line, int> temp;
    bool thefirst;
    scanf("%d", &n);
    while (n != 0)
    {
        t = 0;
        while (t != n)
        {
            t++;
            x.a.input();
            x.b.input();
            //printf("%lf %lf %lf %lf\n", x.a.x, x.a.y, x.b.x, x.b.y);
            size = q.size();
            for (int i = 0; i < size; ++i)
            {
                temp = q.front(); q.pop();
                //if (t == 4)
                //   printf("%d %d", line_make_point(x, temp.first, p), temp.second);
                if (line_make_point(x, temp.first, p) && PointOnSegment(p, x.a, x.b) && PointOnSegment(p, temp.first.a, temp.first.b)) 
                    continue;
                else
                    q.push(temp);
            }
            q.push(pair<line, int>(x, t));
        }
        printf("Top sticks:");
        thefirst = true;
        while (!q.empty())
        {
            temp = q.front();q.pop();
            if (!thefirst) printf(",");
            thefirst = false;
            printf(" %d", temp.second);
        }
        printf(".\n");
        scanf("%d", &n);
    }
    return 0;
}
