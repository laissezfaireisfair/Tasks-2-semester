#include <stdlib.h>
#include <stdio.h>
#include "Errors.h"
#include "Constants.h"
#include "Sequence.h"
#include "Queue.h"
#include "Matrix.h"

error find_way(Matrix const graph, Sequence *way, long int *distances) {
  error const initSeqStatus = init_seq(way, graph.size); // The worst case when need visit all vertex
  if (initSeqStatus!= OK)
    return initSeqStatus;
  for (unsigned int i = 0; i < graph.size; ++i)
    distances[i] = -1;
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
    if (fprintf(fout, "%lu ", distances[i]) < 1) {
      print_error(RUNTIME_ERROR);
      delete_matrix(&graph);
      free(distances);
      return 4;
    }
  }
  free(distances);
  fprintf(fout, "\n");

  error const printWayStatus = print_sequence(fout, way);
  if (printWayStatus != OK) {
    print_error(printWayStatus);
    delete_matrix(&graph);
    return 5;
  }

  delete_matrix(&graph);
  return 0;
}
