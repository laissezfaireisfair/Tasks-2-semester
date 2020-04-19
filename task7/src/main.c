#include <stdlib.h>
#include <stdio.h>
#include "Errors.h"
#include "Sequence.h"
#include "Permutations.h"
#include "Matrix.h"

typedef enum _Boolean {FALSE, TRUE} Boolean;

Boolean check_way(Matrix const graph, Sequence const way) {
  for (unsigned int i = 1; i < way.length; ++i)
    if (!check_edge(&graph, way.body[i - 1], way.body[i]))
      return FALSE;
  return TRUE;
}

// Print "NO" if it does not exist
error print_hamilton_way(Matrix const graph, char const *  const filename) {
  // Make start sequence:
  Sequence way = make_seq();
  error const sinitStatus = init_seq(&way, graph.size);
  if (initStatus != OK)
    return initStatus;
  for (unsigned int i = 0; i < graph.size; ++i)
    way.body[i] = i;

  // Count number of potential ways:
  unsigned int numWays = 1;
  for (unsigned int i = 2; i <= graph.size; ++i)
    numWays *= i;

  // Gen way and check it's correctness:
  for (unsigned int i = 0; i < numWays; ++i) {
    error const genStatus = permutate_to_next(&way);
    if (genStatus != OK)
      return genStatus;

    if (check_way(graph, way)) {
      FILE *fout = fopen(filename, "w");
      print_sequence(fout, way);
      fclose(fout);
      return OK;
    }
  }

  FILE *fout = fopen(filename, "w");
  fprintf(fout, "NO\n");
  fclose(fout);
  return OK;
}

int main() {
  char const * const inputFilename  = "input.txt";
  char const * const outputFilename = "output.txt";

  Matrix graph;
  error const readStatus = read_graph_from_file(inputFilename, &graph);
  if (readStatus != OK) {
    print_error(outputFilename, readStatus);
    return 1;
  }

  error const searchStatus = print_hamilton_way(graph, outputFilename);
  if (searchStatus != OK) {
    print_error(outputFilename, searchStatus);
    return 2;
  }

  delete_matrix(&graph);
  return 0;
}
