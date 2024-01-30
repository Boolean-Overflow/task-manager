#ifndef  __UTILS__
#define __UTILS__

typedef struct Date {
  int day, year, month;
} Date;

void clearConsole();
void pause(char* str);
int isValid(int* value, int lower, int upper);

Date getToday();
Date setDate(int dat, int month, int year);
void dateToString(char* dest, Date date);
void stringToDate(char* src, Date* date);

#endif