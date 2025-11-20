#include "OSM.h"
struct RoadHandler : public osmium::handler::Handler {

    // double length = 0;
    std::vector<std::deque<Point2d> > waysPoints;
    std::vector<std::unordered_map<std::string,std::string> > tags;

    std::vector<int> oneways;
    long totalNumberEdges=0;

    // osmium::detail::subitem_of_type<WayNodeList> nodes;

    // If the way has a "highway" tag, find its length and add it to the
    // overall length.
    void way(const osmium::Way& way) {


        const char* highway = way.tags()["highway"];
        // possibleValuesRoad={}"motorway","trunk","primary","secondary","tertiary","unclassified","residential","service","road","motorway_link","trunk_link","primary_link","secondary_link","tertiary_link"}
        if (highway && (!std::strcmp(highway, "motorway")||!std::strcmp(highway, "primary")||!std::strcmp(highway, "trunk")||!std::strcmp(highway, "secondary")||!std::strcmp(highway, "tertiary")||!std::strcmp(highway, "unclassified")||!std::strcmp(highway, "residential")||!std::strcmp(highway, "service")||!std::strcmp(highway, "road")||!std::strcmp(highway, "motorway_link")||!std::strcmp(highway, "primary_link")||!std::strcmp(highway, "trunk_link")||!std::strcmp(highway, "secondary_link")||!std::strcmp(highway, "tertiary_link"))) {
          waysPoints.push_back(std::deque<Point2d> ());
          tags.push_back(std::unordered_map<std::string,std::string> ());
          // std::cout<<highway<<'\n';
          // for (auto& node_ref : way.nodes()) {
          //           node_ref.set_location(get_node_location(node_ref.ref()));
          //           if (!node_ref.location()) {
          //               error = true;
          //           }else{
          //
          //           }
          //       }
            // nodes=way.nodes();

            tags[tags.size()-1]["highway"]=std::string(highway);

            totalNumberEdges++;
            int oneway=0;
            const char* onewayTag = way.tags()["oneway"];
            if (onewayTag && (!std::strcmp(onewayTag, "yes"))){
              oneway=1;
            }
            if (onewayTag && (!std::strcmp(onewayTag, "no"))){
              oneway=0;
              totalNumberEdges++;
            }
            if (onewayTag && (!std::strcmp(onewayTag, "-1"))){
              oneway=-1;
            }
            if (onewayTag && (!std::strcmp(onewayTag, "reverse"))){
              oneway=-1;
            }
            oneways.push_back(oneway);

            const char* nameTag = way.tags()["name"];
            if (nameTag){
              tags[tags.size()-1]["name"]=std::string(nameTag);
            }
            const char* maxSpeedTag = way.tags()["maxspeed"];
            if (maxSpeedTag){
              tags[tags.size()-1]["maxSpeed"]=std::string(maxSpeedTag);
            }


            // for (const auto& tag : way.tags()) {
            //   if (std::string(tag.key()).compare("name")||std::string(tag.key()).compare("highway")||std::string(tag.key()).compare("maxspeed")){
            //     tags[tags.size()-1][tag.key()]=tag.value();
            //   }
            //
            //   // if (std::string(tag.key()).compare("oneway")){
            //   //   if(std::string(tag.value()).compare("yes")){
            //   //
            //   //   }else if (std::string(tag.value()).compare("no")){
            //   //     oneway=0;
            //   //     totalNumberEdges++;
            //   //   }else if (std::string(tag.value()).compare("-1")||std::string(tag.value()).compare("reverse")){
            //   //     oneway=-1;
            //   //   }else{
            //   //     oneway=1;
            //   //   }
            //   // }
            //
            //     // std::cout << tag.key() << '=' << tag.value() << '\n';
            // }

            // std::swap()


            for (const auto& nr : way.nodes()) {
               if (!nr.location()) {
             // //               error = true;
                }else{
                  if (oneway != -1){
                    waysPoints[waysPoints.size()-1].push_back(Point2d((double)(nr.location().x())/10000000.0,(double)(nr.location().y())/10000000.0));
                  }else{
                    waysPoints[waysPoints.size()-1].push_front(Point2d((double)(nr.location().x())/10000000.0,(double)(nr.location().y())/10000000.0));
                  }
                }

                // std::cout << "  node " << nr.ref() << " " << nr.location() << "\n";
            }

            // length += osmium::geom::haversine::distance(way.nodes());
        }
    }


}; // struct RoadLengthHandler


struct RailwaysHandler : public osmium::handler::Handler {

    // double length = 0;
    std::vector<std::vector<Point2d> > waysPoints;
    // osmium::detail::subitem_of_type<WayNodeList> nodes;

    // If the way has a "highway" tag, find its length and add it to the
    // overall length.
    void way(const osmium::Way& way) {
        waysPoints.push_back(std::vector<Point2d> ());
        const char* rail = way.tags()["railway"];
        // possibleValuesRoad={}"motorway","trunk","primary","secondary","tertiary","unclassified","residential","service","road","motorway_link","trunk_link","primary_link","secondary_link","tertiary_link"}
        if (rail && (!std::strcmp(rail, "light_rail")||!std::strcmp(rail, "narrow_gauge")||!std::strcmp(rail, "rail"))) {
          // std::cout<<highway<<'\n';
          // for (auto& node_ref : way.nodes()) {
          //           node_ref.set_location(get_node_location(node_ref.ref()));
          //           if (!node_ref.location()) {
          //               error = true;
          //           }else{
          //
          //           }
          //       }
            // nodes=way.nodes();
            for (const auto& nr : way.nodes()) {
               if (!nr.location()) {
             // //               error = true;
                       }else{
             waysPoints[waysPoints.size()-1].push_back(Point2d((double)(nr.location().x())/10000000.0,(double)(nr.location().y())/10000000.0));
             }

                // std::cout << "  node " << nr.ref() << " " << nr.location() << "\n";
            }
            // length += osmium::geom::haversine::distance(way.nodes());
        }
    }


}; // struct RoadLengthHandler



struct RiverHandler : public osmium::handler::Handler {

    // double length = 0;
    std::vector<std::vector<Point2d> > waysPoints;
    // osmium::detail::subitem_of_type<WayNodeList> nodes;

    // If the way has a "highway" tag, find its length and add it to the
    // overall length.
    void way(const osmium::Way& way) {
        waysPoints.push_back(std::vector<Point2d> ());
        const char* river = way.tags()["waterway"];
        // possibleValuesRoad={}"motorway","trunk","primary","secondary","tertiary","unclassified","residential","service","road","motorway_link","trunk_link","primary_link","secondary_link","tertiary_link"}
        // if (river && (!std::strcmp(river, "river")||!std::strcmp(river, "canal"))) {
        if (river && (!std::strcmp(river, "river"))) {
          // std::cout<<highway<<'\n';
          // for (auto& node_ref : way.nodes()) {
          //           node_ref.set_location(get_node_location(node_ref.ref()));
          //           if (!node_ref.location()) {
          //               error = true;
          //           }else{
          //
          //           }
          //       }
            // nodes=way.nodes();
            for (const auto& nr : way.nodes()) {
               if (!nr.location()) {
             // //               error = true;
                       }else{
             waysPoints[waysPoints.size()-1].push_back(Point2d((double)(nr.location().x())/10000000.0,(double)(nr.location().y())/10000000.0));
             }

                // std::cout << "  node " << nr.ref() << " " << nr.location() << "\n";
            }
            // length += osmium::geom::haversine::distance(way.nodes());
        }
    }


}; // struct RoadLengthHandler

// struct RiverHandler : public osmium::handler::Handler {
//
//     // double length = 0;
//     std::vector<std::vector<Point2d> > waysPoints;
//     // osmium::detail::subitem_of_type<WayNodeList> nodes;
//
//     // If the way has a "highway" tag, find its length and add it to the
//     // overall length.
//     void way(const osmium::Way& way) {
//         waysPoints.push_back(std::vector<Point2d> ());
//         const char* river = way.tags()["waterway"];
//         // possibleValuesRoad={}"motorway","trunk","primary","secondary","tertiary","unclassified","residential","service","road","motorway_link","trunk_link","primary_link","secondary_link","tertiary_link"}
//         // if (river && (!std::strcmp(river, "river")||!std::strcmp(river, "canal"))) {
//         if (river && (!std::strcmp(river, "river"))&& (!std::strcmp(river, "canal"))) {
//           // std::cout<<highway<<'\n';
//           // for (auto& node_ref : way.nodes()) {
//           //           node_ref.set_location(get_node_location(node_ref.ref()));
//           //           if (!node_ref.location()) {
//           //               error = true;
//           //           }else{
//           //
//           //           }
//           //       }
//             // nodes=way.nodes();
//             for (const auto& nr : way.nodes()) {
//                if (!nr.location()) {
//              // //               error = true;
//                        }else{
//              waysPoints[waysPoints.size()-1].push_back(Point2d((double)(nr.location().x())/10000000.0,(double)(nr.location().y())/10000000.0));
//              }
//
//                 // std::cout << "  node " << nr.ref() << " " << nr.location() << "\n";
//             }
//             // length += osmium::geom::haversine::distance(way.nodes());
//         }
//     }
//
//
// }; // struct RoadLengthHandler


struct ResidentialBuildingLevelsHandler : public osmium::handler::Handler {

    // double length = 0;
    std::vector<double > levels;
    std::vector<double> xs;
    std::vector<double> ys;
    // osmium::detail::subitem_of_type<WayNodeList> nodes;

    // If the way has a "highway" tag, find its length and add it to the
    // overall length.
    void way(const osmium::Way& way) {
        // waysPoints.push_back(std::vector<Point2d> ());
        const char* building = way.tags()["building"];
        // const char* height = way.tags()["height"];
        const char* building_levels = way.tags()["building:levels"];
        const char* roof_levels = way.tags()["roof:levels"];

        // possibleValuesRoad={}"motorway","trunk","primary","secondary","tertiary","unclassified","residential","service","road","motorway_link","trunk_link","primary_link","secondary_link","tertiary_link"}
        // if (river && (!std::strcmp(river, "river")||!std::strcmp(river, "canal"))) {
        if (building && (!std::strcmp(building, "apartments")|| (!std::strcmp(building, "farm"))|| (!std::strcmp(building, "hotel"))|| (!std::strcmp(building, "house"))|| (!std::strcmp(building, "detached"))|| (!std::strcmp(building, "residential"))
        ||  (!std::strcmp(building, "dormitory"))||  (!std::strcmp(building, "yes"))|| (!std::strcmp(building, "terrace"))|| (!std::strcmp(building, "houseboat"))|| (!std::strcmp(building, "bungalow"))|| (!std::strcmp(building, "static_caravan"))|| (!std::strcmp(building, "cabin")) )) {
          // std::cout<<highway<<'\n';
          // for (auto& node_ref : way.nodes()) {
          //           node_ref.set_location(get_node_location(node_ref.ref()));
          //           if (!node_ref.location()) {
          //               error = true;
          //           }else{
          //
          //           }
          //       }
            // nodes=way.nodes();

            double level=-1;
            Point2d centroid;
            if(building_levels){
              double levelTemp=level;
              try {
                // bitset constructor throws an invalid_argument if initialized
                // with a string containing characters other than 0 and 1
                // std::bitset<5> mybitset (std::string("01234"));
                levelTemp=std::stod(building_levels);

                centroid.x=0;
                centroid.y=0;
                double num=0;
                for (const auto& nr : way.nodes()) {
                   if (!nr.location()) {
                 // //               error = true;
                           }else{
                             centroid.x+=(double)(nr.location().x())/10000000.0;
                             centroid.y+=(double)(nr.location().y())/10000000.0;
                             num++;
                             // waysPoints[waysPoints.size()-1].push_back(Point2d((double)(nr.location().x())/10000000.0,(double)(nr.location().y())/10000000.0));
                   }
                }
                centroid.x/=num;
                centroid.y/=num;

              }
              catch (const std::invalid_argument& ia) {
            	  std::cerr << "Invalid argument levels: " << ia.what() <<" "<<building_levels<< '\n';
              }
              level=levelTemp;


            }
            if(roof_levels&&level>0){
              double levelTemp=0;
              try {
                // bitset constructor throws an invalid_argument if initialized
                // with a string containing characters other than 0 and 1
                // std::bitset<5> mybitset (std::string("01234"));
                levelTemp=std::stod(roof_levels);
              }
              catch (const std::invalid_argument& ia) {
            	  std::cerr << "Invalid argument roof levels: " << ia.what()<<" "<<roof_levels << '\n';
              }
              level+=levelTemp;

            }
            // if(!building_levels&&height){
            //   level=height/3
            // }
            if(level!=-1){
              levels.push_back(level);
              xs.push_back(centroid.x);
              ys.push_back(centroid.y);
            }

                // std::cout << "  node " << nr.ref() << " " << nr.location() << "\n";
            }
            // length += osmium::geom::haversine::distance(way.nodes());
        }



}; // struct RoadLengthHandler



struct ResidentialBuildingsHandler : public osmium::handler::Handler {

    // double length = 0;
    // std::vector<double> levels;
    // std::vector<std::vector<double> > xss;
    // std::vector<std::vector<double> > yss;
    std::vector<ExtrudedGraph> buildings;
    // std::vector<double> ys;
    // osmium::detail::subitem_of_type<WayNodeList> nodes;

    // If the way has a "highway" tag, find its length and add it to the
    // overall length.
    void way(const osmium::Way& way) {

        ExtrudedGraph currentBuilding;
        // waysPoints.push_back(std::vector<Point2d> ());
        const char* building = way.tags()["building"];
        const char* height = way.tags()["height"];
        const char* building_levels = way.tags()["building:levels"];
        const char* roof_levels = way.tags()["roof:levels"];

        // possibleValuesRoad={}"motorway","trunk","primary","secondary","tertiary","unclassified","residential","service","road","motorway_link","trunk_link","primary_link","secondary_link","tertiary_link"}
        // if (river && (!std::strcmp(river, "river")||!std::strcmp(river, "canal"))) {
        if (building && (!std::strcmp(building, "apartments")|| (!std::strcmp(building, "farm"))|| (!std::strcmp(building, "hotel"))|| (!std::strcmp(building, "house"))|| (!std::strcmp(building, "detached"))|| (!std::strcmp(building, "residential"))
        ||  (!std::strcmp(building, "dormitory"))||  (!std::strcmp(building, "yes"))|| (!std::strcmp(building, "terrace"))|| (!std::strcmp(building, "houseboat"))|| (!std::strcmp(building, "bungalow"))|| (!std::strcmp(building, "static_caravan"))|| (!std::strcmp(building, "cabin")) )) {
          // std::cout<<highway<<'\n';
          // for (auto& node_ref : way.nodes()) {
          //           node_ref.set_location(get_node_location(node_ref.ref()));
          //           if (!node_ref.location()) {
          //               error = true;
          //           }else{
          //
          //           }
          //       }
            // nodes=way.nodes();

            double level=-1;
            Point2d centroid;
            // std::vector<double> xs;
            // std::vector<double> ys;
            double height_=0;
            if(height){
              try{
                height_=std::stod(height);
              }catch (const std::invalid_argument& ia) {
            	  std::cerr << "Invalid argument height: " << ia.what() <<" "<<height<< '\n';
              }
            }
            if(building_levels){
              double levelTemp=level;
              try {
                // bitset constructor throws an invalid_argument if initialized
                // with a string containing characters other than 0 and 1
                // std::bitset<5> mybitset (std::string("01234"));
                levelTemp=std::stod(building_levels);

                centroid.x=0;
                centroid.y=0;
                double num=0;
                for (const auto& nr : way.nodes()) {
                   if (!nr.location()) {
                 // //               error = true;
                           }else{

                             centroid.x+=(double)(nr.location().x())/10000000.0;
                             centroid.y+=(double)(nr.location().y())/10000000.0;
                             double x=((double)(nr.location().x())/10000000.0);
                             double y=((double)(nr.location().y())/10000000.0);
                             currentBuilding.G.addNode(Point2d(x,y));
                             if(num>0){
                               currentBuilding.G.addLink(currentBuilding.G.nodes[currentBuilding.G.nodes.size()-2]->id,currentBuilding.G.nodes[currentBuilding.G.nodes.size()-1]->id,1);
                             }
                             num++;
                             // waysPoints[waysPoints.size()-1].push_back(Point2d((double)(nr.location().x())/10000000.0,(double)(nr.location().y())/10000000.0));
                   }
                }
                currentBuilding.G.addLink(currentBuilding.G.nodes[currentBuilding.G.nodes.size()-1]->id,currentBuilding.G.nodes[0]->id,1);

                centroid.x/=num;
                centroid.y/=num;

              }
              catch (const std::invalid_argument& ia) {
            	  std::cerr << "Invalid argument levels: " << ia.what()<<" "<<building_levels << '\n';
              }
              level=levelTemp;


            }
            if(roof_levels&&level>0){
              double levelTemp=0;
              try {
                // bitset constructor throws an invalid_argument if initialized
                // with a string containing characters other than 0 and 1
                // std::bitset<5> mybitset (std::string("01234"));
                levelTemp=std::stod(roof_levels);
              }
              catch (const std::invalid_argument& ia) {
            	  std::cerr << "Invalid argument roof levels: " << ia.what()<<" "<<roof_levels << '\n';
              }
              level+=levelTemp;

            }
            // if(!building_levels&&height){
            //   level=height/3
            // }
            if(level!=-1){
              currentBuilding.numberLevels=level;
              currentBuilding.heightPerLevel=3.0;
              currentBuilding.totalHeight=height_;
              currentBuilding.note=building;
              currentBuilding.centroid=Point2d(centroid.x,centroid.y);
              buildings.push_back(currentBuilding);
              // levels.push_back(level);
              // xss.push_back(xs);
              // yss.push_back(ys);
              // xs.push_back(centroid.x);
              // ys.push_back(centroid.y);
            }else if(currentBuilding.G.nodes.size()>3){
                currentBuilding.numberLevels=level;
                currentBuilding.heightPerLevel=3.0;
                currentBuilding.totalHeight=height_;
                currentBuilding.note=building;
                currentBuilding.centroid=Point2d(centroid.x,centroid.y);
                buildings.push_back(currentBuilding);

            }

                // std::cout << "  node " << nr.ref() << " " << nr.location() << "\n";
            }
            // length += osmium::geom::haversine::distance(way.nodes());
        }



}; // struct RoadLengthHandler


struct BuildingsHandler : public osmium::handler::Handler {

    // double length = 0;
    // std::vector<double> levels;
    // std::vector<std::vector<double> > xss;
    // std::vector<std::vector<double> > yss;
    std::vector<ExtrudedGraph> buildings;
    // std::vector<double> ys;
    // osmium::detail::subitem_of_type<WayNodeList> nodes;

    // If the way has a "highway" tag, find its length and add it to the
    // overall length.
    void way(const osmium::Way& way) {

        ExtrudedGraph currentBuilding;
        // waysPoints.push_back(std::vector<Point2d> ());
        const char* building = way.tags()["building"];
        const char* height = way.tags()["height"];
        const char* building_levels = way.tags()["building:levels"];
        const char* roof_levels = way.tags()["roof:levels"];

        // possibleValuesRoad={}"motorway","trunk","primary","secondary","tertiary","unclassified","residential","service","road","motorway_link","trunk_link","primary_link","secondary_link","tertiary_link"}
        // if (river && (!std::strcmp(river, "river")||!std::strcmp(river, "canal"))) {
        // if (building && (!std::strcmp(building, "apartments")|| (!std::strcmp(building, "farm"))|| (!std::strcmp(building, "hotel"))|| (!std::strcmp(building, "house"))|| (!std::strcmp(building, "detached"))|| (!std::strcmp(building, "residential"))
        // ||  (!std::strcmp(building, "dormitory"))|| (!std::strcmp(building, "terrace"))|| (!std::strcmp(building, "houseboat"))|| (!std::strcmp(building, "bungalow"))|| (!std::strcmp(building, "static_caravan"))|| (!std::strcmp(building, "cabin")) )) {
        if(building){
          // std::cout<<highway<<'\n';
          // for (auto& node_ref : way.nodes()) {
          //           node_ref.set_location(get_node_location(node_ref.ref()));
          //           if (!node_ref.location()) {
          //               error = true;
          //           }else{
          //
          //           }
          //       }
            // nodes=way.nodes();

            double level=-1;
            Point2d centroid;
            // std::vector<double> xs;
            // std::vector<double> ys;
            double height_=0;
            if(height){
              try{
                height_=std::stod(height);
              }catch (const std::invalid_argument& ia) {
            	  std::cerr << "Invalid argument height: " << ia.what() <<" "<<height<< '\n';
              }
            }
            if(building_levels){
              double levelTemp=level;
              try {
                // bitset constructor throws an invalid_argument if initialized
                // with a string containing characters other than 0 and 1
                // std::bitset<5> mybitset (std::string("01234"));
                levelTemp=std::stod(building_levels);

                centroid.x=0;
                centroid.y=0;
                double num=0;
                for (const auto& nr : way.nodes()) {
                   if (!nr.location()) {
                 // //               error = true;
                           }else{

                             centroid.x+=(double)(nr.location().x())/10000000.0;
                             centroid.y+=(double)(nr.location().y())/10000000.0;
                             double x=((double)(nr.location().x())/10000000.0);
                             double y=((double)(nr.location().y())/10000000.0);
                             currentBuilding.G.addNode(Point2d(x,y));
                             if(num>0){
                               currentBuilding.G.addLink(currentBuilding.G.nodes[currentBuilding.G.nodes.size()-2]->id,currentBuilding.G.nodes[currentBuilding.G.nodes.size()-1]->id,1);
                             }
                             num++;
                             // waysPoints[waysPoints.size()-1].push_back(Point2d((double)(nr.location().x())/10000000.0,(double)(nr.location().y())/10000000.0));
                   }
                }
                currentBuilding.G.addLink(currentBuilding.G.nodes[currentBuilding.G.nodes.size()-1]->id,currentBuilding.G.nodes[0]->id,1);

                centroid.x/=num;
                centroid.y/=num;

              }
              catch (const std::invalid_argument& ia) {
            	  std::cerr << "Invalid argument levels: " << ia.what()<<" "<<building_levels << '\n';
              }
              level=levelTemp;


            }
            if(roof_levels&&level>0){
              double levelTemp=0;
              try {
                // bitset constructor throws an invalid_argument if initialized
                // with a string containing characters other than 0 and 1
                // std::bitset<5> mybitset (std::string("01234"));
                levelTemp=std::stod(roof_levels);
              }
              catch (const std::invalid_argument& ia) {
            	  std::cerr << "Invalid argument roof levels: " << ia.what()<<" "<<roof_levels << '\n';
              }
              level+=levelTemp;

            }
            // if(!building_levels&&height){
            //   level=height/3
            // }
            if(level!=-1){
              currentBuilding.numberLevels=level;
              currentBuilding.heightPerLevel=3.0;
              currentBuilding.totalHeight=height_;
              currentBuilding.note=building;
              currentBuilding.centroid=Point2d(centroid.x,centroid.y);
              buildings.push_back(currentBuilding);
              // levels.push_back(level);
              // xss.push_back(xs);
              // yss.push_back(ys);
              // xs.push_back(centroid.x);
              // ys.push_back(centroid.y);
            }else if(currentBuilding.G.nodes.size()>3){
                currentBuilding.numberLevels=level;
                currentBuilding.heightPerLevel=3.0;
                currentBuilding.totalHeight=height_;
                currentBuilding.note=building;
                currentBuilding.centroid=Point2d(centroid.x,centroid.y);
                buildings.push_back(currentBuilding);

            }

                // std::cout << "  node " << nr.ref() << " " << nr.location() << "\n";
            }
            // length += osmium::geom::haversine::distance(way.nodes());
        }



}; // struct RoadLengthHandler



// class AmenityHandler : public osmium::handler::Handler {
//
//     // Print info about one amenity to stdout.
//     static void print_amenity(const char* type, const char* name, const osmium::geom::Coordinates& c) {
//         std::printf("%8.4f,%8.4f %-15s %s\n", c.x, c.y, type, name ? name : "");
//     }
//
//     // Calculate the center point of a NodeRefList.
//     static osmium::geom::Coordinates calc_center(const osmium::NodeRefList& nr_list) {
//         // Coordinates simply store an X and Y coordinate pair as doubles.
//         // (Unlike osmium::Location which stores them more efficiently as
//         // 32 bit integers.) Use Coordinates when you want to do calculations
//         // or store projected coordinates.
//         osmium::geom::Coordinates c{0.0, 0.0};
//
//         for (const auto& nr : nr_list) {
//             c.x += nr.lon();
//             c.y += nr.lat();
//         }
//
//         c.x /= nr_list.size();
//         c.y /= nr_list.size();
//
//         return c;
//     }
//
//     public:
//
//         void node(const osmium::Node& node) {
//             // Getting a tag value can be expensive, because a list of tags has
//             // to be gone through and each tag has to be checked. So we store the
//             // result and reuse it.
//             const char* amenity = node.tags()["amenity"];
//             if (amenity) {
//                 print_amenity(amenity, node.tags()["name"], node.location());
//             }
//         }
//
//         void area(const osmium::Area& area) {
//             const char* amenity = area.tags()["amenity"];
//             if (amenity) {
//                 // Use the center of the first outer ring. Because we set
//                 // create_empty_areas = false in the assembler config, we can
//                 // be sure there will always be at least one outer ring.
//                 const auto center = calc_center(*area.cbegin<osmium::OuterRing>());
//
//                 print_amenity(amenity, area.tags()["name"], center);
//             }
//         }
//
//     }; // class AmenityHandler



struct AmenitiesHandler : public osmium::handler::Handler {

    // double length = 0;
    std::vector<std::string > type;
    std::vector<double> xs;
    std::vector<double> ys;
    // osmium::detail::subitem_of_type<WayNodeList> nodes;

    // If the way has a "highway" tag, find its length and add it to the
    // overall length.

    static osmium::geom::Coordinates calc_center(const osmium::NodeRefList& nr_list) {
            // Coordinates simply store an X and Y coordinate pair as doubles.
            // (Unlike osmium::Location which stores them more efficiently as
            // 32 bit integers.) Use Coordinates when you want to do calculations
            // or store projected coordinates.
            osmium::geom::Coordinates c{0.0, 0.0};

            for (const auto& nr : nr_list) {
                c.x += nr.lon();
                c.y += nr.lat();
            }

            c.x /= nr_list.size();
            c.y /= nr_list.size();

            return c;
        }
    void node(const osmium::Node& node) {

        const char* amenity = node.tags()["amenity"];

        if (amenity) {

            Point2d centroid(node.location().x()/10000000.0,node.location().y()/10000000.0);
          //TODO handle types of amenities
              type.push_back("amenity");

              xs.push_back((double)(centroid.x));
              ys.push_back((double)(centroid.y));

            }


        const char* shop = node.tags()["shop"];

        if (shop) {

            Point2d centroid(node.location().x()/10000000.0,node.location().y()/10000000.0);
          //TODO handle types of shops
              type.push_back("shop");

              xs.push_back((double)(centroid.x));
              ys.push_back((double)(centroid.y));

        }

        const char* craft = node.tags()["craft"];

        if (craft) {

            Point2d centroid(node.location().x()/10000000.0,node.location().y()/10000000.0);
          //TODO handle types of craft
              type.push_back("craft");

              xs.push_back((double)(centroid.x));
              ys.push_back((double)(centroid.y));

        }


        const char* office = node.tags()["office"];

        if (office) {

            Point2d centroid(node.location().x()/10000000.0,node.location().y()/10000000.0);
          //TODO handle types of office
              type.push_back("office");

              xs.push_back((double)(centroid.x));
              ys.push_back((double)(centroid.y));

        }

        }
        void area(const osmium::Area& area) {
           const char* amenity = area.tags()["amenity"];
           if (amenity) {
               // Use the center of the first outer ring. Because we set
               // create_empty_areas = false in the assembler config, we can
               // be sure there will always be at least one outer ring.
               const auto centroid = calc_center(*area.cbegin<osmium::OuterRing>());
               type.push_back("amenity");

               xs.push_back((double)(centroid.x/10000000.0));
               ys.push_back((double)(centroid.y/10000000.0));
               // print_amenity(amenity, area.tags()["name"], center);
           }
           const char* shop = area.tags()["shop"];
           if (shop) {
               // Use the center of the first outer ring. Because we set
               // create_empty_areas = false in the assembler config, we can
               // be sure there will always be at least one outer ring.
               const auto centroid = calc_center(*area.cbegin<osmium::OuterRing>());
               type.push_back("shop");

               ys.push_back((double)(centroid.y/10000000.0));
               xs.push_back((double)(centroid.x/10000000.0));
               // print_amenity(amenity, area.tags()["name"], center);
           }
           const char* craft = area.tags()["craft"];
           if (craft) {
               // Use the center of the first outer ring. Because we set
               // create_empty_areas = false in the assembler config, we can
               // be sure there will always be at least one outer ring.
               const auto centroid = calc_center(*area.cbegin<osmium::OuterRing>());
               type.push_back("craft");

               ys.push_back((double)(centroid.y/10000000.0));
               xs.push_back((double)(centroid.x/10000000.0));
               // print_amenity(amenity, area.tags()["name"], center);
           }
           const char* office = area.tags()["office"];
           if (office) {
               // Use the center of the first outer ring. Because we set
               // create_empty_areas = false in the assembler config, we can
               // be sure there will always be at least one outer ring.
               const auto centroid = calc_center(*area.cbegin<osmium::OuterRing>());
               type.push_back("office");

               ys.push_back((double)(centroid.y/10000000.0));
               xs.push_back((double)(centroid.x/10000000.0));
               // print_amenity(amenity, area.tags()["name"], center);
           }

       }



}; // struct RoadLengthHandler








/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////




void OSM::loadRoads(std::string nameFile,Grafo* result,bool directed) {
    // Grafo G;
    result->bidirectional=!directed;
    result->pseudoGraph=false;
    // Initialize the reader with the filename from the command line and
    // tell it to only read nodes and ways.
    osmium::io::Reader reader{nameFile, osmium::osm_entity_bits::node | osmium::osm_entity_bits::way};

    // The index to hold node locations.
    index_type index;

    // The location handler will add the node locations to the index and then
    // to the ways
    location_handler_type location_handler{index};
    location_handler.ignore_errors();

    // Our handler defined above
    RoadHandler road_handler;

    // Apply input data to first the location handler and then our own handler
    osmium::apply(reader, location_handler, road_handler);

    long idPreviousNode;
    Point2d previousNodeLocation;
    // for(auto way:road_handler.waysPoints){
    for(long j=0;j<road_handler.waysPoints.size();j++){
      std::deque<Point2d> way=road_handler.waysPoints[j];
      long i=0;
      std::deque<Point2d> points;
      int oneway=road_handler.oneways[j];
        for(auto point:way){
          if (oneway==2 && directed){
            points.push_front(point);
          }
        Nodo* node=result->addNode(point);

        if(i>0){
          // long id=node->id;
          result->addLink(idPreviousNode,node->id,Functions::getDistance(node->location,previousNodeLocation));


        }
        idPreviousNode=node->id;
        previousNodeLocation=node->location;
        i++;
      }
      if (points.size()>0){
        long i=0;
          for(auto point:points){

          Nodo* node=result->addNode(point);

          if(i>0){
            // long id=node->id;
            result->addLink(idPreviousNode,node->id,Functions::getDistance(node->location,previousNodeLocation));


          }
          idPreviousNode=node->id;
          previousNodeLocation=node->location;
          i++;
        }
      }
    }

    // Output the length. The haversine function calculates it in meters,
    // so we first devide by 1000 to get kilometers.
    // for(auto& node:road_length_handler.nodes){
    //   result->addNode(Point2d(get_node_location(node).x,get_node_location(node).y))
    // }
    // std::cout << "Length: " << road_length_handler.length / 1000 << " km\n";

    // return G;
}

void OSM::loadRoadsAndDataRoads(std::string nameFile,DualExtendedGraph* result,bool directed) {
  // Grafo G;
  result->getPrimalGraph()->bidirectional=!directed;
  result->getPrimalGraph()->pseudoGraph=false;
  // Initialize the reader with the filename from the command line and
  // tell it to only read nodes and ways.
  osmium::io::Reader reader{nameFile, osmium::osm_entity_bits::node | osmium::osm_entity_bits::way};

  // The index to hold node locations.
  index_type index;

  // The location handler will add the node locations to the index and then
  // to the ways
  location_handler_type location_handler{index};
  location_handler.ignore_errors();

  // Our handler defined above
  RoadHandler road_handler;

  // Apply input data to first the location handler and then our own handler
  osmium::apply(reader, location_handler, road_handler);

  // result->getData()->tags.reserve(road_handler.totalNumberEdges);
  long idPreviousNode;
  Point2d previousNodeLocation;
  // for(auto way:road_handler.waysPoints){
  for(long j=0;j<road_handler.waysPoints.size();j++){
    std::deque<Point2d> way=road_handler.waysPoints[j];

    long i=0;
    std::deque<Point2d> points;
    int oneway=road_handler.oneways[j];
      for(auto point:way){
        if (oneway==2 && directed){
          points.push_front(point);
        }
      Nodo* node=result->getPrimalGraph()->addNode(point);

      if(i>0){
        // long id=node->id;
        long idLink=result->getPrimalGraph()->addLink(idPreviousNode,node->id,Functions::getDistance(node->location,previousNodeLocation));
        if(idLink!=-1){
          result->getPrimalGraph()->links[idLink]->data=road_handler.tags[j];
        }
        // result->getData()->tags.push_back(road_handler.tags[j]);

      }
      idPreviousNode=node->id;
      previousNodeLocation=node->location;
      i++;
    }
    if (points.size()>0){
      long i=0;

        for(auto point:points){

        Nodo* node=result->getPrimalGraph()->addNode(point);

        if(i>0){
          // long id=node->id;
          long idLink=result->getPrimalGraph()->addLink(idPreviousNode,node->id,Functions::getDistance(node->location,previousNodeLocation));
          if(idLink!=-1){
            result->getPrimalGraph()->links[idLink]->data=road_handler.tags[j];
          }
          // result->getData()->tags.push_back(road_handler.tags[j]);

        }
        idPreviousNode=node->id;
        previousNodeLocation=node->location;
        i++;
      }
    }
  }

  // Output the length. The haversine function calculates it in meters,
  // so we first devide by 1000 to get kilometers.
  // for(auto& node:road_length_handler.nodes){
  //   result->addNode(Point2d(get_node_location(node).x,get_node_location(node).y))
  // }
  // std::cout << "Length: " << road_length_handler.length / 1000 << " km\n";

  // return G;
}







void OSM::loadRailways(std::string nameFile,Grafo* result,bool directed) {
    // Grafo G;
    result->bidirectional=!directed;
    result->pseudoGraph=false;
    // Initialize the reader with the filename from the command line and
    // tell it to only read nodes and ways.
    osmium::io::Reader reader{nameFile, osmium::osm_entity_bits::node | osmium::osm_entity_bits::way};

    // The index to hold node locations.
    index_type index;

    // The location handler will add the node locations to the index and then
    // to the ways
    location_handler_type location_handler{index};
    location_handler.ignore_errors();

    // Our handler defined above
    RailwaysHandler train_handler;

    // Apply input data to first the location handler and then our own handler
    osmium::apply(reader, location_handler, train_handler);

    long idPreviousNode;
    Point2d previousNodeLocation;
    for(auto way:train_handler.waysPoints){
      long i=0;
        for(auto point:way){
        Nodo* node=result->addNode(point);

        if(i>0){
          // long id=node->id;
          result->addLink(idPreviousNode,node->id,Functions::getDistance(node->location,previousNodeLocation));

        }
        idPreviousNode=node->id;
        previousNodeLocation=node->location;
        i++;
      }
    }

    // Output the length. The haversine function calculates it in meters,
    // so we first devide by 1000 to get kilometers.
    // for(auto& node:road_length_handler.nodes){
    //   result->addNode(Point2d(get_node_location(node).x,get_node_location(node).y))
    // }
    // std::cout << "Length: " << road_length_handler.length / 1000 << " km\n";

  }
    // return G;











    void OSM::loadRivers(std::string nameFile,Grafo* result,bool directed) {
        // Grafo G;
        result->bidirectional=!directed;
        result->pseudoGraph=false;
        // Initialize the reader with the filename from the command line and
        // tell it to only read nodes and ways.
        osmium::io::Reader reader{nameFile, osmium::osm_entity_bits::node | osmium::osm_entity_bits::way};

        // The index to hold node locations.
        index_type index;

        // The location handler will add the node locations to the index and then
        // to the ways
        location_handler_type location_handler{index};
        location_handler.ignore_errors();

        // Our handler defined above
        RiverHandler handler;

        // Apply input data to first the location handler and then our own handler
        osmium::apply(reader, location_handler, handler);

        long idPreviousNode;
        Point2d previousNodeLocation;
        for(auto way:handler.waysPoints){
          long i=0;
            for(auto point:way){
            Nodo* node=result->addNode(point);

            if(i>0){
              // long id=node->id;
              result->addLink(idPreviousNode,node->id,Functions::getDistance(node->location,previousNodeLocation));

            }
            idPreviousNode=node->id;
            previousNodeLocation=node->location;
            i++;
          }
        }

        // Output the length. The haversine function calculates it in meters,
        // so we first devide by 1000 to get kilometers.
        // for(auto& node:road_length_handler.nodes){
        //   result->addNode(Point2d(get_node_location(node).x,get_node_location(node).y))
        // }
        // std::cout << "Length: " << road_length_handler.length / 1000 << " km\n";

        // return G;
    }





    std::tuple<std::vector<double>,std::vector<double>,std::vector<double> > OSM::loadResidentialBuildingLevels(std::string nameFile){
      // Initialize the reader with the filename from the command line and
      // tell it to only read nodes and ways.
      osmium::io::Reader reader{nameFile, osmium::osm_entity_bits::node | osmium::osm_entity_bits::way};

      // The index to hold node locations.
      index_type index;

      // The location handler will add the node locations to the index and then
      // to the ways
      location_handler_type location_handler{index};
      location_handler.ignore_errors();

      // Our handler defined above
      ResidentialBuildingLevelsHandler handler;

      // Apply input data to first the location handler and then our own handler
      osmium::apply(reader, location_handler, handler);

      // std::vector<double> levels;
      // for(auto level:handler.levels){
      //   levels.push_back(level);
      // }
      // std::vector<double> xs;
      // for(auto x:handler.xs){
      //   xs.push_back(x);
      // }
      // std::vector<double> ys;
      // for(auto y:handler.ys){
      //   ys.push_back(y);
      // }
      return std::make_tuple(handler.xs,handler.ys,handler.levels);
    }

    std::vector<ExtrudedGraph> OSM::loadResidentialBuildings(std::string nameFile){
      // Initialize the reader with the filename from the command line and
      // tell it to only read nodes and ways.
      osmium::io::Reader reader{nameFile, osmium::osm_entity_bits::node | osmium::osm_entity_bits::way};

      // The index to hold node locations.
      index_type index;

      // The location handler will add the node locations to the index and then
      // to the ways
      location_handler_type location_handler{index};
      location_handler.ignore_errors();

      // Our handler defined above
      ResidentialBuildingsHandler handler;

      // Apply input data to first the location handler and then our own handler
      osmium::apply(reader, location_handler, handler);

      // std::vector<double> levels;
      // for(auto level:handler.levels){
      //   levels.push_back(level);
      // }
      // std::vector<double> xs;
      // for(auto x:handler.xs){
      //   xs.push_back(x);
      // }
      // std::vector<double> ys;
      // for(auto y:handler.ys){
      //   ys.push_back(y);
      // }
      // return std::make_tuple(handler.xss,handler.yss,handler.levels);
      return handler.buildings;
    }
    std::vector<ExtrudedGraph> OSM::loadBuildings(std::string nameFile){
      // Initialize the reader with the filename from the command line and
      // tell it to only read nodes and ways.
      osmium::io::Reader reader{nameFile, osmium::osm_entity_bits::node | osmium::osm_entity_bits::way};

      // The index to hold node locations.
      index_type index;

      // The location handler will add the node locations to the index and then
      // to the ways
      location_handler_type location_handler{index};
      location_handler.ignore_errors();

      // Our handler defined above
      BuildingsHandler handler;

      // Apply input data to first the location handler and then our own handler
      osmium::apply(reader, location_handler, handler);

      // std::vector<double> levels;
      // for(auto level:handler.levels){
      //   levels.push_back(level);
      // }
      // std::vector<double> xs;
      // for(auto x:handler.xs){
      //   xs.push_back(x);
      // }
      // std::vector<double> ys;
      // for(auto y:handler.ys){
      //   ys.push_back(y);
      // }
      // return std::make_tuple(handler.xss,handler.yss,handler.levels);
      return handler.buildings;
    }








std::tuple<std::vector<double>,std::vector<double>,std::vector<std::string> > OSM::loadAmenities(std::string nameFile){
  // void loadAmenities(std::string nameFile){
  // Initialize the reader with the filename from the command line and
  osmium::io::Reader reader{nameFile, osmium::osm_entity_bits::node | osmium::osm_entity_bits::way};
  // tell it to only read nodes and ways.

  // The index to hold node locations.
  index_type index;

  // The location handler will add the node locations to the index and then
  // to the ways
  location_handler_type location_handler{index};
  location_handler.ignore_errors();

  // Our handler defined above
  AmenitiesHandler handler;

  // osmium::area::MultipolygonManager<osmium::area::Assembler> mp_manager{assembler_config};

        // We read the input file twice. In the first pass, only relations are
        // read and fed into the multipolygon manager.
        // std::cerr << "Pass 1...\n";
        // osmium::relations::read_relations(input_file, mp_manager);

  // Apply input data to first the location handler and then our own handler
  // osmium::apply(reader, location_handler, handler);
  osmium::apply(reader, location_handler, handler);

  // std::vector<double> levels;
  // for(auto level:handler.levels){
  //   levels.push_back(level);
  // }
  // std::vector<double> xs;
  // for(auto x:handler.xs){
  //   xs.push_back(x);
  // }
  // std::vector<double> ys;
  // for(auto y:handler.ys){
  //   ys.push_back(y);
  // }
  return std::make_tuple(handler.xs,handler.ys,handler.type);
  // try {
  //       // The input file
  //       const osmium::io::File input_file{nameFile};
  //
  //       // Configuration for the multipolygon assembler. We disable the option to
  //       // create empty areas when invalid multipolygons are encountered. This
  //       // means areas created have a valid geometry and invalid multipolygons
  //       // are simply ignored.
  //       osmium::area::Assembler::config_type assembler_config;
  //       assembler_config.create_empty_areas = false;
  //
  //       // Initialize the MultipolygonManager. Its job is to collect all
  //       // relations and member ways needed for each area. It then calls an
  //       // instance of the osmium::area::Assembler class (with the given config)
  //       // to actually assemble one area.
  //       osmium::area::MultipolygonManager<osmium::area::Assembler> mp_manager{assembler_config};
  //
  //       // We read the input file twice. In the first pass, only relations are
  //       // read and fed into the multipolygon manager.
  //       std::cerr << "Pass 1...\n";
  //       osmium::relations::read_relations(input_file, mp_manager);
  //       std::cerr << "Pass 1 done\n";
  //
  //       // The index storing all node locations.
  //       index_type index;
  //
  //       // The handler that stores all node locations in the index and adds them
  //       // to the ways.
  //       location_handler_type location_handler{index};
  //
  //       // If a location is not available in the index, we ignore it. It might
  //       // not be needed (if it is not part of a multipolygon relation), so why
  //       // create an error?
  //       location_handler.ignore_errors();
  //
  //       // Create our handler.
  //       AmenityHandler data_handler;
  //
  //       // On the second pass we read all objects and run them first through the
  //       // node location handler and then the multipolygon manager. The manager
  //       // will put the areas it has created into the "buffer" which are then
  //       // fed through our handler.
  //       //
  //       // The read_meta::no option disables reading of meta data (such as version
  //       // numbers, timestamps, etc.) which are not needed in this case. Disabling
  //       // this can speed up your program.
  //       std::cerr << "Pass 2...\n";
  //       osmium::io::Reader reader{input_file, osmium::io::read_meta::no};
  //
  //       osmium::apply(reader, location_handler, data_handler, mp_manager.handler([&data_handler](const osmium::memory::Buffer& area_buffer) {
  //           osmium::apply(area_buffer, data_handler);
  //       }));
  //
  //       reader.close();
  //       std::cerr << "Pass 2 done\n";
  //   } catch (const std::exception& e) {
  //       // All exceptions used by the Osmium library derive from std::exception.
  //       std::cerr << e.what() << '\n';
  //       // std::exit(1);
  //   }
}
