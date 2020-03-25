#include <stdlib.h>
#include <stdio.h>
#include "List.h"
#include "AdjacencyList.h"

List string_to_list(char const *str) {
  List list = make_list();
  for (unsigned int i = 0; str[i] != 0; ++i) {
    unsigned int num = str[i] - '0';
    push_front(&list, num);
  }
  return list;
}

AdjacencyList read_graph_from_file(char const *filename) {
  FILE *fin = fopen(filename, "r");
  unsigned int size;
  fscanf(fin, "%u\n", &size);
  AdjacencyList graph = make_adj_list(size);
  char *str = (char*)malloc(sizeof(char) * size + 1);
  for (unsigned int begin = 0; begin < graph.size; ++begin) {
      fscanf(fin, "%s", str);
      List ends = string_to_list(str);
      add_edges(&graph, begin, ends);
      delete_list(&ends);
  }
  free(str);
  fclose(fin);
  return graph;
}

int main() {
  return 0;
}
