#ifndef QUEUE_PRIO_LIST_DATASTRUCTURE_H
#define QUEUE_PRIO_LIST_DATASTRUCTURE_H

typedef struct list_node{
  Queue_prio *queue;
  struct list_node *next;
  char *name;
}list_Node;

typedef struct queue_prio_list{
  list_Node *head;
  int size;
}Queue_prio_list;

#endif
