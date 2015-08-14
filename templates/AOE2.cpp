#include <cstdio>
#include <cstring>
#include <cstdlib>

#define NMAX 100
#define EMAX (NMAX * NMAX)

struct ArcNode
{
        int adjvex;
        int ord;
        int dul;
        struct ArcNode *nextarc;
};

struct VNode
{
        int num;
        int counti;
        int counto;
        struct ArcNode *headi;
        struct ArcNode *heado;
};

struct LGraph
{
        struct VNode vertexs[NMAX];
        int vexnum, arcnum;
};

struct LGraph lg;
int Ee[NMAX];
int El[NMAX];
int e[EMAX];
int l[EMAX];

void read_data()
{
        int u, v, w;
        struct ArcNode *arct;
        int i;
        scanf("%d%d", &lg.vexnum, &lg.arcnum);
        for (int i = 0; i < lg.arcnum; ++i)
        {
                scanf("%d%d%d", &u, &v, &w);
                arct = (struct ArcNode*)malloc(sizeof(struct ArcNode));
                arct->adjvex = v;
                arct->ord = i + 1;
                arct->dul = w;
                arct->nextarc = lg.vertexs[u].heado;
                lg.vertexs[u].heado = arct;
                lg.vertexs[u].counto++;

                arct = (struct ArcNode*)malloc(sizeof(struct ArcNode));
                arct->adjvex = u;
                arct->ord = i + 1;
                arct->dul = w;
                arct->nextarc = lg.vertexs[v].headi;
                lg.vertexs[v].headi = arct;
                lg.vertexs[v].counti++;
        }
}

void toposort()
{
        int q[NMAX];
        int qf, ql;
        int u, v, w, en;
        struct ArcNode *arct;
        int i;
        memset(Ee, 0, sizeof(Ee));
        qf = ql = 0;
        for (i = 0; i < lg.vexnum; ++i)
                if (lg.vertexs[i].counti == 0)
                {
                        q[ql++] = i;
                        Ee[i] = 0;
                }
        while (qf < ql)
        {
                u = q[qf++];
                //printf("%d %d\n", u, Ee[u]);
                arct = lg.vertexs[u].heado;
                while (arct != NULL)
                {
                        v = arct->adjvex;
                        w = arct->dul;
                        en = arct->ord;
                        lg.vertexs[v].counti--;
                        if (lg.vertexs[v].counti == 0) q[ql++] = v;
                        if (Ee[u] + w > Ee[v]) Ee[v] = Ee[u] + w;
                        e[en] = Ee[u];
                        arct = arct->nextarc;
                }
        }
}

void irtoposort()
{
        int q[NMAX];
        int qf, ql;
        int u, v, w, en;
        struct ArcNode *arct;
        int i;
        memset(El, 0x7f, sizeof(El));
        qf = ql = 0;
        for (i = 0; i < lg.vexnum; ++i)
                if (lg.vertexs[i].counto == 0)
                {
                        q[ql++] = i;
                        El[i] = Ee[i];
                }
        while (qf < ql)
        {
                v = q[qf++];
               // printf("%d %d\n", v, El[v]);
                arct = lg.vertexs[v].headi;
                while (arct != NULL)
                {
                        u = arct->adjvex;
                        w = arct->dul;
                        en =arct->ord;
                        lg.vertexs[u].counto--;
                        if (lg.vertexs[u].counto == 0) q[ql++] = u;
                        if (El[v] - w < El[u]) El[u] = El[v] - w;
                        l[en] = El[v] - w;
                        arct = arct->nextarc;
                }
        }
}

void critical_path()
{
        int u, v, w, en;
        struct ArcNode *arct;
        int i;
        for (i = 0; i < lg.vexnum; ++i)
        {
                u = i;
                arct = lg.vertexs[u].heado;
                while (arct != NULL)
                {
                        v = arct->adjvex;
                        w = arct->dul;
                        en = arct->ord;
                        if (e[en] == l[en]) printf("%d:%d->%d   %d\n", en, u, v, w);
                        arct = arct->nextarc;
                }
        }
}

int main()
{
        read_data();
        toposort();
        irtoposort();
        critical_path();
        return 0;
}
