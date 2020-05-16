#pragma once
#include <stdlib.h>

typedef struct _Matrix {
  unsigned int size;
  unsigned int start;
  unsigned int finish;
  int ** body;
} Matrix;

Matrix init_matrix(unsigned int const size);

void delete_matrix(Matrix *this);

error add_edge(Matrix *this, unsigned int const begin, unsigned int const end, int weight);

error del_edge(Matrix *this, unsigned int const begin, unsigned int const end);

int check_edge(Matrix const *this, unsigned int const begin, unsigned int const end);

error read_graph_from_file(char const *filename, Matrix * graph);
