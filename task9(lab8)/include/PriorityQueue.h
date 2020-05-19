#pragma once
#include <stdlib.h>
#include "List.h"

// Minimum priority number pops first

typedef struct _PriorityQueue {
  List body;
} PriorityQueue;

PriorityQueue make_queue();

void push_to_queue(PriorityQueue *queue, valType const value);

valType pop_from_queue(PriorityQueue *queue);

void delete_queue(PriorityQueue *queue);

int is_queue_empty(PriorityQueue const queue);
