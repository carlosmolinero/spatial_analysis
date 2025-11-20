# Spatial Analysis Library

A comprehensive C++ library for spatial network analysis, graph operations, and urban geometry processing with R integration via Rcpp.

## Features

- **Graph Operations**: Create and manipulate spatial graphs with coordinate-aware nodes
- **Dual Extended Graphs**: Advanced graph representations for complex spatial networks
- **Fractal Dimension Analysis**: Calculate fractal dimensions of spatial structures
- **Spatial Interaction Models**: Analyze spatial relationships and interactions
- **OSM Integration**: Work with OpenStreetMap data
- **Geometry Processing**: Tools for geometric analysis including GeometryGraph operations
- **Network Generation**: Generative procedures for road network creation
- **Clustering**: Spatial clustering with RTree and QTree implementations
- **Percolation Analysis**: Critical exponents and percolation theory applications
- **Entropy and Distribution Analysis**: Statistical analysis of spatial patterns
- **Dijkstra's Algorithm**: Shortest path computation for spatial networks

## Requirements

- C++11 or later
- R (for Rcpp integration)
- Rcpp package
- Eigen library (included)

## Installation

### From R

```r
# Install Rcpp if not already installed
install.packages("Rcpp")

# Compile the package
Rcpp::sourceCpp("wrapperR.cpp")
```

## Usage

### Creating Graphs from igraph

```r
# Load the wrapper functions
source("wrapperC.R")

# Convert an igraph object to the C++ graph representation
G.cpp <- getGraphFromIgraph(graph, directed = FALSE)

# Convert back to igraph
graph <- getIgraphFromGraph(G.cpp)
```

### Working with Spatial Graphs

The library supports graphs with spatial coordinates and various operations:

- Graph creation with node coordinates
- NCOL format import/export
- Directed and undirected graphs
- Weight management

## Core Components

- **Grafo**: Base graph class
- **DualExtendedGraph**: Extended graph with dual representations
- **GeometryGraph**: Graph with geometric operations
- **RTree/QTree**: Spatial indexing structures
- **OSM**: OpenStreetMap data processing
- **SpatialInteraction**: Spatial interaction modeling
- **FractalDimension**: Fractal analysis tools

## License

See [LICENSE](LICENSE) file for details. Free for personal and non-commercial use. Commercial use requires a separate license.

## Author

Carlos Molinero (carlosmolinero@gmail.com)

## Contributing

This is a personal project. For commercial licensing inquiries, please contact the author.
