#include "Entropy.h"

double Entropy::calculateEntropyAreas(std::vector<double>& data){
	Distribution dis=Distribution::createDistribution(data);
    double entropy=0;
    if(dis.initialised){
        for(long i=0;i<dis.f.x.size();i++){
            dis.f.y[i]*=dis.f.x[i];
    //        std::cout<<dis.f.y[i]<<'\n';
        }
        double normFactor=Fxy::integrate(&dis.f,dis.f.x[0],dis.f.x[dis.f.x.size()-1]);

        for(long i=0;i<dis.f.x.size();i++){
            double p=dis.f.y[i]/normFactor;
            if(p>0){
                entropy+=-p*log(p)*dis.f.spacingX;
            }
        }
    }else{
        std::cout<<"Warning: distribution was not initialised"<<'\n';
    }
    return entropy;


}


std::tuple<double,double> Entropy::calculateDiscreteEntropyAreas(std::vector<double>& x){
	double maxSample=0;
	double minSample=INFINITY;
	for(long i=0;i<x.size();i++){
		if(maxSample<x[i]){
			maxSample=x[i];
		}
		if(minSample>x[i]){
			minSample=x[i];
		}
	}
	double N=(double)(x.size());

	// widthBin=500;
	double ee = pow((8.0 + 324.0*N + 12.0*sqrt(36.0*N + 729.0*N*N)),1.0/3.0);
    double bins = round(ee/6.0 + 2.0/(3.0*ee) + 1.0/3.0);
		double widthBin=(maxSample-minSample)/bins;
	// std::cout<<widthBin<<'\n';
    std::unordered_map<double,double> totalPerSize;
    double total;
    for(long i=0;i<x.size();i++){
        total+=x[i];
        totalPerSize[std::floor(x[i]/widthBin)]+=x[i];
    }
    double h=0;
    double n=0;
    for(auto it:totalPerSize){
        double p=it.second/total;
        if(p>0){
            h+=p*log(p);
            n++;
        }
    }
    h=-h;
		// std::cout<<n<<" doub "<<totalPerSize.size()<<'\n';
    std::tuple<double,double> pair=std::make_tuple(h, n);

    return pair;


}

std::tuple<double,double> Entropy::calculateDiscreteEntropyAreas(std::vector<long>& x){
	double maxSample=0;
	double minSample=INFINITY;
	for(long i=0;i<x.size();i++){
		if(maxSample<x[i]){
			maxSample=x[i];
		}
		if(minSample>x[i]){
			minSample=x[i];
		}
	}
	double N=(double)(x.size());

	// widthBin=500;
	double ee = pow((8.0 + 324.0*N + 12.0*sqrt(36.0*N + 729.0*N*N)),1.0/3.0);
    double bins = round(ee/6.0 + 2.0/(3.0*ee) + 1.0/3.0);
		double widthBin=(maxSample-minSample)/bins;
	// std::cout<<widthBin<<'\n';
	std::cout<<"";
    std::unordered_map<double,double> totalPerSize;
    double total;
    for(long i=0;i<x.size();i++){
        total+=(double)(x[i]);
        totalPerSize[std::floor((double)(x[i])/widthBin)]+=(double)(x[i]);
    }
    double h=0;
    double n=0;
    for(auto it:totalPerSize){
        double p=it.second/total;
        if(p>0){
            h+=p*log(p);
            n++;
        }
    }
    h=-h;
		std::cout<<"";
		// std::cout<<n<<" long "<<totalPerSize.size()<<'\n';
    std::tuple<double,double> pair=std::make_tuple(h, n);

    return pair;


}

double Entropy::calculateEntropy(std::vector<double>& data){
	Distribution dis=Distribution::createDistribution(data);
    double entropy=0;
	if(dis.initialised){
        std::cout<<"size x in calculate entropy "<<dis.f.x.size()<<'\n';
        double normFactor=Fxy::integrate(&dis.f,dis.f.x[0],dis.f.x[dis.f.x.size()-1]);
        // std::cout<<"in entropy f size "<<dis.f.x.size()<<'\n';
        // std::cout<<"normfactor "<<normFactor<<'\n';

    //     for(long i=0;i<dis.f.x.size();i++){
    // //        dis.f.y[i]*=dis.f.x[i];
    //         std::cout<<dis.f.y[i]<<'\n';
    //     }

        // std::cout<<dis.f.x.size()<<" "<<dis.f.y.size()<<" "<<dis.f.spacingX<<'\n';
        for(long i=0;i<dis.f.x.size();i++){
        	// std::cout<<i<<" "<<dis.f.x[i]<<" "<<dis.f.y[i]<<'\n';
            double p=dis.f.y[i]/normFactor;
            // std::cout<<p<<'\n';
            if(p>0){
                entropy+=-p*log(p)*dis.f.spacingX;
            }
        }
    }else{
        std::cout<<"Warning: distribution was not initialised"<<'\n';
    }
    return entropy;
}


std::tuple<double,double> Entropy::createDelanuayAndCalculateItsEntropies(double totalArea,long numberAreas){
    double side=sqrt(totalArea);
    std::vector<long> ids;
    std::vector<double> xs;
    std::vector<double> ys;
    ids.reserve(numberAreas);
    xs.reserve(numberAreas);
    ys.reserve(numberAreas);
    for(long i=0;i<numberAreas;i++){
        ids.push_back(i);
        xs.push_back(Functions::runiform(0, side));
        ys.push_back(Functions::runiform(0, side));
    }

    std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > delaunay=Geometry::delaunay(ids,xs,ys);
    std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coords=std::make_tuple(ids,xs,ys);
    DualExtendedGraph deg;
    DualExtendedGraph::addPrimal(&deg,delaunay,coords,false);
    std::vector<double> areas;
    for(long j=1;j<deg.getDualGraph()->nodes.size();j++){
        areas.push_back(deg.getDualGraph()->nodes[j]->mass);
    }
    double H_a=Entropy::calculateEntropyAreas(areas);
    double H_=Entropy::calculateEntropy(areas);
    std::tuple<double,double> Hs=std::make_tuple(H_,H_a);
    return Hs;



}
