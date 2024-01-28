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

typedef struct TaskManager {
  List* users;
  // List* teams;
  // Queue* tasks;
  // Stack* undo, * redo;
  int lastId[3];
} TaskManager;


TaskManager* tm_init();
// TM* tm_insert(TM* tm, Task task);
// TM* tm_remove(TM* tm, char* id);


#endif