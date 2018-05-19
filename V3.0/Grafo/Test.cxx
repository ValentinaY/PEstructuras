#include "Graph.h"
#include <iostream>

int main(int argc, char const *argv[]) {
  Graph<char> *grafo= new Graph<char>(true);
  grafo->addVertex('A');
  grafo->addVertex('B');
  grafo->addVertex('C');
  grafo->addVertex('D');
  grafo->addVertex('E');
  /*
  grafo->addVertex('F');
  grafo->addEdge('A','B','A');
  grafo->addEdge('A','D','A');
  grafo->addEdge('B','C','A');
  grafo->addEdge('C','E','A');
  grafo->addEdge('C','F','A');
  grafo->addEdge('D','E','A');
  grafo->addEdge('D','F','A');
  grafo->addEdge('E','D','A');
  grafo->addEdge('E','C','A');
  grafo->addEdge('F','C','A');
  grafo->addEdge('F','A','A');
  std::cout<<std::endl;
  grafo->breadthfirstsearch('B');
  std::cout<<std::endl;
  */
  grafo->addEdge('A','B', 4);
  grafo->addEdge('A','D', 4);
  grafo->addEdge('B','B', 1);
  grafo->addEdge('B','C',20);
  grafo->addEdge('B','E', 3);
  grafo->addEdge('C','D', 8);
  grafo->addEdge('D','C', 12);
  
  if(grafo->isPath('A')){
    std::cout<<"\n Si es camino !";
  }else{
      std::cout<<"\n No es camino !";
  }

  grafo->dijkstra('E','C');
  return 0;
}
