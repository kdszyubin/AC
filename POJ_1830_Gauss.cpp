#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

#define MAXN 30
#define EPS 1e-8
bool l[MAXN];
double a[MAXN][MAXN + 1];
double x[MAXN];
int n;

inline int solve(double a[][MAXN + 1], bool l[], double ans[], const int &n)
{
    int res = 0, r = 0;
    for (int i = 0; i < n; ++i)
        l[i] = false;
    for (int i = 0; i < n; ++i)
    {
        for (int j = r; j < n; ++j)
            if (fabs(a[j][i]) > EPS)
            {
                for (int k = i; k <= n; ++k)
                    swap(a[j][k], a[r][k]);
                break;
            }
	    if (fabs(a[r][i]) < EPS)
	    {
	        ++res;
	        continue;
	    }
	    for (int j = 0; j < n; ++j)
	        if (j != r && fabs(a[j][i]) > EPS)
	        {
	            double tmp = a[j][i] / a[r][i];
	            for (int k = i; k <= n; ++k)
	                a[j][k] -= tmp * a[r][k];
	        }
	    l[i] = true, ++r;
    }
    for (int j = r; j < n; ++j)
        if (fabs(a[j][n]) > EPS) return -1;
    for (int i = 0; i < n; ++i)
        if (l[i])
            for (int j = 0; j < n; ++j)
                if (fabs(a[j][i]) > 0)
                    ans[i] = a[j][n] / a[j][i];
    return res;
}

int main()
{
    int ini[MAXN];
    int tar[MAXN];
    int t;
    int xi, yj;
    int ans;
    int res;
    scanf("%d", &t);
    while (t--)
    {
        memset(l, 0, sizeof(l));
        memset(a, 0, sizeof(a));
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
            scanf("%d", &ini[i]);
        for (int i = 0; i < n; ++i)
            scanf("%d", &tar[i]);
        for (int j = 0; j < n; ++j)
            a[j][n] = ini[j] != tar[j];
        for (xi = 1; xi <= n; ++xi)
            a[xi - 1][xi - 1] = 1;
        scanf("%d %d", &xi, &yj);
        while (xi != 0 && yj != 0)
        {
            a[xi - 1][xi - 1] = 1;
            a[yj - 1][xi - 1] = 1;
            scanf("%d %d", &xi, &yj);
        }
        res = solve(a, l, x, n);
        if (res == -1)
            printf("Oh,it's impossible~!!\n");
        else
            printf("%d\n", 1 << res);
    }
    return 0;
}
        


