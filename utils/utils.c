#include<stdio.h>
#include "utils.h"

void pause(char* str) {
  puts(str ? str : "Clique em qualquer tecla para continuar.");
  getchar();
}

void clearConsole() {
  printf("\033[2J\033[H");
}
