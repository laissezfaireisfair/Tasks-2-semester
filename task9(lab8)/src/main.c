#include <stdlib.h>
#include <stdio.h>
#include "Errors.h"
#include "Constants.h"
#include "Sequence.h"
#include "Queue.h"
#include "Matrix.h"


int main() {
  Matrix graph;
  error const readStatus = read_graph_from_file(&graph);
  if (readStatus != OK) {
    print_error(readStatus);
    return 1;
  }
  delete_matrix(&graph);
  return 0;
}
