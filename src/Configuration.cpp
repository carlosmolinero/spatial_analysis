#include "Configuration.h"

std::string Configuration::_folder;
std::string Configuration::_subFolderIn;
std::string Configuration::_subFolderOut;
std::string Configuration::_subFolderCoordinatesFile;
std::string Configuration::_coordinatesFileName;
std::unordered_map<unsigned long long,Point2d> Configuration::_coordinatesNodes;
Configuration::Configuration()
{
    //ctor
//   Configuration::_folder="C:/Users/Carlos/Documents/_TRABAJO/CASA/";
}

Configuration::~Configuration()
{
    //dtor
}

std::string Configuration::folder(){
    return Configuration::_folder;
}
std::string Configuration::folderIn(){
    std::stringstream ss;
    ss<<folder()<<Configuration::_subFolderIn;
    return ss.str();
}
std::string Configuration::folderOut(){
    std::stringstream ss;
    ss<<folder()<<Configuration::_subFolderOut;
    return ss.str();
}
std::string Configuration::coordinatesFile(){
    std::stringstream ss;
    ss<<folder()<<Configuration::_subFolderCoordinatesFile<<Configuration::_coordinatesFileName;
    return ss.str();
}

void Configuration::setFolder(std::string name){
    Configuration::_folder=name;
}
void Configuration::setSubFolderIn(std::string name){
    Configuration::_subFolderIn=name;
}
void Configuration::setSubFolderOut(std::string name){
    Configuration::_subFolderOut=name;
}

void Configuration::setSubFolderCoordinatesFile(std::string name){
    Configuration::_subFolderCoordinatesFile=name;
}
void Configuration::setCoordinatesFileName(std::string name){
    Configuration::_coordinatesFileName=name;
}

void Configuration::addCoordinate(unsigned long long id,Point2d location){
    Configuration::_coordinatesNodes[id]=location;
}
void Configuration::addCoordinate(unsigned long long id,double x,double y){
    Configuration::_coordinatesNodes[id]=Point2d(x,y);
}
Point2d Configuration::getCoordinate(unsigned long long id){
    Point2d point=Configuration::_coordinatesNodes[id];
    return point;
}