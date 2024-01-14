#include<tm.h>
#include<stack.c>
#include<queue.c>

typedef struct Task{
  char* name, * id, * description;
  int state;
}Task;

typedef struct no {
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

