#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "queue.h"

Queue* queue_init() {
  Queue* Q = (Queue*)malloc(sizeof(Queue));

  if (!Q) {
    printf("Erro de alocacao de memória\n");
    exit(1);
  }
  Q->front = NULL;
  Q->end = NULL;
  return Q;
}
QueueTask* create_node(char name[], char description[], int last_id, int priority) {
  QueueTask* node = (QueueTask*)malloc(sizeof(QueueTask));
  if (last_id) {
    node->id[0] = 'T';
    strcat(node->id, "000");
  }
  if (!node) {
    printf("Erro de alocação de memória\n");
    exit(1);
  }

  strcpy(node->name, name);
  strcpy(node->description, description);
  node->priority = priority;
  node->next = NULL;
  node->prev = NULL;
  return node;
}
int IsEmptyQueue(Queue* Q) {
  if (!Q->front)
    printf("Fila vazia\n");
  return Q->front == NULL;
}
// void queue_print(Queue* queue) {
//   if (!queue) {
//     printf("Fila nao criada\n");
//     exit(1);
//   }
//   if (!IsEmptyQueue(queue)) {
//     Task* current = queue->front;

//     printf("<=============================FILA==================================>:\n");
//     //print_task(task);
//     printf("\n====================================================================\n");
//   }
//   exit(1);
// };

// Queue* queue_copy(Queue* source) {
//   if (!source) {
//     printf("fila nao criada\n");
//     return NULL;
//   }
//   return source;
// };
// Queue* Enqueue(Queue* queue, Task* task) {

//   if (!queue) {
//     printf("fila nao criada\n");
//     return NULL;
//   }
//   Task* task = create_node(task);
//   if (!task) return queue;

//   if (IsEmptyQueue(queue)) {
//     queue->front = task;
//     queue->end = task;
//     return queue->front;
//   }
//   Task* current = queue->front;
//   while (current->priority >= task->priority && current->next)
//     current = current->next;
//   if (current == queue->front) {
//     queue->front->prev = task;
//     task->next = queue->front;
//     task->prev = NULL;
//     queue->front = task;
//   }
//   else if (current != queue->end) {
//     task->prev = current->prev;
//     task->next = current;
//     current->prev->next = task;
//     current->prev = task;
//   }
//   else {
//     task->prev = current;
//     current->next = task;
//     queue->end = task;
//   }
//   return queue;
// }

// Task* dequeue(Queue** queue) {
//   if (IsEmptyQueue(*queue))
//     exit(1);

//   List* temp = (*queue)->front;
//   Task* task = temp->task;
//   (*queue)->front = temp->next;
//   if (!(*queue)->front)
//     (*queue)->end = NULL;
//   free(temp);
//   return task;
// };