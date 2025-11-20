#include "InterfaceFlows.h"

InterfaceFlows::InterfaceFlows(){
  subdivisionsDistance=1;
  this->distancesTrips.push_back(INFINITY);
}

// void InterfaceFlows::setNumberSubdivisions(int numbersubdivisionsDistance){
//   // std::cout<<"setNumberSubdivisions"<<'\n';
//   this->subdivisionsDistance=numbersubdivisionsDistance;
//   // std::cout<<"setNumberSubdivisions-end"<<'\n';
// }

// void InterfaceFlows::setDistances(double maxDistance){
//   // std::cout<<"setDistances"<<'\n';
//   this->maxDistance=maxDistance;
//   if(this->subdivisionsDistance>1){
//     for(double i=1;i<=this->subdivisionsDistance;i++){
//       this->distancesTrips.push_back(exp(log(maxDistance)*(i/(this->subdivisionsDistance))));
//     }
//   }
//   // std::cout<<"setDistances-end"<<'\n';
// }

void InterfaceFlows::setDistances(std::vector<double> distances){
  // std::cout<<"setDistances"<<'\n';

  this->distancesTrips.clear();
  for(double i=0;i<distances.size();i++){
    this->distancesTrips.push_back(distances[i]);
  }

  this->distancesTrips.push_back(INFINITY);
  this->subdivisionsDistance=this->distancesTrips.size();
  // std::cout<<"setDistances-end"<<'\n';
}

void InterfaceFlows::initFlows(long numberLinks){
  // std::cout<<"initFlows"<<'\n';
  this->flows.reserve(this->subdivisionsDistance);

    for(double i=0;i<this->subdivisionsDistance;i++){
      std::vector<double> flows_temp;
      flows_temp.reserve(numberLinks);
      for(double i=0;i<numberLinks;i++){
        flows_temp.push_back(0);
      }
      this->flows.push_back(flows_temp);
    }
    // std::cout<<"initFlows-end"<<'\n';

}
void InterfaceFlows::initValuesToPass(long numberLinks){
  // std::cout<<"initValuesToPass"<<'\n';
  this->valuesToPass.reserve(this->subdivisionsDistance);

    for(double i=0;i<this->subdivisionsDistance;i++){
      valuesToPass.push_back(std::unordered_map<long,double> ());
    }
  // std::cout<<"initValuesToPass-end"<<'\n';
}

void InterfaceFlows::resetValuesToPass(){
  // std::cout<<"resetValuesToPass"<<'\n';
  // this->valuesToPass.reserve(this->subdivisionsDistance);

    for(double i=0;i<this->subdivisionsDistance;i++){
      valuesToPass[i].clear();
    }
    // std::cout<<"resetValuesToPass-end"<<'\n';
}

void InterfaceFlows::setValuesToPass( long idNode,double distance, double value){
  // std::cout<<"setValuesToPass"<<'\n';
  if ((this->subdivisionsDistance)>1){

      // long i=floor(log(distance)/log(this->maxDistance)*(this->subdivisionsDistance-1));
      long i=this->getIndexOfDistance(distance);
      // std::cout<<"i in setValuesToPass : "<<i<<'\n';
      this->valuesToPass[i][idNode]=value;

  }else{
    this->valuesToPass[0][idNode]+=value;
  }
  // std::cout<<"setValuesToPass-end"<<'\n';
}
void InterfaceFlows::passValuesToParent(long idNode,long idParent){
  if (idParent!=-1){
    // std::cout<<"passValuesToParent "<<idNode<<" idparent "<<idParent<<'\n';
    for(long i=0;i<this->subdivisionsDistance;i++){
      this->valuesToPass[i][idParent]+=this->valuesToPass[i][idNode];
      // this->valuesToPass[i].erase(idNode);
    }
    // std::cout<<"passValuesToParent-end"<<'\n';
  }

}
void InterfaceFlows::accumulateFlow(long idLink,long idNode){
  // std::cout<<"accumulateFlow"<<'\n';
  if ((this->subdivisionsDistance)>1){
    // long i=floor(log(distance)/log(maxDistance)*(this->subdivisionsDistance));
    for(long i=0;i<this->subdivisionsDistance;i++){
      this->flows[i][idLink]+=valuesToPass[i][idNode];
    }
  }else{
    this->flows[0][idLink]+=valuesToPass[0][idNode];
  }
  // std::cout<<"accumulateFlow-end"<<'\n';

}

std::vector<double> InterfaceFlows::getFlows(long indexDistance){
  // std::cout<<"getFlows"<<'\n';
  return this->flows[indexDistance];
  // std::cout<<"getFlows-end"<<'\n';
}

long InterfaceFlows::getIndexOfDistance(double distance){
  long index=this->distancesTrips.size()-1;
  for (long i=this->distancesTrips.size()-1;i>=0;i--){
    if (distance<=this->distancesTrips[i]){
      index=i;
    }
  }
  // std::cout<<distance<<" "<<index<<'\n';
  return index;
}
