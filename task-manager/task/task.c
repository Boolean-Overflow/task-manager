#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "task.h"

//Cria uma Tarefa
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

//Retorna a cópia de uma tarefa
Task* taskcpy(Task* src) {
  if (!src) return NULL;
  return create_task(*src);
}

//Mostra os campos de uma tarefa
void print_task(Task* task) {
  if (!task) {
    puts("Tarefa inexistente!");
    return;
  }

  puts("");
  printf("ID %s\n", task->id);
  printf("Nome: %s\n", task->name);
  if (strlen(task->description) > 1) printf("Descrição: %s\n", task->description);
  printf("Prioridade: %d\n", task->priority);
  printf("Estado Actual:");
  if (task->state == TASK_STATUS_DONE) puts("Concluída");
  if (task->state == TASK_STATUS_PENDING) puts("Pendente");
  if (task->state == TASK_STATUS_EXPIRED) puts("Expirado");

  if (task->responsable) printf("Responsável: %s\n", task->responsable->username);
  printf("Data de criação: %d/%d/%d\n", task->createdAt.day, task->createdAt.month, task->createdAt.year);
  printf("Data de expiração: %d/%d/%d\n", task->expiresAt.day, task->expiresAt.month, task->expiresAt.year);
  puts("");
  fflush(stdin);
};
