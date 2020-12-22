// 26++.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

template <class T>
vector<T> BozoSort(vector<T> array, bool t = true)
{
	bool sorted = false;
	int n = array.size();
	while (!sorted)
	{
		if (t)
		{
			int index1 = rand() % n;
			int index2 = rand() % n;
			T temp = array[index1];
			array[index1] = array[index2];
			array[index2] = temp;
			sorted = true;
			for (int i = 1; i < n; i++)
			{
				if (array[i - 1] > array[i])
				{
					sorted = false;
					break;
				}
			}
		}
		else
		{
			int index1 = rand() % n;
			int index2 = rand() % n;
			T temp = array[index1];
			array[index1] = array[index2];
			array[index2] = temp;
			sorted = true;
			for (int i = 1; i < n; i++)
			{
				if (array[i - 1] < array[i])
				{
					sorted = false;
					break;
				}
			}
		}
	}
	return array;
}

template <class T>
void Out(vector<T> array)
{
	int n = array.size();
	for (int i = 0; i < n; i++)
		cout << array[i] << " ";
	cout << endl;
}

template <class T>
vector<T> BozoSort(vector<vector<T>> array_2, bool t = true)
{
	int s = array_2.size();
	int n = s * s;
	int i = 0;
	vector<T> array(n);
	while (i < n)
	{
		for (int j = 0; j < s; j++)
			for (int l = 0; l < s; l++)
			{
				array[i] = array_2[j][l];
				i++;
			}
	}
	if (t)
		return BozoSort(array);
	else
		return BozoSort(array, false);

}

template <class T>
vector<T> BozoSort(T a, T b, T c, bool t = true)
{
	vector<T>array(3);
	array[0] = a;
	array[1] = b;
	array[2] = c;
	if (t)
		return BozoSort(array);
	else
		return BozoSort(array, false);

}

int main()
{
	srand(time(0));
	setlocale(0, "");
	int n, i, n1;
	i = 0;
	cout << "Введите количество элементов" << endl;
	cin >> n;
	vector<double> array(n);
	cout << "Введите массив(double)" << endl;
	for (i = 0; i < n; i++)
		cin >> array[i];
	cout << endl;
	int s = sqrt(n);
	vector<vector<double>> array_2(s, vector<double>(s));
	for (int j = 0; j < s; j++)
		for (int l = 0; l < s; l++)
		{
			array_2[j][l] = array[j * s + l];
		}

	cout << "Введите количество элементов" << endl;
	cin >> n1;
	vector<string> array1(n);
	cout << "Введите массив (string)" << endl;
	for (i = 0; i < n; i++)
		cin >> array1[i];
	cout << endl;
	int s1 = sqrt(n);
	vector<vector<string>> array1_2(s, vector<string>(s));
	for (int j = 0; j < s; j++)
		for (int l = 0; l < s; l++)
		{
			array1_2[j][l] = array1[j * s + l];
		}

	Out(BozoSort(array));
	Out(BozoSort(array, false));
	Out(BozoSort(array_2));
	Out(BozoSort(array_2, false));
	int a, b, c;
	for (i = 0; i < n; i++)
	{
		a = array[0];
		b = array[1];
		c = array[2];
	}
	Out(BozoSort(a, b, c));
	Out(BozoSort(a, b, c, false));

	Out(BozoSort(array1));
	Out(BozoSort(array1, false));
	Out(BozoSort(array1_2));
	Out(BozoSort(array1_2, false));
	
	Out(BozoSort(array1[0], array1[1], array1[2]));
	Out(BozoSort(array1[0], array1[1], array1[2], false));

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
