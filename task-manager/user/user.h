#ifndef __USER__
#define __USER__
#include "../list/list.h"

#define USERS_FILE_PATH  "users.db.txt"
#define SEPARATOR ", "

#define ID_MAX_SIZE 10
#define NAME_MAX_SIZE 25
#define USERNAME_MAX_SIZE 25
#define PASSWORD_MAX_SIZE 30
#define EMAIL_MAX_SIZE 30
#define PHONE_MAX_SIZE 13


typedef struct User {
  char id[ID_MAX_SIZE];
  char name[NAME_MAX_SIZE], username[USERNAME_MAX_SIZE], password[PASSWORD_MAX_SIZE];
  char email[EMAIL_MAX_SIZE], phone[PHONE_MAX_SIZE];
  char gender;
} User;

User* create_user(User user);
User* findByUsername(List* users, char* username);
void user_print(User* user);
int add_user(List** users, User user);
int connect_users(List** users);

User* login(List* users);
int signup(List** users);

#endif