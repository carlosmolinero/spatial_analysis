#ifndef TIMER_H
#define TIMER_H
#include <sys/timeb.h>
#include <chrono>
#include <sstream>
#include <unordered_map>
#include <vector>
//#include "Point2d.h"
//#include "TextFile.h"
//#include <time_point>
class Timer
{
public:
    Timer();
    virtual ~Timer();
    Timer(const Timer& other);
//    void saveToFile(std::string name);
//    void saveLastTimeToFile(std::string name);
    void start(std::string nameOfFunction);
    void restart(std::string nameOfFunction);

    void stop();
    bool active;
    std::vector<std::string> getTimes();

protected:
private:
    bool restarting;
    std::chrono::high_resolution_clock::time_point startTime;
    bool running;
    std::string nameOfFunction;
    std::unordered_map<std::string,signed long long> namesOfFunctions;
};

#endif // TIMER_H
