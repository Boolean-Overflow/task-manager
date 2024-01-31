#include<stdio.h>
#include<locale.h>
#include<string.h>
#include "task-manager/tm.h"
#include "utils/utils.h"
#include "usecases/usecases.h"

int main() {
  setlocale(0, "Portuguese");
  TaskManager* instance = tm_init();
  int option, valid = 1;

  if (!connect_users(&instance->users)) puts("Erro de conexão com o banco!");

login:
  switch (loginUC(&instance)) {
  case 1:
    goto dashboard_home;
  case 2:
    goto end;
  default:
    goto login;
  }

dashboard_home:
  do {
    clearConsole();
    puts("===========TASKER - DASHBOARD=============");
    if (!valid) puts("Opção Inválida");
    puts("1- Gerenciar Tarefas");
    puts("2- Perfil");
    puts("3- Gerenciar utilizadores");
    puts("4- Logout");
    puts("5- Sair");
    printf("[1-5]: ");

    valid = isValid(&option, 1, 5);
  } while (!valid);

  switch (option) {
  case 1:
    goto dashboard_task;
    break;
  case 2:
    goto dashboard_profile;
    break;
  case 3:
    goto dashboard_admin;
    break;
  case 4:
    goto login;
  case 5:
    goto end;
  }

dashboard_task:
  // Gerenfiar Tarefas
  valid = 1;
  do {
    clearConsole();
    puts("===========TASKER=============");
    if (!valid) puts("Opção Inválida");
    puts("1- Adicionar Tarefa");
    puts("2- Executar Tarefa");
    puts("3- Eliminar Tarefa");
    puts("4- Listar Tarefas Pendentes");
    puts("5- Listar Tarefas concluidas");
    puts("6- Procurar Tarefa");
    puts("7- Voltar");
    printf("[1-7]: ");
    valid = isValid(&option, 1, 7);
  } while (!valid);
  if (option == 7) goto dashboard_home;

  switch (option) {
  case 1:
  {
    Task* t = addTaskUC(&instance);
    if (t) printf("\nTask criada com o id %s\n", t->id);
    else puts("ERRO: Não foi possivel concluir o pedido!");
    fflush(stdin);
  }
  break;
  case 2:
  {
    Task* t = tm_execute_tasks(&instance);
    if (!t) puts("Muito bem! Nada mais por se fazer.");
    else {
      if (t->state == TASK_STATUS_EXPIRED) printf("Tarefa %s expirada!\n", t->id);
      else printf("Tarefa %s concluida!\n", t->id);
    }
    fflush(stdin);
  }
  break;
  case 3:
    removeTaskUC(&instance);
    break;
  case 4:
    if (!tm_print(instance, TM_PRINT_PENDING_TASKS))
      puts("Nada se tem a listar!");

    fflush(stdin);
    break;
  case 5:
    if (!tm_print(instance, TM_PRINT_CONCLUDED_TASKS))
      puts("Nada se tem a listar!");

    fflush(stdin);
    break;
  case 6:
    findTaskUC(&instance);
    break;
  }
  pause("");
  goto dashboard_task;

dashboard_profile:
  valid = 1;
  // Perfil
  do {
    clearConsole();
    puts("===========TASKER - PROFILE=============");
    if (!valid) puts("Opção Inválida");
    if (instance->loggedUser) printf("Olá, %s\n", instance->loggedUser->name);
    puts("1- Visualizar informações");
    puts("2- Voltar");
    printf("[1-2]: ");
    valid = isValid(&option, 1, 3);
  } while (!valid);
  if (option == 2) goto dashboard_home;

  switch (option) {
  case 1:
    user_print(instance->loggedUser);
    break;
  }

  pause("");
  goto dashboard_profile;

dashboard_admin:
  // Gerenciar utilizadores
  do {
    if (!valid) puts("Opção Inválida");
    puts("===========TASKER - USERS=============");
    puts("1- Listar Utilizadores");
    puts("2- Voltar");
    printf("[1-2]: ");
    valid = isValid(&option, 1, 2);
  } while (!valid);
  if (option == 3) goto dashboard_home;

  switch (option) {
  case 1:
    tm_print(instance, TM_PRINT_USERS);
    break;
  case 2:
    goto dashboard_home;
    break;
  }
  pause("");
  goto dashboard_admin;

end:
  puts("Obrigado ;)");
  puts("Matateu André - 20212549🤓");
  puts("Lukeny Silva - 20220718😎");
  puts("Kélsio Mateus -  20221473🧑🏿‍💻");
  return 0;
}
