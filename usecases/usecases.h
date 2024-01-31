#ifndef __PAGES__
#define __PAGES__
#include "../task-manager/tm.h"
#include "../utils/utils.h"

int loginUC(TaskManager** instance);
void removeTaskUC(TaskManager** instance);
void findTaskUC(TaskManager** instance);
void listUsersUC(TaskManager** instance);
Task* addTaskUC(TaskManager** instance);

#endif