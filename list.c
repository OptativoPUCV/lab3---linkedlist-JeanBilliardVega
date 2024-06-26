#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List* list = (List*)malloc(sizeof(List));
  if (list) {
      list->head = list->tail = list->current = NULL;
  }
  return list;
}

void * firstList(List * list) {
  list->current = list->head;
  return list->current ? list->current->data : NULL;
}

void * nextList(List * list) {
  if (list->current) {
    list->current = list->current->next;
    return list->current ? list->current->data : NULL;
  }
  return NULL;
}

void * lastList(List * list) {
  list->current = list->tail;
  return list->current ? list->current->data : NULL;
}

void * prevList(List * list) {
  if (list->current) {
    list->current = list->current->prev;
    return list->current ? list->current->data : NULL;
  }
  return NULL;
}

void pushFront(List * list, void * data) {
  Node* new = createNode(data);
  new->next = list->head;
  if(list->head)
  {
    list->head->prev = new;
  }
  list->head = new;
  list->tail = list->head;
  while(list->tail->next != NULL){
    list->tail = list->tail->next;
  }
}

void pushBack(List * list, void * data) {
  list->current = list->tail;
  pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node * new = createNode(data);
  new->prev = list->current;
  new->next = list->current->next;
  new->prev->next = new;
  if(new->next == NULL) list->tail = new;
  else new->next->prev = new;
}

void * popFront(List * list) {
  list->current = list->head;
  return popCurrent(list);
}

void * popBack(List * list) {
  list->current = list->tail;
  return popCurrent(list);
}

void *popCurrent(List *list) {
    if (list == NULL || list->current == NULL) {
        return NULL;
    }

    Node *current = list->current;

    if (current == list->head && current == list->tail) {
        list->head = list->tail = NULL;
    }

    else if (current == list->head) {
        list->head = current->next;
        list->head->prev = NULL;
    }

    else if (current == list->tail) {
        list->tail = current->prev;
        list->tail->next = NULL;
    }
    // Si el nodo actual está en medio de la lista
    else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

    void *data = current->data;
    free(current);
    return data;
}

void cleanList(List * list) {
  while (list->head != NULL) {
    popFront(list);
  }
}