#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

#define MAXN 105
#define INF 0x3f3f3f3f

struct Edge
{
    int from, to;
    double cost;
};

//点u和点v均允许值为0
struct KM
{
    int xn, yn, m;
    vector<Edge> edges;
    vector<int> G[MAXN];
    bool s[MAXN], t[MAXN];
    double lx[MAXN], ly[MAXN];
    int cx[MAXN], cy[MAXN];
    double slack[MAXN];

    void AddEdge(int from, int to, double cost)
    {
        edges.push_back(Edge{from, to, cost});
        m = edges.size();
        G[from].push_back(m - 1);
    }

    bool equ(double a, double b)
    {
        return (a - b <= 0.00001 && b - a <= 0.00001);
    }

    bool path(int u)
    {
        s[u] = true;
        for (int i = 0; i < G[u].size(); ++i)
        {
            Edge& e = edges[G[u][i]];
            if (!t[e.to] && equ(lx[u] + ly[e.to], e.cost))
            {
                t[e.to] = true;
                if (cy[e.to] == -1 || path(cy[e.to]))//1
                {
                    cx[u] = e.to;
                    cy[e.to] = u;
                    return true;
                }
            }
            else if (slack[e.to] > lx[u] + ly[e.to] - e.cost)//2
                slack[e.to] = lx[u] + ly[e.to] - e.cost;
        }
        return false;
    }

    double update()
    {
        double a = INF;
        for (int v = 0; v < yn; ++v)
            if (!t[v] && slack[v] < a)
                a = slack[v];
        for (int u = 0; u < xn; ++u)
            if (s[u]) lx[u] -= a;
        for (int v = 0; v < yn; ++v)
            if (t[v])
                ly[v] += a;
            else
                slack[v] -= a;
        return a;
    }

    void MaxMatch()
    {
        for (int i = 0; i < xn; ++i) lx[i] = 0;//lx相对与e.cost，要求为无穷大，
                                                //且2处要求slack初始值要相对与lx为无穷大
        memset(ly, 0, sizeof(ly));
        memset(cx, 0xff, sizeof(cx));//1处要求cx初值为-1
        memset(cy, 0xff, sizeof(cy));

        for (int u = 0; u < xn; ++u)
        {
            for (int v = 0; v < yn; ++v) slack[v] = INF;
            while (1)
            {
                memset(s, 0, sizeof(s));
                memset(t, 0, sizeof(t));
                if (path(u))
                    break;
                else
                    if (update() == INF) break;//找不到值可以更新就停止当前u点的配对
            }
        }
    }
};

struct KM g;
void read_data()
{
    double x[MAXN], y[MAXN]; 
    int n;
    cin >> n;
    g.xn = n;
    g.yn = n;
    for (int i = 0; i < n; ++i)
        cin >> x[i] >> y[i];
    for (int v = 0; v < n; ++v)
    {
        double xt, yt;
        cin >> xt >> yt;
        for (int u = 0; u < n; ++u)
            g.AddEdge(u, v, -1 * sqrt((xt - x[u]) * (xt - x[u]) + (yt - y[u]) * (yt - y[u])));
    }
}

int main()
{
    read_data();
    g.MaxMatch();
    for (int i = 0; i < g.xn; ++i)
        cout << g.cx[i] + 1 << endl;
    return 0;
}
