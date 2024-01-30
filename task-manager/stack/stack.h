#ifndef __STACK__
#define __STACK__
#include "../list/list.h"
#include "../task/task.h"

typedef struct Stack {
  List* top;
} Stack;

Stack* stack_init();
int stack_empty(Stack* stack);
Stack* stack_push(Stack* stack, Task* task);
Task* stack_pop(Stack** stack);
Task* stack_peek(Stack* stack);
void stack_clear(Stack** stack);
int is_stack_empty(Stack* stack);
int stack_print(Stack* stack);

#endif