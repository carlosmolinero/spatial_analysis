/*

  EXAMPLE osmium_road_length

  Calculate the length of the road network (everything tagged `highway=*`)
  from the given OSM file.

  DEMONSTRATES USE OF:
  * file input
  * location indexes and the NodeLocationsForWays handler
  * length calculation on the earth using the haversine function

  SIMPLER EXAMPLES you might want to understand first:
  * osmium_read
  * osmium_count
  * osmium_pub_names

  LICENSE
  The code in this example file is released into the Public Domain.

*/

// #include <cstdlib>  // for std::exit
// #include <iostream> // for std::cout, std::cerr

// Allow any format of input files (XML, PBF, ...)
#include "osmium/io/any_input.hpp"

// For the osmium::geom::haversine::distance() function
#include "osmium/geom/haversine.hpp"

// For osmium::apply()
#include "osmium/visitor.hpp"
#include <osmium/geom/coordinates.hpp>
#include "DualExtendedGraph.h"
#include "Grafo.h"
#include "ExtrudedGraph.h"
#include <string> //string, getline()

// For the location index. There are different types of indexes available.
// This will work for all input files keeping the index in memory.
#include "osmium/index/map/flex_mem.hpp"

// For the NodeLocationForWays handler
#include "osmium/handler/node_locations_for_ways.hpp"

#include <osmium/index/map/flex_mem.hpp>

// For the NodeLocationForWays handler
// #include <osmium/handler/node_locations_for_ways.hpp>

// The type of index used. This must match the include file above
// using index_type = osmium::index::map::FlexMem<osmium::unsigned_object_id_type, osmium::Location>;
//
// // The location handler always depends on the index type
// using location_handler_type = osmium::handler::NodeLocationsForWays<index_type>;

// For assembling multipolygons
#include <osmium/area/assembler.hpp>
#include <osmium/area/multipolygon_manager.hpp>

// Allow any format of input files (XML, PBF, ...)
#include <osmium/io/any_input.hpp>

// For osmium::apply()
#include <osmium/visitor.hpp>

// For osmium::geom::Coordinates
#include <osmium/geom/coordinates.hpp>

// The type of index used. This must match the include file above
using index_type = osmium::index::map::FlexMem<osmium::unsigned_object_id_type, osmium::Location>;

// The location handler always depends on the index type
using location_handler_type = osmium::handler::NodeLocationsForWays<index_type>;

// This handler only implements the way() function, we are not interested in
// any other objects.


class OSM{
public:

  static void loadRoads(std::string nameFile,Grafo* result,bool directed);
  static void loadRoadsAndDataRoads(std::string nameFile,DualExtendedGraph* result,bool directed);
  static void loadRailways(std::string nameFile,Grafo* result,bool directed);
  static void loadRivers(std::string nameFile,Grafo* result,bool directed);
  static std::tuple<std::vector<double>,std::vector<double>,std::vector<double> > loadResidentialBuildingLevels(std::string nameFile);
  static std::vector<ExtrudedGraph> loadResidentialBuildings(std::string nameFile);
  static std::vector<ExtrudedGraph> loadBuildings(std::string nameFile);
  static std::tuple<std::vector<double>,std::vector<double>,std::vector<std::string> > loadAmenities(std::string nameFile);
  // static void loadAmenities(std::string nameFile);

};
