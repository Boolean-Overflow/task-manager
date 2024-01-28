#ifndef __QUEUE__
#define __QUEUE__
#include "../list/list.h"
#include "../task/task.h"

typedef struct Queue {
  List* head, * tail;
  struct Queue* next;
} Queue;

// // Matateu
Queue* queue_init();
int is_queue_empty(Queue* queue);
int queue_print(Queue* queue);
Queue* queuecpy(Queue* src);
Queue* enqueue(Queue* queue, Task* task);
Task* dequeue(Queue** queue);
void queue_clear(Queue** queue);
int queuecmp(Queue* queue1, Queue* queue2);

#endif