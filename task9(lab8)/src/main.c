#include <stdlib.h>
#include <stdio.h>
#include "Errors.h"
#include "Constants.h"
#include "Sequence.h"
#include "PriorityQueue.h"
#include "Matrix.h"

void dijkstra_search(Matrix const graph, int *parent, long int *distances) {
  Constants constants = get_constants();
  PriorityQueue queue = make_queue();
  PriorityVal startVertex;
  startVertex.value = graph.start;
  startVertex.priority = 0;
  push_to_queue(&queue, startVertex);

  while(!is_queue_empty(queue)) {
    int const vertexNow = pop_from_queue(&queue).value;
    for (int i = 0; i < (int)graph.size; ++i) {
      int const weight = check_edge(&graph, vertexNow, i);
      if (weight == -1)
        continue;
      if (distances[i] == -1 || distances[i] > distances[vertexNow] + weight) {
        PriorityVal iVertex;
        iVertex.value = i;
        iVertex.priority = distances[vertexNow] + weight;
        push_to_queue(&queue, iVertex);
        parent[i] = vertexNow;
        if (distances[vertexNow] + weight <= constants.MAX_INT)
          distances[i] = distances[vertexNow] + weight;
        else
          distances[i] = constants.MAX_INT + 1; // Will be printed as INT_MAX+
      }
    }
  }
}


// Warning: way is inverted
error find_way(Matrix const graph, Sequence *way, long int *distances) {
  for (unsigned int i = 0; i < graph.size; ++i)
    distances[i] = -1;
  distances[graph.start] = 0;

  int *parent = (int*)malloc(sizeof(int*) * graph.size);
  if (parent == NULL)
    return RUNTIME_ERROR;

  dijkstra_search(graph, parent, distances);

  if (distances[graph.finish] == -1) { // Way generation doesn't needed when the vertex unaccessable
    free(parent);
    return OK;
  }

  error const initSeqStatus = init_seq(way, graph.size); // The worst case is when need visit all vertex
  if (initSeqStatus!= OK)
    return initSeqStatus;

  // Restore way from parent[]:
  for (int i = graph.finish; i != (int)graph.start; i = parent[i], ++way->length)
    way->body[way->length] = i;
  way->body[way->length] = graph.start;
  ++way->length;

  free(parent);
  return OK;
}


error print_distances(FILE* fout, long int const *distances, unsigned int const size) {
  Constants constants = get_constants();
  for (unsigned int i = 0; i < size; ++i) {
    int printStatus = 0;
    if (distances[i] > constants.MAX_INT)
      printStatus = fprintf(fout, "INT_MAX+");
    else if (distances[i] == -1)
      printStatus = fprintf(fout, "NO_PATH");
    else
      printStatus = fprintf(fout, "%lu ", distances[i]);

    if (printStatus < 1)
      return RUNTIME_ERROR;
  }
  if (fprintf(fout, "\n") < 1)
    return RUNTIME_ERROR;
  return OK;
}


typedef enum _WayStatus {EXIST, OVERFLOW, NO_PATH} WayStatus;

error print_way(FILE* fout, WayStatus wayStatus, Sequence const *way) {
  switch (wayStatus) {
    case (EXIST): return print_revert_sequence(fout, *way);
    case (OVERFLOW): {
      int const printStatus = fprintf(fout, "overflow\n");
      if (printStatus < 1)
        return RUNTIME_ERROR;
      return OK;
    }
    case (NO_PATH): {
      int const printStatus = fprintf(fout, "no path\n");
      if (printStatus < 1)
        return RUNTIME_ERROR;
      return OK;
    }
  }
  return INVALID_ARGUMENT;
}


error print_answer(Matrix const graph, Sequence const *way, long int const *distances) {
  Constants const constants = get_constants();
  FILE *fout = fopen(constants.OUTPUT_FILENAME, "w");
  if (fout == NULL)
    return RUNTIME_ERROR;

  error const printDistStatus = print_distances(fout, distances, graph.size);
  if (printDistStatus!= OK) {
    fclose(fout);
    return printDistStatus;
  }

  WayStatus wayStatus = EXIST;
  if (distances[graph.finish] > constants.MAX_INT)
    wayStatus = OVERFLOW;
  if (distances[graph.finish] == -1)
    wayStatus = NO_PATH;

  error const printWayResult = print_way(fout, wayStatus, way);
  fclose(fout);
  return printWayResult;
}


int main() {
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

  error const printStatus = print_answer(graph, &way, distances);

  delete_matrix(&graph);
  free(distances);
  deinit_seq(&way);

  if (printStatus != OK) {
    print_error(printStatus);
    return 3;
  }

  return 0;
}
