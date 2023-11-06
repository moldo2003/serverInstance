#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>


std::string generateUniqueId() {
    // Generate a timestamp
    std::time_t currentTime = std::time(nullptr);

    // Generate a random number
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int random = std::rand();

    // Combine timestamp and random number to create a unique ID
    std::stringstream ss;
    ss << currentTime << random;
    return ss.str();
}

