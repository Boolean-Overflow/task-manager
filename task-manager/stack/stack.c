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

Stack* stack_push(Stack* stack, Task* task) {
  List* node = list_create_node(task, task->id);
  node->next = stack->top;
  stack->top = node;

  return stack;
}

int is_stack_empty(Stack* stack) {
  if (!stack) {
    puts("Pilha Inexistente!");
    return -1;
  }

  return stack->top == NULL;
}

int stack_print(Stack* stack) {
  if (!stack) {
    puts("Pilha Inexistente");
    return -1;
  }

  if (is_stack_empty(stack)) return 0;

  int total = 0;

  List* head = stack->top;
  while (head) {
    print_task(head->data);
    head = head->next;
    total++;
  }
  return total;
}

Task* stack_pop(Stack** stack) {
  if (!(*stack)) {
    puts("Pilha Inexistente\n");
    return NULL;
  }

  if (!((*stack)->top)) {
    puts("Pilha vazia");
    return NULL;
  }

  List* tmp = (*stack)->top;
  Task* task = tmp->data;
  (*stack)->top = tmp->next;

  free(tmp);

  return task;
}

Task* stack_peek(Stack* stack) {
  if (!stack || !stack->top) {
    puts("Pilha Vazia");
    return NULL;
  }
  return stack->top->data;
}

void stack_clear(Stack** stack) {
  while (is_stack_empty(*stack)) {
    List* tmp = (*stack)->top;
    (*stack)->top = tmp->next;
    free(tmp->data);
    free(tmp);
  }
  free(*stack);
  *stack = NULL;
}
