#ifndef __QUEUE__
#define __QUEUE__
#include "../list/list.h"
#include "../task/task.h"

typedef struct TaskList {
 Task task;
 struct TaskList* next; 
 struct TaskList* prev;
} TaskList;

typedef struct Queue {
  TaskList* front, * end;
  struct Queue* next;
}Queue;

// // Matateu
//Queue* queue_init();
// void queue_print(Queue* queue);
// Queue* queue_copy(Queue* queue);
// Queue* enqueue(Queue* queue, TaskList task);
// Task dequeue(Queue** queue);

#endif