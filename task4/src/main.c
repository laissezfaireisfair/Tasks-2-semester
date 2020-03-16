#include <stdlib.h>
#include <stdio.h>
#include "AdjacencyList.h"

AdjacencyList read_graph_from_file(char const *filename) {
  FILE *fin = fopen(filename, "r");
  unsigned int size;
  fscanf(fin, "%u\n", &size);
  AdjacencyList graph = make_adj_list(size);
  for (unsigned int begin = 0; begin < graph.size; ++begin) {
    for (unsigned int end = 0; end < graph.size; ++end) {
      int isEdgeHere;
      fscanf(fin, "%d", &isEdgeHere);
      if (isEdgeHere != 0)
        add_edge(&graph, begin, end);
    }
  }
  fclose(fin);
  return graph;
}

int main() {
  char const *inputFilename = "input.txt";
  AdjacencyList graph = read_graph_from_file(inputFilename);
  delete_adjacency_list(&graph);
  return 0;
}
