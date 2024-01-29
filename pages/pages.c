#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "pages.h"

User* login_page(List** users, int lastId) {
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
    valid = isValid(&option, 1, 3);
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
    int success = signup(users, lastId);
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

Task Add_Task(List* users) {
  Task task;
  char responsable[30];
  User* user = malloc(sizeof(User));
  printf("Digite o nome da tarefa: "); scanf("%s", task.name);
  printf("Digite a descrição da tarefa: "); scanf("%s", task.description);
  printf("Digite o grau de prioridade: "); scanf("%d", &task.priority);
  puts("Deseja indicar um responsável para a tarefa ?");
  int option = 0;
  printf("Sim[1]\\Não[0]:");while (!scanf("%d", &option));
  if (option) {
    scanf("Username: "); scanf("%s", responsable);
  }
}

int dashboard(TaskManager* instance, User* user) {
  int valid = 1, option;
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
    goto dashboard_users;
    break;
  case 4:
    return 0;
  case 5:
    return 1;
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
        scanf("%d", password);
        printf("Confirme a nova senha: ");
        fflush(stdin);
        scanf("%d", newPassword);
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
dashboard_users:
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
  puts("TASKER - USERS");
}