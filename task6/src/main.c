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

typedef enum _Boolean {FALSE, TRUE} Boolean;

Boolean does_contain_Euler_path(AdjacencyList const graph) {
  unsigned int counterUnevenDegree = 0;
  for (unsigned int i = 0; i < graph.size; ++i) {
    List neighbours = graph.body[i];
    unsigned int degree = 0;
    for (ListElem *j = neighbours.head; j != NULL; j = j->next)
      ++degree;
    if (degree % 2 == 1)
      ++counterUnevenDegree;
  }
  if (counterUnevenDegree == 0 || counterUnevenDegree == 2)
    return TRUE;
  return FALSE;
}

// Warning: It destroyes graph
error get_Euler_path(AdjacencyList * graph, List * path);

int main() {
  char const * const inputFilename  = "input.txt";
  char const * const outputFilename = "output.txt";

  AdjacencyList graph;
  error readStatus = read_graph_from_file(inputFilename, &graph);
  if (readStatus != OK) {
    print_error(outputFilename, readStatus);
    return 1;
  }

  if (does_contain_Euler_path(graph) == FALSE) {
    FILE *fout = fopen(outputFilename, "w");
    fprintf(fout, "NO");
    fclose(fout);
    delete_adjacency_list(&graph);
    return 0;
  }

  List eulerPath = make_list();
  error const gettingPathStatus = get_Euler_path(&graph, &eulerPath);
  if (gettingPathStatus != OK) {
    print_error(outputFilename, gettingPathStatus);
    delete_adjacency_list(&graph);
    return 2;
  }

  FILE *fout = fopen(outputFilename, "w");
  for (ListElem *i = eulerPath.head; i != NULL; i = i->next)
    fprintf(fout, "%u ", i->value);
  fclose(fout);
  delete_adjacency_list(&graph);
  return 0;
}
