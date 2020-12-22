// server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include<iostream>
#include<string>
#include<nlohmann/json.hpp>
#include<cpp_httplib/httplib.h>
#include<iomanip>
#include<fstream>
using namespace httplib;
using json = nlohmann::json;
using namespace std;
int go;
string cache;
string str;
int k = 0;
string timekod;
json json_cache;
json json_timekod;
json remember;
string temperatyra;
json j;
void gen_response(const Request& req, Response& response) {


	Client cli("http://worldtimeapi.org");
	auto res = cli.Get("/api/timezone/Europe/Simferopol");
	Client cli1("http://api.openweathermap.org");
	auto res1 = cli1.Get("/data/2.5/onecall?lat=44.948237&lon=34.100318&exclude=current,minutely,daily,alerts&lang=ru&units=metric&APPID=842fc3a1dc489d72adfd0262976857ba");
	if (!res) {
		response.set_content("Не могу получить текущее время", "text/plain");
		return;
	}
	if (!res1) {
		response.set_content("Не могу прочитать погоду", "text/plain");
		return;
	}
	if (cache.empty()) {
		cache = res1->body;
	}
	timekod = res->body;
	json_cache = json::parse(cache);
	json_timekod = json::parse(timekod);
	for (int i = 0; i < 48; i++) {

		if (json_cache["hourly"][i]["dt"] > json_timekod["unixtime"]) {
			k++;
			go = i;
			break;
		}
	}
	if (k == 0) {

		cache = res1->body;
	}
	string makemyShablon = str;
	string str2 = "{hourly[i].weather[0].description}";
	string str3 = "{hourly[i].weather[0].icon}";
	string str4 = "{hourly[i].temp}";
	temperatyra = to_string(int(json_cache["hourly"][go]["temp"].get<double>()));
	makemyShablon.replace(makemyShablon.find(str2), str2.length(), json_cache["hourly"][go]["weather"][0]["description"]);
	makemyShablon.replace(makemyShablon.find(str3), str3.length(), json_cache["hourly"][go]["weather"][0]["icon"]);
	makemyShablon.replace(makemyShablon.find(str4), str4.length(), temperatyra);
	makemyShablon.replace(makemyShablon.find(str4), str4.length(), temperatyra);
	response.set_content(makemyShablon, "text/html");
}




//ДЕЛАЮ /raw



void gen_response1(const Request& req, Response& response) {



	Client cli("http://worldtimeapi.org");
	auto res = cli.Get("/api/timezone/Europe/Simferopol");
	Client cli1("http://api.openweathermap.org");
	auto res1 = cli1.Get("/data/2.5/onecall?lat=44.948237&lon=34.100318&exclude=current,minutely,daily,alerts&lang=ru&units=metric&APPID=842fc3a1dc489d72adfd0262976857ba");
	if (!res) {
		response.set_content("Не могу получить текущее время", "text/plain");
		return;
	}
	if (!res1) {
		response.set_content("Не могу получить погоду", "text/plain");
		return;
	}
	if (cache.empty()) {
		cache = res1->body;
	}
	timekod = res->body;
	json_cache = json::parse(cache);
	json_timekod = json::parse(timekod);
	for (int i = 0; i < 48; i++) {

		if (json_cache["hourly"][i]["dt"] > json_timekod["unixtime"]) {
			k++;
			go = i;
			break;
		}
	}
	if (k == 0) {
		cache = res1->body;
	}
	j["description"] = json_cache["hourly"][go]["weather"][0]["description"];
	j["temp"] = json_cache["hourly"][go]["temp"];
	response.set_content(j.dump(), "text/json");
}



int main() {
	Server svr;
	ifstream file("Weather_now.html");
	getline(file, str, '\0');
	file.close();
	svr.Get("/", gen_response);
	cout << "Start server... OK\n";
	svr.Get("/raw", gen_response1);
	cout << "Start server... OK\n";
	svr.listen("localhost", 3000);
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
