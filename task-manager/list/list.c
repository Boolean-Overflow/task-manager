#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"

List* list_init() {
  return NULL;
}

List* list_insert(List* head, void* data, char id[]) {
  List* node = (List*)malloc(sizeof(List));
  if (!node) {
    perror("Erro de Alocação");
    exit(1);
  }
  node->data = data;
  node->next = NULL;

  strcpy(node->id, id);
  if (!head) return node;

  List* tmp = head;
  while (tmp->next) tmp = tmp->next;
  tmp->next = node;

  return head;
}

List* list_remove(List* head, char id[]) {
  if (!head) return NULL;

  if (strcmp(head->id, id) == 0) {
    List* tmp = head;
    head = head->next;
    free(tmp);
    return list_remove(head, id);
  }

  head->next = list_remove(head->next, id);

  return head;
}