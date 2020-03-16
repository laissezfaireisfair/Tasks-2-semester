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

void mark_connected(AdjacencyList const graph, unsigned int const vertex, char *visited) {
  visited[vertex] = 1;
  for (ListElem *i = graph.body[vertex].head; i != NULL; i = i->next) {
    if (visited[i->value] == 0) {
      visited[i->value] = 1;
      mark_connected(graph, i->value, visited);
    }
  }
}

int is_all_connected(AdjacencyList const graph) {
  char *visited = (char*)malloc(sizeof(char) * graph.size);
  for (unsigned int i = 0; i < graph.size; visited[i] = 0, ++i);

  unsigned int const startVertex = 0;
  mark_connected(graph, startVertex, visited);

  int isConnected = 1;
  for (unsigned int i = 0; i < graph.size; ++i) {
    if (visited[i] == 0) {
      isConnected = 0;
      break;
    }
  }

  free(visited);
  return isConnected;
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

  if (is_all_connected(graph))
    printf("Этот граф связный.\n");
  else
    printf("Этот граф несвязный.\n");

  delete_adjacency_list(&graph);
  return 0;
}
