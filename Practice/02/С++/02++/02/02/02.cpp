﻿// 02.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
int main()
{
    setlocale(0, "");
    int s, p;
    double k, pi;
    s = 3;
    p = 3.14;
    k = 3;
    pi = 3.14;
    cout << s << endl << p << endl << k << endl << pi << endl;
    cout << "int - тип данных, который используется для переменных, содержащих целые числа, а double - дробные. Поэтому при приравнии значения дробного числа к переменной с типом int, программа автоматически округляет по правилам математики и выводит целое число." << endl;
    system("pause");
    return 0;

    
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
