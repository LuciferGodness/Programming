#include <iostream>
using namespace std;

void create(int *&w, int m, int q, int h)
{
    w = new int [m];
    int k = 0;
    for(int i = 0; i < m; i++)
    {
        w[i] = q + k;
        k = k + h;
    }
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

void destroy(int *&w)
{
    if(w != nullptr)
    {
        delete[] w;
        w = nullptr;
    }
}
int main()
{
    int m, q, h;
    cin >> m >> q >> h;
    int *w = new int[0];
    create(w, m, q, h);
    sort(m, w);
    w = print(m, w);
    destroy(w);
    return 0;
}
