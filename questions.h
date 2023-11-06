#pragma once
#include "question.h"
#include "predifinedQuestions.h"
#include <vector>
#include "json.hpp"

class Questions
{
protected:
    std::vector<Question> intrebari;

public:
    Questions()
    {  

        this->intrebari = intrebaripredefinite;

    }
    std::vector<Question> generare_intrebari()
    {
        std::vector<Question> questions;
        srand(0);
        for (int i = 1; i <= 5; i++) {
            int  a = rand() % 10;
            questions.push_back(intrebari[a]);
         //TODO no duplicate
        }
        return questions;
    }

    nlohmann::json toJson( std::vector<Question> questions) {
        nlohmann::json response;
        for (Question& question : questions) {
            response.push_back(question.toJson());
        }

        return response;
    }
    

};