#include<stdio.h>
#include<stdlib.h>
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

int Date_Compare(Task* task){
  if (task->createdAt.year > task->expiresAt.year) return 0;
  if (task->createdAt.year == task->expiresAt.year){
    if(task->createdAt.month > task->expiresAt.month) return 0;
    if(task->createdAt.month == task->expiresAt.month){
      if(task->createdAt.day > task->expiresAt.day) return 0;
    }
  }
  return 1;
}

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

  puts("1- Gerenciar Tarefas");
  puts("2- Perfil");
  puts("3- Gerenciar utilizadores");
  puts("4- Sair");

  // Gerenfiar Tarefas
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

  // Perfil
  printf("Olá, %s\n", user->name);
  puts("1- Visualizar informações");
  puts("2- Editar Informações");
  puts("3- Voltar");

  // Gerenciar utilizadores
  puts("1- Listar Utilizadores");
  puts("2- Eliminar Utilizadores");
  puts("3- Voltar");

}*/