#ifndef __TASK_MANAGER__
#include "list/list.h"
#include "stack/stack.h"
#include "queue/queue.h"
#include "user/user.h"
#include "team/team.h"
#include "task/task.h"
#define __TASK_MANAGER__


typedef struct TaskManager {
  List* users;
  List* teams;
  Queue* tasks;
  Stack* undo, * redo;
  int lastId;
} TaskManager;

void hello();


// TM* tm_init();
// TM* tm_insert(TM* tm, Task task);
// TM* tm_remove(TM* tm, char* id);


#endif