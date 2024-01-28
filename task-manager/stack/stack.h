#ifndef __STACK__
#define __STACK__
#include "../queue/queue.h"

typedef struct Stack {
  Queue* top;
} Stack;

Stack* stack_init();
int stack_empty(Stack* stack);
Stack* stack_push(Stack* stack, Queue* queue);
Queue* stack_pop(Stack** stack);
Queue* stack_peek(Stack* stack);

#endif