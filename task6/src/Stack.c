#include "Stack.h"

Stack make_stack() {
  Stack stack;
  stack.body = make_list();
  return stack;
}

void push_to_stack(Stack *stack, unsigned int const value) {
  push_front(&stack->body, value);
}

unsigned int pop_from_stack(Stack *stack) {
  return pop_front(&stack->body);
}

void delete_stack(Stack *stack) {
  delete_list(&stack->body);
}

int is_stack_empty(Stack const stack) {
  if (stack.body.head == NULL)
    return 1;
  return 0;
}
