#include <stdlib.h>
#include <stdio.h>
#include "Errors.h"
#include "List.h"
#include "Stack.h"
#include "Matrix.h"

error count_graph_size(FILE * fin, unsigned int * size) {
  *size = 0;
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

error read_graph_from_file(char const *filename, Matrix * graph) {
  FILE *fin = fopen(filename, "r");
  unsigned int size;
  error const statusCounting = count_graph_size(fin, &size);
  if (statusCounting != OK)
    return statusCounting;
  *graph = init_matrix(size);

  unsigned int numEdges;
  fscanf(fin, "%u\n", &numEdges);
  for (unsigned int i = 0; i < numEdges; ++i) {
    unsigned int begin, end;
    int const readBeginStatus = fscanf(fin, "%u", &begin);
    if (readBeginStatus == EOF || readBeginStatus == 0) {
      delete_matrix(graph);
      fclose(fin);
      return BAD_INPUT;
    }
    int const readEndStatus = fscanf(fin, "%u", &end);
    if (readEndStatus == EOF || readEndStatus == 0) {
      delete_matrix(graph);
      fclose(fin);
      return BAD_INPUT;
    }
    add_edge(graph, begin, end);
    add_edge(graph, end, begin);
  }

  fclose(fin);
  return OK;
}

typedef enum _GraphType {NO_PATH, PATH, CYCLE} GraphType; // Euler path existing

GraphType does_contain_Euler_path(Matrix const graph, unsigned int * badVertex1, unsigned int * badVertex2) {
  unsigned int counterUnevenDegree = 0;
  for (unsigned int i = 0; i < graph.size; ++i) {
    unsigned int degree = 0;
    for (unsigned int j = 0; j < graph.size; ++j) {
      if (check_edge(&graph, i, j))
        ++degree;
    }
    if (degree == 1)
      ++counterUnevenDegree;
  }
  if (counterUnevenDegree == 0)
    return CYCLE;
  if (counterUnevenDegree == 2)
    return PATH;
  return NO_PATH;
}

// Warning: It destroyes graph
List get_Euler_cycle(Matrix * graph) {
  Stack stack = make_stack();
  unsigned int const startVertex = 0;
  List path = make_list();
  push_to_stack(&stack, startVertex);
  while (!is_stack_empty(stack)) {
    unsigned int const vertex = pop_from_stack(&stack);
    push_front(&path, vertex);
    for (unsigned int i = 0; i < graph->size; ++i) {
      if (graph->body[vertex][i] == 1) {
        push_to_stack(&stack, i);
        graph->body[vertex][i] = 0;
        graph->body[i][vertex] = 0;
      }
    }
  }
  return path;
}

// Warning: It destroyes graph
List get_Euler_path(Matrix * graph, unsigned int const badVertex1, unsigned int const badVertex2) {
  add_edge(graph, badVertex1, badVertex2); // Adding fake edge to make cycle
  List cycle = get_Euler_cycle(graph);
  List path = make_list();
  ListElem *firstBadVertex;
  for (ListElem *i = cycle.head; i->value != badVertex1 && i->value != badVertex2; i = i->next, firstBadVertex = i);
  ListElem *lastBadVertex = firstBadVertex->next;
  for (ListElem *i = lastBadVertex; i != NULL; i = i->next)
    push_back(&path, i->value);
  for (ListElem *i = cycle.head; i != firstBadVertex; i = i->next)
    push_back(&path, i->value);
  return path;
}

int main() {
  char const * const inputFilename  = "input.txt";
  char const * const outputFilename = "output.txt";

  Matrix graph;
  error readStatus = read_graph_from_file(inputFilename, &graph);
  if (readStatus != OK) {
    print_error(outputFilename, readStatus);
    return 1;
  }

  unsigned int badVertex1, badVertex2;

  GraphType const type = does_contain_Euler_path(graph, &badVertex1, &badVertex2);

  if (type == NO_PATH) {
    FILE *fout = fopen(outputFilename, "w");
    fprintf(fout, "NO\n");
    fclose(fout);
    delete_matrix(&graph);
    return 0;
  }

  List eulerPath = make_list();
  if (type == PATH)
    eulerPath = get_Euler_path(&graph, badVertex1, badVertex2);
  else
    eulerPath = get_Euler_cycle(&graph);

  FILE *fout = fopen(outputFilename, "w");
  for (ListElem *i = eulerPath.head; i != NULL; i = i->next)
    fprintf(fout, "%u ", i->value);
  fprintf(fout, "\n");
  fclose(fout);
  delete_matrix(&graph);
  return 0;
}
