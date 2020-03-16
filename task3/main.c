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

AdjacencyList read_graph_from_file(char const *filename) {
  FILE *fin = fopen(filename, "r");
  AdjacencyList graph;
  fscanf(fin, "%u\n", &graph.size);
  graph.body = (List*)malloc(sizeof(List) * graph.size);
  while (1) {
    unsigned int begin, end;
    if (fscanf(fin, "%u", &begin) == EOF)
      break;
    fscanf(fin, "%u", &end);
    push_front(graph.body + begin, end);
  }
  fclose(fin);
  return graph;
}

void mark_component(AdjacencyList const graph, unsigned int const vertex, char const compNow, char *component) {
  component[vertex] = compNow;
  for (ListElem *i = graph.body[vertex].head; i != NULL; i = i->next) {
    if (component[i->value] == 0) {
      component[i->value] = compNow;
      mark_component(graph, i->value, compNow, component);
    }
  }
}

int count_components(AdjacencyList const graph) {
  char *component = (char*)malloc(sizeof(char) * graph.size);
  for (unsigned int i = 0; i < graph.size; component[i] = 0, ++i);

  unsigned int numOfComponent = 0;
  for (unsigned int i = 0; i < graph.size; ++i) {
    if (component[i] == 0) {
      ++numOfComponent;
      mark_component(graph, i, numOfComponent, component);
    }
  }

  free(component);
  return numOfComponent;
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
  char const *filename = "input.txt";
  AdjacencyList graph = read_graph_from_file(filename);

  printf("%d\n", count_components(graph));

  delete_adjacency_list(&graph);
  return 0;
}
