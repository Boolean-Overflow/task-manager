#include<stdio.h>
#include<locale.h>
#include<string.h>
#include "task-manager/tm.h"
#include "utils/utils.h"
#include "usecases/usecases.h"

void seed(TaskManager** instance) {
  Task t1 = { "", "Tratar da Loiça1", "Lavar os pratos do jantar", __TIMESTAMP__ , __TIMESTAMP__, 3, 0, NULL };
  Task t2 = { "", "Tratar da Loiça2", "Lavar os pratos do jantar", __TIMESTAMP__ , __TIMESTAMP__, 1, 0, NULL };
  Task t3 = { "", "Tratar da Loiça2", "Lavar os pratos do jantar", __TIMESTAMP__, __TIMESTAMP__, 7, 0, NULL };
  Task t4 = { "", "Tratar da Loiça4", "Lavar os pratos do jantar", __TIMESTAMP__, __TIMESTAMP__, 9, 0, NULL };
  Task t5 = { "", "Tratar da Loiça5", "Lavar os pratos do jantar", __TIMESTAMP__, __TIMESTAMP__, 0, 0, NULL };
  Task t6 = { "", "Tratar da Loiça6", "Lavar os pratos do jantar", __TIMESTAMP__, __TIMESTAMP__, 7, 0, NULL };

  tm_add_task(instance, t1);
  tm_add_task(instance, t2);
  tm_add_task(instance, t3);
  tm_add_task(instance, t4);
  tm_add_task(instance, t5);
  tm_add_task(instance, t6);
}

int main() {
  setlocale(0, "Portuguese");
  TaskManager* instance = tm_init();
  int option, valid = 1;

  seed(&instance);

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
    puts("2- Editar Tarefa");
    puts("3- Eliminar tarefa");
    puts("4- Listar Tarefas");
    puts("5- Procurar Tarefa");
    puts("6- Duplicar Tarefa");
    puts("7- Marcar tarefa como concluida");
    // puts("8- Desfazer ultima acção(undo)");
    // puts("9- Refazer ultima acção(redo)");
    puts("10- Voltar");
    printf("[1-10]: ");
    valid = isValid(&option, 1, 10);
  } while (!valid);
  if (option == 10) goto dashboard_home;

  switch (option) {
  case 3:
    removeTaskUC(&instance);
    break;
  case 4:
    tm_print(instance, TM_PRINT_TASKS);
    break;
  case 5:
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
    puts("2- Editar Informações");
    puts("3- Voltar");
    printf("[1-3]: ");
    valid = isValid(&option, 1, 3);
  } while (!valid);
  if (option == 3) goto dashboard_home;

  switch (option) {
  case 1:
    user_print(instance->loggedUser);
    break;
  case 2:
    if (!updateUserUC(&instance)) goto login;
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
    puts("2- Eliminar Utilizadores");
    puts("3- Voltar");
    printf("[1-3]: ");
    valid = isValid(&option, 1, 3);
  } while (!valid);
  if (option == 3) goto dashboard_home;

  switch (option) {
  case 1:
    tm_print(instance, TM_PRINT_USERS);
    break;
  case 2:
    puts("Remove");
    break;
  case 3:
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
