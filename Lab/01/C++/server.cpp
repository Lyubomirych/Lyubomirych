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
			std::cout << j3;
			res.set_content(j3.dump(), "text/json");
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
