//
//  Window.cpp
//  harmonicCities
//
//  Created by Carlos Molinero on 04/07/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#include "Windows.h"
long Windows::add(Point2d location,double sizeX,double sizeY){
    

    DrawingObjects object;
    object.startWindowX=location.x;
    object.startWindowY=location.y;
    object.scale=1;
    object.widthWindowX=sizeX;
    object.heightWindowY=sizeY;
    View view;
    
    view.objects.push_back(object);

    view.current=view.objects.size()-1;

    views.push_back(view);
    return views.size()-1;
    
}
void Windows::setTitle(long index,std::string title){
    views[index].title=title;
    indexByTitle[title]=index;
}
std::string Windows::getTitle(long index){
    return views[index].title;
}
long Windows::add(long index){
    DrawingObjects* objectReference=get(index);
    
    DrawingObjects object;
    object.copyAllParameters(objectReference);
//    object.startWindowX=location.x;
//    object.startWindowY=location.y;
//    object.scale=1;
//    object.widthWindowX=sizeX;
//    object.heightWindowY=sizeY;
    
    
    
    views[index].objects.push_back(object);
    
    views[index].current=views[index].objects.size()-1;
    
//    views.push_back(views[index]);
    return views.size()-1;
    
}
DrawingObjects* Windows::get(long indexWindow){
    return &views[indexWindow].objects[views[indexWindow].current];
}

DrawingObjects* Windows::get(std::string title){
    long indexWindow=indexByTitle[title];
    return &views[indexWindow].objects[views[indexWindow].current];
}

long Windows::size(){
    return views.size();
}

void Windows::decreaseCurrent(){
//    std::cout<<"-----------"<<'\n';
    for(long i=0;i<views.size();i++){
        if(views[i].current>0){
            views[i].current--;
//            std::cout<<views[i].current<<'\n';
        }
    }
}
void Windows::increaseCurrent(){
//    std::cout<<"-----------"<<'\n';
    for(long i=0;i<views.size();i++){
//        if(views[i].current<views[i].objects.size()-2&&views[i].objects.size()>1){
        if(views[i].current<views[i].objects.size()-1){
            views[i].current++;
//            std::cout<<views[i].current<<'\n';
        }
    }
}