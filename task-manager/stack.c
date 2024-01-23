#include "./tm.h"
#include "./queue.c"
#include <stdio.h>
#include <stdlib.h>

typedef struct Task {
  char* name, * id, * description;
  int state;
}Task;

typedef struct Node {
   struct no* next;
   Task task;
}List;

typedef struct Queue {
  List* first, *last;
  struct Queue* next;
}Queue;

typedef struct Stack{
  Queue* top;
}Stack;

Stack* stack_init(){
  Stack* stack = malloc(sizeof(Stack));
  if(stack){
    stack->top = NULL;
    printf("Memoria alocada com sucesso!\n");
  }else{
    exit(EXIT_FAILURE);
  }
  return stack;
}

int stack_empty(Stack* stack){
  return (!!stack);
}

Stack* stack_push(Stack* stack, Queue* queue){
  queue->next = stack->top;
  stack->top = queue;
  return stack;
}

Queue* stack_pop(Stack** stack){
  Queue* queue = (*stack)->top;
  (*stack)->top = (*stack)->top->next;
  queue->next = NULL;
  return queue;
}

Queue* stack_peek(Stack* stack){
  Queue* copy = queue_copy(stack->top);
  return copy;
}
