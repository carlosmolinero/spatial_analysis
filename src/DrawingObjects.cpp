//
//  DrawingObjects.cpp
//  harmonicCities
//
//  Created by Carlos Molinero on 04/07/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#include "DrawingObjects.h"

DrawingObjects::DrawingObjects(){
    drawing=true;
    indexStableObject=0;
    indexTemporaryObject=0;
    scale=1;
    startX=0;
    startY=0;
    widthWindowX=900;
    heightWindowY=900;
    startWindowX=0;
    startWindowY=0;
    VectorNDim vec;
//    vec.values={0,0,0};
    vec.values.clear();
    vec.values.push_back(0);
    vec.values.push_back(0);
    vec.values.push_back(0);
    colorNextObject=vec;
}

void DrawingObjects::addStableObject(DrawingObject object){
    if(drawing){
        stableObjects.push_back(object);
    }
}
void DrawingObjects::addTemporaryObject(DrawingObject object){
    if(drawing){
        temporaryObjects.push_back(object);
    }
}

void DrawingObjects::deleteTemporary(){
    temporaryObjects.clear();
}

DrawingObject* DrawingObjects::getStableObject(){
    indexStableObject++;
    if(indexStableObject>=stableObjects.size()){
        indexStableObject=0;
        return NULL;
    }else{
        return &stableObjects[indexStableObject-1];
    }
    
    
}
DrawingObject* DrawingObjects::getTemporaryObject(){
    indexTemporaryObject++;
    if(indexTemporaryObject>=temporaryObjects.size()){
        indexTemporaryObject=0;
        return NULL;
    }else{
        return &temporaryObjects[indexTemporaryObject-1];
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


VectorNDim DrawingObjects::rgb2hsv(VectorNDim rgb)
{
    //    VectorNDim K = VectorNDim({0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0});
    //    VectorNDim p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    //    VectorNDim q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));
    //
    //    float d = q.x - min(q.w, q.y);
    //    float e = 1.0e-10;
    //    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
    
    float h = 0.0;
    float s = 0.0;
    float v = 0.0;
    
    float r=rgb[0];
    float g=rgb[1];
    float b=rgb[2];
    
    float min = std::min( std::min(r, g), b );
    float max = std::max( std::max(r, g), b );
    v = max;               // v
    
    float delta = max - min;
    
    if( max != 0.0 )
        s = delta / max;       // s
    else {
        // r = g = b = 0       // s = 0, v is undefined
        s = 0.0;
        h = -1.0;
        VectorNDim vec;
        vec.values.clear();
        vec.values.push_back(h);
        vec.values.push_back(s);
        vec.values.push_back(v);
        return vec;
    }
    if( r == max )
        h = ( g - b ) / delta;     // between yellow & magenta
    else if( g == max )
        h = 2.0 + ( b - r ) / delta;   // between cyan & yellow
    else
        h = 4.0 + ( r - g ) / delta;   // between magenta & cyan
    
    h = h * 60.0;              // degrees
    
    if( h < 0.0 )
        h += 360.0;
    
    VectorNDim vec;
    vec.values.clear();
    vec.values.push_back(h);
    vec.values.push_back(s);
    vec.values.push_back(v);
    return vec;
}




VectorNDim DrawingObjects::HSVtoRGB(VectorNDim hsv)
{
    int i;
    float f, p, q, t;
    float r,g,b;
    float h=hsv[0]/255*360;
    float s=hsv[1]/255;
    float v=hsv[2]/255;
    
    if( s == 0 ) {
        // achromatic (grey)
        r=g=b= v*255;
        VectorNDim vec;
        vec.values.clear();
        vec.values.push_back(r);
        vec.values.push_back(g);
        vec.values.push_back(b);
        return vec;
    }
    h /= 60;			// sector 0 to 5
    i = floor( h );
    f = h - i;			// factorial part of h
    p = v * ( 1 - s );
    q = v * ( 1 - s * f );
    t = v * ( 1 - s * ( 1 - f ) );
    switch( i ) {
        case 0:
            r = v;
            g = t;
            b = p;
            break;
        case 1:
            r = q;
            g = v;
            b = p;
            break;
        case 2:
            r = p;
            g = v;
            b = t;
            break;
        case 3:
            r = p;
            g = q;
            b = v;
            break;
        case 4:
            r = t;
            g = p;
            b = v;
            break;
        default:		// case 5:
            r = v;
            g = p;
            b = q;
            break;
    }
    VectorNDim vec;
    vec.values.clear();
    vec.values.push_back(r*255);
    vec.values.push_back(g*255);
    vec.values.push_back(b*255);
    return vec;
}

VectorNDim DrawingObjects::getColor(double value,double min,double max){
    double h=((max-value)/(max-min)*2/3+1/3)*255;
    VectorNDim hsv;
    hsv.values.clear();
    hsv.values.push_back(h);
    hsv.values.push_back(255);
    hsv.values.push_back(255);
    VectorNDim rgb=HSVtoRGB(hsv);
    return rgb;
}



void DrawingObjects::setColor(VectorNDim color){
    colorNextObject=color;
}
void DrawingObjects::setColor(VectorNDim color,double alpha){
    VectorNDim vec;
    vec.values.clear();
    vec.values.push_back(color[1]);
    vec.values.push_back(color[2]);
    vec.values.push_back(color[3]);
    vec.values.push_back(alpha);
//    vec.values={color[1],color[2],color[3],alpha};
    colorNextObject=vec;
}
void DrawingObjects::setColor(double r,double g,double b){
    VectorNDim vec;
    vec.values.clear();
    vec.values.push_back(r);
    vec.values.push_back(g);
    vec.values.push_back(b);
    colorNextObject=vec;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawingObjects::zoomExtents(){
    double minX=INFINITY;
    double minY=INFINITY;
    double maxX=-INFINITY;
    double maxY=-INFINITY;
    for(long i=0;i<temporaryObjects.size();i++){
        if(temporaryObjects[i].type==DrawingObject::CIRCLE||temporaryObjects[i].type==DrawingObject::POINT){
            if(minX>temporaryObjects[i].center.x-temporaryObjects[i].radius){
                minX=temporaryObjects[i].center.x-temporaryObjects[i].radius;
            }
            if(minY>temporaryObjects[i].center.y-temporaryObjects[i].radius){
                minY=temporaryObjects[i].center.y-temporaryObjects[i].radius;
            }
            if(maxX<temporaryObjects[i].center.x+temporaryObjects[i].radius){
                maxX=temporaryObjects[i].center.x+temporaryObjects[i].radius;
            }
            if(maxY<temporaryObjects[i].center.y+temporaryObjects[i].radius){
                maxY=temporaryObjects[i].center.y+temporaryObjects[i].radius;
            }
        }
        if(temporaryObjects[i].type==DrawingObject::LINE){
            if(minX>temporaryObjects[i].start.x){
                minX=temporaryObjects[i].start.x;
            }
            if(minX>temporaryObjects[i].end.x){
                minX=temporaryObjects[i].end.x;
            }
            if(minY>temporaryObjects[i].start.y){
                minY=temporaryObjects[i].start.y;
            }
            if(minY>temporaryObjects[i].end.y){
                minY=temporaryObjects[i].end.y;
            }
            
            if(maxX<temporaryObjects[i].start.x){
                maxX=temporaryObjects[i].start.x;
            }
            if(maxX<temporaryObjects[i].end.x){
                maxX=temporaryObjects[i].end.x;
            }
            if(maxY<temporaryObjects[i].start.y){
                maxY=temporaryObjects[i].start.y;
            }
            if(maxY<temporaryObjects[i].end.y){
                maxY=temporaryObjects[i].end.y;
            }
            
        }
        if(temporaryObjects[i].type==DrawingObject::RECTANGLE_FILLED){
            if(maxX<temporaryObjects[i].corner2.x){
                maxX=temporaryObjects[i].corner2.x;
            }
           
            if(maxY<temporaryObjects[i].corner2.y){
                maxY=temporaryObjects[i].corner2.y;
            }
            if(minX>temporaryObjects[i].corner1.x){
                minX=temporaryObjects[i].corner1.x;
            }
            if(minY>temporaryObjects[i].corner1.y){
                minY=temporaryObjects[i].corner1.y;
            }
            
        }
        
    }
    double realWidth=maxX-minX;
    double realHeight=maxY-minY;
    scale=Functions::min(widthWindowX/realWidth,heightWindowY/realHeight);
    startX-=minX;
    startY-=minY;
    //    std::cout<<"scale in do "<<maxX<<" "<<minX<<" "<<widthWindowX<<" "<<heightWindowY<<" "<<realWidth<<" "<<realHeight<<" "<<scale<<" "<<startX<<" "<<startY<<'\n';
}

void DrawingObjects::copyViewParameters(DrawingObjects* otherWindow){
    scale=otherWindow->scale;
    startX=otherWindow->startX;
    startY=otherWindow->startY;
}
void DrawingObjects::copyAllParameters(DrawingObjects* otherWindow){
    scale=otherWindow->scale;
    startX=otherWindow->startX;
    startY=otherWindow->startY;
    widthWindowX=otherWindow->widthWindowX;
    heightWindowY=otherWindow->heightWindowY;
    startWindowX=otherWindow->startWindowX;
    startWindowY=otherWindow->startWindowY;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DrawingObjects::line(double x1,double y1,double x2,double y2,double width){
    DrawingObject line;
    line.type=DrawingObject::LINE;
    line.start=Point2d(x1,y1);
    line.end=Point2d(x2,y2);
    line.colorLine=colorNextObject;
    line.widthLine=width;
    addTemporaryObject(line);
}

void DrawingObjects::line(double x1,double y1,double x2,double y2){
    DrawingObject line;
    line.type=DrawingObject::LINE;
    line.start=Point2d(x1,y1);
    line.end=Point2d(x2,y2);
    line.colorLine=colorNextObject;
    line.widthLine=1;
    addTemporaryObject(line);
}

void DrawingObjects::text(std::string text,Point2d location,int size){
    DrawingObject textObject;
    textObject.type=DrawingObject::TEXT;
    textObject.start=location;
    textObject.text=text;
    textObject.colorLine=colorNextObject;
    textObject.size=size;
    addTemporaryObject(textObject);
}

void DrawingObjects::point(double x, double y,double radius){
    DrawingObject circle;
    circle.type=DrawingObject::POINT;
    circle.center=Point2d(x,y);
    circle.radius=radius;
    circle.colorFill=colorNextObject;
    addTemporaryObject(circle);
}
void DrawingObjects::filledCircle(double x, double y,double radius){
    DrawingObject circle;
    circle.type=DrawingObject::CIRCLE_FILLED;
    circle.center=Point2d(x,y);
    circle.radius=radius;
    circle.colorFill=colorNextObject;
    addTemporaryObject(circle);
}
void DrawingObjects::filledRectangle(double x1, double y1,double x2, double y2){
    DrawingObject rect;
    rect.type=DrawingObject::RECTANGLE_FILLED;
    rect.corner1=Point2d(x1,y1);
    rect.corner2=Point2d(x2,y2);
    rect.colorFill=colorNextObject;
    addTemporaryObject(rect);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawingObjects::drawPotentialField(PotentialField* potentialField,bool BW,bool logged,bool minIs0){
    for(long i=0;i<potentialField->clusters.size();i++){
        double min;
        if(minIs0){
            min=0;
        }else{
            min=potentialField->min;
        }
        double delta=0.0001;
        
        double normVal=Functions::normalize((potentialField->clusters[i].value),min,  (potentialField->max));
        if(logged){
            normVal=Functions::normalize(log(potentialField->clusters[i].value+delta),log(min+delta),  log(potentialField->max+delta));
        }
        
        if(BW){
            VectorNDim vec;
            vec.values.clear();
            vec.values.push_back(0);
            vec.values.push_back(0);
            vec.values.push_back(0);
            vec.values.push_back(normVal*255);
            setColor(vec);
        }else{
            setColor(getColor((potentialField->clusters[i].value), min,  (potentialField->max)));
            if(logged){
                setColor(getColor(log(potentialField->clusters[i].value+delta), log(min+delta),  log((potentialField->max+delta))));
            }
        }
        filledRectangle(potentialField->clusters[i].corner1.x, potentialField->clusters[i].corner1.y, potentialField->clusters[i].corner2.x, potentialField->clusters[i].corner2.y);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void DrawingObjects::drawGraph(Graph* graph){
//    
//    for(long i=0;i<graph->nodes.size();i++){
//        if(graph->nodes[i].mass>0){
//            DrawingObject circle;
//            circle.type=DrawingObject::CIRCLE_FILLED;
//            circle.center=graph->nodes[i].location;
//            circle.radius=pow(graph->nodes[i].mass/M_PI,.5);
//            VectorNDim vec;
//            vec.values.clear();
//            vec.values.push_back(0);
//            vec.values.push_back(0);
//            vec.values.push_back(0);
//            vec.values.push_back(100);
//            circle.colorFill=vec;
//            addTemporaryObject(circle);
//        }
//    }
//    std::vector<double> values;
//    for(long i=0;i<graph->transitions.size();i++){
//        values.push_back(graph->transitions[i].levelHierarchyRoad);
////        std::cout<<"levelHierarchicalRoad "<<values[i]<<'\n';
//    }
//    VectorNDim minMax=Functions::getMinMax(values);
//    for(long i=0;i<graph->transitions.size();i++){
//        DrawingObject line;
//        line.type=DrawingObject::LINE;
//        line.start=graph->transitions[i].a->location;
//        line.end=graph->transitions[i].b->location;
//        VectorNDim rgb=getColor(values[i], minMax[0], minMax[1]);
//
////                std::cout<<"levelHierarchicalRoad "<<values[i]<<" "<<minMax[0]<<" "<< minMax[1]<<" "<<rgb[0]<<" "<<rgb[1]<<" "<<rgb[2]<<'\n';
//        line.colorLine=rgb;
//        addTemporaryObject(line);
//    }
//    
//}
//
//void DrawingObjects::drawGraphEdges(Graph* graph,VectorNDim colorEdges){
//    
//
//    for(long i=0;i<graph->transitions.size();i++){
//        DrawingObject line;
//        line.type=DrawingObject::LINE;
//        line.start=graph->transitions[i].a->location;
//        line.end=graph->transitions[i].b->location;
//
//        line.colorLine=colorEdges;
//        addTemporaryObject(line);
//    }
//    
//}
//
//
//
//void DrawingObjects::drawGraph(Graph* graph,VectorNDim colorEdges){
//    
//        for(long i=0;i<graph->nodes.size();i++){
//            if(graph->nodes[i].mass>0){
//                DrawingObject circle;
//                circle.type=DrawingObject::CIRCLE_FILLED;
//                circle.center=graph->nodes[i].location;
//                circle.radius=pow(graph->nodes[i].mass/M_PI,.5)*50;
//                VectorNDim vec;
//                vec.values.clear();
//                vec.values.push_back(0);
//                vec.values.push_back(0);
//                vec.values.push_back(0);
//                vec.values.push_back(100);
//                circle.colorFill=vec;
//                addTemporaryObject(circle);
//            }
//        }
//
//    for(long i=0;i<graph->transitions.size();i++){
//        DrawingObject line;
//        line.type=DrawingObject::LINE;
//        line.start=graph->transitions[i].a->location;
//        line.end=graph->transitions[i].b->location;
//
//        line.colorLine=colorEdges;
//        addTemporaryObject(line);
//    }
//    
//}







void DrawingObjects::drawPlot(std::vector<Plot> &plots){
    double marginLeft=50;
    double marginRight=0;
    double marginTop=10;
    double marginBottom=0;
    for(long j=0;j<plots.size();j++){
        plots[j].location=Point2d(marginLeft,marginBottom);
        plots[j].width=widthWindowX-marginLeft-marginRight;
        plots[j].height=heightWindowY-marginTop-marginBottom;
    }
    double maxWidth=plots[0].width;
    double maxHeight=plots[0].height;
    
    
    
    if(plots[0].mode==Plot::DYNAMIC){
        
        
        double maxWidth=plots[0].width;
        double maxHeight=plots[0].height;
        double width=maxWidth/((double)plots[0].maxSize-1.0);
        double max=-INFINITY;
        double min=INFINITY;
        for(long i=0;i<plots.size();i++){
            if(max<plots[i].max){
                max=plots[i].max;
            }
            if(min>plots[i].min){
                min=plots[i].min;
            }
        }
        
        double height=maxHeight/(max-min);
        
        long i=0;
        double previous=0;
        
        
        
        for(long j=0;j<plots.size();j++){
            Plot plot=plots[j];
            double h=(((double)plots.size()-(double)j)/(double)(plots.size())*2/3+2/3)*255;
            VectorNDim hsv;
            hsv.values.clear();
            hsv.values.push_back(h);
            hsv.values.push_back(255);
            hsv.values.push_back(255);
            VectorNDim rgb=HSVtoRGB(hsv);
            setColor(rgb);
            double plotMax=-INFINITY;
            double plotMin=INFINITY;
            
            for (auto it=plot.setOfValuesDynamic.cbegin(); it != plot.setOfValuesDynamic.cend(); ++it)
            {
                
                
                point(i*width+plot.location.x,*it*height+plot.location.y-min*height,2);
                if(i>0){
                    line((i-1)*width+plot.location.x,previous*height+plot.location.y-min*height,i*width+plot.location.x,*it*height+plot.location.y-min*height,1);
                    
                }
                previous=*it;
                if(plotMax<previous){
                    plotMax=previous+previous/1000+.000000001;
                }
                if(plotMin>previous){
                    plotMin=previous-previous/1000-.000000001;
                }
                i++;
                
            }
            
            i=0;
            
            plots[j].max=plotMax;
            plots[j].min=plotMin;
            
        }
        setColor(0,0,0);
        if(max>0&&min<0){
            line(0*width+plots[0].location.x,0*height+plots[0].location.y-min*height,maxWidth+plots[0].location.x,0*height+plots[0].location.y-min*height);
            text("0",Point2d(plots[0].location.x-marginLeft,0*height+plots[0].location.y-min*height),8);
        }
        std::stringstream value;
        value<<min;
        line(0*width+plots[0].location.x,min*height+plots[0].location.y-min*height,maxWidth+plots[0].location.x,min*height+plots[0].location.y-min*height);
        text(value.str(),Point2d(plots[0].location.x-marginLeft,min*height+plots[0].location.y-min*height),8);
        line(0*width+plots[0].location.x,max*height+plots[0].location.y-min*height,maxWidth+plots[0].location.x,max*height+plots[0].location.y-min*height);
        value.str("");
        value<<max;
        text(value.str(),Point2d(plots[0].location.x-marginLeft,max*height+plots[0].location.y-min*height),8);
        line(0*width+plots[0].location.x,min*height+plots[0].location.y-min*height,0*width+plots[0].location.x,max*height+plots[0].location.y-min*height);
        line(plots[0].maxSize*width+plots[0].location.x,min*height+plots[0].location.y-min*height,plots[0].maxSize*width+plots[0].location.x,max*height+plots[0].location.y-min*height);
//        text(title,Point2d(maxWidth-10+plots[0].location.x,max*height+plots[0].location.y-min*height),10);
        
        
    }
    
    if(plots[0].mode==Plot::EUCLIDEAN){
        double maxX=-INFINITY;
        double minX=INFINITY;
        
        for(long i=0;i<plots.size();i++){
            if(maxX<plots[i].maxX){
                maxX=plots[i].maxX;
            }
            if(minX>plots[i].minX){
                minX=plots[i].minX;
            }
        }
        
        double maxY=-INFINITY;
        double minY=INFINITY;
        
        for(long i=0;i<plots.size();i++){
            if(maxY<plots[i].maxY){
                maxY=plots[i].maxY;
            }
            if(minY>plots[i].minY){
                minY=plots[i].minY;
            }
        }
        
        
        double width=maxWidth/(maxX-minX);
        
        
        double height=maxHeight/(maxY-minY);
        
        
        Point2d previous(0,0);
        
        
        for(long j=0;j<plots.size();j++){
            Plot plot=plots[j];
            double h=(((double)plots.size()-(double)j)/(double)(plots.size())*2/3+2/3)*255;
            VectorNDim hsv;
            hsv.values.clear();
            hsv.values.push_back(h);
            hsv.values.push_back(255);
            hsv.values.push_back(255);
            VectorNDim rgb=HSVtoRGB(hsv);
            setColor(rgb);
            double plotMaxX=-INFINITY;
            double plotMinX=INFINITY;
            double plotMaxY=-INFINITY;
            double plotMinY=INFINITY;
            long i=0;
            for (auto it=plot.setOfValuesEuclidean.cbegin(); it != plot.setOfValuesEuclidean.cend(); ++it)
            {
                
                if(i>0){
                    
                    point(it->x*width+plot.location.x-minX*width,it->y*height+plot.location.y-minY*height,2);
                }
                previous=*it;
                if(plotMaxX<previous.x){
                    plotMaxX=previous.x+previous.x/1000+.000000001;
                }
                if(plotMinX>previous.x){
                    plotMinX=previous.x-previous.x/1000-.000000001;
                }
                if(plotMaxY<previous.y){
                    plotMaxY=previous.y+previous.y/1000+.000000001;
                }
                if(plotMinY>previous.y){
                    plotMinY=previous.y-previous.y/1000-.000000001;
                }
                i++;
                
            }
            if(plots[j].regression){
                double x1=plots[j].minX;
                double y1=plots[j].interceptRegression+plots[j].slopeRegression*x1;
                
                double x2=plots[j].maxX;
                double y2=plots[j].interceptRegression+plots[j].slopeRegression*x2;
                
                line(x1*width+plot.location.x-minX*width,y1*height+plot.location.y-minY*height,x2*width+plot.location.x-minX*width,y2*height+plot.location.y-minY*height);
                if(plotMaxY<y2){
                    plotMaxY=y2+y2/1000+.000000001;
                }
                if(plotMinY>y1){
                    plotMinY=y1-y1/1000-.000000001;
                }
                std::stringstream textVar;
                textVar<<plots[j].slopeRegression;
                text(textVar.str(),Point2d(plots[0].location.x-minX*width+maxX*width,0*height+plots[0].location.y),8);
            }
            
            
            plots[j].maxX=plotMaxX;
            plots[j].minX=plotMinX;
            plots[j].maxY=plotMaxY;
            plots[j].minY=plotMinY;
            
            
        }
        setColor(0,0,0);
        if(maxY>0&&minY<0){
            line(0*width+plots[0].location.x,0*height+plots[0].location.y-minY*height,maxWidth+plots[0].location.x,0*height+plots[0].location.y-minY*height);

            text("0",Point2d(plots[0].location.x-marginLeft,0*height+plots[0].location.y-minY*height),8);
        }
        if(maxX>0&&minX<0){
            line(0*width+plots[0].location.x-minX*width,minY*height+plots[0].location.y-minY*height,0*width+plots[0].location.x-minX*width,maxY*height+plots[0].location.y-minY*height);
            text("0",Point2d(plots[0].location.x-minX*width,0*height+plots[0].location.y-minY*height),8);
        }
        std::stringstream value;
        value<<minY;
        line(0*width+plots[0].location.x,minY*height+plots[0].location.y-minY*height,maxWidth+plots[0].location.x,minY*height+plots[0].location.y-minY*height);
        text(value.str(),Point2d(plots[0].location.x-marginLeft,minY*height+plots[0].location.y-minY*height),8);
        line(0*width+plots[0].location.x,maxY*height+plots[0].location.y-minY*height,maxWidth+plots[0].location.x,maxY*height+plots[0].location.y-minY*height);
        value.str("");
        value<<maxY;
        text(value.str(),Point2d(plots[0].location.x-marginLeft,maxY*height+plots[0].location.y-minY*height),8);
        line(0*width+plots[0].location.x,minY*height+plots[0].location.y-minY*height,0*width+plots[0].location.x,maxY*height+plots[0].location.y-minY*height);
        line(maxX*width+plots[0].location.x,minY*height+plots[0].location.y-minY*height,maxX*width+plots[0].location.x,maxY*height+plots[0].location.y-minY*height);
//        text(title,Point2d(maxWidth-10+plots[0].location.x,maxY*height+plots[0].location.y-minY*height),10);
        
    }
    
}







