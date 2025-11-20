#include "Timer.h"

Timer::Timer()
{
    //ctor
    active=false;
    running=false;
    restarting=false;
}

Timer::~Timer()
{

    //dtor
}

Timer::Timer(const Timer& other)
{
    //copy ctor
}

void Timer::start(std::string nameOfFunction)
{
    if(active)
    {
        restarting=false;
        if(running)
        {
            stop();
        }
        running=true;
//        timeb tb;
//        ftime(&tb);
        startTime=std::chrono::high_resolution_clock::now();
//        long nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
//        startTime=nCount;
        this->nameOfFunction=nameOfFunction;
    }
}
void Timer::restart(std::string nameOfFunction)
{
    if(active)
    {
        restarting=true;
        if(running)
        {
            stop();
        }
        running=true;
        timeb tb;
        ftime(&tb);
        startTime=std::chrono::high_resolution_clock::now();
//        long nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
        
        this->nameOfFunction=nameOfFunction;
    }
}
void Timer::stop()
{
    std::stringstream resultSS;
    if(active)
    {
        auto secondPoint =std::chrono::high_resolution_clock::now();
        auto duration=secondPoint-startTime;
        restarting=false;
        running=false;
//        timeb tb;
//        ftime(&tb);
        
        
        double timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
//        std::cout<<"in stop "<<timeElapsed<<" "<<duration.count()<<'\n';
//        if(microseconds < 0)
//            microseconds += 0x100000 * 1000;
        namesOfFunctions[nameOfFunction]=timeElapsed+namesOfFunctions[nameOfFunction];
//        if(!restarting)
//        {
//            namesOfFunctions[nameOfFunction].y=1+namesOfFunctions[nameOfFunction].y;
//        }
//        resultSS<<nameOfFunction<<" "<<nanoseconds;
        nameOfFunction="____";
//        startTime=0;
        
    }
//    return resultSS.str();
    
}

std::vector<std::string> Timer::getTimes()
{

    std::vector<std::string> times;
    if(active)
    {
        restarting=false;
        if(running)
        {
            stop();
        }
        for (std::unordered_map<std::string,signed long long>::iterator it = namesOfFunctions.begin(); it != namesOfFunctions.end(); ++it)
        {
            std::stringstream valueSS;
            valueSS<<it->first<<" "<<std::to_string(it->second);
            std::string value=valueSS.str();
            times.push_back(value);
        }

    }
    return times;
}

//void Timer::saveToFile(std::string name){
////    ArchivoTexto textFile;
//    TextFile::writeToFile(name,getTimes(),false);
//}
//void Timer::saveLastTimeToFile(std::string name){
////    ArchivoTexto textFile;
//    std::vector<std::string> lines;
//    std::vector<std::string> linesTemp=getTimes();
//    lines.push_back(linesTemp[linesTemp.size()-1]);
////        lines.push_back(linesTemp[0]);
//    TextFile::writeToFile(name,lines,true);
//}

