#include "crow.h"
#include "crow/middlewares/cors.h"
#include "idGenerator.h"
#include "game.h"
#include "json.hpp"
#include <iostream>
#include <vector>
#include "questions.h"





int main()
{

    crow::App<crow::CORSHandler> app;
    auto& cors = app.get_middleware<crow::CORSHandler>();
    cors
        .global()
        .headers("X-Custom-Header", "Upgrade-Insecure-Requests")
        .methods("POST"_method, "GET"_method)
        .prefix("/")
        .origin("*")
        .prefix("/nocors")
        .ignore();
    

    std::vector<Game> games;

    CROW_ROUTE(app, "/")
        ([]() {
        return "Check Access-Control-Allow-Methods header";
            });

    CROW_ROUTE(app, "/generateId")
        ([]() {
        return generateUniqueId();
            });

    CROW_ROUTE(app, "/startGame")
        ([&games](const crow::request& req) {
        std::string response = "No User ID";

        if (req.url_params.get("userId") != NULL) {
            std::string userId = req.url_params.get("userId");
            std::cout << userId;
            games.push_back(Game(userId));
            response =  std::to_string(games.size());
        }
        return response;
        
       });
    CROW_ROUTE(app, "/getGame")(
        [&games](const crow::request& req) {

            if (req.url_params.get("userId") != NULL && req.url_params.get("gameId") != NULL) {
              std::string userId = req.url_params.get("userId");
              int gameId = std::atoi(req.url_params.get("gameId"));

              if (games[gameId - 1].compareId(userId) ){
          
                  crow::response response(games[gameId-1].toJson().dump());
                  response.add_header("Content-Type", "application/json");

                  return response;
              }
            }
            nlohmann::json a = {
                {"message","InvalidParams"}
            };
            crow::response response(a.dump());
            response.add_header("Content-Type", "application/json");
            return response;
        }
     );
    CROW_ROUTE(app, "/verifyQuestion")(
        [&games](const crow::request& req) {
            if (req.url_params.get("userId") != NULL && req.url_params.get("gameId") != NULL && req.url_params.get("index") != NULL && req.url_params.get("answer") != NULL) {
                std::string userId = req.url_params.get("userId");
                int gameId = std::atoi(req.url_params.get("gameId"));
                std::string answer = req.url_params.get("answer");
                int index = std::atoi(req.url_params.get("index"));

                std::cout << index;
                if (games[gameId - 1].compareId(userId))
                    return games[gameId - 1].verifyQuestion(index, answer);
            }
            return std::string("InvalidParams");
        }
     );


    app.port(7777).run();

    return 0;
}