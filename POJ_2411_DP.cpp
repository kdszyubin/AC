/*
 * 将行列转置后，行为n，列为4
 * 每一行有4个方格，对每个方格，有4种状态
 *      0.以其为起点放置了一个横块（即方格为横块的左半部分）
 *      1.以其为终点放置了一个横块（即方格为横块的右半部分）
 *      2.以其为起点放置了一个竖块（即方格为竖块的上半部分）
 *      3.以其为终点放置了一个竖块（即方格为竖块的下半部分）
 *  即每个方格状态可用2bits表示其状态，行状态需要4*2bits，即最多128种状态。
 * 对每一行从第一个方块开始，递归的枚举每个方块的4种状态，可得128种状态。
 * dp方程：
 * a[n][statenow] = sum{a[n - 1][statepre]} {statepre和statenow相邻}
 * 最后一行的所有方格均不能为竖块的上半部分，去掉相应的状态的策略数后
 * 128中行状态中余下的行状态的策略数的和即为答案。

 * 也可对方格进行如下标记：
 *      0.当前行方格留空（与下一行相应位置的方块一起组成竖块）
 *      1.当前行方格不留空（填横块，或者竖块的下半部分）
 * 每个方格需要1bit表示其状态，一行所有放置策略需要4bits表示，即最多16个状态
 * 最后一行的所有方格均不能为竖块的上半部分，所以
 * 目标是求最后一行状态值1111的所有策略数。
 * 但这样的一个状态表示了一行的多种放置策略：
 *  下面两种放置策略中间一行均为1110
 *          *       * 
 * 1110  ** *  *    *  ** *
 *             *          *
 *       横 竖 竖   竖 横 竖
 * 不过，同样递归的枚举每个方格的4种状态，可枚举到128种放置策略，
 * 只不过得到的二进制数只有16种。
 * 通过下面dfs的枚举，可得到每种放置策略的状态值now和对应的前一行的状态值pre
 * 进行策略数累加++mat.a[now][pre],可得到每两种状态之间转移的策略数。
 * 答案为状态1111经过n次状态转移后的状态值1111的所有策略数。
 * 
 */
#include <cstdio>
#include <cstring>
#define COL 3
#define MAXN (1 << COL)
int M;
struct Matrix
{
    int n;
    int a[MAXN][MAXN];

    void clear()
    {
        n = 0;
        memset(a, 0, sizeof(a));
    }

    Matrix operator * (const Matrix& b) const
    {
        Matrix tmp;
        tmp.clear();
        tmp.n = n;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < b.n; ++j)
                for (int k = 0; k < n; ++k)
                    tmp.a[i][j] = (tmp.a[i][j] + a[i][k] * b.a[k][j]) % M;
        return tmp;
    }
};
Matrix mat;


//dfs为用枚举一行方格所有的可能的放置策略，
//得到对应策略的状态值now和上一行的状态值pre。
//由于不同策略可能对应一个状态值(如上面的例子)，
//所以每次得到一个状态转移的策略，就对对应的状态转移进行策略数累加
//即++mat.a[pre][now];
//这样，一次dfs(0, 0, 0)可得到不同状态之间转移的策略数mat
void dfs(int l, int now, int pre)
{
    if (now == (1 << COL) - 1) printf("   %d %d %d\n", l, now, pre);
    if (l > COL) return ;
    if (l == COL)
        ++mat.a[pre][now];
    else
    {
        //当前行方格放横块，上一行对应两个方格不能留空
        dfs(l + 2, now << 2 | 3, pre << 2 | 3);
        //当前行方格留空给下一行放竖块，上一行对应一个方格不能留空
        dfs(l + 1, now << 1 | 0, pre << 1 | 1);
        //当前行方格放竖块，上一行对应方格必须留空
        dfs(l + 1, now << 1 | 1, pre << 1 | 0);
    }
}

Matrix expo(Matrix mx, int e)
{
    Matrix tmp;
    tmp.clear();
    tmp.n = mx.n;
    for (int i = 0; i < tmp.n; ++i)
        tmp.a[i][i] = 1;
    if (e == 0) return tmp;
    while (e)
    {
        if (e & 1) tmp = tmp * mx;
        mx = mx * mx;
        e >>= 1;
    }
    return tmp;
}

void print()
{
    for (int i = 0; i < (1 << COL); ++i)
    {
        for (int j = 0; j < (1 << COL); ++j)
            printf("%d ", mat.a[i][j]);
        printf("\n");
    }
    printf("\n");
}

int main()
{
    int n, m;
    while (scanf("%d %d", &n, &m) && n != 0)
    {
        M = m;
        mat.clear();
        mat.n = (1 << COL);
        dfs(0, 0, 0);
        print();
        mat = expo(mat, n);
        printf("%d\n", mat.a[(1 << COL) - 1][(1 << COL) - 1]);
    }
    return 0;
}

