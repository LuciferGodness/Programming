#include <iostream>
using namespace std;

struct IntArray
{
    int *data;
    int size;
};

void create(IntArray& arr, int size)
{
    arr.data = new int[size];
    arr.size = size;
}

int get(IntArray& arr, int index)
{
    if(index < 0 || index >= arr.size)
    {
        cout << "Mistake!" << endl;
        exit(1);
    }
    return arr.data[index];
}

void set(IntArray& arr, int index, int value)
{
    if(index < 0 || index >= arr.size)
    {
        cout << "Mistake!" << endl;
        exit(1);
    }
    arr.data[index] = value;
}

void print(IntArray& arr)
{
    cout << "[";
    for(int i = 0; i < arr.size; i++)
        cout << arr.data[i] << ", ";
    cout << "]" << endl;
}

void resize(IntArray& arr, int newSize)
{
    if(newSize > arr.size)
    {
        int* arr1 = new int[newSize];
        for (int i = 0; i < arr.size; ++i)
            arr1[i] = arr.data[i];
        for (int i = arr.size; i < newSize; ++i)
            arr1[i] = 0;
        delete[] arr.data;
        arr.data = arr1;
        arr.size = newSize;
     }
     else
     {
        int* arr1 = new int[newSize];
        for (int i = 0; i < newSize; ++i)
            arr1[i] = arr.data[i];
        delete[] arr.data;
        arr.data = arr1;
        arr.size = newSize;
      }
}

void destroy(IntArray& arr)
{
    delete[] arr.data;
    arr. data = nullptr;
    arr.size = 0;
}

void create(IntArray* arr, int size)
{
    create(*arr, size);
}

int get(IntArray* arr, int index)
{
    get(*arr, index);
}

int set(IntArray* arr, int index, int value)
{
    set(*arr, index, value);
}

void print(IntArray* arr)
{
    print(*arr);
}

void resize(IntArray* arr, int newSize)
{
    resize(*arr, newSize);
}

void destroy(IntArray* arr)
{
    destroy(*arr);
}

int main()
{
    IntArray arr;
    create(arr, 30);
    for(int i = 0; i < 30; i++)
        set(arr, i, i+1);
    print(arr);
    resize(arr, 50);
    print(arr);
    resize(arr, 10);
    print(arr);
    destroy(arr);
}
