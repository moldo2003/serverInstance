#pragma once
#include <iostream>
#include <string.h>
#include  "questions.h"
#include "loger.h"
#include "leaderbord.h"
class Game {
private:

    std::string userId;
    int level;
    int penalty;
    int answerd[6] = { 0,0,0,0,0};
    Questions* q ;
    Logger loger = Logger();
    LeaderBoard* leaderboard;
    std::vector<Question> gameQuestions;
public:

    Game(std::string userId , LeaderBoard* leaderboard, Questions* q) {
        this->userId = userId;
        this->penalty = 0;
        this->level = 0;
        this->leaderboard = leaderboard;
        this->q = q;
        gameQuestions = q->generare_intrebari();
    }

    nlohmann::json toJson() {
        loger.start();
        nlohmann::json response;

        response["level"] = std::to_string(level);
        response["questions"] = q->toJson(gameQuestions);

        return response;
    }

    bool compareId(std::string userId) {
        return this->userId == userId;
    }
    
    std::string verifyQuestion(int index,std::string raspuns,std::string name) {
        if (gameQuestions[index].verifyQuestion(raspuns) && answerd[index] == 0) {
            if (level == 4) {
                return this->endGame(name);
            }
            else {
                answerd[index] = 1;
                level++;
                return "Correct";
            }
        }
        else {
            penalty += 5;
            
            return "Incorect";
        }

    }
    std::string endGame(std::string name) {
        loger.end();
        if (loger.check(penalty))
        {   
            leaderboard->checkLeaderBoard(name, loger.getTime() + penalty);
            return "GameValid";

            //verify in scoreboard
        }
        else {
            return "GameInvalid";
        }
    }
};
