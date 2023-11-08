#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "json.hpp"
class User {
private:
    std::string name;
    double time;
public:
    User(std::string name, double time) {
        this->name = name;
        this->time = time;
    }

    // Getter method for the 'name' member
    std::string getName() const {
        return name;
    }

    // Getter method for the 'time' member
    double getTime() const {
        return time;
    }
};

class LeaderBoard {
    
private:
	std::vector<User> users;
	int lastTime;
    int leaderboardSize = 0;
public:
	LeaderBoard(){
        std::ifstream inputFile("leaderboard.txt"); // Open the file for reading
        lastTime = 60;
        if (!inputFile.is_open()) {
            std::cerr << "Failed to open the file." << std::endl;
        }
        else {
            std::string name;
            double time;

            while (inputFile >> name >> time) {
                User newUser(name, time);  // Create a User object
                this->users.push_back(newUser); // Add the object to the vector
            }
            leaderboardSize = users.size();
            lastTime = users[users.size() - 1].getTime();
        }
        inputFile.close();
	}

    void saveLeaderBoard() {
        std::ofstream outputFile("leaderboard.txt"); // Open the file for writing

        if (!outputFile.is_open()) {
            std::cerr << "Failed to open the file for writing." << std::endl;
            return;
        }

        // Iterate through the users vector and save each user's data to the file
        for (const User& user : users) {
            outputFile << user.getName() << " " << user.getTime() << std::endl;
        }

        outputFile.close(); // Close the file
    }

    void checkLeaderBoard(const std::string& name, double time) {

        if (time < lastTime || leaderboardSize <10) {
            User newUser(name, time);
            this->users.push_back(newUser);

            std::cout << "asdas";
            // Sort the leaderboard in ascending order of time
            std::sort(this->users.begin(), this->users.end(), [](const User& a, const User& b) {
                return a.getTime() < b.getTime();
                });

            // If the leaderboard size exceeds the limit, remove the last user
            if (users.size() > 10) {
                this->users.pop_back();
            }
            saveLeaderBoard();
            // Update the lastTime
            this->lastTime = users[users.size() - 1].getTime();
        }
    }

    nlohmann::json toJson() const {
        nlohmann::json leaderboardJson;

        for (const User& user : users) {
            nlohmann::json userJson;
            userJson["name"] = user.getName();
            userJson["time"] = user.getTime();
            leaderboardJson.push_back(userJson);
        }

        return leaderboardJson;
    }

};
