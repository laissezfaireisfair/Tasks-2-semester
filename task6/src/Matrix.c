#include "Errors.h"
#include "Matrix.h"

Matrix init_matrix(unsigned int const size) {
  Matrix this;
  this.size = size;
  this.body = (int**)malloc(sizeof(int*) * size);
  if (this.body == NULL)
    exit(RUNTIME_ERROR);
  for (unsigned int i = 0 ; i < size; ++i) {
    this.body[i] = (int*)malloc(sizeof(int) * size);
    if (this.body[i] == NULL)
      exit(RUNTIME_ERROR);
    for (unsigned int j = 0; j < size; ++j)
      this.body[i][j] = 0;
  }
  return this;
}

void delete_matrix(Matrix *this) {
  for (unsigned int i = 0; i < this->size; ++i)
    free(this->body[i]);
  free(this->body);
}

void add_edge(Matrix *this, unsigned int const begin, unsigned int const end) {
  if (begin >= this->size || end >= this->size)
    exit(INVALID_ARGUMENT);
  this->body[begin][end] = 1;
}

void del_edge(Matrix *this, unsigned int const begin, unsigned int const end) {
  if (begin >= this->size || end >= this->size)
    exit(INVALID_ARGUMENT);
  this->body[begin][end] = 0;
}

int check_edge(Matrix const *this, unsigned int const begin, unsigned int const end) {
  if (begin >= this->size || end >= this->size)
    exit(INVALID_ARGUMENT);
  return this->body[begin][end];
}
