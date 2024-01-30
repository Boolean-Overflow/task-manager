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
#define TM_PRINT_PENDING_TASKS 1
#define TM_PRINT_CONCLUDED_TASKS 2

typedef struct TaskManager {
  User* loggedUser;
  List* users;
  Queue* tasks;
  Stack* concludedTasks;
  int lastId[3];
} TaskManager;


TaskManager* tm_init();
Task* tm_add_task(TaskManager** instance, Task task);
int tm_print(TaskManager* instance, int option);
User* tm_add_user(TaskManager** instance, User user);
Task* tm_execute_tasks(TaskManager** instance);
List* tm_find_matched_tasks(TaskManager* instance, char* str);

#endif