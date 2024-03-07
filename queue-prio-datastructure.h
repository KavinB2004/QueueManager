#ifndef QUEUE_PRIO_DATASTRUCTURE_H
#define QUEUE_PRIO_DATASTRUCTURE_H

typedef struct node{
  char *data;
  int priority;
  struct node *next;
}Node;

typedef struct queue_prio{
  Node *head;
  int size;
}Queue_prio;

#endif
