#include <iostream>
#include <string>
using namespace std;
#include <cpp_httplib/httplib.h>
using namespace httplib;
#include <json/json.hpp>
using json = nlohmann::json;

string get_command(json yandex_json);
string get_product_name(json yandex_json, int product_token_index);
json get_product_set(json yandex_json, int product_token_index);
void remove_product(int product_token_index, json& yandex_json, json& state);


const string SPEECH_JSON_PATH = "\\json\\speech";
json state; 
string post_root_ans; 


void speech(string speech_name, json config = R"({})"_json) {
  
   string target_json_string = file_read(pwd + SPEECH_JSON_PATH + "/" + speech_name + ".json");
  
   json target_dialog = json::parse(target_json_string);
   
   bool not_startup = state != nullptr;

   cout << "Speech: " << speech_name << endl; 

   if (not_startup) { 
      if (config.contains("buttons")) { 
         auto buttons = config["buttons"].get<string>(); 

         if (buttons == "speak") { 
            if (!state["speak"].get<bool>()) { 
               target_dialog["response"].erase("tts"); 
               
               target_dialog["response"]["buttons"].push_back(R"({ "title": "Говорить" })"_json); 
            }
            else {
               target_dialog["response"]["buttons"].push_back(R"({ "title": "Молчать" })"_json);
            }
            target_dialog["response"]["buttons"].push_back(R"({ "title": "Корзина" })"_json);
         }
         else if (buttons == "cart") { 
            json buttons_cart = R"([
               { "title": "Очистить корзину" },
               { "title": "Добавить в корзину" },
               { "title": "Удалить из корзины" },
               { "title": "Что в корзине" },
               { "title": "Сумма" },
               { "title": "Покупка завершена" }
            ])"_json;

            for (auto& button : buttons_cart) { 
               target_dialog["response"]["buttons"].push_back(button);
            }
         }
      }

      
      if (config.contains("help_all_name")) {
         string help_text, help_tts;
         auto help_name = config["help_all_name"].get<string>();

         auto help_arr = json::parse(target_dialog["help_arr"].dump());
         target_dialog.erase("help_arr");

         
         for (auto it = help_arr.begin(); it != help_arr.end(); ++it) {
            json help_curr = *it;
            auto help_name_curr = help_curr["name"].get<string>();
            if (help_name_curr == help_name) {
               help_text = help_curr["text"].get<string>();
               help_tts = help_curr["tts"].get<string>();
               break;
            }
         }

         
         cout << "help::text: " << help_text << endl;
         cout << "help::tts: " << help_tts << endl;
         
         target_dialog["response"]["text"] = help_text;
         target_dialog["response"]["tts"] = help_tts;
      }

     
      if (config.contains("text")) {
         auto newText = config["text"].get<string>();
         target_dialog["response"]["text"] = newText;
         target_dialog["response"]["tts"] = newText;
      }

   
      target_dialog["session_state"] = state;
   }
   else { 
      state = R"({
            "speak": true,
            "cart": [],
            "mode": "normal"
         })"_json;

      target_dialog["session_state"] = state;
   }

  
   post_root_ans = target_dialog.dump(); 
}


void post_root_handler(const Request& req, Response& res)
{
try {
   cout << "////////////////" << endl;

   
   auto yandex_json = json::parse(req.body);

   
   if (yandex_json["session"]["new"].get<bool>()) {
      speech("startup", nullptr);
   } 
   else {
      state = yandex_json["state"]["session"]; 

      
      string command = get_command(yandex_json);
      cout << "\nЗапрос: " << command << "\n" << endl; 
     
      string command_orig = yandex_json["request"]["original_utterance"].get<string>();

      
      if (!(state.contains("cart") && state.contains("speak") && state.contains("mode"))) {
         speech("error"); 
      }
      else { 
         auto cart = state["cart"];
         auto speak = state["speak"];
         auto mode = state["mode"];

         bool is_wait = state.contains("wait") && !state["wait"].is_null();
         string wait = is_wait ? state["wait"].get<string>() : "";

         auto buttons_normal = R"({ 
               "buttons": "speak"
            })"_json;
         auto buttons_cart = R"({ 
               "buttons": "cart"
            })"_json;

         // число слов в запросе юзера
         int tokens_count = yandex_json["request"]["nlu"]["tokens"].size();

         // если мы в нормальном режиме (стартовый)
         if (mode == "normal") {
            if (false) {
            }
            else if (command == "молчать") {
               state["speak"] = false;
               speech("mode/silent", buttons_normal);
            }
            else if (command == "говорить") {
               state["speak"] = true;
               speech("mode/speak", buttons_normal);
            }
            else if (command == "помощь") {
               state["mode"] = "help";
               speech("help/start");
            }
            else if (command == "корзина") {
               state["mode"] = "cart";
               speech("cart/start", buttons_cart);
            }
            else {
               speech("unknown", buttons_normal);
            }
         }

         // если мы в режиме помощи
         else if (mode == "help") {
            if (command == "назад") {
               state["mode"] = "normal";
               speech("help/end", buttons_normal);
            }
            else {
               speech("help/all", json::parse("{ \"help_all_name\": \"" + command_orig + "\" }"));
            }
         }

         // если мы в режиме корзины
         else if (mode == "cart") {
            if (false) {
            }

            else if (command == "очистить корзину") {
               state["cart"] = json::array();
               speech("cart/skill/clean", buttons_cart);
            }

            else if ((is_wait && wait == "добавить в корзину") || command.rfind("добавить в корзину", 0) == 0) {
               if (!is_wait) {
                  if (tokens_count == 3) {
                     state["wait"] = "добавить в корзину";
                     speech("cart/skill/add_no_args");
                  }
                  else {
                     json productData = get_product_set(yandex_json, 3);
                     state["cart"].push_back(productData);
                     speech("cart/skill/add", buttons_cart);
                  }
               }
               else {
                  state["wait"] = nullptr;

                  json productData = get_product_set(yandex_json, 0);
                  state["cart"].push_back(productData);
                  speech("cart/skill/add", buttons_cart);
               }
            }

            else if ((is_wait && wait == "удалить из корзины") || command.rfind("удалить из корзины", 0) == 0) {
               if (!is_wait) {
                  if (tokens_count == 3) {
                     state["wait"] = "удалить из корзины";
                     speech("cart/skill/remove_no_args");
                  }
                  else {
                     remove_product(3, yandex_json, state);
                     speech("cart/skill/remove", buttons_cart);
                  }
               }
               else {
                  state["wait"] = nullptr;
                  remove_product(0, yandex_json, state);
                  speech("cart/skill/remove", buttons_cart);
               }
            }

            else if (command == "что в корзине") {
               auto cart = state["cart"];

               if (cart.empty()) speech("cart/skill/list_free", buttons_cart);
               else {
                  // генерация текста корзины
                  string cartText = "Корзина выглядит так: \\n";
                  for (auto& product : cart) {
                     auto name = product["name"].get<string>();
                     int priceVal = product["price"].get<int>();
                     auto price = to_string(priceVal);
                     cartText += name + " : " + price + "\\n";
                  }
                  json configList = {
                     { "text", cartText },
                     { "buttons", "cart" },
                  };
                  speech("cart/skill/list", configList);
               }
            }

            else if (command == "сумма") {
               int cartSum = 0;
               // подсчет суммы
               for (auto& product : state["cart"]) {
                  cartSum += product["price"].get<int>();
               }

               json configSum = {
                     { "text", "Суммарная стоимость: " + to_string(cartSum) },
                     { "buttons", "cart" },
               };
               speech("cart/skill/sum", configSum);
            }

            else if (command == "покупка завершена") {
               // получение id юзера
               string id = yandex_json["session"]["user"].contains("user_id")
                  ? yandex_json["session"]["user"]["user_id"].get<string>()
                  : "anonymous"; // он может быть анонимным
               // массив всех товаров юзера 
               json check = {
                  {"user_id", id},
                  {"check", state["cart"]},
               };

               // преобразуем json в строку
               string checkString = check.dump();

               // отправляем каждому вебхуку этот джейсон
               for (auto& hook : config["webhooks"]) {
                  string hookString = hook.get<string>();
                  Client sender{ hookString.c_str() };
                  // само отправление пост запроса
                  sender.Post("/", checkString, "application/json; charset=utf8");
               }

               state["mode"] = "normal";
               state["cart"] = json::array();
               speech("cart/end", buttons_normal);
            }

            else {
               speech("unknown", buttons_cart);
            }
         }
      }
   }

   cout << req.body.c_str() << endl; // вывод джейсона пришедшего от яндекса
   // вывод сгенерированного функцией speech в ответ яндексу
   res.set_content(post_root_ans, "text/json; charset=UTF-8");
} catch (const char* e) {
   cout << e;
}
}


string get_command(json yandex_json) {
   string command;
   if (yandex_json["request"].contains("command")) {
      command = yandex_json["request"]["command"].get<string>();
   }
   else {
      command = "";
      for (auto& token : yandex_json["request"]["nlu"]) {
         command += token.get<string>();
      }
   }
   return command;
}

string get_product_name(json yandex_json, int product_token_index) {
   return yandex_json["request"]["nlu"]["tokens"][product_token_index].get<string>();
}

json get_product_set(json yandex_json, int product_token_index) {
   string product_name = get_product_name(yandex_json, product_token_index);

   json entities = yandex_json["request"]["nlu"]["entities"];
   int product_price;
   for (auto it = entities.begin(); it != entities.end(); ++it) {
      if ((*it)["type"] == "YANDEX.NUMBER") {
         product_price = (*it)["value"].get<int>();
         break;
      }
   }

   auto res = json{
      {"name", product_name},
      {"price", product_price},
   };
   return res;
}

void remove_product(int product_token_index, json& yandex_json, json& state) {
   json new_cart = json::array();

   string product_name = get_product_name(yandex_json, product_token_index);
   int i = 0;
   for (auto& product : state["cart"]) {
      string product_nameCurr = product["name"].get<string>();
      if (product_name != product_nameCurr) {
         new_cart.push_back(product);
      }
      i++;
   }

   state["cart"] = new_cart;
}