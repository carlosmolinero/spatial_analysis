getGraphFromIgraph=function(graph,directed=F){
  ncol.graph=getNCOLFromGraph(graph,internalRepresentation = T)
  coordinates.tmp=data.frame(V(graph)$x,V(graph)$y)
  G.cpp=createGraph(as.numeric(V(graph)$name),coordinatesNodes = coordinates.tmp,ncol = ncol.graph,directed = directed)
  return (G.cpp)
}

getIgraphFromGraph=function(G){
  ncol.graph=getNCOL(G);
  coordinates=getCoordinates(G);
#   graph=graph.data.frame(vertices = coordinates[,1],ncol.graph,directed=isDirected(G))
  graph=graph.data.frame(ncol.graph,vertices = coordinates[,1],directed=isDirected(G))
  matched=match(V(graph)$name,coordinates[,1])
  V(graph)$x=coordinates[matched,2]
  V(graph)$y=coordinates[matched,3]
  graph=permute.vertices(graph,matched)
  return (graph)
}

getLargeGraphFromIgraph=function(G,directed=F){
    ncol.graph=getNCOLFromGraph(G,internalRepresentation = T)
    coordinates=getCoordinatesFromGraph(G)
    G.l.cpp=createLargeGraph(ncol.graph,coordinates,directed)
}

