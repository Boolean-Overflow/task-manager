#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<tm.h>
#include<stack.c>
#include<queue.c>


typedef struct Task{
  char* name, * id, * description;
  int state;
}Task;

typedef struct no {
   struct no* next;
   Task task;
}List;

typedef struct Queue {
  List* first, *last;
  struct Queue* next;
}Queue;

typedef struct Stack{
  Queue* top;
}Stack;

struct Tasks {
  char name[150], id[25], description[255], * datetime;
  int state, priority;
  struct Tasks* prev, * next;
};

struct Queue{
  Task* first, *last;
  struct Queue* next;
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
