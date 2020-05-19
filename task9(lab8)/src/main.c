#include <stdlib.h>
#include <stdio.h>
#include "Errors.h"
#include "Constants.h"
#include "Sequence.h"
#include "PriorityQueue.h"
#include "Matrix.h"

// Warning: way is inverted
error find_way(Matrix const graph, Sequence *way, long int *distances) {
  Constants const constants = get_constants();

  error const initSeqStatus = init_seq(way, graph.size); // The worst case when need visit all vertex
  if (initSeqStatus!= OK)
    return initSeqStatus;
  for (unsigned int i = 0; i < graph.size; ++i)
    distances[i] = -1;
  distances[graph.start] = 0;

  int *parent = (int*)malloc(sizeof(int*) * graph.size);
  if (parent == NULL)
    return RUNTIME_ERROR;

  Queue queue = make_queue();
  PriorityVal startVertex;
  startVertex.value = graph.start;
  startVertex.priority = 0;
  push_to_queue(&queue, startVertex);

  while(!is_queue_empty(queue)) {
    int const vertexNow = pop_from_queue(&queue).value;
    for (int i = 0; i < (int)graph.size; ++i) {
      int const weight = check_edge(&graph, vertexNow, i);
      if (weight == -1)
        continue;
      if (distances[i] == -1 || distances[i] > distances[vertexNow] + weight) {
        PriorityVal iVertex;
        iVertex.value = i;
        iVertex.priority = distances[vertexNow] + weight;
        push_to_queue(&queue, iVertex);
        parent[i] = vertexNow;
        if (distances[vertexNow] + weight <= constants.MAX_INT)
          distances[i] = distances[vertexNow] + weight;
        else
          distances[i] = constants.MAX_INT + 1; // Will be printed as INT_MAX+
      }
    }
  }

  if (distances[graph.finish] == -1) {
    free(parent);
    return OK;
  }

  for (int i = graph.finish; i != (int)graph.start; i = parent[i], ++way->length)
    way->body[way->length] = i;
  way->body[way->length] = graph.start;
  ++way->length;

  free(parent);
  return OK;
}

int main() {
  Constants const constants = get_constants();

  Matrix graph;
  error const readStatus = read_graph_from_file(&graph);
  if (readStatus != OK) {
    print_error(readStatus);
    return 1;
  }

  Sequence way = make_seq();
  long int *distances = (long int*)malloc(sizeof(long int) * graph.size);
  if (distances == NULL)
    return RUNTIME_ERROR;
  error const findStatus = find_way(graph, &way, distances);
  if (findStatus != OK) {
    print_error(findStatus);
    delete_matrix(&graph);
    free(distances);
    return 2;
  }

  FILE *fout = fopen(constants.OUTPUT_FILENAME, "w");
  if (fout == NULL) {
    print_error(RUNTIME_ERROR);
    delete_matrix(&graph);
    free(distances);
    return 3;
  }

  for (unsigned int i = 0; i < graph.size; ++i) {
    int printDistStatus = 0;
    if (distances[i] > constants.MAX_INT)
      printDistStatus = fprintf(fout, "INT_MAX+");
    else if (distances[i] == -1)
      printDistStatus = fprintf(fout, "NO_PATH");
    else
      printDistStatus = fprintf(fout, "%lu ", distances[i]);

    if (printDistStatus < 1) {
      print_error(RUNTIME_ERROR);
      delete_matrix(&graph);
      free(distances);
      return 4;
    }
  }

  fprintf(fout, "\n");

  if (distances[graph.finish] > constants.MAX_INT) {
    fprintf(fout, "overflow\n");
    free(distances);
    delete_matrix(&graph);
    return 0;
  } else if (distances[graph.finish] == -1) {
    fprintf(fout, "no path\n");
    free(distances);
    delete_matrix(&graph);
    return 0;
  }

  free(distances);

  error const printWayStatus = print_revert_sequence(fout, way);
  if (printWayStatus != OK) {
    print_error(printWayStatus);
    delete_matrix(&graph);
    return 5;
  }

  delete_matrix(&graph);
  return 0;
}
