#include <stdlib.h>
#include <stdio.h>

typedef struct _Edge {
  unsigned int source, destination;
  int weight;
  struct _Edge *next;
} Edge;

typedef struct _EdgeList {
  Edge *head;
  unsigned int size;
} EdgeList;

typedef struct _Matrix {
  unsigned int size;
  int **body;
} Matrix;

EdgeList init_edge_list() {
  EdgeList graph;
  graph.head = NULL;
  graph.size = 0;
  return graph;
}

void add_edge(EdgeList *graph, Edge const edge) {
  Edge *tail;
  for (tail = graph->head; tail != NULL; tail = tail->next);
  tail = (Edge*)malloc(sizeof(Edge));
  *tail = edge;

  if (graph->head == NULL) // Case of adding first elem
    graph->head = tail;
}

EdgeList read_graph_from_file(char const *filename) {
  FILE *fin = fopen(filename, "r");
  unsigned int size;
  fscanf(fin, "%u\n", &size);
  EdgeList graph = init_edge_list();
  graph.size = size;
  for (unsigned int i = 0; i < size; ++i) {
    Edge newEdge;
    fscanf(fin, "%u", &(newEdge.source));
    fscanf(fin, "%u", &(newEdge.destination));
    fscanf(fin, "%d", &(newEdge.weight));
    newEdge.next = NULL;
    add_edge(&graph, newEdge);
  }
  fclose(fin);
  return graph;
}

void delete_edge_list(EdgeList *graph) {
  for (Edge *head = graph->head; head != NULL;) {
    Edge *newHead = head->next;
    free(head);
    head = newHead;
  }
}

Matrix init_matrix_with_list(EdgeList const list) {
  Matrix matrix;
  matrix.size = list.size;
  matrix.body = (int**)malloc(sizeof(int*) * matrix.size);
  for (unsigned int i = 0; i < list.size; ++i) {
    matrix.body[i] = (int*)malloc(sizeof(int*) * matrix.size);
    for (unsigned j = 0; j < list.size; ++j) {
      if (i == j)
        matrix.body[i][j] = 0;
      else
        matrix.body[i][j] = -1;
    }
  }
  for (Edge *tail = list.head; tail != NULL; tail = tail->next) {
    matrix.body[tail->source][tail->destination] = tail->weight;
    matrix.body[tail->destination][tail->source] = tail->weight;
  }
  return matrix;
}

void delete_matrix(Matrix *matrix) {
  for (unsigned int i = 0; i < matrix->size; ++i)
    free(matrix->body[i]);
  free(matrix->body);
}

int get_weight(Matrix const graph, unsigned int const source, unsigned int const destination) {
  if (source > graph.size || destination > graph.size) {
    printf("get_weight: Out of range error.\n");
    exit(1);
  }
  return graph.body[source][destination];
}

unsigned int ask_source() {
  printf("What is edge begin? ");
  unsigned int source;
  scanf("%u", &source);
  return source;
}

unsigned int ask_destination() {
  printf("What is edge end? ");
  unsigned int source;
  scanf("%u", &source);
  return source;
}

void print_weight(int const weight) {
  if (weight == -1) {
    printf("There is no edge here.\n");
    return;
  }
  printf("Weight of the edge is %d\n", weight);
}

int main() {
  char const *filename = "input.txt";
  EdgeList edgeList = read_graph_from_file(filename);
  Matrix matrix = init_matrix_with_list(edgeList);
  delete_edge_list(&edgeList);
  unsigned int source = ask_source();
  unsigned int destination = ask_destination();
  int const weight = get_weight(matrix, source, destination);
  delete_matrix(&matrix);
  print_weight(weight);
  return 0;
}
