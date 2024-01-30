#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"

Task* create_task(Task data) {
  Task* task = malloc(sizeof(Task));
  if (!task) {
    perror("Erro de Alocação");
    exit(1);
  }
  task->priority = data.priority;
  task->state = data.state;
  task->responsable = data.responsable;
  strcpy(task->id, data.id);
  strcpy(task->name, data.name);
  strcpy(task->description, data.description);
  task->createdAt = data.createdAt;
  task->expiresAt = data.expiresAt;
  return task;
}

Task* taskcpy(Task* src) {
  if (!src) return NULL;
  return create_task(*src);
}

void print_task(Task* task) {
  if (!task) {
    puts("Tarefa inexistente!");
    return;
  }
  puts("====================");
  puts(task->id);
  puts(task->name);
  printf("Prioridade: %d\n", task->priority);
  if (strlen(task->description) > 0) puts(task->description);
  if (task->responsable) printf("Responsável: %s\n", task->responsable->username);
  printf("Data de criação: %s\n", task->createdAt);
  printf("Data de expiração: %s\n", task->expiresAt);
  fflush(stdin);
};

List* find_matched_tasks(List* tasks, char* str) {
  if (!tasks) return NULL;
  List* head = list_init();
  while (tasks) {
    Task* task = tasks->data;
    if (strstr(task->name, str) || strstr(task->description, str)) {
      head = list_insert(head, taskcpy(task), task->id);
    }
    tasks = tasks->next;
  }

  return head;
}

