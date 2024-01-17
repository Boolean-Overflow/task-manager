#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<tm.h>
#include<stack.c>
#include<queue.c>

struct Tasks {
  char name[150], id[25], description[255], * datetime;
  int state, priority;
  struct Tasks* prev, * next;
};

struct Queue{
  T 
}

char* get_datetime() {
  //#include<time.h>
  //#include<string.h>
  time_t currentTime;
  struct tm* localTime;

  time(&currentTime);
  localTime = localtime(&currentTime);
  char* datetime = (char*)malloc(26 * sizeof(char));

  if (!datetime) perror("Memory allocation error"), exit(EXIT_FAILURE);

  strcpy(datetime, asctime(localTime));

  return datetime;
}