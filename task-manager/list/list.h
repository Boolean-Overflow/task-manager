#ifndef __LIST__
#define __LIST__

typedef struct List {
  char id[10];
  void* data;
  struct List* prev, * next;
} List;

List* list_init();
List* list_create_node(void* data, char id[]);
List* list_insert(List* head, void* data, char id[]);
List* list_remove(List* head, char id[]);
List* list_push_front(List* head, void* data, char id[]);
void list_clear(List** head);

#endif