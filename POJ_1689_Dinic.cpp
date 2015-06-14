/* 模板题
   写模板代码注意细节
   模型：
        w最大为50
        [0,350)中代表[0,w)周的每一天，0表示地0周的第0天，7表示第1周的第0天
        [350,350+n)代表每一部电影filmx
   1.源点s为350+n，汇点t为350+n+1
   2.s到每个filmx，建容量为dx的边
   3.每个filmx到[0,w)周内所有可选的工作日，建容量为1的边
   4.所有工作日到t,建容量为1的边
   5.result = sum(dx);求最大流flow
   6.flow == result则Yes，否则No
   */
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAXN 400
#define MAXD (50 * 7)
#define INF 0x3f3f3f3f
struct Edge
{
        int from, to, cap, flow;
};

struct Dinic
{
        int s, t, m, n;
        vector<Edge> edges;
        vector<int> G[MAXN];
        int d[MAXN];
        bool vis[MAXN];
        int cur[MAXN];

        void AddEdge(int from, int to, int cap)
        {
                edges.push_back(Edge{from, to, cap, 0});
                edges.push_back(Edge{to, from, 0, 0});
                m = edges.size();
                G[from].push_back(m - 2);
                G[to].push_back(m - 1);
        }
        bool BFS()
        {
                memset(vis, 0, sizeof(vis));            //1、每次都要对vis初始化，忘了就是1-2h的调试
                queue<int> Q;
                Q.push(s);
                d[s] = 0;
                vis[s] = true;
                while (!Q.empty())
                {
                        int u = Q.front(); Q.pop();
                        for (int i = 0; i < G[u].size(); ++i)
                        {
                                Edge& e = edges[G[u][i]];
                                if (!vis[e.to] && e.cap > e.flow)//2.e.cap>e.flow这条件
                                {
                                        vis[e.to] = true;
                                        Q.push(e.to);
                                        d[e.to] = d[u] + 1;
                                }
                        }
                }
                return vis[t];
        }

        int DFS(int x, int a)
        {
                if (x == t || a == 0) return a;
                int flow = 0, f;
                for (int& i = cur[x]; i < G[x].size(); ++i)//3.引用符号容易忽略
                {
                        Edge& e = edges[G[x][i]];
                        if (d[e.to] == d[x] + 1 && (f = DFS(e.to, min(a, e.cap - e.flow))) != 0)//4.min要在DFS里
                        {
                                e.flow += f;
                                edges[G[x][i]^1].flow -= f;
                                flow += f;
                                a -= f;
                                if (a == 0) break;//5.不加效率低下
                        }
                }
                return flow;
        }

        int MaxFlow(int s, int t)
        {
                int flow = 0;
                this->s = s;
                this->t = t;
                while (BFS())
                {
                        memset(cur, 0, sizeof(cur));
                        flow += DFS(s, INF);
                }
                return flow;
        }
};

struct Dinic g;
int s, t;
int target;

void read_data()
{
        int n;
        int temp[7];
        int d, w;
        scanf("%d", &n);
        s = MAXD + n;
        t = s + 1;
        target = 0;
        g.edges.clear();
        for (int i = 0; i < MAXN; ++i)
                g.G[i].clear();
        for (int i = 0; i < n; ++i)
        {
                for (int j = 0; j < 7; ++j)
                        scanf("%d", &(temp[j]));
                scanf("%d %d", &d, &w);
                target += d;
                g.AddEdge(s, MAXD + i, d);
                for (int k = 0; k < w; ++k)
                        for (int j = 0; j < 7; ++j)
                                if (temp[j] == 1) g.AddEdge(MAXD + i, k * 7 + j, 1);
        }
        for (int j = 0; j < MAXD; ++j)
                g.AddEdge(j, t, 1);
}

int main()
{
        int test;
        int flow;
        scanf("%d", &test);
        while (test--)
        {
                read_data();
                flow = g.MaxFlow(s, t);
                if (flow == target) 
                        printf("Yes\n");
                else
                        printf("No\n");
        }
        return 0;
}
