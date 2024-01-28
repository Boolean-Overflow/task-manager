#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "queue.h"

Queue* queue_init() {
  Queue* queue = (Queue*)malloc(sizeof(Queue));
  if (!queue) {
    perror("Erro de alocacao de memória");
    exit(1);
  }
  queue->head = NULL;
  queue->tail = NULL;
  return queue;
}

int is_queue_empty(Queue* queue) {
  return queue->head == NULL;
}

int queue_print(Queue* queue) {
  if (!queue) {
    puts("Fila nao criada");
    return -1;
  }

  if (is_queue_empty(queue)) {
    puts("Fila vazia!");
    return 0;
  }

  int count = 0;
  List* tmp = queue->head;
  while (tmp) {
    print_task((Task*)(tmp->data));
    fflush(stdin);
    tmp = tmp->next;
    count++;
  }

  return count;
}

Queue* enqueue(Queue* queue, Task* task) {
  if (!queue) {
    printf("Fila nao criada\n");
    return NULL;
  }

  List* node = list_create_node(task, task->id);

  if (!queue->head) {
    queue->head = node;
    queue->tail = node;

    return queue;
  }

  List* current = queue->head;
  while (((Task*)(current->data))->priority >= task->priority && current->next)
    current = current->next;
  if (current == queue->head) {
    queue->head->prev = node;
    current->next = queue->head;
    current->prev = NULL;
    queue->head = node;
  }
  else if (current != queue->tail) {
    node->prev = current->prev;
    node->next = current;
    current->prev->next = node;
    current->prev = node;
  }
  else {
    node->prev = current;
    current->next = node;
    queue->tail = node;
  }
  return queue;
}

Task* dequeue(Queue** queue) {
  if (is_queue_empty(*queue)) {
    puts("Fila Vazia");
    return NULL;
  }

  List* temp = (*queue)->head;
  Task* task = temp->data;

  (*queue)->head = temp->next;

  if (!(*queue)->head)
    (*queue)->tail = NULL;

  free(temp);

  return task;
}

Queue* queuecpy(Queue* src) {
  if (!src) {
    return src;
  }

  Queue* dest = queue_init();
  List* tmp = src->head;
  while (tmp) {
    dest = enqueue(dest, tmp->data);
    tmp = tmp->next;
  }

  return dest;
}

void queue_clear(Queue** queue) {
  if (!(*queue)) return;

  list_clear(&((*queue)->head));
  (*queue)->tail = NULL;
  free(queue);

  *queue = NULL;
}

int queuecmp(Queue* queue1, Queue* queue2) {
  List* t1 = queue1->head, * t2 = queue2->head;
  while (t1 && t2) {
    if (strcmp(t1->id, t2->id)) return 0;
    t1 = t1->next;
    t2 = t2->next;
  }

  return t1 == t2;
}