#include "Distribution.h"

Distribution::Distribution(){
    initialised=false;
}
 double Distribution::getMode(Distribution* dis){
   double max=-INFINITY;
   double value;
  for(long i=0;i<dis->f.x.size();i++){
    if(dis->f.y[i]>max){
      max=dis->f.y[i];
      value=dis->f.x[i];
    }
  }
  return value;
}

Distribution Distribution::createCDFDistributionFromData(Fxy f){
  Distribution dis;
  dis.f.x.push_back(f.x[0]);
  dis.f.y.push_back(f.y[0]);
  long current=0;
  for (long i=1;i<f.x.size();i++){
    if(f.x[i]==f.x[current]){
      dis.f.y[current]+=f.y[i];
    }else{
      current++;
      dis.f.x.push_back(f.x[i]);
      dis.f.y.push_back(f.y[i]+dis.f.y[current-1]);
    }
  }
  for (long i=1;i<dis.f.x.size();i++){
    dis.f.y[i]/=dis.f.y[dis.f.y.size()-1];
  }
  dis.f.derivated=false;
  dis.f.integrated=false;
  dis.f.initialised=true;
  return dis;
}

Fxy Distribution::getP(std::vector<double>& x){
  return Fxy::interpolateDataInX(&this->f,x);
}

Fxy Distribution::getP(double x){
  std::vector<double> xs;
  xs.push_back(x);
  return Fxy::interpolateDataInX(&this->f,xs);
}

Distribution Distribution::createDistribution(std::vector<double>& data){
	Distribution dis;
    if(data.size()>3){
        dis.initialised=true;
        Fxy f;
        f.initialised=true;
        f.x=Functions::orderValues(data,true);
        // std::vector<double> y;
        f.y.resize(f.x.size(),0);
        for(double i=0.0;i<f.x.size();i+=1.0){
            // std::cout<<"f("<<i<<")="<<f.x[i]<<'\n';
            f.y[i]=i/(double)(f.x.size());

        }
        Fxy::insertSetOfPoints(&f);
        double numSubdivisions=Functions::max(10.0,Functions::min((double)(2000.0),(double)(f.x.size()/20.0)));
        // std::cout<<"numSubdivisions "<<numSubdivisions<<'\n';
        // double softening=pow(numSubdivisions,.45);
        // numSubdivisions=20;
        // softening=1;
        // std::cout<<"numSubdivisions "<<numSubdivisions<<" softening "<<softening<<'\n';
        Fxy::interpolateData(&f,numSubdivisions);
        // Fxy::movingAverage(&f,Fxy::UNIFORM_AV,softening);

        Fxy::derivate(&f);

        // Fxy f2;
        // Fxy::insertData(&f2,f.x,f.derivative);
        // Fxy::interpolateData(&f2,2000);
        // Fxy::movingAverage(&f2,Fxy::UNIFORM_AV,50);
        // Fxy::interpolateData(&f2,2000);
        // Fxy::movingAverage(&f2,Fxy::UNIFORM_AV,300);
        // Fxy::interpolateData(&f2,2000);
        // Fxy::movingAverage(&f2,Fxy::UNIFORM_AV,300);
        // Fxy::interpolateData(&f2,2000);
        // Fxy::movingAverage(&f2,Fxy::UNIFORM_AV,300);
        // Fxy::integrate(&f2);
        // std::swap(f2.x,f.x);
        // std::swap(f2.integral,f.y);

        // f.y=Functions::normalize(f2.integral);

        // Fxy::derivate(&f);

        // std::cout<<"in create distribution f size "<<f.x.size()<<'\n';
        std::swap(dis.f.x,f.x);
        // std::cout<<"in create distribution f size after swap"<<dis.f.x.size()<<'\n';
        std::swap(dis.f.y,f.derivative);
        // Fxy::movingAverage(&dis.f,Fxy::UNIFORM_AV,20,2000);
        // std::swap(dis.f.y,f.y);
        dis.f.spacingX=f.spacingX;
        dis.f.derivated=false;
        dis.f.integrated=false;
        dis.f.initialised=true;
        // std::tuple<std::vector<double>,std::vector<double> > xy_result=movingAverage(x,y,F:UNIFORM_AV,4,1000);
        // std::tuple<std::vector<double>,std::vector<double> > xy_result_=interpolateData(std::get<0>(xy_result),std::get<1>(xy_result),1000);
        // return xy_result_;
    }else{
        std::cout<<"Warning: data was too small to generate a distribution"<<'\n';
    }
    return dis;

}


double Distribution::getMoment(Distribution* dis,double n){
    double moment=0;
    if(dis->initialised){
        double normFactor=Fxy::integrate(&dis->f,dis->f.x[0],dis->f.x[dis->f.x.size()-1]);
        // std::cout<<"in entropy f size "<<dis.f.x.size()<<'\n';
        // std::cout<<"normfactor "<<normFactor<<'\n';

    //     for(long i=0;i<dis.f.x.size();i++){
    // //        dis.f.y[i]*=dis.f.x[i];
    //         std::cout<<dis.f.y[i]<<'\n';
    //     }
        for(long i=0;i<dis->f.x.size();i++){
            double p=dis->f.y[i]/normFactor;
            if(p>0){
                moment+=p*pow(dis->f.x[i],n)*dis->f.spacingX;
            }
        }
    }else{
        std::cout<<"Warning: distribution was not initialised"<<'\n';

    }
    return moment;

}
