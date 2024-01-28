#include<stdio.h>
#include<locale.h>
#include "task-manager/tm.h"
#include "utils/utils.h"
#include "pages/pages.h"

int main() {
  TaskManager* instance = tm_init();
  clearConsole();
  // User* user = login_page(&(instance->users), instance->lastId[USER_LAST_ID_INDEX]);
  // if (!user) return 0;
  Task t1 = { "", "Tratar da Loiça1", "Lavar os pratos do jantar", __TIMESTAMP__, __TIMESTAMP__ , __TIMESTAMP__, 1, 0, NULL };
  Task t2 = { "", "Tratar da Loiça2", "Lavar os pratos do jantar", __TIMESTAMP__, __TIMESTAMP__ , __TIMESTAMP__, 2, 0, NULL };
  Task t3 = { "", "Tratar da Loiça3", "Lavar os pratos do jantar", __TIMESTAMP__, __TIMESTAMP__ , __TIMESTAMP__, 3, 0, NULL };
  Task t4 = { "", "Tratar da Loiça4", "Lavar os pratos do jantar", __TIMESTAMP__, __TIMESTAMP__ , __TIMESTAMP__, 4, 0, NULL };
  Task t5 = { "", "Tratar da Loiça5", "Lavar os pratos do jantar", __TIMESTAMP__, __TIMESTAMP__ , __TIMESTAMP__, 5, 0, NULL };

  instance = tm_add_task(instance, t1);
  instance = tm_add_task(instance, t2);
  instance = tm_add_task(instance, t3);
  instance = tm_add_task(instance, t4);
  instance = tm_add_task(instance, t5);

  // queue_print(instance->tasks);
  List* t = instance->tasks->head;
  int c = 0;
  while(t) c++, t = t->next;
  printf("%d", c);

  return 0;
}
