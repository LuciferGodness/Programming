// server2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <cpp_httplib/httplib.h>
#include<nlohmann/json.hpp>
#include <vector>
#include<filesystem>//с помощью этой библиотеки 
#include<string>

using namespace httplib;
using json = nlohmann::json;
using namespace std;
namespace fs = std::filesystem;


const string file_name = "file.json";
const string webpage_file_name = "webhooks.html";
const string webhook_template = u8R"(
                    <div class="form-row align-items-center">
                      <div class="col">
                        <input type="text" value="	https://webhook.site/648aee19-f67a-4424-80fa-3bd2b1e72e97" class="form-control mb-2" disabled>
                      </div>
                      <div class="col">
                        <button type="submit" name="del" value="https://webhook.site/648aee19-f67a-4424-80fa-3bd2b1e72e97" class="btn btn-danger mb-2">Удалить</button>
                      </div>
                    </div>)";

void web(string& data, const string& to, const string& from)
{
	size_t find = data.find(to);//size_t хранение длины размеров(целый тип данных), заменить в переменной дата все строки to, 

	while (find != string::npos)//npos - максимально возможное значение для элемента типа size_t., find берёт строку и возвращает индекс
	{
		data.replace(find, to.size(), from);//изменение в data строку from на to
		find = data.find(to, find + from.size());//ищу словов to и заменяю на find + размер
	}
}
	
json get_from_web()
{
	ifstream open_file(file_name);
	json f;

	if (open_file.is_open())
	{
		open_file >> f;//в переменную записываю данные из файла
		open_file.close();//закрываю
	}

	return f;
}
void save(json f)
{
	ofstream file(file_name);//перезаписываем

	if (file.is_open())
	{
		file << f.dump(2);//перевод из объекта(json) в строку с пробелами(2) в табуляции
		file.close();
	}
	else
	{
		cout << "Ошибка пути или прав доступа" << endl;
	}
}

string h()
{
	ifstream webpage_file(webpage_file_name);//режим чтения
	string webpage;
	if (webpage_file.is_open())
	{
		getline(webpage_file, webpage, '\0');//записываем всё до конца в переменную webpage
		webpage_file.close();
	}
	else return "";

	json f = get_from_web();
	if (!f["webhooks"].empty()) { 
		for (int i = 0; i < f["webhooks"].size(); i++)//для каждого элемента из webhooks, который является строкой
		{
			int use = webpage.find("{webhooks_list}") - 1;//индекс { в веб-странице
			string templ = webhook_template;//копия шаблона для webhook
			web(templ, "https://webhook.site/648aee19-f67a-4424-80fa-3bd2b1e72e97", f["webhooks"][i].get<std::string>());//заменяем  webhook url на строку из webhook
			webpage.insert(webpage.begin() + use, templ.begin(), templ.end());//добавляет в файл фрагмент 
		}
	}
	web(webpage, "{webhooks_list}", "");//заменяем на пустые строки
	return webpage;
}

void h_get(const Request& req, Response& res)
{
	res.set_content(h(), "text/html; charset=UTF-8");//выводит сайт
}

void h_post(const Request& req, Response& res)
{
	json f = get_from_web();
	if (req.has_param("del"))//если в запросе есть параметр del
	{
		string value = req.get_param_value("del"); //получаем параметр по имени del
		if (!f["webhooks"].empty())//проверка  
		{
			//ссылка - переменная, которая имеет адрес памяти
			for (auto ptr = f["webhooks"].begin(); ptr != f["webhooks"].end(); ++ptr)//auto - тип из правого выражения
			{
				if (ptr->is_string() && ptr->get<string>() == value)//если по этой ссылке строка и значение этой строки = значению параметру del
				{
					f["webhooks"].erase(ptr);//удаляем по этой ссылке
					break;
				}
			}
		}
	}
	else if (req.has_param("set"))
	{
		string value = req.get_param_value("set");//принять(то что вводим)

		if (value == "")//если пустой 
		{
		}
		else
		{
			if (!f["webhooks"].empty())
			{
				bool found = false;//отвечает за то, найден ли такой элемент в массиве
				for (auto ptr = f["webhooks"].begin(); ptr != f["webhooks"].end(); ++ptr)
				{
					if (ptr->is_string() && ptr->get<std::string>() == value)
					{
						found = true;
					}
				}
				if (!found) {
					f["webhooks"].push_back(value);
				}
			}
			else
			{
				f["webhooks"].push_back(value);//если массив пустой
			}
		}
	}
	save(f);
	res.set_content(h(), "text/html; charset=UTF-8");
	std::cout << std::endl;
}

std::string str = u8R"(
{
"request": {
    "command": "",
        "original_utterance" : "ping",
        "type" : "SimpleUtterance",
})";

enum voice_mode
{
	silent_mode,
	speak_mode
};
enum skill_mode
{
	help_mode,
	exit_mode
};
json s_array = json::array();

json silent_button
{
		{"title", u8"Молчать"},
		{"hide", true}
};

json speak_button
{

		{"title", u8"Говорить"},
		{"hide", true}

};

json exit_button =
{
		{"title", u8"Помощь"},
		{"hide", true}
};

json help_button =
{

		{"title", u8"Помощь"},
		{"hide", true},

		{"title", u8"Говорить"},
		{"hide", true},

		{"title", u8"Молчать"},
		{"hide", true},

		{"title", u8"Выйти из помощи"},
		{"hide", true},

		{"title", u8"Корзина"},
		{"hide", true},

		{"title", u8"Покупка завершена"},
		{"hide", true},
};

//json get_config();
json gen_response(const std::string& text, const std::string& tts, const json& buttons, const json* session_now = nullptr, const bool end_session = false)
{
	json response = {
		{"response", {
			{"buttons", {buttons}},
			{"end_session", end_session}
		}},
		{"version", "1.0"}
	};
	if (text != "")
	{
		response["response"]["text"] = text;
	}
	if (session_now != nullptr && (*session_now)["voice_mode"] == speak_mode)//nullptr - указатель типа json, но со значением 0, * - непрямое обращение
	{
		if (tts != "")
		{
			response["response"]["tts"] = tts;
		}
		response["response"]["buttons"].push_back(silent_button);
	}
	else if (session_now != nullptr && (*session_now)["voice_mode"] == silent_mode)
	{
		response["response"]["buttons"].push_back(speak_button);
	}
	return response;
}

void alice(const Request& req, Response& res)
{
	json request = json::parse(req.body);

	string user_id = request["session"]["application"]["application_id"];
	json response;
	json* session_now = nullptr;//nullptr указатель на 0, нельзя разыменовать, но можем изменить

	for (auto& session : s_array)//проверка, была ли такая сессия
	{
		if (session["user_id"] == user_id)
		{
			session_now = &session;
			break;
		}
	}
	//новая сессия

	string text;
	string tts;

	if (request["session"]["new"].get<bool>())
	{
		if (session_now == nullptr)
		{
			json session =
			{
				{"user_id", user_id},
				{"skill_mode", exit_mode},
				{"voice_mode", silent_mode},
				{"korzina", json::array()}
			};
			s_array.push_back(session);
			session_now = &s_array[s_array.size() - 1];
		}
		else
		{
			(*session_now)["skill_mode"] = exit_mode;
			(*session_now)["voice_mode"] = silent_mode;
		}

		json response = gen_response(
			text = u8"Салам бедным студентам.",
			tts = u8"Сал+ам б+едным студ+ентам.",
			exit_button,
			session_now);

		res.set_content(response.dump(2), "text/json; charset=UTF-8");
		return;
	}

	if (session_now == nullptr)
	{
		json response = gen_response(
			text = u8"Извините, произошла ошибка",
			tts = u8"Извин+ите, произошл+а ош+ибка",
			exit_button,
			session_now,
			true);
		res.set_content(response.dump(2), "text/json; charset=UTF-8");
		return;
	}

	string command = request["request"]["command"];
	if ((*session_now)["skill_mode"] == help_mode)
	{

		if (command == u8"молчать")
		{
			text = u8"Скажите мне эту фразу и я не буду озвучивать свои сообщения.";
			tts = u8"Скажите мне эту фразу и я не буду озвучивать свои сообщения.";
		}
		else if (command == u8"говорить")
		{
			text = u8"Скажите мне говорить и я буду озвучивать все свои сообщения";
			tts = u8"Скажите мне говорить и я буду озвучивать все свои сообщения";
		}
		else if (command == u8"помощь")
		{
			text = u8"Это то, где вы сейчас находитесь. "
				u8"В этом режиме я расскажу вам подробно о своих возможностях.";
			tts = u8"Это то, где вы сейчас находитесь. "
				u8"В этом режиме я расскажу вам подробно о своих возможностях.";
		}
		else if (command == u8"корзина")
		{
			text = u8"Я запомню, что вы будете добавлять или удалять из корзины.\n"
				u8"Чтобы добавить что-то, скажите \"Добавить в корзину сыр 5 рублей\".\n"
				u8"Чтобы удалить что-то, скажите \"Удалить из корзины сыр\".";
			tts = u8"Я запомню, что вы будете добавлять или удалять из корзины.\n"
				u8"Чтобы добавить что-то, скажите \"Добавить в корзину сыр 5 рублей\".\n"
				u8"Чтобы удалить что-то, скажите \"Удалить из корзины сыр\".";
		}
		else if (command == u8"сумма")
		{
			text = u8"Я подсчитаю стоимость всех товаров в вашей корзине и назову их общую стоимость.";
			tts = u8"Я подсчитаю стоимость всех товаров в вашей корзине и назову их общую стоимость.";
		}
		else if (command == u8"покупка завершена")
		{
			text = u8"Я передам список ваших покупок и очищу корзину.";
			tts = u8"Я передам список ваших покупок и очищу корзину.";
		}
		else if (command == u8"выйти из помощи")
		{
			text = u8"Выхожу. Нужна будет помощь - обращайтесь.";
			tts = u8"Выхожу. Нужна будет помощь - обращайтесь.";
			(*session_now)["skill_mode"] = exit_mode;
		}
		else
		{
			text = u8"С этим я не могу вам помочь.";
			tts = u8"С +этим я не мог+у вам пом+очь.";
		}

		json response;
		if ((*session_now)["skill_mode"] == help_mode)
		{
			response = gen_response(text, tts, help_button, session_now);
		}
		else
		{
			response = gen_response(text, tts, exit_button, session_now);
		}
		res.set_content(response.dump(2), "text/json; charset=UTF-8");
	}
	else
	{
		if (command == u8"молчать")
		{
			string text = u8"Молчу, молчу";
			string tts;
			(*session_now)["voice_mode"] = silent_mode;
			json response = gen_response(
				text,
				tts,
				exit_button,
				session_now);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");//передаём в ответ json response
		}
		else if (command == u8"говорить")
		{
			string text = u8"Хорошо.";
			string tts = u8"Хорош+о.";
			(*session_now)["voice_mode"] = speak_mode;
			json response = gen_response(
				text,
				tts,
				exit_button,
				session_now);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command == u8"помощь")
		{
			string text =
				u8"Говорить или молчать. Включает и выключает голосовой режим.\n"
				u8"Корзина. Позволяет вести список покупок, а так же их совершать.\n"
				u8"Помощь. Рассказывает о возможностях этого навыка.\n"
				u8"Совершить покупку. Очищает корзину и сохраняет данные в формате эксель.\n"
				u8"Сумма. Считает сумму товаров и называет её вам.\n"
				u8"О чём рассказать подробнее?";
			string tts =
				u8"Говорить или молчать. Включает и выключает голосовой режим.\n"
				u8"Корзина. Позволяет вести список покупок.\n"
				u8"Помощь. Рассказывает о возможностях этого навыка.\n"
				u8"Совершить покупку. Очищает корзину.\n"
				u8"Сумма. Считает сумму товаров.\n"
				u8"О чём рассказать подробнее?";
			json response = gen_response(
				text,
				tts,
				help_button,
				session_now);
			(*session_now)["skill_mode"] = help_mode;
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command == u8"очистить корзину")
		{
			string text = u8"Корзина пуста.";
			string tts = u8"Кориз+ина пуст+а.";
			json response = gen_response(
				text,
				tts,
				exit_button,
				session_now);
			(*session_now).erase("cart");
			(*session_now)["cart"] = json::array();
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command == u8"что в корзине")
		{
			cout << "cart: " << (*session_now)["cart"] << std::endl;

			string text;
			string tts;

			if ((*session_now)["cart"].empty())
			{
				text = u8"На данный момент ваша корзина пуста.";
				tts = u8"На данный момент ваша корзина пуста.";
			}
			else
			{
				text = u8"На данный момент в вашей корзине:";
				for (auto& elem : (*session_now)["cart"])
				{
					int price = elem["price"].get<int>();

					text += "\n"
						+ elem["item"].get<std::string>()
						+ u8" ценой "
						+ to_string(price);

					if (price % 10 == 0)
					{
						text += u8" рублей,";
					}
					else if (price % 10 == 1)
					{
						text += u8" рубль,";
					}
					else if (price % 10 < 5 && price % 10 > 0)
					{
						text += u8" рубля,";
					}
					else
					{
						text += u8" рублей,";
					}
				}
				text.pop_back();
				tts = text;
			}

			json response = gen_response(
				text,
				tts,
				exit_button,
				session_now);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command == u8"покупка завершена")
		{
			string text = u8"Заходите ещё!";
			string tts = u8"Заход+ите ещ+ё!";

			json output =
			{
				{"user_id", user_id},
				{"cart", (*session_now)["cart"]}
			};

			json file = get_from_web();

			for (string link : file["webhooks"])
			{
				cout << "link " << link << endl;
				int index = link.find('/', static_cast<string>("https://").size());
				Client cli(link.substr(0, index).c_str());
				cli.Post(link.substr(index, -1).c_str(), output.dump(2), "application/json; charset=UTF-8");
				
			}

			(*session_now).erase("cart");
			(*session_now)["cart"] = json::array();

			json response = gen_response(
				text,
				tts,
				exit_button,
				session_now,
				true);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command == u8"сумма")
		{
			string text = "";
			string tts = "";

			size_t size = request["request"]["nlu"]["tokens"].size();
			int sum = 0;
			for (auto& cart_item : (*session_now)["cart"])
			{
				sum += cart_item["price"].get<int>();
			}
			if (sum == 0)
			{
				text = u8"У вас в корзине нет товаров.";
				tts = u8"У вас в корз+ине нет тов+аров.";
			}
			else
			{
				text = u8"В общей сумме у вас товаров на " + std::to_string(sum);
				tts = u8"В +общей с+умме у вас тов+аров на " + std::to_string(sum);
				if (sum % 10 == 0)
				{
					text += u8" рублей.";
					tts += u8" рубл+ей.";
				}
				else if (sum % 10 == 1)
				{
					text += u8" рубль.";
					tts += u8" рубль.";
				}
				else if (sum % 10 < 5 && sum % 10 > 0)
				{
					text += u8" рубля.";
					tts += u8" рубл+я.";
				}
				else
				{
					text += u8" рублей.";
					tts += u8" рубл+ей.";
				}
			}

			json response = gen_response(
				text,
				tts,
				exit_button,
				session_now);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command.find(u8"добавить в корзину") == 0)
		{
			size_t size = request["request"]["nlu"]["tokens"].size();
			std::string text = u8"ОК.";
			std::string tts = u8"Ок+ей.";
			std::string item_name;
			int			item_price = 0;
			int			number_index = 0;
			bool			number_index_set = false;

			for (auto entity : request["request"]["nlu"]["entities"])
			{
				if (entity["type"].get<string>() == "YANDEX.NUMBER")
				{
					number_index = entity["tokens"]["start"];
					std::cout << entity["value"].type_name() << std::endl;
					int val = entity["value"];
					if (val < 0)
					{
						text = u8"Да где такое видано?!";
						tts = u8"Да где такое в+идано?!";
					}
					else if (val == 0)
					{
						text = u8"Своровал?";
						tts = u8"Своровал?";
					}
					else
					{
						item_price = val;
					}
					number_index_set = true;
					break;
				}
			}
			if (size == 3)
			{
				text = u8"А что добавлять-то?";
				tts = u8"А что добавлять-то?";
			}
			else if (!number_index_set)
			{
				text = u8"Когда взвешивали, наклейку не наклеили? Идите, клейте. ";
				tts = u8"Когда взв+ешивали, накл+ейку не накл+еили? Ид+ите, кл+ейте.";
			}
			else if (number_index == 3)
			{
				text = u8"Покажуйста, укажите название товара.";
				tts = u8"Пож+алуйста, укаж+ите назв+ание тов+ара.";
			}
			else
			{
				for (int i = 3; i < number_index; ++i)
				{
					item_name += request["request"]["nlu"]["tokens"][i].get<std::string>();
					item_name += " ";
				}
				item_name.pop_back();
				json item = {
					{"item",  item_name},
					{"price", item_price}
				};
				(*session_now)["cart"].push_back(item);
			}

			json response = gen_response(
				text,
				tts,
				exit_button,
				session_now);

			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command.find(u8"удалить из корзины") == 0)
		{
			cout << (*session_now)["cart"] << std::endl;
			size_t size = request["request"]["nlu"]["tokens"].size();

			string text;
			string tts;
			string item_name = "";

			for (int i = 3; i < size; ++i)
			{
				cout << request["request"]["nlu"]["tokens"][i].get<std::string>() << endl;
				item_name += request["request"]["nlu"]["tokens"][i].get<std::string>();
				item_name += " ";
			}
			bool found_item = false;
			int	item_index = 0;

			if (item_name == "")
			{
				text = u8"Ну вы хоть скажите, что собираетесь убирать.";
				tts = u8"Ну вы хоть скаж+ите, что собир+аетесь убир+ать.";
			}
			else
			{
				item_name.pop_back();
				for (auto& cart_item : (*session_now)["cart"])
				{
					if (cart_item["item"].get<std::string>() == item_name)
					{
						found_item = true;
						break;
					}
					++item_index;
				}
				if (!found_item)
				{
					text = u8"Такого в вашей корзине нету";
					tts = u8"Так+ого в в+ашей корз+ине н+ету.";
				}
				else
				{
					text = u8"Галя, отмена!";
					tts = u8"Г+аля, отм+ена!";
					(*session_now)["cart"].erase((*session_now)["cart"].begin() + item_index);
				}
			}
			json response = gen_response(
				text,
				tts,
				exit_button,
				session_now);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else
		{
			string text = u8"Это что за шуточки?";
			string tts = u8"Это что за шуточки?";

			json response = gen_response(
				text,
				tts,
				exit_button,
				session_now);

			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
	}
}



int main()
{
	Server svr;
	svr.Get("/webhooks", h_get);
	svr.Post("/webhooks", h_post);
	svr.Post("/alice", alice);
	svr.listen("localhost", 1234);
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
