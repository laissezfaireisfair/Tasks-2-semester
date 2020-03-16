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

void delete_list(List *list) {
  for (ListElem *i = list->head; i != NULL;) {
    ListElem *next = i->next;
    free(i);
    i = next;
  }
}
