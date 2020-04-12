#include "AdjacencyList.h"

AdjacencyList make_adj_list(unsigned int const size) {
  AdjacencyList graph;
  graph.body = (List*)malloc(sizeof(List) * size);
  graph.size = size;
  return graph;
}

void add_edge(AdjacencyList *graph, unsigned int const begin, unsigned int const end) {
  push_front(graph->body + begin, end);
}

int check_edge(AdjacencyList *graph, unsigned int const begin, unsigned int const end) {
  List neighbours = graph->body[begin];
  for (ListElem * i = neighbours.head; i != NULL; i = i->next) {
    if (i->value == end)
      return 1;
  }
  return 0;
}

void delete_edge(AdjacencyList *graph, unsigned int const begin, unsigned int const end) {
  List neighbours = graph->body[begin];
  for (ListElem * i = neighbours.head; i->next != NULL; i = i->next) {
    if (i->next->value == end) {
      ListElem *next = i->next->next;
      free(i->next);
      i->next = next;
    }
  }
}

void delete_adjacency_list(AdjacencyList *graph) {
  for (unsigned int i = 0; i < graph->size; ++i)
    delete_list(graph->body + i);
  free(graph->body);
}
