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
  strcpy(task->createdAt, __TIMESTAMP__);
  strcpy(task->updatedAt, data.createdAt);
  strcpy(task->expiresAt, data.expiresAt);

  return task;
}

Task* update_task(Task* task) {
  if (!task) {
    puts("Tarefa inexistente!");
    return task;
  }
  strcpy(task->updatedAt, __TIMESTAMP__);

  return task;
}

void print_task(Task* task) {
  if (!task) {
    puts("Tarefa inexistente!");
    return;
  }

  puts(task->id);
  puts(task->name);
  if (strlen(task->description) > 0) puts(task->description);
  if (task->responsable) printf("Responsável: %s\n", task->responsable->username);
  printf("Data de criação: %s\n", task->createdAt);
  printf("Data de expiração: %s\n", task->expiresAt);
  printf("Última actualização: %s\n", task->updatedAt);
};

int task_cmp(Task* task, char* str) {
  if (!task) {
    puts("Task Inexistente");
    return 0;
  }

  return !strcmp(task->name, str) || !strcmp(task->description, str);
}