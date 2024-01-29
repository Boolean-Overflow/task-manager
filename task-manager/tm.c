#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tm.h"

TaskManager* tm_init() {
  TaskManager* instance = malloc(sizeof(TaskManager));
  if (!instance) {
    perror("Erro alocação");
    exit(1);
  }

  instance->users = NULL;
  // instance->teams = NULL;
  instance->tasks = queue_init();
  instance->undo = stack_init();
  instance->redo = stack_init();
  instance->lastId[USER_LAST_ID_INDEX] = 0;
  instance->lastId[TASK_LAST_ID_INDEX] = 0;
  instance->lastId[TEAM_LAST_ID_INDEX] = 0;

  return instance;
}

TaskManager* tm_add_task(TaskManager* instance, Task task) {
  if (!instance) {
    puts("Instância inexistente");
    return NULL;
  }

  snprintf(task.id, 10, "TASK-0%d", instance->lastId[TASK_LAST_ID_INDEX]++);

  Task* createdTask = create_task(task);

  if (!stack_empty(instance->redo))
    instance->undo = stack_push(instance->undo, queuecpy(instance->tasks));

  instance->tasks = enqueue(instance->tasks, createdTask);

  instance->redo = stack_push(instance->redo, queuecpy(instance->tasks));

  return instance;
}

TaskManager* tm_undo(TaskManager* instance) {
  if (!instance) {
    puts("Instância inexistente");
    return NULL;
  }

  Queue* q = stack_pop(&(instance->undo));
  instance->redo = stack_push(instance->redo, queuecpy(instance->tasks));
  queue_clear(&instance->tasks);
  instance->tasks = q;

  return instance;
}

TaskManager* tm_redo(TaskManager* instance) {
  if (queuecmp(stack_peek(instance->redo), instance->tasks)) return instance;

  Queue* q = stack_pop(&(instance->redo));
  instance->undo = stack_push(instance->undo, queuecpy(instance->tasks));
  queue_clear(&(instance->tasks));
  instance->tasks = q;

  return instance;
}