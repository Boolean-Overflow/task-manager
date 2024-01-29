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
    print_task(tmp->data);
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
  while (current && task->priority <= ((Task*)(current->data))->priority)
    current = current->next;

  if (!current) {
    queue->tail->next = node;
    node->prev = queue->tail;
    queue->tail = node;
  }
  else {
    node->prev = current->prev;
    node->next = current;
    if (current->prev)  current->prev->next = node;
    else queue->head = node;
    current->prev = node;
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
    return NULL;
  }

  Queue* dest = queue_init();
  List* tmp = src->head;
  while (tmp) {
    Task* task = create_task(*((Task*)(tmp->data)));
    dest = enqueue(dest, task);
    tmp = tmp->next;
  }
  return dest;
}

void queue_clear(Queue** queue) {
  if (*queue) {
    list_clear(&(*queue)->head);
    (*queue)->tail = NULL;
    free(*queue);
  }
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