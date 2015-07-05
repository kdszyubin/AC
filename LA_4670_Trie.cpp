#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <queue>
using namespace std;

#define MAXNODE 15000
#define SIGMA_SIZE 26

#define idx(c) (c - 'a')
struct Trie
{
    int ch[MAXNODE][SIGMA_SIZE];//ch放的是sz的值，sz可能很大，char类型会挂
    int val[MAXNODE];
    int sz;

    void initial(){sz = 1; memset(ch[0], 0, sizeof(ch[0])); val[0] = 0;}
    
    void insert(const char *str, int v)
    {
        int u = 0;
        for (int i = 0; i < strlen(str); ++i)
        {
            int c = idx(str[i]);
            if (ch[u][c] == 0)
            {
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u] = v;
    }

    int f[MAXNODE], last[MAXNODE];
    void getfail()
    {
        queue<int> Q;
        last[0] = 0;
        for (int c = 0; c < SIGMA_SIZE; ++c)
        {
            int u = ch[0][c];
            if (u != 0)
            {
                Q.push(u);
                last[u] = 0;
                f[u] = 0;
            }
        }
        while (!Q.empty())
        {
            int r = Q.front(); Q.pop();
            for (int c = 0; c < SIGMA_SIZE; ++c)
            {
                int u = ch[r][c];
                if (u == 0)
                {
                    ch[r][c] = ch[f[r]][c];
                    continue;
                }
                Q.push(u);
                f[u] = ch[f[r]][c];
                last[u] = val[f[u]] != 0 ? f[u] : last[f[u]];
                /*
                if (f[u] != 0)
                    if (val[f[u]] != 0)
                        last[u] = f[u];
                    else
                        last[u] = last[f[u]];
                else
                    last[u] = 0;
                    */
            }
        }
    }

    void find(char *str)
    {
        int u = 0;
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < strlen(str); ++i)
        {
            int c = idx(str[i]);
            u = ch[u][c];
            if (val[u] != 0)
                count(u);
            else if (last[u] != 0)
                count(last[u]);
        }
    }

    int cnt[MAXNODE];
    void count(int u)
    {
        if (u != 0)
        {
            cnt[val[u] - 1]++;//cnt统计的是val[u], 不是last[u];
            count(last[u]);
        }
    }
};

struct Trie trie;
char large_str[1000002];
char pattern[150][72];

int main()
{
        int n;
        int max;
        map<string, int> ms;
        while (scanf("%d", &n) && n != 0)
        {
                trie.initial();
                ms.clear();
                max = 0;
                for (int i = 0; i < n; ++i)
                {
                        scanf(" %s", pattern[i]);
                        ms[(string)pattern[i]] = i;
                        trie.insert(pattern[i], i + 1);
                }
                trie.getfail();
                scanf(" %s", large_str);
                trie.find(large_str);
                for (int i = 0; i < n; ++i)
                        if (trie.cnt[i] > max) max = trie.cnt[i];
                printf("%d\n", max);
                for (int i = 0; i < n; ++i)
                        if (trie.cnt[ms[(string)pattern[i]]] == max)
                                printf("%s\n", pattern[i]);
        }
        return 0;
}
