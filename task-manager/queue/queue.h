#ifndef __QUEUE__
#define __QUEUE__
#include "../list/list.h"

// typedef struct TaskList {
//   Task* task;
//   struct TaskList* next;
// } TaskList;

// typedef struct Queue {
//   List* head, * tail;
//   struct Queue* next;
// } Queue;

typedef struct QueueTask {
  char id[10], name[150], description[255];
  char date[25];
  int priority, state;
  struct QueueTask* next, * prev;
}QueueTask;

typedef struct Queue {
  QueueTask* front, * end;
  struct Queue* next;
}Queue;

// // Matateu
Queue* queue_init();
// void queue_print(Queue* queue);
// Queue* queue_copy(Queue* source);
// Queue* enqueue(Queue* queue, Task task);
// Task dequeue(Queue** queue);

#endif