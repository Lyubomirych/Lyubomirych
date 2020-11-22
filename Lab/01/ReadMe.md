<p align="center">МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ<br>
Федеральное государственное автономное образовательное учреждение высшего образования<br>
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"<br>
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ<br>
Кафедра компьютерной инженерии и моделирования</p>
<br>
<h3 align="center">Отчёт по лабораторной работе № 1<br> по дисциплине "Программирование"</h3>
<br><br>
<p>студента 1 курса группы ПИ-б-о-202(1)<br>
Ясина Любомира Любомировича<br>
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

## Цель:

1. Закрепить навыки разработки многофайловыx приложений;
2. Изучить способы работы с API web-сервиса;
3. Изучить процесс сериализации/десериализации данных в/из json;
4. Получить базовое представление о сетевом взаимодействии приложений;

## Постановка задачи
Разработать сервис предоставляющий данные о погоде в городе Симферополе на момент запроса.  В качестве источника данных о погоде используйте: http://openweathermap.org/. В состав сервиса входит: серверное приложение на языке С++ и клиентское приложение на языке Python.

Серверное приложение (далее Сервер) предназначенное для обслуживания клиентских приложений и минимизации количества запросов к сервису openweathermap.org. Сервер должен обеспечивать возможность получения данных в формате JSON и виде html виджета (для вставки виджета на страницу будет использоваться iframe).

Клиентское приложение должно иметь графический интерфейс отображающий сведения о погоде и возможность обновления данных по требованию пользователя.

## Выполнение работы
В ходе выполнения работы была пройдена регистрация на сервисе API openwheatermap.org, а также пройдено его изучение. После прохождения регистрации был создан индивидуальный API ключ: 44cdaae41e8f31ab402fc602121792db.

После этого были произведены тестовые запросы, для исключения ошибок и изучения на ответов сервера.

Запрос, отправляемый на сервер погоды включает в себя широту и долготу места, для которого необходимо получить погоду, в запросе были изменены параметры, кроме почасового, установлен ключ API, метрические единицы изменения (цельсий) и описание на русском языке: 

api.openweathermap.org/data/2.5/onecall?lat=44.95719&lon=34.11079&exclude=current,minutely,daily,alerts&appid=44cdaae41e8f31ab402fc602121792db&units=metric&lang=ru

Также на ресурсе worldtimeapi.org был получен ключ API для сервера времени:

http://worldtimeapi.org/api/timezone/Europe/Simferopol

После написания приложений сервера и клиента была использованна программа ngrok для установки туннеля связи с сервером из интернета (Рис. 1-2).

![](./image/1.png)

Рисунок 1 - запущенная программа ngrok

![](./image/2.PNG)

Рисунок 2 - проверка работы туннеля подключением со смартфона

Исходный код сервера:
```cpp
#include <iostream>
#include <string>
#include <cpp_httplib/httplib.h>
#include <nlohmann/json.hpp>
using namespace httplib;
std::ostringstream ostr;

std::string latitude = "44.95719";
std::string longitude = "34.11079";
std::string exclude = "current,minutely,daily,alerts";
std::string lang = "ru";
std::string units = "metric";
std::string appid = "44cdaae41e8f31ab402fc602121792db";

using json = nlohmann::json;
json cache;
Client cli("http://api.openweathermap.org");


int vremya() {
	Client time("http://worldtimeapi.org");
	auto res = time.Get("/api/timezone/Europe/Simferopol");
	if (res) {
		if (res->status == 200) {
			json j = json::parse(res->body);
			int unixtime = j["unixtime"];
			return unixtime;
		}
	}
	else {
		auto err = res.error();
	}
}

json pogoda() {
	std::string request = "/data/2.5/onecall?lat=" + latitude + "&lon=" + longitude + "&exclude=" + exclude + "&appid=" + appid + "&units=" + units + "&lang=" + lang;
	auto res = cli.Get(request.c_str());
	json j2;
	if (res) {
		if (res->status == 200) {
			json j = json::parse(res->body);
			return j["hourly"];
		}
		else {
			return "error";
		}
	}
	else {
		auto err = res.error();
		return "error";
	}
}

void findAndReplaceAll(std::string& data, std::string toSearch, std::string replaceStr) {
	size_t pos = data.find(toSearch);
	while (pos != std::string::npos) {
		data.replace(pos, toSearch.size(), replaceStr);
		pos = data.find(toSearch, pos + replaceStr.size());
	}
}


int cache_time(int unixtime) {
	for (int i = 0; i < cache.size(); i++) {
		int cache_time = cache[i]["dt"];
		if ((unixtime - cache[i]["dt"] < 3600) && (unixtime - cache[i]["dt"] > 0)) {
			return i;
		}
	}
	return -1;
}


void gen_response(const Request& req, Response& res) {

	std::string http_templ = R"(<!DOCTYPE html>
<html lang="ru"><head><meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
	
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>Погода сейчас</title>
<style type="text/css">
body {
	margin: 0;
	padding: 0;
}
.container-widget--18 {
	margin-top: 15px;
}
</style>
<link rel="stylesheet" type="text/css" href="chrome-extension://onbkopaoemachfglhlpomhbpofepfpom/styles.css"></head>
<body>
<div id="openweathermap-widget-18" class="container-widget container-widget--18">
	<div id="container-openweathermap-widget-18">
		<link href="http://openweathermap.org/themes/openweathermap/assets/vendor/owm/css/openweathermap-widget-right.min.css" rel="stylesheet">
		<div class="widget-right widget-right--type5 widget-right--brown">
			<div class="widget-right__layout widget-right__layout--brown">
				<div class="widget-right-card">
					<div class="widget-right__title">Simferopol</div>
					<div class="widget-right__description">{hourly[i].weather[0].description}</div>
                    </div><img src="http://openweathermap.org/img/wn/{hourly[i].weather[0].icon}.png" width="64" height="64" class="weather-right__icon weather-right__icon--type5 weather-right__icon--brown">
                    <table class="weather-right-card">
                      <tbody><tr class="weather-right-card__items">
                        <td class="weather-right-card__item weather-right-card__temperature-min">{hourly[i].temp}<span>&degC</span></td>
						<td class="weather-right-card__item weather-right-card__temperature-min">{hourly[i].temp}<span>&degC</span></td>
                      </tr>
                    </tbody></table>
                  </div>
                  <div class="widget-right__footer widget-right__footer--brown">
                    <div class="widget-right__layout">
                        <div class="widget-right__logo_container widget-right__negative_top_container">
                            <a href="http://openweathermap.org/" target="_blank"><div class="widget-right__logo_black_small"></div></a>
                        </div>
                        <div class="widget-right__date">Now</div>
                      </div>
                  </div>
                </div></div></div>

<div class="mallbery-caa" style="z-index: 2147483647 !important; text-transform: none !important; position: fixed;"></div></body></html>)";

	int time = vremya();

	if (cache.empty()) {
		cache = pogoda();
	}

	int i = cache_time(time);

	bool prover = 1;
	while (prover == 1) {
		if (i == -1) {
			cache = pogoda();
			int i = cache_time(time);
		}
		else {
			double temp_cache = cache[i]["temp"];
			int temp = round(temp_cache);

			findAndReplaceAll(http_templ, "{hourly[i].weather[0].description}", cache[i]["weather"][0]["description"]);
			findAndReplaceAll(http_templ, "{hourly[i].weather[0].icon}", cache[i]["weather"][0]["icon"]);
			findAndReplaceAll(http_templ, "{hourly[i].temp}", std::to_string(temp));

			prover = 0;

			res.set_content(http_templ, "text/html");
		}
	}

}

void gen_response_raw(const Request& req, Response& res) {

	int time = vremya();

	if (cache.empty()) {
		cache = pogoda();
	}

	int i = cache_time(time);

	bool prover = 1;
	while (prover == 1) {
		if (i == -1) {
			cache = pogoda();
			int i = cache_time(time);
		}
		else {
			double temp_cache = cache[i]["temp"];
			int temp = round(temp_cache);

			json j3;
			j3["temp"] = temp;
			j3["description"] = cache[0]["weather"][0]["description"];

			prover = 0;

			res.set_content(j3, "text/json");
		}
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	Server svr;
	svr.Get("/", gen_response);
	svr.Get("/raw", gen_response_raw);
	svr.listen("localhost", 3000);
}
```

Исходный код клиента:
```python
from tkinter import *
import json
import requests

def reload_data(event=None):
	try:
		response = requests.get('http://localhost:3000/raw').content.decode("utf8")
		forecast_j = json.loads(response)
		desc.config(text=str(forecast_j["description"]))
		temp.config(text=str(forecast_j["temp"]) + "°C")
	except requests.exceptions.ConnectionError:
		pass
root = Tk()
root.title("Погода")
root.pack_propagate(0)
root.bind("<Button-1>", reload_data)
zheltiy = "#ffb84d"
beliy = "#ffffff"
_w = 100
_h = 30

top_frame =    Frame(root, bg=_yellow, width=_w, height=_h)
middle_frame = Frame(root, bg=_white,  width=_w, height=_h*3)
bottom_frame = Frame(root, bg=_yellow, width=_w, height=_h)

top_frame.pack(side=TOP, fill=X)
middle_frame.pack(expand=True, fill=BOTH)
bottom_frame.pack(side=BOTTOM, fill=X)

city = Label(top_frame, font=("Calibri Bold", 12), text="Симферополь", bg=zheltiy)
weather = Label(middle_frame, font=("Impact", 48), bg=beliy)
desc = Label(top_frame, font=("Calibri", 12), bg=zheltiy)


city.pack(pady=0)
weather.pack(expand=True)
desc.pack(pady=0)


reload_data()
root.mainloop()
```

Скриншот приложения клиента показан на рисунке 3.

![](./image/3.png)

Рисунок 3 - приложение клиента

Скриншот виджета клиента показан на рисунке 4.

![](./image/4.png)

Рисунок 4 - приложение сервера

## Вывод по работе. 
Для достижения поставленной цели были выполнены все поставленные задачи, а именно:
	1) Изучены документации по API для серверов погоды и времени, структура HTTP-запросов, работа с JSON на языках программирования C++ и Python, модуль TKinter;
	2) Создано серверное приложение на языке программирования C++, которое по запросу может возвращать виджет в формате html или данные для использования в клиентском приложении в формате json;
	3) Создано клиентское приложение на языке программирования Python, имеющее графическое представление, для чего была использована библиотека TKinter. Приложение позволяет отправлять запросы на сервер и обрабатывать ответы, для получения погоды на текущий момент.
