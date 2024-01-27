#ifndef __USER__
#define __USER__
#include "../list/list.h"

typedef struct User {
  int id;
  char name[25], username[25], password[30];
  char gender;
} User;

User* user_create(User user);
User* findByUsername(List* users, char* username);
void user_print(User* user);

#endif