#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "String.h"
#include "List.h"

int main() {
  List list = make_list();
  if (list.head == NULL)
    printf("Making list - OK\n");
  else
    printf("Making list - WRONG\n");

  String str = make_str();
  init_str(&str, 256);
  assert(add_symbol('a', &str) == OK);
  assert(add_symbol('b', &str) == OK);
  assert(add_symbol('c', &str) == OK);
  push_back(&list, str);
  // Should be ["abc"]
  int cmp1;
  assert(compare_string(&str, &list.head->value, &cmp1) == OK);
  if (cmp1 != 0)
    printf("Push back   - OK\n");
  else {
    printf("Push back   - WRONG\n");
    exit(1);
  }

  String strFromList = pop_back(&list);
  // Should be []
  int cmp2;
  assert(compare_string(&str, &strFromList, &cmp2) == OK);
  if (cmp2 != 0 && list.head == NULL)
    printf("Pop back    - OK\n");
  else
    printf("Pop back    - WRONG\n");

  delete_list(&list);
  deinit_str(&str);
  deinit_str(&strFromList);
  return 0;
}
