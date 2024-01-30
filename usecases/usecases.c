#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "usecases.h"

int loginUC(TaskManager** instance) {
  int option, valid = 1;
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
    if (((*instance)->loggedUser = login((*instance)->users))) {
      printf("Seja bem vindo Sr");
      if ((*instance)->loggedUser->gender == 'F') printf("a");
      printf(". %s\n", (*instance)->loggedUser->name);
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

void removeTaskUC(TaskManager** instance) {
  char str[255];
  char ids[50][ID_MAX_SIZE];
  int valid = 1, index = 0, count = 0;
  printf("Informe o nome da task: ");
  fflush(stdin);
  scanf("%254[^\n]", str);
  puts(str);
  fflush(stdin);

  List* head = find_matched_tasks((*instance)->tasks->head, str);
  if (head->next) {
    puts("\nForam encontradas as seguintes tarefas:");
    List* t = head;
    while (t) {
      printf("[%d]\n", count + 1);
      print_task(t->data);
      strcpy(ids[count], t->id);
      count++;
      t = t->next;
    }

    do {
      if (!valid) puts("Indice Inválido");
      printf("Informe o indice da tarefa que deseja eliminar: ");
      valid = isValid(&index, 1, count);
      index--;
    } while (!valid);
  }
  else strcpy(ids[index], head->id);
  list_clear(&head);

  if (strcmp(ids[index], (*instance)->tasks->tail->id) == 0)
    (*instance)->tasks->tail = (*instance)->tasks->tail->prev;

  (*instance)->tasks->head = list_remove((*instance)->tasks->head, ids[index]);
  printf("\nTarefa com id %s removida com sucesso!\n", ids[index]);
  fflush(stdin);
}

void findTaskUC(TaskManager** instance) {
  char payload[255];
  clearConsole();
  printf("Informe o nome da tarefa: ");
  fflush(stdin);
  scanf("%254[^\n]", payload);
  List* head = find_matched_tasks((*instance)->tasks->head, payload);
  if (head) {
    List* tmp = head;
    while (tmp) {
      print_task(tmp->data);
      tmp = tmp->next;
    }
    list_clear(&head);
    head = tmp = NULL;
  }
  else puts("Tarefa Inexistente!");
  fflush(stdin);
}

int updateUserUC(TaskManager** instance) {
  int opt, valid = 1;
  User* user = (*instance)->loggedUser;
profile_options:
  do {
    clearConsole();
    if (!valid) puts("Valor inválido");
    puts("Informe qual campo deseja editar");
    puts("1. Nome");
    puts("2. Email");
    puts("3. Telemovel");
    puts("4. Senha de Utilizador");
    puts("5. Voltar");
    printf("[1-5]: ");
    valid = isValid(&opt, 1, 5);
  } while (!valid);

  switch (opt) {
  case 1:
    printf("Informe o novo nome: ");
    scanf("%29[^\n]", user->name);
    break;
  case 2:
    printf("Informe o novo nome: ");
    scanf("%29[^\n]", user->email);
    break;
  case 3:
    printf("Informe o novo nome: ");
    scanf("%29[^\n]", user->phone);
    break;
  case 4:
  {
    int attempts = 3;
    char password[PASSWORD_MAX_SIZE];
    do {
      if (attempts < 3) printf("Senha Inválida.\nRestam lhe %d tentativas", attempts);
      printf("Informe a senha atual: ");
      fflush(stdin);
      scanf("%29[^\n]", password);
    } while (strcmp(password, user->password) || attempts > 0);

    if (!attempts) return 0;

    char newPassword[PASSWORD_MAX_SIZE];
    valid = 1;
    do {
      if (!valid) puts("As senhas não coincidem");
      printf("Informe a nova senha: ");
      fflush(stdin);
      scanf("%s", password);
      printf("Confirme a nova senha: ");
      fflush(stdin);
      scanf("%s", newPassword);
    } while ((valid = strcmp(password, newPassword)));
    strcpy(user->password, newPassword);
  }
  break;
  case 5:
    return 1;
  }
  puts("Campo Atualizado com sucesso!");
  fflush(stdin);
  pause("");
  goto profile_options;
}

void listUsersUC(TaskManager** instance) {
  List* users = (*instance)->users;
  while (users) {
    user_print(users->data);
    users = users->next;
  }
}