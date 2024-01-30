#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "usecases.h"

//Permite fazer login ou criação uma conta usuário
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

//Remove uma Tarefa do Gerenciador de Tarefas
void removeTaskUC(TaskManager** instance) {
  char str[TASK_DESCRIPTION_MAX_SIZE];
  char ids[50][ID_MAX_SIZE];
  int valid = 1, index = 0, count = 0;
  printf("Informe o nome da task: ");
  fflush(stdin);
  scanf("%254[^\n]", str);

  List* head = tm_find_matched_tasks(*instance, str);
  if (head && head->next) {
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

//Procura uma Tarefa no Gerenciador de Tarefas
void findTaskUC(TaskManager** instance) {
  char payload[255];
  clearConsole();
  printf("Informe o nome da tarefa: ");
  fflush(stdin);
  scanf("%254[^\n]", payload);
  List* head = tm_find_matched_tasks(*instance, payload);
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


//Lista os usuários
void listUsersUC(TaskManager** instance) {
  List* users = (*instance)->users;
  while (users) {
    user_print(users->data);
    users = users->next;
  }
}

//Verifica se os dados de uma data são válidos (dia, mês e ano)
int isDateValid(int day, int month, int year) {
  if (year % 4 && (month == 2) && day > 28) return 0;
  if (!(year % 4) && (month == 2) && day > 29) return 0;
  if ((!(--month % 7 + 1) % 2 == 1) && (day > 30)) return 0;
  return 1;
}

//Adicionar Tarefa
Task* addTaskUC(TaskManager** instance) {
  Task task;
  int option = 0, valid = 1;
  char username[USERNAME_MAX_SIZE];
  int day, month = 0, year = 0;
  User* user = NULL;
  task.state = TASK_STATUS_PENDING;
  task.createdAt = getToday();

  do {
    clearConsole();
    if (task.name[0] == 32) puts("O nome da tarefa nao deve iniciar com o caractere ' '.");
    printf("Digite o nome da tarefa: ");
    fflush(stdin);
    scanf("%149[^\n]", task.name);
  } while (task.name[0] == 32);

  do {
    if (task.description[0] == 32) puts("O nome da descrição da tarefa nao deve iniciar com o caractere ' '.");
    printf("Digite a descrição da tarefa: ");
    fflush(stdin);
    scanf("%29[^\n]", task.description);
  } while (task.description[0] == 32);

  do {
    if (!valid) puts("Valor Inválido!");
    printf("Digite o grau de prioridade: ");
    valid = isValid(&(task.priority), 0, 1000);
  } while (!valid);
  valid = 1;

  puts("Deseja indicar um responsável para a tarefa ?");
  do {

    do {
      if (!valid) puts("ERRO: Valor Inválido!");
      printf("Sim[1] ou Nao[0]: ");
      valid = isValid(&option, 0, 1);
    } while (!valid);

    if (option == 1) {
      printf("Digite o username do responsável: ");
      fflush(stdin);
      scanf("%24[^\n]", username);
      user = findByUsername((*instance)->users, username);
      if (!user) {
        puts("Username incorrecto! Deseja digitar novamente ?");
      }
    }
  } while ((option == 1) && (!user));

  task.responsable = user;

  valid = 1;

  do {
    clearConsole();
    if (!valid) puts("ERRO: Data Inválida!");
    valid = 1;
    do {
      if (!valid) puts("ERRO: Dia Inválido!");
      printf("Digite o dia de expiração da tarefa [1-31]: ");
      valid = isValid(&day, 1, 31);
    } while (!valid);
    valid = 1;

    do {
      if (!valid) puts("ERRO: Mês inválido!");
      printf("Digite o mês de expiração da tarefa [1-12]: ");
      valid = isValid(&month, 1, 12);
    } while (!valid);

    valid = 1;
    do {
      if (!valid) puts("ERRO: Ano de expiração inválido!");
      printf("Digite o ano de expiração da tarefa [Data de Criacao - 3000 D.C]: ");
      valid = isValid(&year, task.createdAt.year, 3000);
    } while (!valid);

    valid = isDateValid(day, month, year) && datecmp(task.createdAt, setDate(day, month, year));
  } while (!valid);

  task.expiresAt = setDate(day, month, year);
  day = month = year = 0;

  return tm_add_task(instance, task);
}