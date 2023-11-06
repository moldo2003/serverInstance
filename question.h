#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "json.hpp"

class Question
{
 protected:
    std::string question;
    std::vector<std::string> answers;
    std::string correct_answer;
 public:
    Question(std::string question , std::vector<std::string> answers, std::string correct_answer ){
         this->question = question;
         this->answers = answers;
         this->correct_answer = correct_answer;
    }
    bool verifyQuestion(std::string answer) {
        return answer == correct_answer;
    }
    nlohmann::json toJson() {
        nlohmann::json json;
        json["question"] = question;
        json["answers"] = answers;
        return json;
    }
};