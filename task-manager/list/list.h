#ifndef __LIST__
#define __LIST__

typedef struct Node {
  void* data;
  struct Node* next;
} List;

List* insert(List* head, void* data);

void list_test();

#endif