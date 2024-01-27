#ifndef __TASK__
#include "../user/user.h"
#define __TASK__
#define DONE 1
#define PENDING 0
#define EXPIRED -1

typedef struct Task {
  int state;
  char* name, * id, * description;
  User* responsable;
} Task;

// Task create_task();
// Task* create_task();
// void print_task(Task task);

#endif