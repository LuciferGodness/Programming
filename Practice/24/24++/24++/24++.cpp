// 24++.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <nlohmann\json.hpp>
using namespace std;
int main()
{
    int c, i, a, us, j;
    ifstream input("in.json");
    nlohmann::json indata;
    input >> indata;
    us = 0;
    for (i = 0; i < indata.size(); i++)
    {
        if (indata[i]["userId"] > us)
            us = indata[i]["userId"];
    }
    nlohmann::json outdata;
    for (i = 1; i <= us; i++)
    {
        c = 0; 
        for (int j = 0; j < indata.size(); j++)
            if (indata[j]["completed"] && indata[j]["userId"] == i)
            {
                c++;
                nlohmann::json object;
                object["task complited"] = c;
                object["userId"] = i;
                outdata.push_back(object);
            }
           
    }
    ofstream output("out.json");
    output << setw(2) << outdata << endl;
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
