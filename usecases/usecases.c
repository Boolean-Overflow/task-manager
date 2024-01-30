#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "usecases.h"

int login_page(TaskManager** instance) {
  int option, valid = 1;
  User* user = NULL;
  do {
    clearConsole();
    if (!valid) puts("Opção inválida!");

    puts("1- Login");
    puts("2- Criar conta");
    puts("3- Exit");
    printf("[1-3]:");
    valid = isValid(&option, 1, 3);
  } while (!valid);

  switch (option) {
  case 1:
    if ((user = login((*instance)->users))) {
      printf("Seja bem vindo Sr");
      if (user->gender == 'F') printf("a");
      printf(". %s\n", user->name);
      return 1;
    }
    else {
      puts("Efetue o seu cadastro!");
      pause("");
      return 0;
    }
    break;
  case 2:
  {
    int success = signup(&(*instance)->users, (*instance)->lastId[USER_LAST_ID_INDEX]);
    if (success) puts("Usuario criado com sucesso!");
    else perror("Erro na criação do user");
    pause("");
    return 0;
  }
  break;
  default:
    return 2;
  }
}