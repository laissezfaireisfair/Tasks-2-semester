#include <stdlib.h>
#include <stdio.h>
#include "AdjacencyList.h"
#include "Queue.h"

typedef enum _VertexStatus {NOT_PASSED, IN_QUEUE, PASSED} VertexStatus;

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

int is_acyclic(AdjacencyList const graph) {
  VertexStatus *status = (VertexStatus*)malloc(sizeof(VertexStatus) * graph.size);
  for (unsigned int vertex = 0; vertex < graph.size; ++vertex)
    status[vertex] = NOT_PASSED;
  Queue queue = make_queue();
  unsigned int const startVertex = 0;
  push(&queue, startVertex);
  while (is_queue_empty(queue)) {
    unsigned int const nextVertex = pop(&queue);
    for (ListElem *i = graph.body[nextVertex].head; i != NULL; i = i->next) {
      unsigned int const neighbourVertex = i->value;
      if (status[neighbourVertex] == NOT_PASSED) {
        push(&queue, neighbourVertex);
        status[neighbourVertex] = IN_QUEUE;
        continue;
      }
      if (status[neighbourVertex] == IN_QUEUE) {
        delete_queue(&queue);
        return 0;
      }
    }
    status[nextVertex] = PASSED;
  }
  delete_queue(&queue);
  return 1;
}

int main() {
  char const *inputFilename = "input.txt";
  AdjacencyList graph = read_graph_from_file(inputFilename);
  if (is_acyclic(graph))
    printf("YES\n");
  else
    printf("NO\n");
  delete_adjacency_list(&graph);
  return 0;
}
