<p align="center">МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ<br>
Федеральное государственное автономное образовательное учреждение высшего образования<br>
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"<br>
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ<br>
Кафедра компьютерной инженерии и моделирования</p>
<br>
<h3 align="center">Отчёт по лабораторной работе №1<br> по дисциплине "Программирование"</h3>
<br><br>
<p>студенти 1 курса группы ПИ-б-о-201(2)<br>
Абибулаева Эмине Ридван къызы<br>
направления подготовки 09.03.04 "Программная инженерия"</p>
<br><br>
<table>
<tr><td>Научный руководитель<br> старший преподаватель кафедры<br> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br><br>
<p align="center">Симферополь, 2020</p>
<hr>
<h2> Цель </h2>
<br>
1. Закрепить навыки разработки многофайловыx приложений;
<br>
2. Изучить способы работы с API web-сервиса;
<br>
3. Изучить процесс сериализации/десериализации данных в/из json;
<br>
4. Получить базовое представление о сетевом взаимодействии приложений;
<br>
<h2> Постановка задачи </h2>
<br>
Разработать сервис предоставляющий данные о погоде в городе Симферополе на момент запроса.  В качестве источника данных о погоде используйте: http://openweathermap.org/. В состав сервиса входит: серверное приложение на языке С++ и клиентское приложение на языке Python.
<br>
Серверное приложение (далее Сервер) предназначенное для обслуживания клиентских приложений и минимизации количества запросов к сервису openweathermap.org. Сервер должен обеспечивать возможность получения данных в формате JSON и виде html виджета (для вставки виджета на страницу будет использоваться iframe).
<br>
Клиентское приложение должно иметь графический интерфейс отображающий сведения о погоде и возможность обновления данных по требованию пользователя.
<br>
<br>
<h2> Выполнение работы </h2>
<br>
Итак, для начала я зарегестрировалась на сайте http://openweathermap.org/ для получения API Key. После регистрации в разделе API keys получаем ключ. 
Я сгенерировала API key "Weather": 251a0cb08a13314cf13109459c8230ad.
Далее, использую шаблон http://api.openweathermap.org/data/2.5/onecall? и такие параметры, как: lat(ширина), lon(долгота) - координаты города, exclude - исключение(исключаем всё, кроме почасового измерения), 
lang - установление языка(в нашем случае приравниваем к ru(русский)), units - устанавливаем в чём измеряем скорость ветра и температуру(metric - температура в Цельсиях, скорость ветра - м/с), 
а затем в переменную APPID вставляю API key. Таким образом, я создала запрос:http://api.openweathermap.org/data/2.5/onecall?lat=44.948237&lon=34.100318&exclude=current,minutely,daily,alerts&lang=ru&units=metric&APPID=842fc3a1dc489d72adfd0262976857ba.
<br>
<img src=./image/zap1.png>
Рис. 1 - Запрос на получение прогноза погоды для Симферополя.
<br>
Теперь сгенерирую запрос на сайте https://worldtimeapi.org. Для этого прописываю параметр timezone, далее указываю часть света (Europe), а затем город (Simferopol).
Сам запрос: https://worldtimeapi.org/api/timezone/Europe/Simferopol.
<br>
<img src=./image/zap2.png>
Рис. 2 - Запрос для получения времени в Симферополе
<br>
<h3> Создание серверного приложения </h3>
<br> 
Для начала скачиваю из репозитория библиотеку cpp_httplib, которая понадобится нам для работы с сетью. Также из того же репозитория скачиваем библиотеку nlohmann:json, которая понадобится для работы с json.
Создаю консольное приложение С++, перехожу в папку с главным проектом и создаю папку include, куда распаковываю архивы, которые содержат библиотеки. 
Открываю сам проект, на вкладке "Проект" выбираю "С/С++", затем кликаю по вкладке "Общие", а там выбираю "Дополнительные каталоги включает". Там выбираю путь к папке include и нажимаю "ОК".
Теперь подключаю все необходимые библиотеки. Теперь создадим функцию типа void для получения данных от сервисов  http://openweathermap.org/ и http://worldtimeapi.org. Посылаем им get-запросы, записываем в переменную.
<br>
<img src=./image/c1.png>
Рис. 3 - Подключение библиотек и создание get-запросов
<br>
Далее проверяем наличие ошибок. Затем в цикле for обноляется кэш. Если в нём содержится информация на 1 час больше, то кэш не обновляем. Если в кэше нет данных, устарел или запрос не делали, то кэш обновляется.
<br>
<img src=./image/c2.png>
Рис. 4 - Проверка и обновление кэша.
<br>
Выводим на сайт: http://localhost:3000/
После этого программа ищет строки в html-коде и заменяет их на строки, которые нам выдает сервер.
<br>
<img src=./image/c3.png>
Рис. 5 - Замена строк в html
<br>
Создаю ещё одну функцию типа void для raw. Снова обращаюсь к сервисам с помощью get-запросов. Вновь проверяю наличие ошибок. 
<br>
<img src=./image/c4.png> 
Рис. 6 - Создание get-запросов и проверка ошибок.
<br>
Также проверяем кэш в цикле. Если в кэше нет данных, устарел или запрос не делали, то кэш обновляется и высвечивается информация о погоде на начало следующего часа.
Затем кидаем в переменную значение описания и температуры и выводим на сайт: http://localhost:3000/raw
<br>
<img src=./image/c5.png>
Рис. 7 - Проверка кэша и загрузка в переменные занчения описания и температуры.
<br>
Переходим теперь в основное тело программы. Открываем тот файл html, из которого берём виджет и заменяем данные. Считываем всё до "\0", а затем закрываем файл.
<br>
<img src=./image/c6.png> 
Рис. 8 - Открытие файла html и считывание
<br> 
Создаём сервер. Затем для основного используем первую функцию, для /raw используем вторую функцию. Указываем, на каком хосте работает. В консоль выводим, что всё работает, переходим на сайты и проверяем работу сервера.
<br>
<details>
<summary>Весь код</summary>

```c++
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <cpp_httplib/httplib.h>
#include <iomanip>
#include <fstream>

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
```
</details>
<br>
<img src=./image/s.png> 
Рис. 9 - Готовый сервер
<br> 
<h3> Создание клиентского приложения </h3>
<br>
Графический интерфейс я реализовала с помощью Tkinter. В консоле, с помощью команды pip install requests(если пр установке Pythona напротив PYTH вы не поставили галочку, то придётся решать эту проблемы собственноручно или воспользоваться Visual Studio Code) устанавливаем модуль requetsts, который нам понадобится для работы с сетью. А для работы с json пользуемся модулем json. 
Теперь создаём функцию, в которую помещаем подключение к http://localhost:3000/raw, куда мы недавно выводили информацию о температуре и погоде.
<br>
<img src=./image/py1.png> 
Рис. 10 - Подключение модулей и создание функции, которая берёт данные из сервера
<br>
Сейчас задаём размер окна. Ещё прописываем в коде, что если пользователь щёлкнет правой кнопкой мыши в любом месте окна, то сайт обновляет информацию, то есть снова посылает запрос на сервер. 
<br>
<img src=./image/py2.png> 
Рис. 11 - Настройки окна и добавление обновления
<br> 
Затем используем класс виджета Frame для группировки виджетов и класс виджетов Label для отображения текста. Для Frame задаём цвет, высоту, ширину. Область, которую мы обозначили в root.geometry, мы разделили на три части. Также задаём положение каждому Frame. Верхнее и нижнее мы растягиваем по оси X, а по середине по Y и X.
<br>
<img src=./image/py3.png> 
Рис. 12 - Виджеты Frame
<br> 
Текст у нас только в верхней и средней части, поэтому для нижней области Label не создаём.
Отступы у верхнего текста равны 0, а тексту, который по середине придаём значение expand = true, что значит, что он должен заполнять всё пространство контейнера. 
<br>
<img src=./image/py4.png> 
Рис. 13 - виджеты Label
<br> 
Запускаем и убеждаемся в работоспособности клиентского приложения.
<br>
<details>
<summary>Весь код</summary>

```python
from tkinter import *
import json
import requests

def site(event=None):
	try:
		upload = requests.get('http://localhost:3000/raw').content.decode("utf8")
		upload_date = json.loads(upload)

		up1.config(text=str(upload_date["description"]))
		main.config(text=str(round(upload_date["temp"])) + "°C")
	except requests.exceptions.ConnectionError:
		pass

root = Tk()
root.title("Погода")
root.pack_propagate(0)
root.bind("<Button-1>", site)
tex = "Симферополь"
root.geometry("200x250")

yellow = "#ffa343"
f = 100
h = 30

up_frame =    Frame(root, bg= yellow, width=f, height=h)
main_frame = Frame(root, bg="white",  width=f, height=h*3)
down_frame = Frame(root, bg=yellow, width=f, height=h)

up_frame.pack(side=TOP, fill=X)
main_frame.pack(expand=True, fill=BOTH)
down_frame.pack(side=BOTTOM, fill=X)

up = Label(up_frame, font=("Arial", 14), text= tex, bg=yellow)
main = Label(main_frame, font=("Calibri", 52), bg="white")
up1 = Label(up_frame, font=("Arial", 14), bg=yellow)


up.pack(pady=0)
main.pack(expand=True)
up1.pack(pady=0)


site()
root.mainloop()
```
</details>
<br>
<img src=./image/v.png> 
Рис. 14 - Готовое клиенсткое приложение
<br> 
<h2> Вывод: </h2>
<br>
Закрепила навыки разработки многофайловых приложений, изучила способы работы с API web-сервиса, изучила процесс сериализации/десериализации данных в/из json, получила базовое представление о сетевом взаимодействии приложения.
Разработала сервис, который предоставляет данные о погоде в городе Симферополь на момент запроса. Используя тег iframe, вставила виджет на страницу. Разработала для клиентского приложения графический интерфейс, отображающий данные о погоде и возможность объявления их по требованию пользователя.


