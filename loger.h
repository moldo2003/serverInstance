#pragma once
#include<ctime>
class Loger {
   private:
	float startTime;
	float endTime;

    public:
		void start() {
			this->startTime = time(NULL);
		}

		void end() {
			this->endTime = time(NULL);
		}

		bool check(int penalty){
			if (endTime - startTime + penalty < 60)
				return true;
			else
				return false;
		}
	
};