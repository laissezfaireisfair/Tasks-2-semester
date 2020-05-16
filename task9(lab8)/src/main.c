#include <stdlib.h>
#include <stdio.h>
#include "Errors.h"
#include "Constants.h"
#include "Sequence.h"
#include "Queue.h"
#include "Matrix.h"

error find_way(Matrix const graph, Sequence *way, unsigned int *distances) {}

int main() {
  Constants const constants = get_constants();

  Matrix graph;
  error const readStatus = read_graph_from_file(&graph);
  if (readStatus != OK) {
    print_error(readStatus);
    return 1;
  }

  Sequence way = make_seq();
  unsigned int *distances = NULL;
  error const findStatus = find_way(graph, &way, distances);
  if (findStatus != OK) {
    print_error(findStatus);
    delete_matrix(&graph);
    return 2;
  }

  FILE *fout = fopen(constants.INPUT_FILENAME, "w");
  if (fout == NULL) {
    print_error(RUNTIME_ERROR);
    delete_matrix(&graph);
    return 3;
  }

  for (unsigned int i = 0; i < graph.size; ++i) {
    if (fprintf(fout, "%u ", distances[i]) < 1) {
      print_error(RUNTIME_ERROR);
      delete_matrix(&graph);
      return 4;
    }
  }
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
