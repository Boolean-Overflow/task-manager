#include<stdio.h>
#include<stdlib.h>
#include "stack.h"

Stack* stack_init() {
  Stack* stack = malloc(sizeof(Stack));
  if (!stack) {
    perror("Erro de Alocação");
    exit(1);
  }
  stack->top = NULL;

  return stack;
}

int stack_empty(Stack* stack) {
  if (!stack) {
    perror("Stack Inexistente");
    return 0;
  }
  return stack->top == NULL;
}

Stack* stack_push(Stack* stack, Queue* queue) {
  queue->next = stack->top;
  stack->top = queue;

  return stack;
}

Queue* stack_pop(Stack** stack) {
  Queue* queue = (*stack)->top;
  (*stack)->top = (*stack)->top->next;
  queue->next = NULL;
  return queue;
}

Queue* stack_peek(Stack* stack) {
  if (!stack || !stack->top) {
    return NULL;
  }

  return stack->top;
}
