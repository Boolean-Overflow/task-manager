#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"

List* list_init() {
  return NULL;
}

List* list_create_node(void* data, char id[]) {
  List* node = malloc(sizeof(List));
  if (!node) {
    perror("Erro de Alocação");
    exit(1);
  }

  strcpy(node->id, id);
  node->data = data;
  node->prev = NULL;
  node->next = NULL;
  return node;
}

List* list_insert(List* head, void* data, char id[]) {
  List* node = list_create_node(data, id);
  if (!head) return node;
  List* tmp = head;
  while (tmp->next) tmp = tmp->next;
  node->prev = tmp;
  tmp->next = node;
  return head;
}

List* list_remove(List* head, char id[]) {
  if (!head) return NULL;
  List* current = head;
  while (current && strcmp(current->id, id) != 0) current = current->next;
  if (!current) return head;
  if (current->prev) current->prev->next = current->next;
  if (current->next) {
    current->next->prev = current->prev;
    if (!current->prev) head = current->next;
  }
  free(current);
  return head;
}

void list_clear(List** head) {
  if (*head) {
    while (*head) {
      List* tmp = *head;
      *head = tmp->next;
      free(tmp->data);
      free(tmp);
      tmp = NULL;
    }
  }
  *head = NULL;
}

void* list_find(List* head, char* id) {
  if (!head) return NULL;

  while (head && strcmp(head->id, id)) head = head->next;

  return head ? head->data : NULL;
}