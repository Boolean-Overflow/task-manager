#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "queue.h"
#include "../list/list.h"
#include "../task/task.h"

Queue* queue_init() {
  Queue* queue = (Queue*)malloc(sizeof(Queue));

  if (!queue) {
    perror("Erro de alocacao de memória");
    exit(1);
  }
  queue->front = NULL;
  queue->end = NULL;
  return queue;
}

int IsEmptyQueue(Queue* queue) {
  if (!queue->front)
    printf("Fila vazia\n");
  return queue->front == NULL;
}

void queue_print(Queue* queue) {
  if (!queue) {
    printf("Fila nao criada\n");
    exit(1);
  }
  if (!IsEmptyQueue(queue)) {
    TaskList* aux = queue->front;
    printf("<=============================FILA==================================>:\n");
    while (aux) {
      print_task(&(aux->task));
      aux = aux->next;
    }
    printf("\n====================================================================\n");
  }
  exit(1);
}
Queue* enqueue(Queue* queue, Task t){
  if (!queue) {
    printf("Fila nao criada\n");
    return NULL;
  }
  TaskList* node = malloc(sizeof(TaskList));
  node->task = create_task(t);
  if (IsEmptyQueue(queue)) {
    queue->front = node;
    queue->end = node;
    return queue;
  }
  TaskList* current = queue->front;
  while (current->task.priority >= node->task.priority && current->next)
    current = current->next;
  if (current == queue->front) {
    queue->front->prev = node;
    node->next = queue->front;
    node->prev = NULL;
    queue->front = node;
  }
   else if (current != queue->end) {
    node->prev = current->prev;
    node->next = current;
    current->prev->next = node;
    current->prev = node;
   }
   else {
   node->prev = current;
   current->next = node;
   queue->end = node;
}
return queue;
}

Queue* queue_copy(Queue* queue) {
  if (!queue) {
    printf("Fila nao criada\n");
    return NULL;
  }
  TaskList* aux = queue->front;
  Queue* copy = malloc(sizeof(Queue));
  if(!copy){
    perror("Memoria nao alocada");
    return NULL;
  }
  while (1) {
    copy = enqueue(copy, aux->task);
    aux = aux->next;
  }
  
  return queue;
}

Task dequeue(Queue** queue) {
  if (IsEmptyQueue(*queue)) exit(1);
  TaskList* temp = (*queue)->front;
  Task task = temp->task;
  (*queue)->front = temp->next;
  if (!(*queue)->front)
    (*queue)->end = NULL;
  free(temp);
  return task;
}