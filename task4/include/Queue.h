#pragma once
#include <stdlib.h>
#include "List.h"

typedef struct _Queue {
  List body;
} Queue;

Queue make_queue();

void push(Queue *queue, unsigned int const value);

unsigned int pop(Queue *queue);

void delete_queue(Queue *queue);

int is_queue_empty(Queue const queue);
