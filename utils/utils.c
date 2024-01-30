#include<stdio.h>
#include "utils.h"
#include <stdlib.h>
#include <string.h>

void pause(char* str) {
  puts(*str ? str : "Clique em qualquer tecla para continuar.");
  getchar();
}

void clearConsole() {
  printf("\033[2J\033[H");
}

<<<<<<< HEAD
int Valid_Date(int day,int month,int year){
  if(month >= 1 && month <= 12){
    if((--month%7 + 1)%2 == 1){
      if(!(day >= 1 && day <= 31)){
        puts("Data Inválida");
        return 0;
      }
    }
    if(year%4 == 0){
        if ((month == 2) && !(day >= 1 && day <= 29)){
          puts("Data Inválida");
          return 0;
        }
    }else{
      if ((month == 2) && !(day <= 1 && day <= 28)){
        puts("Data Inválida");
        return 0;
      }
    }
    if(!(day >= 1 && day <= 30)){
      puts("Data Inválida");
      return 0;
    }
  }
  return 1;
}
=======
int isValid(int* v, int lower, int upper) {
  fflush(stdin);
  return scanf("%d", v) && (*v >= lower && *v <= upper);
}
>>>>>>> 64004ec6dc4502d29643e088a32a1ec1db7f16b1
