#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "List.h"

typedef struct _AdjacencyList {
  unsigned int size;
  List *body;
} AdjacencyList;

AdjacencyList make_adj_list(valType const size);

void add_edge(AdjacencyList *graph, valType const begin, valType const end);

void delete_adjacency_list(AdjacencyList *graph);
