#ifndef __TASK__
#include "../user/user.h"
#include "../list/list.h"
#include "../../utils/utils.h"
#define __TASK__

#define TASK_NAME_MAX_SIZE 150
#define TASK_DESCRIPTION_MAX_SIZE 255

#define TASK_STATUS_DONE 1
#define TASK_STATUS_PENDING 0
#define TASK_STATUS_EXPIRED -1

typedef struct Task {
  char id[ID_MAX_SIZE], name[TASK_NAME_MAX_SIZE], description[TASK_DESCRIPTION_MAX_SIZE];
  Date createdAt, expiresAt;
  int priority, state;
  User* responsable;
} Task;

Task* create_task(Task task);
void print_task(Task* task);
Task* taskcpy(Task* src);

#endif