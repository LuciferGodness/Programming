// 25++.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

vector<int> BozoSort(vector<int> array, bool t = true)
{
	bool sorted = false;
	int n = array.size();
	while (!sorted)
	{
		if (t)
		{
			int index1 = rand() % n;
			int index2 = rand() % n;
			int temp = array[index1];
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
			int temp = array[index1];
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
void Out(vector<int> array, int n)
{
	for (int i = 0; i < n; i++)
		cout << array[i] << " ";
	cout << endl;
}

vector<int> BozoSort(vector<vector<int>> array_2, bool t = true)
{
	int s = array_2.size();
	int n = s * s;
	int i = 0;
	vector<int> array(n);
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
vector<int> BozoSort(int a, int b, int c, bool t = true)
{
	vector<int>array(3);
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
	int n, i;
	i = 0;
	cout << "Введите количество элементов" << endl;
	cin >> n;
	vector<int> array(n);
	cout << "Введите массив" << endl;
	for (i = 0; i < n; i++)
		cin >> array[i];
	cout << endl;
	int s = sqrt(n);
	vector<vector<int>> array_2(s, vector<int>(s));
	for (int j = 0; j < s; j++)
		for (int l = 0; l < s; l++)
		{
			array_2[j][l] = array[j * s + l];
		}
	array = BozoSort(array);
	Out(array, n);
	array = BozoSort(array, false);
	Out(array, n);
	array = BozoSort(array_2);
	Out(array, n);
	array = BozoSort(array_2, false);
	Out(array, n);
	int a, b, c;
	for (i = 0; i < n; i++)
	{
		a = array[0];
		b = array[1];
		c = array[2];
	}
	array = BozoSort(a, b, c);
	Out(array, 3);
	array = BozoSort(a, b, c, false);
	Out(array, 3);

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
