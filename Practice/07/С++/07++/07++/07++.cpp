﻿// 07++.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    setlocale(0, "");
    int count;
    float a, b, c, x1, y1, x2, y2, x3, y3, s, p;
    cout << "Выберите способ:\n 1.Через длины сторон\n 2.Черех координаты вершин" << endl;
    cin >> count;
    switch (count)
    {
    case 1:
    {
        cout << "Введите стороны треугольника" << endl;
        cin >> a >> b >> c;
        if (a > 1000 || b > 1000 || c > 1000)
        {
            cout << "Неправильно! Попробуйте ещё раз!" << endl;
            return main();
        }
        p = (a + b + c) / 2;
        s = sqrt(p * (p - a) * (p - b) * (p - c));
        cout << "S = " << s << endl;
        break;
    }
    case 2:
    {
        cout << "Введите координаты треугольника" << endl;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        if (x1 > 1000 || x2 > 1000 || x3 > 1000 || y1 > 1000 || y2 > 1000 || y3 > 1000)
        {
            cout << "Неправильно! Попробуйте ещё раз!" << endl;
            return main();
        }
        a = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
        b = sqrt((x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3));
        c = sqrt((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1));
        p = (a + b + c) / 2;
        s = sqrt(p * (p - a) * (p - b) * (p - c));
        cout << "S = " << s << endl;
        break;
    }
    default:
        cout << "Неправильный ввод" << endl;

    }
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
