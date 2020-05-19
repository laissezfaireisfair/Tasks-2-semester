#include "PriorityQueue.h"

Queue make_queue() {
  Queue queue;
  queue.body = make_list();
  return queue;
}

void push_to_queue(Queue *queue, PriorityVal const value) {
  ListElem * const newElem = (ListElem*)malloc(sizeof(ListElem));
  newElem->value = value;
  if (queue->body.head->value.priority < value.priority) {
    newElem->next = queue->body.head;
    queue->body.head = newElem;
    return;
  }
  ListElem *i = queue->body.head;
  while (i->next != NULL && i->next->value.priority >= value.priority) {}
  newElem->next = i->next;
  i->next = newElem;
}

valType pop_from_queue(Queue *queue) {
  return pop_front(&queue->body);
}

void delete_queue(Queue *queue) {
  delete_list(&queue->body);
}

int is_queue_empty(Queue const queue) {
  if (queue.body.head == NULL)
    return 1;
  return 0;
}
