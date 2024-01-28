#ifndef __TASK__
#include "../user/user.h"
#define __TASK__
#define DONE 1
#define PENDING 0
#define EXPIRED -1

typedef struct Task {
  char id[10], name[150], description[255];
  char createdAt[25], updatedAt[25], expiresAt[25];
  int priority, state;
  User* responsable;
} Task;

Task* create_task(Task task);
Task* update_task(Task* task);
void print_task(Task* task);
int task_cmp(Task* task, char* str);

#endif