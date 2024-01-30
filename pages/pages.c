#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "pages.h"
#include <string.h>

User* login_page(List** users, int lastId) {
  int option, valid = 1;
  User* user = NULL;
  lastId = 0;
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

<<<<<<< HEAD
int Date_Compare(Task* task){
  if (task->createdAt.year > task->expiresAt.year) return 0;
  if (task->createdAt.year == task->expiresAt.year){
    if(task->createdAt.month > task->expiresAt.month) return 0;
    if(task->createdAt.month == task->expiresAt.month){
      if(task->createdAt.day > task->expiresAt.day) return 0;
    }
=======
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
>>>>>>> 64004ec6dc4502d29643e088a32a1ec1db7f16b1
  }
  return 1;
}

<<<<<<< HEAD
TaskManager* Add_Task(TaskManager* instance) {
  Task task;
  int option = 0, count = 0;
  char responsable[30];
  int day, month = 0, year = 0;
  User* user = malloc(sizeof(User));
  do {
    printf("Digite o nome da tarefa: "); scanf("%29[^\n]",task.name);
    for (int i = 0; i < strlen(task.name); i++){
      if(task.name[i] == 32) count++;
    }
  } while (strlen(task.name) == count);
  count = 0;
  do {
    printf("Digite a descrição da tarefa: "); scanf("%29[^\n]",task.description);
    for (int i = 0; i < strlen(task.description); i++){
      if(task.name[i] == 32) count++;
    }
  } while ( strlen(task.description) == count);
  
  printf("Digite a descrição da tarefa: "); scanf("%29[^\n]",task.description);
  printf("Digite o grau de prioridade: "); scanf("%d", &(task.priority));
  puts("Deseja indicar um responsável para a tarefa ?");
  do{
    printf("Sim[1]\\Não[0]:"); while(!scanf("%d",&option));
    fflush(stdin);
    if(option){
      scanf("Digite o username do responsável: "); scanf("%29[^\n]",responsable);
      user = findByUsername(instance->users, responsable);
      if(!user){
        puts("Username incorrecto. Deseja digitar novamente ?");
      }
    }
  } while ((option == 1) && (!user));
  task.state = PENDING;
  do {
      do {
        printf("Digite o dia de criação da tarefa: "); while(!(scanf("%d",&day))) fflush(stdin);
        printf("Digite o mês de criação da tarefa: "); while(!(scanf("%d",&month))) fflush(stdin);
        printf("Digite o ano de criação da tarefa: "); while(!(scanf("%d",&year))) fflush(stdin);
      } while (!Valid_Date(day,month,year));
      task.createdAt.year = year;
      task.createdAt.month = month;
      task.createdAt.day = day;
      day = month = year = 0;
      do {
        printf("Digite o dia de expiração da tarefa: "); while(!(scanf("%d",&day))) fflush(stdin);
        printf("Digite o mês de expiração da tarefa: "); while(!(scanf("%d",&month))) fflush(stdin);
        printf("Digite o ano de expiração da tarefa: "); while(!(scanf("%d",&year))) fflush(stdin);
      } while (!Valid_Date(day,month,year));
      task.expiresAt.year = year;
      task.expiresAt.month = month;
      task.expiresAt.day = day;
      day = month = year = 0;
  } while (!Date_Compare(&task));

  instance = tm_add_task(instance, task);
  return instance;
}

Task* Duplicate_Task(Task task1){
  Task* task2 = taskcpy(&task1);
  return task2;
}

Task* Conclued(Task* task){
  task->state = DONE;
  return task;
}

int Task_Expired(Task* task){
  int day = 0, month = 0, year = 0;
  do {
    printf("Digite o dia Actual: "); while(!(scanf("%d",&day))) fflush(stdin);
    printf("Digite o mês Actual: "); while(!(scanf("%d",&month))) fflush(stdin);
    printf("Digite o ano Actual: "); while(!(scanf("%d",&year))) fflush(stdin);
  } while (!Valid_Date(day,month,year));
  if(task->expiresAt.year > year) return 0;
  if(task->expiresAt.year == year){
    if(task->expiresAt.month > month) return 0;
    if(task->expiresAt.month == month){
      if(task->expiresAt.day > day) return 0;
    }
  }
  task->state = EXPIRED;
  return 1;
}

Task* Edit_Task(Task* task, List* users){
int option1 = 0, option2 = 0;
int day = 0, month = 0, year = 0;
char responsable[20]; 
User* user;
  do{
    puts("1- Editar Nome");
    puts("2- Editar Descrição");
    puts("3- Editar Grau de Prioridade");
    puts("4- Editar Data Expiração");
    puts("5- Editar Responsável da Tarefa");
    puts("6- Sair");
    while(!(scanf("%d",&option1))) fflush(stdin);
    switch (option1) {
    case 1: 
      printf("Digite o nome da tarefa: "); scanf("%29[^\n]", task->name);
      break;
    case 2:
      printf("Digite a descrição da tarefa: "); scanf("%29[^\n]",task->description);
      break;
    case 3:
      printf("Digite o grau de prioridade: "); scanf("%d", &task->priority);
      break;
    case 4:
        do {
        printf("Digite o dia de expiração da tarefa: "); while(!(scanf("%d",&day))) fflush(stdin);
        printf("Digite o mês de expiração da tarefa: "); while(!(scanf("%d",&month))) fflush(stdin);
        printf("Digite o ano de expiração da tarefa: "); while(!(scanf("%d",&year))) fflush(stdin);
        } while (!Valid_Date(day,month,year));
        task->expiresAt.year = year;
        task->expiresAt.month = month;
        task->expiresAt.day = day;
        break;
    case 5:
      do{
          printf("Digite o username do responsável: "); scanf("%20[^\n]",responsable);
          user = findByUsername(users, responsable);
          if(!user){
            puts("Username incorrecto. Deseja digitar novamente ?");
            printf("Sim[1]\\Não[0]:"); while(!scanf("%d",&option2))
            fflush(stdin);
          }
      }while ((option2 == 1) && (!user));
      break;
    }
  } while (option1 != 6);
  return task;
}


/*void dashboard(TaskManager* instance, User* user) {
  puts("========= TASK MANAGER ===========");
=======
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
>>>>>>> 64004ec6dc4502d29643e088a32a1ec1db7f16b1

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
<<<<<<< HEAD
  puts("1- Listar Utilizadores");
  puts("2- Eliminar Utilizadores");
  puts("3- Voltar");

}*/
=======
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
>>>>>>> 64004ec6dc4502d29643e088a32a1ec1db7f16b1
