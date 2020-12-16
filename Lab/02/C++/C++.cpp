
#include <iostream> 
#include <string> 
#include <vector> 
#include <fstream> 
#include <sstream> 
using namespace std; 

#include <cpp_httplib/httplib.h> 
using namespace httplib; 
#include <json/json.hpp> 
using json = nlohmann::json; 



Server server; 
const int SERVER_PORT = 1234;

string pwd; 

string template_webhook_single; 
string template_webhook_page; 

string config_path; 
string speech_path; 

json config; 

string file_pwd() {
	return ".";
}

string file_read(string abspath) {
	string res;
	ifstream file(abspath);
	if (file.good()) {
		res = string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
		file.close();
		return res;
	}
	else {
		file.close();
		cout << "file_read Error: file ifstream is bad. (" << abspath << ")" << endl;
		throw "file_read Error: file ifstream is bad.";
	}
}
void file_write(string abspath, const string& data) {
	ofstream file;
	file.open(abspath);
	file << data;
	file.close();
}

json file_read_json(string abspath) {
	return json::parse(file_read(abspath));
}

void file_write_json(string abspath, json data) {
	file_write(abspath, data.dump());
}

bool file_exists(string abspath) {
	ifstream file(abspath);
	bool res = file.good();
	file.close();
	return res;
}

string replace_all(string str, const string& from, const string& to)
{
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != string::npos)
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); 
	}
	return str;
}

void config_write() {
	file_write_json(config_path, config);
}

void config_read() {
	config = file_read_json(config_path);
}

int hook_get_index(string url) {
	int i = 0;
	for (auto& hook : config["webhooks"]) {
		if (url == hook.get<string>()) return i;
		i++;
	}
	return -1; 
}

void hook_set(string url) {
	if (hook_get_index(url) == -1) {
		config["webhooks"].push_back(url);
		config_write();
	}
}

void hook_del(string url) {
	int index = hook_get_index(url);
	if (index != -1) {
		config["webhooks"].erase(index);
		config_write();
	}
}

string hook_page_get_html() {
	string webhooks_html = "";
	for (auto& hook : config["webhooks"]) {
		webhooks_html += replace_all(template_webhook_single, "{Webhook URL}", hook) + "\n";
	}
	string res_html = replace_all(template_webhook_page, "{webhooks_list}", webhooks_html);
	return res_html;
}


#include "post_root.cpp"
#include "post_webhooks.cpp"


int main(int argc, char** argv)
{
	try {
		pwd = file_pwd();

		template_webhook_page = file_read(pwd + "\\html\\webhook-page.html");
		template_webhook_single = file_read(pwd + "\\html\\webhook-single.html");

		config_path = pwd + "\\json\\config.json"; 
		if (!file_exists(config_path)) 
			file_write(config_path, R"({ "webhooks": [] })"); 
		config_read(); 

		server.Post("/", post_root_handler); 
		server.Post("/webhooks", post_webhooks_handler);

		cout << "Server served on localhost:" << SERVER_PORT << "\n";
		server.listen("localhost", SERVER_PORT);

		return 0;
	}
	catch (const char* e) {
		cout << e;
	}
}