#include<stdio.h>
#include<stdlib.h>
#include "pages.h"

User* login_page(List** users) {
  int option, valid = 1;
  User* user = NULL;

  if (!connect_users(users)) puts("Erro de conexão com o banco!");

sign:
  do {
    clearConsole();
    if (!valid) puts("Opção inválida!");

    puts("1- Login");
    puts("2- Criar conta");
    puts("3- Exit");
    printf("[1-3]:");
    fflush(stdin);
    valid = scanf("%d", &option) && (option >= 1 && option <= 3);
  } while (!valid);

  switch (option) {
  case 1:
    if ((user = login(*users))) {
      printf("Seja bem vindo Sr");
      if (user->gender == 'F') printf("a");
      printf(". %s\n", user->name);
      return user;
    }
    else {
      puts("Efetue o seu cadastro!");
      pause("");
      goto sign;
    }
    break;
  case 2:
  { 
    int success = signup(users);
    if (success) puts("Usuario criado com sucesso!");
    else perror("Erro na criação do user");
    pause("");
    goto sign;
  }
  break;
  default:
    return NULL;
  }
}