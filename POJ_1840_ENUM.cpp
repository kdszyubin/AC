/*
   sum( ai*(xi^3) ) = 0, (0 <= i <= 4, -50 <= ai, xi <= 50)
   由于直接枚举50^4 * 5数据太大，
   可将等式后3项移动到等号右边，然后枚举前面两项和至多不超过25000000项
   然后在用等式右边100^3种可能与等式左边进行比较。
   */
#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 25000000
#define MID (MAXN >> 1) 
short counter[MAXN];
int ans = 0;

int main()
{
    int a[5];
    for (int i = 0; i < 5; ++i)
        cin >> a[i];
    for (int x0 = -50; x0 <= 50; ++x0)
        for (int x1 = -50; x1 <= 50; ++x1)
            if (x0 != 0 && x1 != 0)
            counter[MID + a[0] * x0 * x0 * x0 + a[1] * x1 * x1 * x1]++;
    for (int x2 = -50; x2 <= 50; ++x2)
        for (int x3 = -50; x3 <= 50; ++x3)
            for (int x4 = -50; x4 <= 50; ++x4)
                if (x2 != 0 && x3 != 0 && x4 != 0)
            {
                int temp = MID - (a[2] * x2 * x2 * x2 + 
                        a[3] * x3 * x3 * x3 + a[4] * x4 * x4 * x4);
                if (0 <= temp && temp <= MAXN) ans += counter[temp];
            }
    cout << ans << endl;
    return 0;
}
