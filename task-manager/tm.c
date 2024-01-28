#include<stdio.h>
#include<stdlib.h>
#include "tm.h"

TaskManager* tm_init() {
  TaskManager* instance = malloc(sizeof(TaskManager));
  if (!instance) {
    perror("Erro alocação");
    exit(1);
  }

  instance->users = NULL;
  // instance->teams = NULL;
  // instance->tasks = queue_init();
  // instance->undo = stack_init();
  // instance->redo = stack_init();
  instance->lastId[USER_LAST_ID_INDEX] = 0;
  instance->lastId[TASK_LAST_ID_INDEX] = 0;
  instance->lastId[TEAM_LAST_ID_INDEX] = 0;

  return instance;
}