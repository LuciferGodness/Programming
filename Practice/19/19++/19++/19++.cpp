// 19++.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include<iostream>
#include<set>
#include<vector>
#include<string>

using namespace std;

void ql(string a, int position, set<string>& q) {
	if (position >= a.size()) {
		q.insert(a);
		return;
	}
	else {
		for (int i = position; i < a.size(); i++) {
			swap(a[i], a[position]);
			ql(a, position + 1, q);
		}
	}
}
void asd(string s2, int& n, set<string>& q) {
	if (n == s2.size()) {
		ql(s2, 0, q);
		return;
	}
	else {
		for (int j = 0; j < s2.size(); j++) {
			for (int i = 0; i < n - s2.size(); i++) {
				s2 = s2 + s2[j];
				asd(s2, n, q);
			}
		}
	}
}
int main() {
	int n;
	string s1, s3 = "";
	char w;
	set <string> q;
	cin >> n;
	cin >> s1;
	if (n == s1.size()) {
		ql(s1, 0, q);
		for (auto c : q) {
			cout << c << "\n";
		}
	}
	else {
		for (int i = 0; i < n - s1.size() + 1; i++) {
			s3 = s1[0];
			s1.erase(0, 1);
			asd(s1 + s3, n, q);
			s1 = s1 + s3;
			s3.erase(0, 1);
		}
		for (auto c : q) {
			cout << c << "\n";
		}
	}
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
