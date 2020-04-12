#include "AdjacencyList.h"

AdjacencyList make_adj_list(valType const size) {
  AdjacencyList graph;
  graph.body = (List*)malloc(sizeof(List) * size);
  graph.size = size;
  return graph;
}

void add_edge(AdjacencyList *graph, valType const begin, valType const end) {
  push_front(graph->body + begin, end);
}

void delete_adjacency_list(AdjacencyList *graph) {
  for (valType i = 0; i < graph->size; ++i)
    delete_list(graph->body + i);
  free(graph->body);
}
