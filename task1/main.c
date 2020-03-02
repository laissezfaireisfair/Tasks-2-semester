#include <stdlib.h>
#include <stdio.h>

typedef struct _Edge {
  unsigned int begin, end;
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
  if (graph->head == NULL) { // Case of adding first elem
    graph->head = (Edge*)malloc(sizeof(Edge));
    *graph->head = edge;
    return;
  }

  Edge *tail;
  for (tail = graph->head; tail->next != NULL; tail = tail->next);
  tail->next = (Edge*)malloc(sizeof(Edge));
  *tail->next = edge;
}

EdgeList read_graph_from_file(char const *filename) {
  FILE *fin = fopen(filename, "r");
  unsigned int size;
  fscanf(fin, "%u\n", &size);
  EdgeList graph = init_edge_list();
  graph.size = size;
  while (1) {
    Edge newEdge;
    if (fscanf(fin, "%u", &(newEdge.begin)) == EOF)
      break;
    fscanf(fin, "%u", &(newEdge.end));
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
    matrix.body[tail->begin][tail->end] = tail->weight;
    matrix.body[tail->end][tail->begin] = tail->weight;
  }
  return matrix;
}

void delete_matrix(Matrix *matrix) {
  for (unsigned int i = 0; i < matrix->size; ++i)
    free(matrix->body[i]);
  free(matrix->body);
}

int get_weight(Matrix const graph, unsigned int const begin, unsigned int const end) {
  if (begin > graph.size || end > graph.size) {
    printf("get_weight: Out of range error.\n");
    exit(1);
  }
  return graph.body[begin][end];
}

unsigned int ask_begin() {
  printf("What is edge begin? ");
  unsigned int begin;
  scanf("%u", &begin);
  return begin;
}

unsigned int ask_end() {
  printf("What is edge end? ");
  unsigned int begin;
  scanf("%u", &begin);
  return begin;
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
  unsigned int begin = ask_begin();
  unsigned int end = ask_end();
  int const weight = get_weight(matrix, begin, end);
  delete_matrix(&matrix);
  print_weight(weight);
  return 0;
}
