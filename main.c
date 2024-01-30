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

  tm_add_task(*instance, t1);
  tm_add_task(*instance, t2);
  tm_add_task(*instance, t3);
  tm_add_task(*instance, t4);
  tm_add_task(*instance, t5);
  tm_add_task(*instance, t6);
}

int main() {
  setlocale(0, "Portuguese");
  TaskManager* instance = tm_init();
  User* user = instance->user;
  int option, valid = 1;

  seed(&instance);

  if (!connect_users(&instance->users)) puts("Erro de conexão com o banco!");

login:

  switch (login_page(&instance)) {
  case 1:
    goto dashboard_home;
  case 2:
    goto end;
  default:
    goto login;
  }

dashboard_home:
  clearConsole();
  do {
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

  puts("TASKER - DASHBOARD");
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
    return 1;
  case 5:
    return 0;
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
    puts("3- Eliminar tarefa"); // KM
    puts("4- Listar Tarefas"); // KM
    puts("5- Procurar Tarefa"); // KM
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
  {
    char str[255];
    char ids[50][ID_MAX_SIZE];
    int valid = 1, index = 0, count = 0;
    printf("Informe o nome da task: ");
    fflush(stdin);
    scanf("%254[^\n]", str);
    puts(str);
    fflush(stdin);

    List* head = find_matched_tasks(instance->tasks->head, str);
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

    if (strcmp(ids[index], instance->tasks->tail->id) == 0)
      instance->tasks->tail = instance->tasks->tail->prev;

    instance->tasks->head = list_remove(instance->tasks->head, ids[index]);
    printf("\nTarefa com id %s removida com sucesso!\n", ids[index]);
    fflush(stdin);
  }
  break;
  case 4:
  {
    int total = queue_print(instance->tasks);
    printf("\nTotal %d tarefas\n", total);
  }
  break;
  case 5:
  {
    char payload[255];
    clearConsole();
    printf("Informe o nome da tarefa: ");
    fflush(stdin);
    scanf("%254[^\n]", payload);
    List* head = find_matched_tasks(instance->tasks->head, payload);
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
    printf("Olá, %s\n", user->name);
    puts("1- Visualizar informações");
    puts("2- Editar Informações");
    puts("3- Voltar");
    printf("[1-3]: ");
    valid = isValid(&option, 1, 3);
  } while (!valid);
  if (option == 3) goto dashboard_home;
  valid = 1;
  switch (option) {
  case 1:
    user_print(user);
    break;
  case 2:
  {
    int opt;
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

      if (!attempts)
        return 1;
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
      goto dashboard_profile;
      break;
    }
    puts("Campo Atualizado com sucesso!");
    fflush(stdin);
    pause("");
    goto profile_options;
  }
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
  {
    List* users = instance->users;
    while (users) {
      user_print(users->data);
      users = users->next;
    }
  }
  break;
  case 2:
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
