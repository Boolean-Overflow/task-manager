#ifndef __TASK__
#include "../user/user.h"
#include "../list/list.h"
#define __TASK__
#define DONE 1
#define PENDING 0
#define EXPIRED -1

typedef struct Task {
  char id[10], name[150], description[255];
  char createdAt[25], expiresAt[25];
  int priority, state;
  User* responsable;
} Task;

Task* create_task(Task task);
void print_task(Task* task);
Task* taskcpy(Task* src);
List* find_matched_tasks(List* tasks, char* str);

#endif