#include "Queue.h"

Queue make_queue() {
  Queue queue;
  queue.body = make_list();
  return queue;
}

void push(Queue *queue, unsigned int const value) {
  push_front(&queue->body, value);
}

unsigned int pop(Queue *queue) {
  return pop_back(&queue->body);
}

void delete_queue(Queue *queue) {
  delete_list(&queue->body);
}
