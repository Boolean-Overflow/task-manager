#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tm.h"


//Inicializa o Gerenciador de tarefas
TaskManager* tm_init() {
  TaskManager* instance = malloc(sizeof(TaskManager));
  if (!instance) {
    perror("Erro alocação");
    exit(1);
  }

  instance->loggedUser = NULL;
  instance->users = NULL;
  instance->concludedTasks = stack_init();
  instance->tasks = queue_init();
  instance->lastId[USER_LAST_ID_INDEX] = 0;
  instance->lastId[TASK_LAST_ID_INDEX] = 0;
  instance->lastId[TEAM_LAST_ID_INDEX] = 0;

  return instance;
}

//Adiciona uma tarefa ao Gerenciador de Tarefas
Task* tm_add_task(TaskManager** instance, Task task) {
  if (!(*instance)) {
    puts("Instância inexistente");
    return NULL;
  }

  sprintf(task.id, "TASK-0%d", (*instance)->lastId[TASK_LAST_ID_INDEX]);

  Task* createdTask = create_task(task);

  (*instance)->tasks = enqueue((*instance)->tasks, createdTask);

  if (createdTask) (*instance)->lastId[TASK_LAST_ID_INDEX]++;

  return createdTask;
}

//Procura uma tarefa dado uma string

List* tm_find_matched_tasks(TaskManager* instance, char* str) {
  List* head = list_init();
  List* tmp = instance->tasks->head;
  while (tmp) {
    Task* task = tmp->data;
    if (strstr(task->name, str) || strstr(task->description, str)) {
      head = list_insert(head, taskcpy(task), task->id);
    }
    tmp = tmp->next;
  }

  tmp = instance->concludedTasks->top;
  while (tmp) {
    Task* task = tmp->data;
    if (strstr(task->name, str) || strstr(task->description, str)) {
      head = list_insert(head, taskcpy(task), task->id);
    }
    tmp = tmp->next;
  }

  return head;
}

int tm_print(TaskManager* instance, int option) {
  int total = 0;
  if (!instance) {
    puts("Instância inexistente");
    return total;
  }

  if (option == 1) total = queue_print(instance->tasks);
  else if (option == 2) total = stack_print(instance->concludedTasks);
  else {
    List* head = instance->users;
    while (head) {
      user_print(head->data);
      head = head->next;
      total++;
    }
  }

  if (total > 1) printf("\n[Total de %d %s]\n", total, option == 1 || option == 2 ? "Tarefas" : "Utilizadores");
  fflush(stdin);
  return total;
}

//Adiciona usuários ao Gerenciador de Tarefa
User* tm_add_user(TaskManager** instance, User user) {
  if (!(*instance)) {
    puts("Instância inexistente");
    return NULL;
  }

  sprintf(user.id, "USER-0%d", (*instance)->lastId[USER_LAST_ID_INDEX]);

  return add_user(&(*instance)->users, user);
}

//Executa uma Tarefa
Task* tm_execute_tasks(TaskManager** instance) {
  if (!(*instance)) {
    puts("Instância inexistente");
    return NULL;
  }
  Task* task = dequeue(&((*instance)->tasks));
  if (!task) return NULL;

  if (datecmp(getToday(), task->expiresAt)) task->state = TASK_STATUS_EXPIRED;
  else task->state = TASK_STATUS_DONE;

  (*instance)->concludedTasks = stack_push((*instance)->concludedTasks, task);

  return task;
}

