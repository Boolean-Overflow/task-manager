#ifndef  __UTILS__
#define __UTILS__
#include "../task-manager/tm.h"

void clearConsole();
void pause(char* str);

User* login_page(List** users, int lastId);

#endif