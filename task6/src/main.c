#include <stdlib.h>
#include <stdio.h>
#include "Errors.h"
#include "List.h"
#include "AdjacencyList.h"

error count_graph_size(FILE * fin, unsigned int * size) {
  unsigned int numEdges;
  fscanf(fin, "%u\n", &numEdges);

  for (unsigned int i = 0; i < numEdges; ++i) {
    unsigned int begin, end;

    int const readBeginStatus = fscanf(fin, "%u", &begin);
    if (readBeginStatus == EOF || readBeginStatus == 0)
      return BAD_INPUT;
    if (begin + 1 > *size)
      *size = begin + 1;

    int const readEndStatus = fscanf(fin, "%u", &end);
    if (readEndStatus == EOF || readEndStatus == 0)
      return BAD_INPUT;
    if (end + 1 > *size)
      *size = end + 1;
  }

  rewind(fin);
  return OK;
}

error read_graph_from_file(char const *filename, AdjacencyList * graph) {
  FILE *fin = fopen(filename, "r");
  unsigned int size;
  error const statusCounting = count_graph_size(fin, &size);
  if (statusCounting != OK)
    return statusCounting;
  *graph = make_adj_list(size);

  unsigned int numEdges;
  fscanf(fin, "%u\n", &numEdges);
  for (unsigned int i = 0; i < numEdges; ++i) {
    unsigned int begin, end;
    int const readBeginStatus = fscanf(fin, "%u", &begin);
    if (readBeginStatus == EOF || readBeginStatus == 0) {
      delete_adjacency_list(graph);
      fclose(fin);
      return BAD_INPUT;
    }
    int const readEndStatus = fscanf(fin, "%u", &end);
    if (readEndStatus == EOF || readEndStatus == 0) {
      delete_adjacency_list(graph);
      fclose(fin);
      return BAD_INPUT;
    }
    add_edge(graph, begin, end);
  }

  delete_adjacency_list(graph);
  fclose(fin);
  return OK;
}

int main() {
  return 0;
}
