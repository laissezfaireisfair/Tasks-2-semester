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

// Counts in time and minimal in time of subtree (including back edges):
void dfs(AdjacencyList const graph, unsigned int const vertex, unsigned int const timeNow, unsigned int *time, unsigned int *minTime) {
  time[vertex] = timeNow;
  List const *neighbours = &graph.body[vertex];
  unsigned int min = time[vertex];
  for (ListElem *i = neighbours->head; i != NULL; i = i->next) {
    unsigned int const neighbour = i->value;
    if (time[neighbour] == 0) { // Means not visited, so edge is straignt
      dfs(graph, neighbour, timeNow + 1, time, minTime);
      if (minTime[neighbour] < min)
        min = minTime[neighbour];
    } else { // Edge is back
      if (time[neighbour] < min)
        min = time[neighbour];
    }
  }
  minTime[vertex] = min;
}

// Only suitable for non-start vertex
int is_articulation_point(unsigned int const vertex, AdjacencyList const graph, unsigned int const *time, unsigned int const *minTime) {
  List const *neighbours = &graph.body[vertex];
  for (ListElem *i = neighbours->head; i != NULL; i = i->next) {
    unsigned int const neighbour = i->value;
    if (time[neighbour] < time[vertex]) // It is parent not daughter
      continue;
    if (minTime[neighbour] < time[vertex]) // Other way founded
      return 0;
  }
  return 1;
}

List get_articulation_points(AdjacencyList const graph) {
  // Vertex visit time (0 - not visited):
  unsigned int *time = (unsigned int*)malloc(sizeof(unsigned int) * graph.size);

  // Min visit time of vertex and it's subtree (including back edges):
  unsigned int *minTime = (unsigned int*)malloc(sizeof(unsigned int) * graph.size);

  for (unsigned int i = 0; i < graph.size; ++i)
    time[i] = 0;

  // Count times and minimal subtree times:
  unsigned int const startTime = 1;
  unsigned int const startVertex = 0;
  dfs(graph, startVertex, startTime, time, minTime);

  // Check non-start vertex for articulation point:
  List artPnts = make_list();
  for (unsigned int i = 1; i < graph.size; ++i)
    if (is_articulation_point(i, graph, time, minTime))
      push_front(&artPnts, i);

  // Check if start vertex articulation point (run from other start):
  for (unsigned int i = 0; i < graph.size; ++i)
    time[i] = 0;
  unsigned int const otherStart = 1;
  dfs(graph, otherStart, startTime, time, minTime);
  if (is_articulation_point(otherStart, graph, time, minTime))
    push_front(&artPnts, otherStart);

  free(time);
  free(minTime);
  return artPnts;
}

void print_list(FILE *fout, List const list) {
  for (ListElem *i = list.head; i != NULL; i = i->next)
    fprintf(fout, "%u ", i->value);
}

int main() {
  char const *INPUT_FILE_NAME  = "input.txt";
  char const *OUTPUT_FILE_NAME = "output.txt";
  AdjacencyList graph = read_graph_from_file(INPUT_FILE_NAME);
  List articulationPoints = get_articulation_points(graph);
  delete_adjacency_list(&graph);
  FILE *fout = fopen(OUTPUT_FILE_NAME, "w");
  print_list(fout, articulationPoints);
  fclose(fout);
  delete_list(&articulationPoints);
  return 0;
}
