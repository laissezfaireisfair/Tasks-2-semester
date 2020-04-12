#pragma once

typedef struct _Matrix {
  unsigned int size;
  int ** body;
} Matrix;

Matrix init_matrix(unsigned int const size);

void delete_matrix(Matrix *this);

void add_edge(Matrix *this, unsigned int const begin, unsigned int const end);

void del_edge(Matrix *this, unsigned int const begin, unsigned int const end);

int check_edge(Matrix const *this, unsigned int const begin, unsigned int const end);
