// данные
#include <unordered_map>
#include <vector>
#include <iostream>

// потоки
#include <thread>
#include <chrono>
#include <condition_variable>
#include <mutex>

// json и httplib
#include "include/httplib.h"
#include "include/json.hpp"

using namespace std;
using nlohmann::json;
using namespace httplib;

const char* response_type = "text/json; charset=utf-8";


struct Game
{
    struct Move {
        int player;
        string move;
    };
    const unsigned char
        player1_connected = 0b001,
        player2_connected = 0b010,
        player1_first_turn = 0b100;

    unsigned char bitmap;
    vector<Move> moves;

    Game()
        : bitmap(0)
    {}
    Game(Game&& rhs)
        : bitmap(rhs.bitmap),
        moves(move(rhs.moves))
    {
        rhs.bitmap = 0;
    }
    Game& operator =(Game&& rhs) {
        if (this == &rhs)
            return *this;
        moves = move(rhs.moves);
        return *this;
    }
};

// map[uid] -> Game
unordered_map<string, Game> game_map;
mutex m;

void post_handler(const Request& req, Response& res)
{
    string uid, move;
    int player;
    json j = json::parse(req.body);
    uid = j["uid"].get<string>();
    move = j["move"].get<string>();
    player = j["player"].get<int>();

    {
        unique_lock<mutex> lock(m);

        if (!game_map[uid].moves.empty())
        {
            Game::Move last_move = game_map[uid].moves.back();
            if (last_move.player == player) {
                json to_send{
                    {"status", "not-your-move"}
                };
                res.set_content(to_send.dump(2), response_type);
                return;
            }
        }

        game_map[uid].moves.push_back({ player, move });
    }

    json to_send{
        {"status", "success"}
    };
    res.set_content(to_send.dump(2), response_type);
}

void other_connected(const Request& req, Response& res)
{
    string uid = req.get_param_value("uid");
    int player = stoi(req.get_param_value("player"));

    auto& game = game_map[uid];
    bool other_connected;
    if (player == 1 and game.bitmap & game.player2_connected) {
        other_connected = true;
    }
    else if (player == 2) {
        other_connected = true;
    }
    else {
        other_connected = false;
    }
    json to_send{
        {"other-connected", other_connected},
    };
    res.set_content(to_send.dump(2), response_type);
}

void assign_role(Response& res, string uid)
{
    auto& game = game_map[uid];
    bool turn;
    int player;

    if (!(game.bitmap & game.player1_connected)) {
        player = 1;

        turn = rand() % 2;
        if (turn) game.bitmap |= game.player1_first_turn;
        game.bitmap |= game.player1_connected;
    }
    else {
        if (game.bitmap & game.player2_connected) {
            json to_send{
                {"status", "full"}
            };
            res.set_content(to_send.dump(2), response_type);
            return;
        }
        player = 2;

        turn = !(game.bitmap & game.player1_first_turn);
        game.bitmap |= game.player2_connected;
    }
    json to_send{
        {"status", "assign-role"},
        {"your-turn", turn},
        {"player", player},
    };
    res.set_content(to_send.dump(2), response_type);
}

void return_move(Response& res, string uid, int player)
{
    unique_lock<mutex> lock(m);

    if (game_map[uid].moves.empty()) {
        json to_send{
            {"status", "empty"}
        };
        res.set_content(to_send.dump(2), response_type);
        return;
    }

    Game::Move last_move = game_map[uid].moves.back();
    if (last_move.player != player)
    {
        json to_send{
            {"status", "move"},
            {"move", last_move.move},
            {"player", last_move.player}
        };
        res.set_content(to_send.dump(2), response_type);
        return;
    }

    json to_send{
        {"status", "no-moves"},
    };
    res.set_content(to_send.dump(2), response_type);
    return;
}

void get_handler(const Request& req, Response& res)
{
    string uid;
    uid = req.get_param_value("uid");

    if (!req.has_param("player")) {
        assign_role(res, uid);
        return;
    }

    int player;
    player = stoi(req.get_param_value("player"));

    return_move(res, uid, player);
}

int main()
{
    setlocale(0, "");
    Server server;
    server.Get("/other_connected", other_connected);
    server.Get("/", get_handler);
    server.Post("/", post_handler);
    server.set_exception_handler([](const Request&, Response& res, std::exception& e) {
        cout << "Exception: " << e.what() << endl;
        json j{ {"status", "server-error"} };
        res.set_content(j.dump(2), response_type);
        });

    string ip("127.0.0.1");
    //    cout << "Введите IP сервера: ";
    //    cin >> ip;

    int port = 8080;
    cout << "Введите порт сервера: " << flush;
    cin >> port;

    cout << "Запускаю сервер..." << endl;
    server.listen(ip.c_str(), port);
}
