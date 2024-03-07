#include "queue-prio.h"
#include "queue-prio-list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*This program manages a collection of priority queues using a 
  linked list data structure. It offers a set of functions to 
  facilitate the management of these queues within the list. The 
  primary features of the program include initializing the list 
  of queues, adding new queues with unique names, checking the 
  number of queues in the list, and retrieving specific queues by 
  their names. These functionalities collectively allow users to 
  create and maintain a list of priority queues, each identified 
  by a distinct name, making it a useful tool for efficient organization.*/

/* This function initializes a list of priority queues. 
   It sets the head of the list to NULL and the size to 0. 
   If queue_prio_list is NULL, it returns 0 to indicate failure; 
   otherwise, it returns 1 to signify successful initialization.*/
short init_queue_list(Queue_prio_list *const queue_prio_list){
  if(queue_prio_list == NULL)
    return 0;
  queue_prio_list -> head = NULL;
  queue_prio_list -> size = 0;
  return 1;
}

/* This function adds a new priority queue to the list. 
   It checks for duplicates in queue names and prevents adding duplicates. 
   If either queue_prio_list or new_queue_name is NULL, it returns 0 
   for failure. If the queue is successfully added, it returns 1.*/
short add_queue_prio(Queue_prio_list *const queue_prio_list,
		     const char new_queue_name[]){
  /*Setting all variables to NULL to start*/
  list_Node *curr = NULL;
  Queue_prio *queue = NULL;
  list_Node *ans_node = NULL;
  char *name = NULL;

  /*Check if either the queue_prio_list or new_queue_name 
    is NULL, and return 0 if so.*/
  if(queue_prio_list == NULL || new_queue_name == NULL)
    return 0;

  /*Declare a pointer curr and initialize it with the 
    head of the queue_prio_list.*/
  curr = queue_prio_list -> head;

  /*Traverse the existing list of queue names to check if new_queue_name 
    already exists.*/
  while(curr != NULL){
    /* If new_queue_name matches the name of an existing queue, return 0
    to indicate failure.*/
    if(strcmp(curr ->  name,new_queue_name) == 0)
      return 0;
    curr = curr -> next;
  }
  
  /*Allocate memory for a new Queue_prio structure and a 
    new list_Node structure.*/
  queue = calloc(1,sizeof(Queue_prio));
  ans_node = malloc(sizeof(list_Node));

  /*Allocate memory for a new character array to store the new_queue_name.*/
  name = malloc(strlen(new_queue_name)+1);
  
  /*Assign the newly allocated queue to the queue field of the ans_node*/
  ans_node -> queue = queue;

  /*Copy the contents of new_queue_name to the newly allocated 
    name character array.*/
  strcpy(name, new_queue_name);

  /*Set the name field of ans_node to point to the newly 
    allocated name character array*/
  ans_node -> name = name;

  /*Set the newly created queue to the begining of the queue list 
    given in the parameter.*/ 
  ans_node -> next = queue_prio_list -> head;
  queue_prio_list -> head = ans_node;

  /* Increase size reflect the addition of a new queue.*/
  queue_prio_list -> size += 1;
  return 1;
}
/* This function returns the number of priority queues in the list.
   If queue_prio_list is NULL, it returns -1 to indicate failure. 
   Otherwise, it returns the size of the list.*/
short num_queues(const Queue_prio_list *const queue_prio_list){
  if(queue_prio_list == NULL)
    return -1;
  return queue_prio_list -> size;
}

/* This function retrieves a specific priority queue by its 
   name from the list. It searches the list for the specified 
   name and returns the associated queue. If queue_prio_list 
   or queue_name is NULL, or if the specified queue is not found, 
   it returns NULL.*/
Queue_prio *get_queue(const Queue_prio_list *const queue_prio_list,
                      const char queue_name[]){
  Queue_prio *ans_queue = NULL;
  list_Node *curr = NULL;
  /* Check if queue_prio_list and queue_name are not NULL.*/
  if (queue_prio_list != NULL && queue_name != NULL) {
    /*Initialize curr to point to the head of the queue_prio_list.*/
    curr = queue_prio_list -> head;
    
    /*Iterate through the queue_prio_list to find the queue 
      with a matching name.*/
    while (curr != NULL) {
      /*If the name of the current node matches 
	queue_name, set ans_queue to the associated queue.*/
      if (strcmp(curr -> name, queue_name) == 0)
        ans_queue = curr -> queue;
     
      /* Move to the next node in the list.*/
      curr = curr -> next;
    }
  }
  return ans_queue;
}

/* 
 * Removes a priority queue from the linked list of priority queues.
 * Returns -1 if the operation is unsuccessful (e.g., the queue_to_remove 
 is not found),
 * Returns 0 if the operation is successful and the removed queue was empty,
 * Returns 1 if the operation is successful and the removed queue 
 was not empty.
 */
short remove_queue(Queue_prio_list *const queue_prio_list,
                   const char queue_to_remove[]) {
  short ret = -1;
  list_Node *curr = NULL;
  list_Node *prev = NULL;

  /* Check if the queue_prio_list and queue_to_remove are not NULL */
  if (queue_prio_list != NULL && queue_to_remove != NULL) {
    /* Set the current node to the head of the linked list */
    curr = queue_prio_list -> head;

    /* Loop through each node in the linked list */
    while (curr != NULL && ret != 1) {
      /* Check if the name in the current node matches the 
	 specified queue_to_remove */
      if (strcmp(curr -> name, queue_to_remove) == 0) {
	/* Remove the current node from the linked list */
	if (prev != NULL)
	  prev -> next = curr -> next;
	else
	  queue_prio_list -> head = curr -> next;

	/* Clear the priority queue in the removed node */
	clear_queue_prio(curr -> queue);

	/* Update the size of the linked list */
	queue_prio_list -> size--;

	/* Set the return value to 1 (success) */
	ret = 1;
      } else {
	/* Set the return value to 0 (operation successful, 
	   removed queue was empty) */
	ret = 0;
      }

      /* Save the current node */
      prev = curr;

      /* Move to the next node */
      curr = curr -> next;
    }
  }

  return ret;
}

/* 
 * Clears the memory used by the linked list of priority queues.
 * Frees the memory of all nodes in the linked list and resets the size to 0.
 * Returns 1 if the operation is successful, 0 otherwise.
 */
unsigned short clear_queue_prio_list(Queue_prio_list *const queue_prio_list) {
  unsigned short ret = 0;
  list_Node *curr = NULL;

  /* Check if the queue_prio_list is not NULL */
  if (queue_prio_list != NULL) {
    /* Set the current node to the head of the linked list */
    curr = queue_prio_list -> head;

    /* Loop through each node in the linked list */
    while (curr != NULL) {
      /* Clear the priority queue in the current node */
      clear_queue_prio(curr -> queue);

      /* Move to the next node */
      curr = curr -> next;
    }

    /* Set the return value to 1 (success) */
    ret = 1;
  }

  return ret;
}
