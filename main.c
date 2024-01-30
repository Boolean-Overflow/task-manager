#include<stdio.h>
#include<locale.h>
#include "task-manager/tm.h"
#include "utils/utils.h"
#include "pages/pages.h"

int main() {
  TaskManager* instance = tm_init();
  clearConsole();
  User* user = login_page(&(instance->users), instance->lastId[USER_LAST_ID_INDEX]);
  if (!user) return 0;
  //instance = Add_Task(instance); 
  //Task* task = Edit_Task(task, instance->users);
  Task* task;
  int a = Task_Expired(task);
  return 0;
}
