#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "user.h"
#include "../../utils/utils.h"

User* create_user(User user) {
  User* createdUser = (User*)malloc(sizeof(User));
  if (!createdUser) perror("Erro de Alocação"), exit(1);

  strcpy(createdUser->id, user.id);
  createdUser->gender = user.gender;
  strcpy(createdUser->name, user.name);
  strcpy(createdUser->email, user.email);
  strcpy(createdUser->phone, user.phone);
  strcpy(createdUser->username, user.username);
  strcpy(createdUser->password, user.password);

  return createdUser;
}

void user_print(User* user) {
  if (!user) puts("User not created!");
  else {
    printf("%s\n", user->id);
    printf("%c\n", user->gender);
    printf("%s\n", user->name);
    printf("%s\n", user->username);
    printf("%s\n", user->email);
    printf("%s\n", user->phone);
  }
  fflush(stdin);
}

User* findByUsername(List* users, char* username) {
  if (!users) return NULL;

  while (users && strcmp(((User*)(users->data))->username, username)) users = users->next;

  return users ? users->data : NULL;
}

User* usercpy(User* src) {
  if (!src) return NULL;

  return create_user(*src);
}

User* add_user(List** users, User user) {
  User* createdUser = create_user(user);
  if (!createdUser) {
    puts("Erro na criação do utilizador");
    return NULL;
  }

  createdUser->isAdmin = *users ? 0 : 1;
  *users = list_insert(*users, createdUser, createdUser->id);

  FILE* file = fopen(USERS_FILE_PATH, "a");
  if (!file) {
    perror("Erro ao abrir arquivo");
    exit(1);
  }

  fprintf(file, "%s%s", createdUser->id, SEPARATOR);
  fprintf(file, "%c%s", createdUser->gender, SEPARATOR);
  fprintf(file, "%s%s", createdUser->name, SEPARATOR);
  fprintf(file, "%s%s", createdUser->username, SEPARATOR);
  fprintf(file, "%s%s", createdUser->email, SEPARATOR);
  fprintf(file, "%s%s", createdUser->phone, SEPARATOR);
  fprintf(file, "%s%s", createdUser->password, SEPARATOR);
  fputs("", file);

  fflush(file);

  fclose(file);

  return createdUser;
}

int connect_users(List** users) {
  FILE* file = fopen(USERS_FILE_PATH, "r");
  if (!file) {
    perror("Arquivo Inexistente");
    return 0;
  }
  int count = 0;
  char buffer[150];
  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    char* token = strtok(buffer, SEPARATOR);
    int i = 0;
    User user;
    while (token) {
      switch (i++) {
      case 0:
        strcpy(user.id, token);
        break;
      case 1:
        user.gender = *token;
        break;
      case 2:
        strcpy(user.name, token);
        break;
      case 3:
        strcpy(user.username, token);
        break;
      case 4:
        strcpy(user.email, token);
        break;
      case 5:
        strcpy(user.phone, token);
        break;
      case 6:
        strcpy(user.password, token);
        break;
      }
      token = strtok(NULL, ", ");
    }

    *users = list_insert(*users, create_user(user), user.id);
    count++;
  }

  fclose(file);
  return count;
}

User* login(List* users) {
  clearConsole();
  fflush(stdin);
  char username[USERNAME_MAX_SIZE], password[PASSWORD_MAX_SIZE];
  puts("Informe os seus dados corretamente!");
  int attempts = 3;

  while (attempts) {
    if (attempts < 3) {
      clearConsole();
      puts("Nome de Utilizador ou Senha incorreta!");
      printf("Restam-lhe apenas %d tentativa%s", attempts, attempts > 1 ? "s\n" : "\n");
    }

    printf("Username: ");
    scanf("%24[^\n]", username);
    fflush(stdin);
    printf("Password: ");
    scanf("%29[^\n]", password);
    fflush(stdin);

    User* user = findByUsername(users, username);
    if (user && strcmp(user->password, password) == 0) return user;
    attempts--;
  }

  return NULL;
}

int signup(List** users, int lastId) {
  clearConsole();
  fflush(stdin);
  User user;

  puts("Informe abaixo os dados para o cadastro!");
  puts("");
  int valid = 1;
  do {
    if (!valid) puts("O nome deve conter no maximo 25 caracteres sem simbolos");
    printf("Nome: ");
    scanf("%24[^\n]", user.name);
    fflush(stdin);
    for (int i = 0; user.name[i]; ++i) {
      char c = user.name[i];
      if ((c >= 65 && c <= 91) || (c >= 97 && c <= 123) || c == ' ') {
        valid &= 1;
        continue;
      }
      valid &= 0;
      break;
    }
  } while (!valid);

  do {
    if (!valid) puts("O username deve conter no maximo 25 caracteres\n sem espaços e sem simbolos excepto \"_\"");
    printf("Username: ");
    scanf("%24[^\n]", user.username);
    fflush(stdin);
    for (int i = 0; user.username[i]; ++i) {
      char c = user.username[i];
      if ((c >= 65 && c <= 91) || (c >= 97 && c <= 123) || c == '_') {
        valid &= 1;
        continue;
      }
      valid &= 0;
      break;
    }
  } while (!valid);

  printf("Email: ");
  scanf("%29[^\n]", user.email);
  fflush(stdin);

  printf("Telemovel: ");
  scanf("%12[^\n]", user.phone);
  fflush(stdin);

  //puts("A senha deve conter no maximo 30 caracteres");
  printf("Senha: ");
  scanf("%29[^\n]", user.password);
  fflush(stdin);

  printf("Sexo[M | F]: ");
  scanf("%c", &user.gender);
  fflush(stdin);

  char id[10];
  snprintf(id, 10, "USER-0%d", lastId);
  strcpy(user.id, id);

  return add_user(users, user) != NULL;
}

List* find_matched_users(List* users, char* str) {
  if (!users) return NULL;
  List* head = list_init();
  while (users) {
    User* user = users->data;
    if (strstr(user->username, str)) {
      head = list_insert(head, usercpy(user), user->id);
    }
    users = users->next;
  }

  return head;
}