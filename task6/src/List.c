#include <assert.h>
#include "List.h"

List make_list() {
  List list;
  list.head = NULL;
  return list;
}

void push_front(List *list, unsigned int const value) {
  ListElem *newElem = (ListElem*)malloc(sizeof(ListElem));
  newElem->value = value;
  newElem->next = list->head;
  list->head = newElem;
}

void push_back(List *list, unsigned int const value) {
  ListElem *newElem = (ListElem*)malloc(sizeof(ListElem));
  newElem->value = value;
  newElem->next = NULL;

  if (list->head == NULL) {
    list->head = newElem;
    return;
  }

  ListElem *last;
  for (ListElem *i = list->head; i != NULL; i = i->next)
    last = i;
  last->next = newElem;
}

unsigned int pop_back(List *list) {
  assert(list->head != NULL);

  // Deleting last element case
  if (list->head->next == NULL) {
    unsigned int const lastValue = list->head->value;
    free(list->head);
    list->head = NULL;
    return lastValue;
  }

  // Deleting non-last element case
  ListElem *preLast;
  for (preLast = list->head; preLast->next->next != NULL; preLast = preLast->next);
  unsigned int const lastValue = preLast->next->value;
  free(preLast->next);
  preLast->next = NULL;
  return lastValue;
}

unsigned int pop_front(List *list) {
  assert(list->head != NULL);

  unsigned int const lastValue = list->head->value;
  ListElem *newHead = list->head->next;
  free(list->head);
  list->head = newHead;
  return lastValue;
}

void delete_list(List *list) {
  while (list->head != NULL)
    pop_front(list);
}
