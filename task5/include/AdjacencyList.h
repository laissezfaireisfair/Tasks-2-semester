#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "List.h"

typedef struct _AdjacencyList {
  unsigned int size;
  List *body;
} AdjacencyList;

AdjacencyList make_adj_list(unsigned int const size);

void add_edge(AdjacencyList *graph, unsigned int const begin, unsigned int const end);

void add_edges(AdjacencyList *graph, unsigned int const begin, List const ends);

void delete_adjacency_list(AdjacencyList *graph);
