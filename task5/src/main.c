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

List get_articulation_points(AdjacencyList const graph);

void print_list(List const list);

int main() {
  char const *INPUT_FILE_NAME = "input.txt";
  AdjacencyList graph = read_graph_from_file(INPUT_FILE_NAME);
  List articulationPoints = get_articulation_points(graph);
  delete_adjacency_list(&graph);
  print_list(articulationPoints);
  delete_list(articulationPoints);
  return 0;
}
