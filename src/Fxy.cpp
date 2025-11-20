#include "Fxy.h"

Fxy::Fxy(){
	initialised=false;
	derivated=false;
	integrated=false;
	definitionSubdivisionX=1000.0;
	// equalSpacing=false;
}

// std::tuple<std::vector<double>,std::vector<double> > Fxy::movingAverage(std::vector<double> x, std::vector<double> y,int type,int width,double numberBreaks){


// 	std::tuple<std::vector<double>,std::vector<double> > xy_=interpolateData(x,y,numberBreaks);
// 	std::vector<double> x_=std::get<0>(xy_);
// 	std::vector<double> y_=std::get<1>(xy_);

// 	std::vector<double> x_result;
// 	x_result.resize(x_.size(),0);
// 	std::vector<double> y_result;
// 	y_result.resize(y_.size(),0);
// 	if(type==F::UNIFORM_AV){

// 		for(long i=0;i<x_.size();i++){
// 			double accum=0;


// 			for(long j=-width;j<=width;j++){
// 				if(i+j<0){
// 					accum+=y[0];
// 				}else if(i+j>y.size()-1){
// 					accum+=y[y.size())-1];
// 				}else{
// 					accum+=y[i+j];
// 				}
// 			}
// 			accum/=width*2.0+1.0;
// 			x_result=x_[i];
// 			y_result=accum;

// 		}

// 	}else{
// 		std::cout<<"not yet implemented for this type"<<'\n';
// 	}
// 	std::tuple<std::vector<double>,std::vector<double> > xy_result=std::make_tuple(x_result,y_result);
// 	return xy_result;



// }
void Fxy::insertSetOfPoints(Fxy* f){
	double maxX=-INFINITY;
	 f->minX=INFINITY;
	double maxY=-INFINITY;
	 f->minY=INFINITY;
	for(long i=0;i<f->x.size();i++){
		if(f->x[i]>maxX){
			maxX=f->x[i];
		}
		if(f->x[i]<f->minX){
			f->minX=f->x[i];
		}
		if(f->y[i]>maxY){
			maxY=f->y[i];
		}
		if(f->y[i]<f->minY){
			f->minY=f->y[i];
		}
	}
	f->scaleX=maxX-f->minX;
	f->scaleY=maxY-f->minY;
	f->totalDistance=0;
	for(long i=0;i<f->x.size();i++){
		f->setOfPoints.push_back(Point2d((f->x[i]-f->minX)/f->scaleX,(f->y[i]-f->minY)/f->scaleY));
		if(i>0){
			f->totalDistance+=Functions::getDistance(f->setOfPoints[i],f->setOfPoints[i-1]);
		}
	}
	f->x.clear();
	f->y.clear();
    f->x.resize(f->setOfPoints.size(),0);
    f->y.resize(f->setOfPoints.size(),0);
	for(long i=0;i<f->setOfPoints.size();i++){
		f->x[i]=f->setOfPoints[i].x*f->scaleX+f->minX;
		f->y[i]=f->setOfPoints[i].y*f->scaleY+f->minY;
	}
//	Fxy::interpolateData(f);


}

void Fxy::interpolateData(Fxy* f,double numberBreaks){
	f->setOfPoints.clear();
	if(f->setOfPoints.size()==0){
		Fxy::insertSetOfPoints(f);
	}

	double breaksEach=f->totalDistance/numberBreaks;
	std::vector<Point2d> sp;
	sp.push_back(f->setOfPoints[0]);
	// double counter=0.0;
	// double distance=Functions::getDistance(f->setOfPoints[1],f->setOfPoints[0]);
	// 	double numberPoints=distance/breaksEach;
	// 	double dx=f->setOfPoints[1].x-f->setOfPoints[0].x;
	// 	double dy=f->setOfPoints[1].y-f->setOfPoints[0].y;
	// 	// if(numberPoints>=1){
 //        // if(distanceA<=breaksEach&&distanceB>breaksEach&&f->setOfPoints[i].x>=reference.x){
	// 	// if(numberPoints>1)
 //            for(double j=1.0;j<numberPoints;j+=1.0){
 //        	// while(breaksEach*counter<distanceB){
 //        		double dd=breaksEach*j;
 //                sp.push_back(Point2d(dx/distance*dd+f->setOfPoints[0].x,dy/distance*dd+f->setOfPoints[0].y));
 //                // counter++;
 //        	}
 //        // }
	double discountDistance=0;
	double distanceUpToThisPoint=0;
	for(long i=0;i<f->setOfPoints.size()-1;i++){
		double distance=Functions::getDistance(f->setOfPoints[i+1],f->setOfPoints[i]);
		double distanceLink=distance;
		// double numberPoints=distance/breaksEach;
		double dx=f->setOfPoints[i+1].x-f->setOfPoints[i].x;
		double dy=f->setOfPoints[i+1].y-f->setOfPoints[i].y;
		// double distanceA=Functions::getDistance(sp[sp.size()-1],f->setOfPoints[i]);
		// double distanceB=Functions::getDistance(sp[sp.size()-1],f->setOfPoints[i+1]);

		// Point2d reference=sp[sp.size()-1];
		// double initialDistanceA=0;
		double counter=1.0;
		double initialDiscountDistance=discountDistance;
     	while(distance>breaksEach-discountDistance){
     		double dd=Functions::max(0.0,breaksEach*counter-initialDiscountDistance);
     		sp.push_back(Point2d(dx/distanceLink*dd+f->setOfPoints[i].x,dy/distanceLink*dd+f->setOfPoints[i].y));
     		distance-=breaksEach-discountDistance;
     		discountDistance=0;
     	}
     	discountDistance=Functions::getDistance(sp[sp.size()-1],f->setOfPoints[i+1]);
        	// while(breaksEach*counter-initialDistanceA<distance){
        	// 	double dd=breaksEach*counter-initialDistanceA;
         //        sp.push_back(Point2d(dx/distance*dd+f->setOfPoints[i].x,dy/distance*dd+f->setOfPoints[i].y));
         //        counter++;
        	// }



	}
	sp.push_back(f->setOfPoints[f->setOfPoints.size()-1]);
	std::swap(f->setOfPoints,sp);
	f->x.clear();
	f->y.clear();
    f->x.resize(f->setOfPoints.size(),0);
    f->y.resize(f->setOfPoints.size(),0);
	for(long i=0;i<f->setOfPoints.size();i++){
		f->x[i]=f->setOfPoints[i].x*f->scaleX+f->minX;
		f->y[i]=f->setOfPoints[i].y*f->scaleY+f->minY;
	}
}



void Fxy::movingAverage(Fxy* f,int type,int width){

if(f->initialised){
	// Fxy::interpolateData(f,numberBreaks);
	// std::vector<double> x_=std::get<0>(xy_);
	// std::vector<double> y_=std::get<1>(xy_);

	std::vector<double> x_result;
	x_result.resize(f->x.size(),0);
	std::vector<double> y_result;
	y_result.resize(f->y.size(),0);
	if(type==Fxy::UNIFORM_AV){

		for(long i=0;i<f->x.size();i++){
			double accum=0;


			for(long j=-width;j<=width;j++){
				if(i+j<0){
					accum+=f->y[0];
				}else if(i+j>f->y.size()-1){
					accum+=f->y[f->y.size()-1];
				}else{
					accum+=f->y[i+j];
				}
			}
			accum/=width*2.0+1.0;
			x_result[i]=f->x[i];
			y_result[i]=accum;

		}

	}else{
		std::cout<<"not yet implemented for this type"<<'\n';
	}
	// std::tuple<std::vector<double>,std::vector<double> > xy_result=std::make_tuple(x_result,y_result);
	// return xy_result;
	std::swap(f->x,x_result);
	std::swap(f->y,y_result);
}else{
		std::cout<<"Warning: operation on empty function"<<'\n';
	}


}

// std::tuple<std::vector<double>,std::vector<double> > Fxy::interpolateData(std::vector<double> x, std::vector<double> y,double numberBreaks){
// 	std::vector<long> indexes=Functions::getIndexesOfOrderedValues(x,true);
// 	x=Functions::orderVectorUsingAnotherVectorWithPositions(x,indexes);
// 	y=Functions::orderVectorUsingAnotherVectorWithPositions(y,indexes);

// 	double maxX=-INFINITY;
// 	double minX=INFINITY;
// 	for(long i=0;i<x.size();i++){
// 		if(x[i]<minX){
// 			minX=x[i];
// 		}
// 		if(x[i]>maxX){
// 			maxX=x[i];
// 		}
// 	}
// 	double breaksXEach=(maxX-minX)/numberBreaks;
// 	std::vector<double> x_result;
// 	x_result.resize(numberBreaks+1,0);
// 	std::vector<double> y_result;
// 	y_result.resize(numberBreaks+1,0);

// 	long current=0;
// 	x_result[0]=x[0];
// 	x_result[numberBreaks]=x[x.size()-1];
// 	y_result[0]=y[0];
// 	y_result[numberBreaks]=y[x.size()-1];
// 	double dx=x[1]-x[0];
// 	double dy=y[1]-y[0];
// 	double counterBreaks=0;
// 	for(long i=1;i<numberBreaks;i++){
// 		while(x_result[0]+breaksXEach*i>x[current]+dx){


// 			current++;
// 			dx=x[current+1]-x[current];
// 			dy=y[current+1]-y[current];
// 		}
// 		double dx_b=x_result[0]+breaksXEach*i-x[current];
// 			x_result[i]=x_result[0]+breaksXEach*i;
// 			y_result[i]=y[current]+dy*dx_b/dx;
// 	}
// 	std::tuple<std::vector<double>,std::vector<double> > xy_result=std::make_tuple(x_result,y_result);
// 	return xy_result;

// }
void Fxy::interpolateDataInX(Fxy* f,double numberBreaks){
	if(f->initialised){
	double maxX=-INFINITY;
	double minX=INFINITY;
	for(long i=0;i<f->x.size();i++){
		if(f->x[i]<minX){
			minX=f->x[i];
		}
		if(f->x[i]>maxX){
			maxX=f->x[i];
		}
	}
	double breaksXEach=(maxX-minX)/numberBreaks;
	std::vector<double> x_result;
	x_result.resize(numberBreaks+1,0);
	std::vector<double> y_result;
	y_result.resize(numberBreaks+1,0);

	long current=0;
	x_result[0]=f->x[0];
	x_result[numberBreaks]=f->x[f->x.size()-1];
	y_result[0]=f->y[0];
	y_result[numberBreaks]=f->y[f->x.size()-1];
	double dx=f->x[1]-f->x[0];
	double dy=f->y[1]-f->y[0];
//	double counterBreaks=0;
	for(double i=1.0;i<numberBreaks;i+=1.0){
		while(f->x[0]+breaksXEach*i>f->x[current]+dx){


			current++;
			dx=f->x[current+1]-f->x[current];
			dy=f->y[current+1]-f->y[current];
		}
		dx=f->x[current+1]-f->x[current];
		dy=f->y[current+1]-f->y[current];
		double dx_b=f->x[0]+breaksXEach*i-f->x[current];
		x_result[i]=f->x[0]+breaksXEach*i;
		y_result[i]=f->y[current]+dy*dx_b/dx;
		if(current==1){
			// std::cout<<dy*dx_b/dx<< " "<<f->y[2]-f->y[1]<<" "<<dy<<" "<<dx<< " "<<dx_b<< '\n';
		}
	}
	// std::tuple<std::vector<double>,std::vector<double> > xy_result=std::make_tuple(x_result,y_result);
	// return xy_result;
	// f->equalSpacing=true;
	f->spacingX=breaksXEach;
        std::swap(f->x,x_result);
        std::swap(f->y,y_result);
	// std::cout<<"in interpolate, spacingX "<<f->spacingX<<'\n';
	}else{
		std::cout<<"Warning: operation on empty function"<<'\n';
	}

}




Fxy Fxy::interpolateDataInX(Fxy* f,std::vector<double>& newX){
	if(f->initialised){
	double maxX=-INFINITY;
	double minX=INFINITY;
	// for(long i=0;i<f->x.size();i++){
	// 	if(f->x[i]<minX){
	// 		minX=f->x[i];
	// 	}
	// 	if(f->x[i]>maxX){
	// 		maxX=f->x[i];
	// 	}
	// }
	Fxy fNew;
	// double breaksXEach=(maxX-minX)/numberBreaks;
	// std::vector<double> x_result;
	fNew.x.resize(newX.size(),0);
	std::vector<double> y_result;
	fNew.y.resize(newX.size(),0);
	std::vector<double> xSorted=Functions::orderValues(newX,true);
	long current=0;
	// x_result[0]=f->x[0];
	// x_result[numberBreaks]=f->x[f->x.size()-1];
	// if(xSorted[0]<=f->x[0]){
	// 	// xSorted[0]==f->x[0];
	// 	y_result[0]=f->y[0];
	// }
	// if(xSorted[xSorted.size()-1]>=f->x[f->x.size()-1]){
	// 		// y_result[numberBreaks]=f->y[f->x.size()-1];
	// 		y_result[xSorted.size()-1]=f->y[f->x.size()-1];
	// }
	double dx;
	double dy;
	// double dx=f->x[1]-f->x[0];
	// double dy=f->y[1]-f->y[0];
//	double counterBreaks=0;
	// for(double i=0;i<xSorted.size();i++){
	long i=0;
	while(i<xSorted.size()){
			if(xSorted[i]<=f->x[0]){
				fNew.x[i]=xSorted[i];
				fNew.y[i]=f->y[0];
				i++;

			// dx=f->x[current+1]-f->x[current];
			// dy=f->y[current+1]-f->y[current];
		}else{
			if (current<f->x.size()-1 && xSorted[i]>=f->x[current] && xSorted[i]<f->x[current+1]){

				dx=f->x[current+1]-f->x[current];
				dy=f->y[current+1]-f->y[current];
				double dx_b=xSorted[i]-f->x[current];
				// x_result[i]=f->x[0]+breaksXEach*i;
				fNew.x[i]=xSorted[i];
				fNew.y[i]=f->y[current]+dy*dx_b/dx;
				i++;
			}else if (current<f->x.size()-1){
				current++;
			}else{
				fNew.x[i]=xSorted[i];
				fNew.y[i]=f->y[f->y.size()-1];
				i++;
			}
		}
		// if(current==1){
		// 	// std::cout<<dy*dx_b/dx<< " "<<f->y[2]-f->y[1]<<" "<<dy<<" "<<dx<< " "<<dx_b<< '\n';
		// }
	}
	// std::tuple<std::vector<double>,std::vector<double> > xy_result=std::make_tuple(x_result,y_result);
	// return xy_result;
	// f->equalSpacing=true;
	fNew.spacingX=-1;
	return fNew;
        // std::swap(f->x,x_result);
        // std::swap(f->y,y_result);
	// std::cout<<"in interpolate, spacingX "<<f->spacingX<<'\n';
	}else{
		std::cout<<"Warning: operation on empty function"<<'\n';
		return *f;
	}

}


void Fxy::interpolateDataInY(Fxy* f,double numberBreaks){
	if(f->initialised){
	double maxY=-INFINITY;
	double minY=INFINITY;
	for(long i=0;i<f->y.size();i++){
		if(f->y[i]<minY){
			minY=f->y[i];
		}
		if(f->y[i]>maxY){
			maxY=f->y[i];
		}
	}
	double breaksYEach=(maxY-minY)/numberBreaks;
	std::vector<double> x_result;
	x_result.resize(numberBreaks+1,0);
	std::vector<double> y_result;
	y_result.resize(numberBreaks+1,0);

	long current=0;
	x_result[0]=f->x[0];
	x_result[numberBreaks]=f->x[f->x.size()-1];
	y_result[0]=f->y[0];
	y_result[numberBreaks]=f->y[f->x.size()-1];
	double dx=f->x[1]-f->x[0];
	double dy=f->y[1]-f->y[0];
//	double counterBreaks=0;
	for(double i=1.0;i<numberBreaks;i+=1.0){
		while(f->y[0]+breaksYEach*i>f->y[current]+dy){


			current++;
			dx=f->x[current+1]-f->x[current];
			dy=f->y[current+1]-f->y[current];
		}
		dx=f->x[current+1]-f->x[current];
		dy=f->y[current+1]-f->y[current];
		double dy_b=f->y[0]+breaksYEach*i-f->y[current];
		x_result[i]=f->x[current]+dx*dy_b/dy;
		y_result[i]=f->y[0]+breaksYEach*i;
		// y_result[i]=f->y[current]+dy*dx_b/dx;
		if(current==1){
			// std::cout<<dy*dx_b/dx<< " "<<f->y[2]-f->y[1]<<" "<<dy<<" "<<dx<< " "<<dx_b<< '\n';
		}
	}
	// std::tuple<std::vector<double>,std::vector<double> > xy_result=std::make_tuple(x_result,y_result);
	// return xy_result;
	// f->equalSpacing=true;
	f->spacingY=breaksYEach;
        std::swap(f->x,x_result);
        std::swap(f->y,y_result);
	// std::cout<<"in interpolate, spacingX "<<f->spacingX<<'\n';
	}else{
		std::cout<<"Warning: operation on empty function"<<'\n';
	}

}

// std::tuple<std::vector<double>,std::vector<double> > Fxy::getNumericApproximationToFunctionFromData(std::vector<double> data){
// 	std::vector<double> x=Functions::orderValues(data,true);
// 	std::vector<double> y;
// 	y.resize(x.size(),0);
// 	for(double i=0;i<x.size();i++){
// 		y[i]=i/(double)(x.size()-1);

// 	}
// 	std::tuple<std::vector<double>,std::vector<double> > xy_result=movingAverage(x,y,F:UNIFORM_AV,4,1000);
// 	std::tuple<std::vector<double>,std::vector<double> > xy_result_=interpolateData(std::get<0>(xy_result),std::get<1>(xy_result),1000);
// 	return xy_result_;

// }
Fxy Fxy::createFunction(std::vector<double>& x, std::vector<double>& y){
	Fxy f;
	// Fxy::insertData(&f,x,y);
	for(long i=0;i<x.size();i++){
		f.x.push_back(x[i]);
		f.y.push_back(y[i]);
	}
	Fxy::insertSetOfPoints(&f);
 	f.initialised=true;
 	// Fxy::interpolateData(&f,5000);
	// Fxy::approximate(&f);
	return f;
}
void Fxy::insertData(Fxy* f,std::vector<double>& x, std::vector<double>& y){
	// std::vector<long> indexes=Functions::getIndexesOfOrderedValues(x,true);
	// f->x=Functions::orderVectorUsingAnotherVectorWithPositions(x,indexes);
	// f->y=Functions::orderVectorUsingAnotherVectorWithPositions(y,indexes);
	f->x.clear();
	f->y.clear();
	f->x.reserve(x.size());
	f->y.reserve(y.size());
	for(long i=0;i<x.size();i++){
		f->x.push_back(x[i]);
		f->y.push_back(y[i]);
	}

	f->setOfPoints.clear();

	// std::tuple<std::vector<double>,std::vector<double> > xy_result=movingAverage(x,y,F:UNIFORM_AV,4,1000);
	// std::tuple<std::vector<double>,std::vector<double> > xy_result_=interpolateData(std::get<0>(xy_result),std::get<1>(xy_result),1000);
	// return xy_result_;
	f->initialised=true;
	// Fxy::interpolateData(f,5000);
	// Fxy::approximate(f);

}
void Fxy::approximate(Fxy* f){
	// std::vector<long> indexes=Functions::getIndexesOfOrderedValues(x,true);
	// std::vector<double> x_=Functions::orderVectorUsingAnotherVectorWithPositions(x,indexes);
	// std::vector<double> y_=Functions::orderVectorUsingAnotherVectorWithPositions(y,indexes);
	if(f->initialised){
        // double numSubdivisions=Functions::max(10,Functions::min(2000,f->x.size()/1.75));
        // std::cout<<"numSubdivisions "<<numSubdivisions<<'\n';
        // double softening=pow(numSubdivisions,.45);
        // std::cout<<"softenign "<<softening<<'\n';
       Fxy::movingAverage(f,Fxy::UNIFORM_AV,200);
       // Fxy::movingAverage(f,Fxy::UNIFORM_AV,50,2000);

       // Fxy::interpolateDataInX(f,2000);
		// Fxy::interpolateData(f,2000);
	}else{
		std::cout<<"Warning: operation on empty function"<<'\n';
	}
	// return xy_result_;

}
// std::tuple<std::vector<double>,std::vector<double> > Fxy::derivate(std::vector<double> x, std::vector<double> y,double definition){
// 	std::vector<double> d;
// 	d.resize(x.size(),0);
// 	for(long i=0;i<x.size();i++){
// 		if(i==0){
// 			// double minLeft=Functions::min(x[i]-x[i-1],definition);
// 			double min=Functions::min(x[i+1]-x[i],definition);
// 			// double min=Functions::min(minLeft,minRight);
// 			definition=min;
// 			// double dx=x[i]-x[i-1];
// 			// double dy=y[i]-y[i-1];
// 			// double dx_=dx-definition;
// 			// double dy_l=dy*dx_/dx;
// 			// double y_l=y[i-1]+dy_l;
// 			dx=x[i+1]-x[i];
// 			dy=y[i+1]-y[i];
// 			dx_=definition;
// 			double dy_r=dy*dx/dx_;
// 			double y_r=y[i]+dy_r;

// 			dx=definition;
// 			dy=y_r-y[i];
// 			d[i]=dy/dx;
// 		}else if(i==x.size()-1){
// 			double min=Functions::min(x[i]-x[i-1],definition);
// 			// double minRight=Functions::min(x[i+1]-x[i],definition);
// 			// double min=Functions::min(minLeft,minRight);
// 			definition=min;
// 			double dx=x[i]-x[i-1];
// 			double dy=y[i]-y[i-1];
// 			double dx_=dx-definition;
// 			double dy_l=dy*dx_/dx;
// 			double y_l=y[i-1]+dy_l;
// 			// dx=x[i+1]-x[i];
// 			// dy=y[i+1]-y[i];
// 			// dx_=definition;
// 			// double dy_r=dy*dx/dx_;
// 			// double y_r=y[i]+dy_r;

// 			dx=definition;
// 			dy=y[i]-y[l];
// 			d[i]=dy/dx;
// 		}else{
// 			double minLeft=Functions::min(x[i]-x[i-1],definition);
// 			double minRight=Functions::min(x[i+1]-x[i],definition);
// 			double min=Functions::min(minLeft,minRight);
// 			definition=min;
// 			double dx=x[i]-x[i-1];
// 			double dy=y[i]-y[i-1];
// 			double dx_=dx-definition;
// 			double dy_l=dy*dx_/dx;
// 			double y_l=y[i-1]+dy_l;
// 			dx=x[i+1]-x[i];
// 			dy=y[i+1]-y[i];
// 			dx_=definition;
// 			double dy_r=dy*dx/dx_;
// 			double y_r=y[i]+dy_r;

// 			dx=definition*2.0;
// 			dy=y_r-y_l;
// 			d[i]=dy/dx;



// 		}

// 	}



// }

Fxy Fxy::getDerivative(Fxy* f){
	Fxy d;
	if(f->initialised){
	if(!f->derivated){

		Fxy::derivate(f);
	}

	d.x=f->x;
	d.y=f->derivative;
	d.initialised=true;

}else{
		std::cout<<"Warning: operation on empty function"<<'\n';
	}
	return d;

}

void Fxy::derivate(Fxy* f){
	Fxy::interpolateDataInX(f,f->definitionSubdivisionX);
    // Fxy::movingAverage(f,Fxy::UNIFORM_AV,10,5000);
   // Fxy::interpolateData(f,30);
	 // f->spacingX=f->x[1]-f->x[0];
    double definition=f->spacingX/20;
	if(f->initialised){
	f->derivated=true;
	std::vector<double> d;
	f->derivative.resize(f->x.size(),0);
	for(long i=0;i<f->x.size();i++){
		if(i==0){
			// double minLeft=Functions::min(x[i]-x[i-1],definition);
			double min=Functions::min(f->x[i+1]-f->x[i],definition);
			// double min=Functions::min(minLeft,minRight);
			definition=min;
			// double dx=x[i]-x[i-1];
			// double dy=y[i]-y[i-1];
			// double dx_=dx-definition;
			// double dy_l=dy*dx_/dx;
			// double y_l=y[i-1]+dy_l;
			double dx=f->x[i+1]-f->x[i];
			double dy=f->y[i+1]-f->y[i];
			double dx_=definition;
			double dy_r=dy*dx_/dx;
			double y_r=f->y[i]+dy_r;

			dx=definition;
			dy=y_r-f->y[i];
			f->derivative[i]=dy/dx;
		}else if(i==f->x.size()-1){
			double min=Functions::min(f->x[i]-f->x[i-1],definition);
			// double minRight=Functions::min(x[i+1]-x[i],definition);
			// double min=Functions::min(minLeft,minRight);
			definition=min;
			double dx=f->x[i]-f->x[i-1];
			double dy=f->y[i]-f->y[i-1];
			double dx_=dx-definition;
			double dy_l=dy*dx_/dx;
			double y_l=f->y[i-1]+dy_l;
			// dx=x[i+1]-x[i];
			// dy=y[i+1]-y[i];
			// dx_=definition;
			// double dy_r=dy*dx/dx_;
			// double y_r=y[i]+dy_r;

			dx=definition;
			dy=f->y[i]-y_l;
			f->derivative[i]=dy/dx;
		}else{
			double minLeft=Functions::min(f->x[i]-f->x[i-1],definition);
			double minRight=Functions::min(f->x[i+1]-f->x[i],definition);
			double min=Functions::min(minLeft,minRight);
			definition=min;
			double dx=f->x[i]-f->x[i-1];
			double dy=f->y[i]-f->y[i-1];
			double dx_=dx-definition;
			double dy_l=dy*dx_/dx;
			double y_l=f->y[i-1]+dy_l;
			dx=f->x[i+1]-f->x[i];
			dy=f->y[i+1]-f->y[i];
			dx_=definition;
			double dy_r=dy*dx_/dx;
			double y_r=f->y[i]+dy_r;

			dx=definition*2.0;
			dy=y_r-y_l;
			f->derivative[i]=dy/dx;
			// std::cout<<"Derivative "<<dy/dx<<" "<<'\n';



		}

	}
	}else{
		std::cout<<"Warning: operation on empty function"<<'\n';
	}


}


void Fxy::integrate(Fxy* f){
	Fxy::interpolateDataInX(f,f->definitionSubdivisionX);
	if(f->initialised){
		f->integral.clear();
		f->integral.resize(f->x.size(),0);
		for(long i=0;i<f->x.size();i++){
			f->integral[i]=f->y[i]*f->spacingX;
			if(i>0){
				f->integral[i]+=f->integral[i-1];
			}
		}

	}else{
		std::cout<<"Warning: operation on empty function"<<'\n';
	}
}

double Fxy::integrate(Fxy* f,double from,double to){
	Fxy::interpolateDataInX(f,f->definitionSubdivisionX);
	if(f->initialised){
		// f->integral.resize(x.size(),0);
		double result=0;
		// std::cout<<"in integrage, spacingX "<<f->spacingX<<'\n';
		for(long i=0;i<f->x.size();i++){
			if(f->x[i]>=from&&f->x[i]<=to){
				result+=f->y[i]*f->spacingX;
				// std::cout<<"integrating "<<f->y[i]<<" "<<f->spacingX<<" "<<result<<'\n';

			}else if(f->x[i]>to){
				break;
			}
		}
		return result;

	}else{
		std::cout<<"Warning: operation on empty function"<<'\n';
		return 0;
	}
}




Fxy Fxy::getIntegral(Fxy* f){
	Fxy i;
	if(f->initialised){
	// if(!f->derivated){

		Fxy::integrate(f);
	// }

	i.x=f->x;
	i.y=f->integral;
	i.initialised=true;

}else{
		std::cout<<"Warning: operation on empty function"<<'\n';
	}
	return i;
}


// void Fxy krige(Fxy *f){
// 	 MatrixXd m(2,2);
//   m(0,0) = 3;
//   m(1,0) = 2.5;
//   m(0,1) = -1;
//   m(1,1) = m(1,0) + m(0,1);
//   std::cout << "Here is the matrix m:\n" << m << std::endl;
//   VectorXd v(2);
//   v(0) = 4;
//   v(1) = v(0) - 1;
//   std::cout << "Here is the vector v:\n" << v << std::endl;
// 	atrix3f A;
//    Vector3f b;
//    A << 1,2,3,  4,5,6,  7,8,10;
//    b << 3, 3, 4;
//    cout << "Here is the matrix A:\n" << A << endl;
//    cout << "Here is the vector b:\n" << b << endl;
//    Vector3f x = A.colPivHouseholderQr().solve(b);
//    cout << "The solution is:\n" << x << endl;

// }
