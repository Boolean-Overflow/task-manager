#ifndef __LIST__
#define __LIST__

typedef struct Node {
  char id[10];
  void* data;
  struct Node* next;
} List;

List* list_init();
List* list_insert(List* head, void* data, char id[]);
List* list_remove(List* head, char id[]);

#endif