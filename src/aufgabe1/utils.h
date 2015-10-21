#ifndef	UTILS_H_ 
#define UTILS_H_

#include <ctime>
#include <vector>

class Utils {
    private:
    	static std::vector<std::clock_t> begintimes;	
	Utils() {}

    public:
        static void startTimeMeasurement();
	static double endTimeMeasurement();
};

#endif /* UTILS_H_ */
