#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

#define MAXN 1005
#define INF 0x3f3f3f3f
struct Edge
{
    int from, to, cap, flow, cost;
};

struct MCMF
{
    int n, m, s, t;
    vector<Edge> edges;
    vector<int> G[MAXN];
    int d[MAXN];
    int p[MAXN];
    int alpha[MAXN];
    bool inq[MAXN];
    
    void AddEdge(int from, int to, int cap, int cost)
    {
        edges.push_back(Edge{from, to, cap, 0, cost});
        edges.push_back(Edge{to, from, 0, 0, -cost});
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }

    bool BellmanFord(int s, int t, int &flow, int& cost)
    {
        queue<int> Q;
        memset(d, 0x3f, sizeof(d));
        memset(inq, 0, sizeof(inq));
        d[s] = 0;
        inq[s] = true;
        Q.push(s);
        alpha[s] = INF;
        //p[s];
        while (!Q.empty())
        {
            int u = Q.front(); Q.pop();
            inq[u] = false;
            for (int i = 0; i < G[u].size(); ++i)
            {
                Edge& e = edges[G[u][i]];
                if (d[e.to] > d[u] + e.cost && e.cap > e.flow)
                {
                    d[e.to] = d[u] + e.cost;
                    alpha[e.to] = min(alpha[u], e.cap - e.flow);
                    p[e.to] = G[u][i];
                    if (!inq[e.to])
                    {
                        inq[e.to] = true;
                        Q.push(e.to);
                    }
                }
            }
        }
        if (d[t] == INF) return false;
        flow += alpha[t];
        cost += alpha[t] * d[t];
        int u = t;
        while (u != s)
        {
            edges[p[u]].flow += alpha[t];
            edges[p[u]^1].flow -= alpha[t];
            u = edges[p[u]].from;
        }
        return true;
    }

    int Mincost(int s, int t)
    {
        int flow = 0, cost = 0;
        this->s = s;
        this->t = t;
        while (BellmanFord(s, t, flow, cost));
        return cost;
    }
};

struct MCMF g;
int n, m;
int source, target;

void read_data()
{
    int from, to, cost;
    cin >> n >> m;
    source = 0;
    target = n + 1;
    for (int i = 0; i < m; ++i)
    {
        cin >> from >> to >> cost;
        g.AddEdge(from, to, 1, cost);
        g.AddEdge(to, from, 1, cost);
    }
    g.AddEdge(source, 1, 2, 0);
    g.AddEdge(n, target, 2, 0);
}

int main()
{
    read_data();
    cout << g.Mincost(source, target) << endl;
    return 0;
}

