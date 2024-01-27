#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "user.h"

User* user_create(User user) {
  User* createdUser = (User*)malloc(sizeof(User));
  if (!createdUser) perror("Erro de Alocação"), exit(1);

  createdUser->id = user.id;
  strcpy(createdUser->name, user.name);
  strcpy(createdUser->password, user.password);
  strcpy(createdUser->username, user.username);
  createdUser->gender = user.gender;

  return createdUser;
}

void user_print(User* user) {
  if (!user) puts("User not created!");
  else {
    printf(" %3d  \t%s  \t%s  \t%c\n", user->id, user->username, user->name, user->gender);
  }
}

// User* findByUsername(List* users, char* username) {
//   while (users && strcmp(users->user->username, username) != 0) users = users->next;

//   return users ? users->user : NULL;
// }