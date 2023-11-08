#pragma once
#include <ctime>
#include <iostream>

class Logger {
private:
    time_t startTime;
    time_t endTime;

public:
    void start() {
        startTime = time(0);
    }

    void end() {
        endTime = time(0);
    }

    bool check(int penalty) {
        int elapsedSeconds = endTime - startTime;

        if (elapsedSeconds + penalty < 60) {

            return true;
        }
        else {
             
            return false;
        }
    }

    int getTime() {
        return endTime - startTime;
    }
};
