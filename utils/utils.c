#include<stdio.h>
#include "utils.h"

void pause(char* str) {
  puts(*str ? str : "Clique em qualquer tecla para continuar.");
  getchar();
}

void clearConsole() {
  printf("\033[2J\033[H");
}

int isValid(int* v, int lower, int upper) {
  fflush(stdin);
  return scanf("%d", v) && (*v >= lower && *v <= upper);
}