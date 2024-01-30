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

  instance->loggedUser = NULL;
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

Task* tm_add_task(TaskManager** instance, Task task) {
  if (!(*instance)) {
    puts("Instância inexistente");
    return NULL;
  }

  sprintf(task.id, "TASK-0%d", (*instance)->lastId[TASK_LAST_ID_INDEX]++);

  Task* createdTask = create_task(task);

  if (!stack_empty((*instance)->redo))
    (*instance)->undo = stack_push((*instance)->undo, queuecpy((*instance)->tasks));

  (*instance)->tasks = enqueue((*instance)->tasks, createdTask);

  (*instance)->redo = stack_push((*instance)->redo, queuecpy((*instance)->tasks));

  return createdTask;
}

int tm_print(TaskManager* instance, int option) {
  int total = 0;
  if (!instance) {
    puts("Instância inexistente");
    return total;
  }

  if (option == 1) total = queue_print(instance->tasks);
  else {
    List* head = instance->users;
    while (head) {
      user_print(head->data);
      head = head->next;
      total++;
    }
  }

  printf("\n[Total de %d %s]\n", total, option == 1 ? "Tarefas" : "Utilizadores");
  return total;
}

int tm_undo(TaskManager** instance) {
  if (!(*instance)) {
    puts("Instância inexistente");
    return 0;
  }

  Queue* q = stack_pop(&((*instance)->undo));
  (*instance)->redo = stack_push((*instance)->redo, queuecpy((*instance)->tasks));
  queue_clear(&(*instance)->tasks);
  (*instance)->tasks = q;

  return 1;
}

int tm_redo(TaskManager** instance) {
  if (!(*instance)) {
    puts("Instância inexistente");
    return 0;
  }

  if (queuecmp(stack_peek((*instance)->redo), (*instance)->tasks)) return 1;

  Queue* q = stack_pop(&((*instance)->redo));
  (*instance)->undo = stack_push((*instance)->undo, queuecpy((*instance)->tasks));
  queue_clear(&((*instance)->tasks));
  (*instance)->tasks = q;

  return 1;
}

User* tm_add_user(TaskManager** instance, User user) {
  if (!(*instance)) {
    puts("Instância inexistente");
    return NULL;
  }

  sprintf(user.id, "USER-0%d", (*instance)->lastId[USER_LAST_ID_INDEX]);

  return add_user(&(*instance)->users, user);
}

Task* tm_execute_tasks(TaskManager** instance) {
  if (!(*instance)) {
    puts("Instância inexistente");
    return NULL;
  }

  return dequeue(&(*instance)->tasks);
}

