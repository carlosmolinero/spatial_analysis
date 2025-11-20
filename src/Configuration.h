#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include<string>
#include<sstream>
#include<unordered_map>
#include "Point2d.h"


class Configuration
{
    static std::string _folder;
    static std::string _subFolderIn;
    static std::string _subFolderOut;
    static std::string _subFolderCoordinatesFile;
    static std::string _coordinatesFileName;
    static std::unordered_map<unsigned long long,Point2d> _coordinatesNodes;

public:

    Configuration();
    static const bool PARALLEL=true;
    static const bool NON_PARALLEL=false;
    static const bool PRECISE=true;
    static const bool NON_PRECISE=false;
    static const bool WITH_HEURISTIC=true;
    static const bool NO_WITH_HEURISTIC=false;
    static const bool CALCULATE_CENTRALITIES=true;
    static const bool NO_CALCULATE_CENTRALITIES=false;

    static const int numThreads=1;

    virtual ~Configuration();
    static std::string folder();
    static std::string folderIn();
    static std::string folderOut();
    static std::string coordinatesFile();
    static void setFolder(std::string name);
    static void setSubFolderIn(std::string name);
    static void setSubFolderOut(std::string name);
    static void addCoordinate(unsigned long long id,Point2d location);
    void addCoordinate(unsigned long long id,double x,double y);
    static Point2d getCoordinate(unsigned long long id);

    static void setSubFolderCoordinatesFile(std::string name);
    static void setCoordinatesFileName(std::string name);

//        static std::string getFolder();
//        static std::string folder="/Users/carlos/Documents/";
protected:
private:
};

#endif // CONFIGURATION_H
