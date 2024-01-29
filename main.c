#include<stdio.h>
#include<locale.h>
#include "task-manager/tm.h"
#include "utils/utils.h"
#include "pages/pages.h"

int main() {
  TaskManager* instance = tm_init();
  User* user = NULL;

//TMP
  Task t1 = { "", "Tratar da Loiça1", "Lavar os pratos do jantar", __TIMESTAMP__ , __TIMESTAMP__, 3, 0, NULL };
  Task t2 = { "", "Tratar da Loiça2", "Lavar os pratos do jantar", __TIMESTAMP__ , __TIMESTAMP__, 1, 0, NULL };
  Task t3 = { "", "Tratar da Loiça2", "Lavar os pratos do jantar", __TIMESTAMP__, __TIMESTAMP__, 7, 0, NULL };
  Task t4 = { "", "Tratar da Loiça4", "Lavar os pratos do jantar", __TIMESTAMP__, __TIMESTAMP__, 9, 0, NULL };
  Task t5 = { "", "Tratar da Loiça5", "Lavar os pratos do jantar", __TIMESTAMP__, __TIMESTAMP__, 0, 0, NULL };
  Task t6 = { "", "Tratar da Loiça6", "Lavar os pratos do jantar", __TIMESTAMP__, __TIMESTAMP__, 7, 0, NULL };

  instance = tm_add_task(instance, t1);
  instance = tm_add_task(instance, t2);
  instance = tm_add_task(instance, t3);
  instance = tm_add_task(instance, t4);
  instance = tm_add_task(instance, t5);
  instance = tm_add_task(instance, t6);

//

login:
  user = login_page(&(instance->users), instance->lastId[USER_LAST_ID_INDEX]);
  if (dashboard(instance, user)) {
    user_print(user);
    // logout(user);
    goto login;
  }

end:
  puts("Obrigado ;)");
  puts("Matateu André - 20212549🤓");
  puts("Lukeny Silva - 20220718😎");
  puts("Kélsio Mateus -  20221473🧑🏿‍💻");
  return 0;
}
