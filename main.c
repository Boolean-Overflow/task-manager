#include<stdio.h>
#include<locale.h>
#include "task-manager/tm.h"
#include "utils/utils.h"

int main() {
  TaskManager* instance = tm_init();

  User* user = login_page(&(instance->users), instance->lastId[USER_LAST_ID_INDEX]);
  if (!user) return 0;
  return 0;
}
