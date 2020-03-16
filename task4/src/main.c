#include <stdlib.h>
#include <stdio.h>

typedef struct _ListElem {
  unsigned int value;
  struct _ListElem *next;
} ListElem;

typedef struct _List {
  ListElem *head;
} List;

typedef struct _AdjacencyList {
  unsigned int size;
  List *body;
} AdjacencyList;

void push_front(List *list, unsigned int const value) {
  ListElem *newElem = (ListElem*)malloc(sizeof(ListElem));
  newElem->value = value;
  newElem->next = list->head;
  list->head = newElem;
}

void add_edge(AdjacencyList *graph, unsigned int const begin, unsigned int const end) {
  push_front(graph->body + begin, end);
}

AdjacencyList read_graph_from_file(char const *filename) {
  FILE *fin = fopen(filename, "r");
  AdjacencyList graph;
  fscanf(fin, "%u\n", &graph.size);
  graph.body = (List*)malloc(sizeof(List) * graph.size);
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

void delete_list(List *list) {
  for (ListElem *i = list->head; i != NULL;) {
    ListElem *next = i->next;
    free(i);
    i = next;
  }
}

void delete_adjacency_list(AdjacencyList *graph) {
  for (unsigned int i = 0; i < graph->size; ++i)
    delete_list(graph->body + i);
  free(graph->body);
}

int main() {
  char const *inputFilename = "input.txt";
  AdjacencyList graph = read_graph_from_file(inputFilename);
  delete_adjacency_list(&graph);
  return 0;
}
