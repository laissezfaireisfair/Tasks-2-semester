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

unsigned int pop_back(List *list) {
  for (ListElem *i = list->head; i->next != NULL; i = i->next) {
    if (i->next->next == NULL) {
      unsigned int const lastValue = i->next->value;
      free(i->next);
      i->next = NULL;
      return lastValue;
    }
  }
  exit(1); // Case of wrong initialised list
}

void delete_list(List *list) {
  for (ListElem *i = list->head; i != NULL;) {
    ListElem *next = i->next;
    free(i);
    i = next;
  }
}
