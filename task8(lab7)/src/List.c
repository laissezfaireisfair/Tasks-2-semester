#include <assert.h>
#include "List.h"

List make_list() {
  List list;
  list.head = NULL;
  return list;
}

void push_front(List *list, String const value) {
  ListElem *newElem = (ListElem*)malloc(sizeof(ListElem));
  copy_str(&value, &newElem->value);
  newElem->next = list->head;
  list->head = newElem;
}

void push_back(List *list, String const value) {
  ListElem *newElem = (ListElem*)malloc(sizeof(ListElem));
  copy_str(&value, &newElem->value);
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

String pop_back(List *list) {
  assert(list->head != NULL);

  // Deleting last element case
  if (list->head->next == NULL) {
    String lastValue = make_str();
    copy_str(&lastValue, &list->head->value);
    free(list->head);
    list->head = NULL;
    return lastValue;
  }

  // Deleting non-last element case
  ListElem *preLast;
  for (preLast = list->head; preLast->next->next != NULL; preLast = preLast->next);
  String lastValue = make_str();
  copy_str(&lastValue, &preLast->next->value);
  free(preLast->next);
  preLast->next = NULL;
  return lastValue;
}

String pop_front(List *list) {
  assert(list->head != NULL);

  String lastValue = make_str();
  copy_str(&lastValue, &list->head->value);
  ListElem *newHead = list->head->next;
  free(list->head);
  list->head = newHead;
  return lastValue;
}

void delete_list(List *list) {
  while (list->head != NULL) {
    ListElem *newHead = list->head->next;
    free(list->head);
    list->head = newHead;
  }
}
