#include<stdio.h>
#include "utils.h"
#include<time.h>

void pause(char* str) {
  puts(*str ? str : "\nClique em qualquer tecla para continuar.");
  getchar();
}

void clearConsole() {
  printf("\033[2J\033[H");
}

int isValid(int* v, int lower, int upper) {
  fflush(stdin);
  return scanf("%d", v) && (*v >= lower && *v <= upper);
}

Date getToday() {
  Date today;

  time_t t = time(NULL);
  struct tm* current_time = localtime(&t);

  today.day = current_time->tm_mday;
  today.month = current_time->tm_mon + 1;
  today.year = current_time->tm_year + 1900;

  return today;
}

Date setDate(int day, int month, int year) {
  Date customDate;

  customDate.day = day;
  customDate.month = month;
  customDate.year = year;

  return customDate;
}

void dateToString(char* dest, Date date) {
  snprintf(dest, sizeof(dest), "%d/%d/%d", date.day, date.month, date.year);
}

void stringToDate(char* src, Date* date) {
  if (sscanf(src, "%d/%d/%d", &date->day, &date->month, &date->year) != 3) {
    puts("Error: Invalid date format or values.\n");
  }
}

int datecmp(Date date1, Date date2) {
  if (date1.year > date2.year) return 0;
  if (date1.year == date2.year) {
    if (date1.month > date2.month) return 0;
    if (date1.month == date2.month) {
      if (date1.day > date2.day) return 0;
    }
  }

  return 1;
}