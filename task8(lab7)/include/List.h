#pragma once
#include <stdlib.h>
#include "String.h"

typedef struct _ListElem {
  String value;
  struct _ListElem *next;
} ListElem;

typedef struct _List {
  ListElem *head;
} List;

List make_list();

void push_front(List *list, String const value);

void push_back(List *list, String const value);

String pop_back(List *list);

String pop_front(List *list);

void delete_list(List *list);
