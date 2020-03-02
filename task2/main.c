#include <stdlib.h>
#include <stdio.h>

typedef struct _Matrix {
  unsigned int size;
  int **body;
} Matrix;

Matrix read_graph_from_file(char const *filename) {
  FILE *fin = fopen(filename, "r");
  Matrix graph;
  fscanf(fin, "%u\n", &graph.size);
  graph.body = (int**)malloc(sizeof(int*) * graph.size);
  for (unsigned int i = 0; i < graph.size; ++i) {
    graph.body[i] = (int*)malloc(sizeof(int*) * graph.size);
    for (unsigned j = 0; j < graph.size; ++j) {
      if (i == j)
        graph.body[i][j] = 1;
      else
        graph.body[i][j] = 0;
    }
  }
  while (1) {
    unsigned int begin, end;
    if (fscanf(fin, "%u", &begin) == EOF)
      break;
    fscanf(fin, "%u", &end);
    graph.body[begin][end] = 1;
  }
  fclose(fin);
  return graph;
}

void mark_connected(Matrix const graph, unsigned int const vertex, char *visited) {
  
}

int is_all_connected(Matrix const graph) {
  char *visited = (char*)malloc(sizeof(char) * graph.size);
  for (unsigned int i = 0; i < graph.size; visited[i] = 0, ++i);

  unsigend int const startVertex = 0;
  mark_connected(graph, startVertex, visited);

  int isConnected = 1;
  for (unsigned int i = 0; i < graph.size; ++i) {
    if (visited[i] == 0) {
      isConnected = 0;
      break;
    }
  }

  free(visited);
  return isConnected;
}

void delete_matrix(Matrix *matrix) {
  for (unsigned int i = 0; i < matrix->size; ++i)
    free(matrix->body[i]);
  free(matrix->body);
}

int main() {
  char const *filename = "input.txt";
  Matrix graph = read_graph_from_file(filename);

  if (is_all_connected(graph))
    printf("Этот граф связный.\n");
  else
    printf("Этот граф несвязный.\n");

  delete_matrix(&matrix);
  return 0;
}
