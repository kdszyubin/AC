#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

#define MAXN 100
#define MAXE (MAXN * MAXN)
struct Edge { 
    int from, to, cost, ord;
};

struct AOE
{
    int n, m;
    vector<Edge> edges;
    vector<int> G[MAXN];
    vector<int> G_rev[MAXN];
    int counti[MAXN], counto[MAXN];
    int e[MAXE];
    int l[MAXE];
    int Ee[MAXN];
    int El[MAXN];

    void AddEdge(int from, int to, int cost, int ord)
    {
        edges.push_back(Edge{from, to, cost, ord});
        m = edges.size();
        //cout << from << ' ' << to << ' ' << cost << ' ' << ord << endl;
        G[from].push_back(m - 1);
        G_rev[to].push_back(m - 1);
        //cout << ord << endl;
        counto[from]++;
        counti[to]++;
    }

    void toposort()
    {
        queue<int> Q;
        memset(Ee, 0, sizeof(Ee));
        for (int i = 0; i < n; ++i)
            if (counti[i] == 0)
            {
                Ee[i] = 0;
                Q.push(i);
            }
        while (!Q.empty())
        {
            int u = Q.front(); Q.pop();
            for (int i = 0; i < G[u].size(); ++i)
            {
                Edge& ex = edges[G[u][i]];
                counti[ex.to]--;
                if (counti[ex.to] == 0) 
                {
                    Q.push(ex.to);
                    //cout << ex.to << endl;
                }

                if (Ee[ex.to] < Ee[u] + ex.cost) Ee[ex.to] = Ee[u] + ex.cost;
                e[ex.ord] = Ee[u];
            }
        }
    }

    void irtoposort()
    {
        queue<int> Q;
        memset(El, 0x3f, sizeof(El));
        for (int i = 0; i < n; ++i)
            if (counto[i] == 0)
            {
                El[i] = Ee[i];
                Q.push(i);
            }
        while (!Q.empty())
        {
            int v = Q.front(); Q.pop();
            for (int i = 0; i < G_rev[v].size(); ++i)
            {
                Edge& ex = edges[G_rev[v][i]];
                counto[ex.from]--;
                if (counto[ex.from] == 0) Q.push(ex.from);
                if (El[ex.from] > El[v] - ex.cost) El[ex.from] = El[v] - ex.cost;
                l[ex.ord] = El[v] - ex.cost;
            }
        }
    }

    void critical_path()
    {
        for (int i = 0; i < edges.size(); ++i)
            if (e[edges[i].ord] == l[edges[i].ord])
                cout << edges[i].ord << ' ' << edges[i].from << ' ' << edges[i].to << ' ' << edges[i].cost << endl;
    }
};

struct AOE g;
int main()
{
    int n, m;
    int from, to, cost;
    cin >> n >> m;
    g.n = n;
    for (int i = 0; i < m; ++i)
    {
        cin >> from >> to >> cost;
        g.AddEdge(from, to, cost, i + 1);
    }
    g.toposort();
    g.irtoposort();
    g.critical_path();
    return 0;
}

