#include <stdio.h>
#include "Errors.h"
#include "Constants.h"
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
      this.body[i][j] = -1;
  }
  return this;
}

void delete_matrix(Matrix *this) {
  for (unsigned int i = 0; i < this->size; ++i)
    free(this->body[i]);
  free(this->body);
}

error add_edge(Matrix *this, unsigned int const begin, unsigned int const end, int const weight) {
  if (begin >= this->size || end >= this->size)
    return INVALID_ARGUMENT;
  if (this->body[begin][end] != -1 || this->body[end][begin] != -1)
    return INVALID_ARGUMENT;
  this->body[begin][end] = weight;
  this->body[end][begin] = weight;
  return OK;
}

error del_edge(Matrix *this, unsigned int const begin, unsigned int const end) {
  if (begin >= this->size || end >= this->size)
    return INVALID_ARGUMENT;
  this->body[begin][end] = -1;
  this->body[end][begin] = -1;
  return OK;
}

int check_edge(Matrix const *this, unsigned int const begin, unsigned int const end) {
  if (begin >= this->size || end >= this->size)
    exit(INVALID_ARGUMENT);
  return this->body[begin][end];
}

error read_graph_from_file(Matrix * graph) {
  Constants const constants = get_constants();

  FILE *fin = fopen(constants.INPUT_FILENAME, "r");
  unsigned int numVertex;
  int const vertexReadStatus = fscanf(fin, "%u\n", &numVertex);
  if (vertexReadStatus == EOF || vertexReadStatus == 0)
    return BAD_INPUT;
  if (numVertex > constants.MAX_VERTEX)
    return BAD_INPUT;
  *graph = init_matrix(numVertex);

  int const startReadStatus = fscanf(fin, "%u\n", &graph->start);
  if (startReadStatus == EOF || startReadStatus == 0) {
    delete_matrix(graph);
    fclose(fin);
    return BAD_INPUT;
  }

  int const finishReadStatus = fscanf(fin, "%u\n", &graph->finish);
  if (finishReadStatus == EOF || finishReadStatus == 0) {
    delete_matrix(graph);
    fclose(fin);
    return BAD_INPUT;
  }

  if (graph->start >= numVertex || graph->finish >= numVertex) {
    delete_matrix(graph);
    fclose(fin);
    return BAD_INPUT;
  }

  unsigned int numEdges;
  int const edgesReadStatus = fscanf(fin, "%u\n", &numEdges);
  if (edgesReadStatus == EOF || edgesReadStatus == 0) {
    delete_matrix(graph);
    fclose(fin);
    return BAD_INPUT;
  }
  if (numEdges > constants.MAX_EDGES) {
    delete_matrix(graph);
    fclose(fin);
    return BAD_INPUT;
  }

  for (unsigned int i = 0; i < numEdges; ++i) {
    unsigned int begin, end, weight;
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
    int const readWeightStatus = fscanf(fin, "%u", &weight);
    if (readWeightStatus == EOF || readWeightStatus == 0) {
      delete_matrix(graph);
      fclose(fin);
      return BAD_INPUT;
    }

    if (end >= numVertex || begin >= numVertex || weight > constants.MAX_INT)
      return BAD_INPUT;

    error const addStatus = add_edge(graph, begin, end, (int)weight);
    if (addStatus != OK) {
      delete_matrix(graph);
      fclose(fin);
      return addStatus;
    }
  }

  fclose(fin);
  return OK;
}
