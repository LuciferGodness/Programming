#include <iostream>
using namespace std;

int* create(int m, int q = 0, int h = 0)
{
    int *w = new int [m];
    int k = 0;
    for(int i = 0; i < m; i++)
    {
        w[i] = q + k;
        k = k + h;
    }
    return w;
}

void sort(int m, int* array)
{
    for(int i=1;i<m;i++)
        for(int j=i;j>0 && array[j-1]>array[j];j--)
            swap(array[j-1],array[j]);
}

int* print(int m, int* array)
{
    for (int i = 0; i < m; i++){
            cout << array[i] << " ";
        }
        return array;
}
int main()
{
    int m, q, h;
    cin >> m >> q >> h;
    int *w = create(m, q, h);
    sort(m, w);
    w = print(m, w);
    delete[] w;
    return 0;
}
