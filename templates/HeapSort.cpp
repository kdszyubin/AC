#include <iostream>
using namespace std;

void HeapAdjust(int *a, int i, int size)
{
    if (i <= size / 2)
    {
        int left = i + i;
        int right = i + i + 1;
        int max = i;
        if (left <= size && a[left - 1] > a[max - 1]) max = left;
        if (right <= size  && a[right - 1] > a[max - 1]) max = right;
        if (max != i)
        {
            swap(a[max - 1], a[i - 1]);
            HeapAdjust(a, max, size);
        }
    }
}

void BuildHeap(int *a, int size)
{
    for (int i = size / 2; i >= 1; --i)
        HeapAdjust(a, i, size);
}

void HeapSort(int *a, int size)
{
    BuildHeap(a, size);
    for (int i = size; i >= 1; --i)
    {
        swap(a[i - 1], a[1 - 1]);
        HeapAdjust(a, 1, i - 1);
    }
}

int main()
{
    int n;
    int a[100];
    cout << "Input n:";
    cin >> n;
    cout << "input a[" << n << "]" << endl;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    HeapSort(a, n);
    for (int i = 0; i < n; ++i)
        cout << a[i] << ' ';
    cout << endl;
    return 0;
}




