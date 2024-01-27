#include<stdio.h>
#include<stdlib.h>
#include "list.h"

List* insert(List* head, void* data) {
  List* node = (List*)malloc(sizeof(List));
  if (!node) {
    perror("Erro de Alocação");
    exit(1);
  }
  node->data = data;
  node->next = head;

  return node;
}

void list_test() {
  puts("List");
}