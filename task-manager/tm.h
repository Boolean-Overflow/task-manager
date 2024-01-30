#ifndef __TASK_MANAGER__
#include "list/list.h"
#include "stack/stack.h"
#include "queue/queue.h"
#include "user/user.h"
#include "team/team.h"
#include "task/task.h"
#define __TASK_MANAGER__

#define USER_LAST_ID_INDEX 0
#define TASK_LAST_ID_INDEX 1
#define TEAM_LAST_ID_INDEX 2

#define TM_PRINT_USERS 0
#define TM_PRINT_TASKS 1

typedef struct TaskManager {
  User* loggedUser;
  List* users;
  int lastId[3];
  // List* teams;
  Queue* tasks;
  Stack* undo, * redo;
} TaskManager;


TaskManager* tm_init();
Task* tm_add_task(TaskManager** instance, Task task);
int tm_undo(TaskManager** instance);
int tm_redo(TaskManager** instance);
int tm_print(TaskManager* instance, int option);
User* tm_add_user(TaskManager** instance, User user);
Task* tm_execute_tasks(TaskManager** instance);
void tm_create_task(TaskManager** instance);
#endif