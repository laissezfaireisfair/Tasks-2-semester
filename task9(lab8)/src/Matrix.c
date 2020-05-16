#include <stdio.h>
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
  this->body[begin][end] += 1;
  this->body[end][begin] += 1;
}

void del_edge(Matrix *this, unsigned int const begin, unsigned int const end) {
  if (begin >= this->size || end >= this->size)
    exit(INVALID_ARGUMENT);
  this->body[begin][end] -= 1;
  this->body[end][begin] -= 1;
}

int check_edge(Matrix const *this, unsigned int const begin, unsigned int const end) {
  if (begin >= this->size || end >= this->size)
    exit(INVALID_ARGUMENT);
  return this->body[begin][end];
}

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
  }

  fclose(fin);
  return OK;
}
