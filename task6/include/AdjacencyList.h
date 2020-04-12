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

int check_edge(AdjacencyList *graph, unsigned int const begin, unsigned int const end);

// Doing nothing if edge does not exist
void delete_edge(AdjacencyList *graph, unsigned int const begin, unsigned int const end);

void delete_adjacency_list(AdjacencyList *graph);
