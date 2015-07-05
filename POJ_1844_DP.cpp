#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 200010
bool d[2][MAXN];
int s;
int n;
int main()
{
    int pre, next;
    while (cin >> s)
    {
        memset(d[0], 0, sizeof(d[0]));
        d[0][MAXN / 2 + 1] = true;
        d[0][MAXN / 2 - 1] = true;
        pre = 0;
        n = 1;
        while (!d[pre][MAXN / 2 + s])
        {
            n++;
            next = 1 - pre;
            memset(d[next], 0, sizeof(d[next]));
            for (int k = 0; k < MAXN; ++k)
                if (d[pre][k])
                {
                    if (k + n < MAXN) d[next][k + n] = 1;
                    if (k - n >= 0) d[next][k - n] = 1;
                }
            pre = next;
        }
        cout << n << endl;
    }
    return 0;
}
                

        


