#include<stdio.h>
#include<stdlib.h>
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

Task Add_Task(List* users) {
  Task task;
  char responsable[30];
  User* user = malloc(sizeof(User));
  printf("Digite o nome da tarefa: "); scanf("%s", task.name);
  printf("Digite a descrição da tarefa: "); scanf("%s", task.description);
  printf("Digite o grau de prioridade: "); scanf("%d", &task.priority);
  puts("Deseja indicar um responsável para a tarefa ?");
  int option = 0; 
  printf("Sim[1]\\Não[0]:");while(!scanf("%d",&option));
  if(option){
    scanf("Username: "); scanf("%s",responsable);
    
  }
}

void dashboard(TaskManager* instance, User* user) {
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

}