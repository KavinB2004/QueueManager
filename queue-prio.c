#include <stdio.h>
#include "queue-prio.h"
#include <stdlib.h>
#include <string.h>

/*The program is designed to manage a priority queue using a linked 
  list data structure. A priority queue is a type of data structure 
  in which elements are stored with associated priorities, and elements 
  with higher priorities are dequeued before those with lower priorities. 
  The program offers a set of functions that collectively allow users to 
  create, modify, and query this priority queue. At its core, the program 
  initializes an empty priority queue and provides methods to add elements 
  to the queue while respecting their priorities. Elements can be enqueued 
  with specific priority levels, and duplicate priorities are not allowed. 
  The program also offers functionalities to check the status of the queue, 
  such as determining whether it's empty or retrieving its size. Additionally, 
  the program allows users to inspect the data associated with the 
  highest-priority element without dequeuing it, providing a "peek" 
  functionality.Dequeuing elements removes the highest-priority element from 
  the queue and updates the size accordingly. Moreover, users can retrieve the 
  names of all elements in the queue as an array of strings.*/

/* This function initializes a priority queue and sets its initial values.
   It takes a pointer to a 'Queue_prio' structure as an argument. */
unsigned short init_queue(Queue_prio *const queue_prio) {
  /*Declare a variable 'ret' to store the return value.*/
  unsigned short ret = 0;
  
  /*Check if the provided parameter is not NULL.*/
  if (queue_prio != NULL) {
    
    /*Set the head to NULL, indicating an empty queue.*/
    queue_prio -> head = NULL;
    
    /*Set the size to 0 since it's initially empty.*/
    queue_prio -> size = 0;

    /*Update the return value to 1 to indicate successful initialization.*/
    ret = 1;
  }

  /* Return the value of ret, which will be 1 if initialization is 
     successful, or 0 if queue_prio is NULL and initialization fails.*/
  return ret;
}

/* This function enqueue new element with a specified priority in the 
   priority queue.It returns 1 if the operation is successful, 0 if 
   the element cannot be enqueued, and handles NULL for queue_prio 
   and new_element appropriately.*/
unsigned short en_queue(Queue_prio *const queue_prio, 
			const char new_element[], unsigned int priority) { 
  Node *curr = NULL;
  Node *prev = NULL;
  Node *new_entry = NULL;
  /*Check if queue_prio and new_element pointers are not NULL.*/ 
  if (queue_prio != NULL && new_element != NULL) { 
    curr = queue_prio->head; 
	     
    /*Create a new entry for the element and allocate memory for its data.*/ 
    new_entry = malloc(sizeof(Node)); 
    new_entry->data = malloc(strlen(new_element) + 1); 
    strcpy(new_entry->data, new_element); 
    new_entry->priority = priority;
    new_entry -> next = NULL;
	 
    /*Check if the priority already exists in the queue, return 0 if found.*/ 
    while (curr != NULL) { 
      if (curr->priority == priority) 
	return 0; 
      curr = curr->next; 
    } 
	 
    curr = queue_prio->head; 
    prev = NULL; 
	 
    /*If the queue is empty or the new element has higher priority, 
      insert at the head.*/ 
    if (curr == NULL || curr->priority < priority) { 
      new_entry->next = curr; 
      queue_prio->head = new_entry; 
      queue_prio->size += 1; 
      return 1; 
    } else { 
	       
      /*Insert the new element in appropriate position based on priority.*/ 
      while (curr != NULL) { 
	if (prev != NULL && prev->priority > priority && 
	    curr->priority < priority) { 
	  prev->next = new_entry; 
	  new_entry->next = curr; 
	  queue_prio->size += 1; 
	  return 1; 
	} 
	prev = curr; 
	curr = curr->next; 
      } 
	       
      /*If the new element has the lowest priority, insert it at the end.*/ 
      prev->next = new_entry; 
      queue_prio->size += 1;
      return 1; 
    
    } 
  }
  return 0; 
} 

/* This function checks if a given priority queue has no elements. 
   It returns -1 if the queue pointer is NULL, 1 if the queue is empty, 
   and 0 if the queue contains elements. */
short has_no_elements(const Queue_prio *const queue_prio) {
  short ret = 0;
  if (queue_prio == NULL)
    ret = -1;
  if (queue_prio -> head == NULL)
    ret = 1;
  return ret;
}

/* This function returns the current size of the provided priority queue.*/
short size(const Queue_prio *const queue_prio) {
  return queue_prio -> size;
}

/* This function retrieves a copy of the data from the head 
   of the priority queue and returns it as a dynamically 
   allocated string. It returns NULL if the queue pointer is 
   NULL or if there's no data in the queue.*/
char *peek(const Queue_prio *const queue_prio) {
  char *name = NULL;
  /*Check if the queue pointer is NULL.*/
  if (queue_prio != NULL){
    /*Allocate memory for a copy of the data and copy it to name.*/
    name = malloc(strlen(queue_prio->head->data) + 1);
    strcpy(name, queue_prio->head->data);
  }
  return name;
}

/* This function dequeues the head element from the prioritys queue, 
   updates the head pointer, and decreases the queue size by 1. 
   It returns the data of the dequeued element as a string, or NULL 
   if the queue is empty or the queue pointer is NULL.*/
char *de_queue(Queue_prio *const queue_prio) {
  Node *temp = NULL;
  char *name = NULL;

  /*Check if the queue pointer is not NULL and if the queue is not empty.*/
  if (queue_prio != NULL && queue_prio->head != NULL) {
    /*Assign the data of the head element to 'name'.*/
    name = queue_prio->head->data;
    temp = queue_prio->head;
    /*Update the head pointer to the next element.*/
    queue_prio->head = queue_prio->head->next;
    free(temp);
    /*Decrease the queue size by 1.*/
    queue_prio->size -= 1;
  }
  return name;
}

/* This function retrieves the names of all elements in the priority queue
   and returns them as an array of strings. The array is dynamically 
   allocated. It also returns NULL if the queue is empty or the queue 
   pointer is NULL.*/
char **all_element_names(const Queue_prio *const queue_prio) {

  /*Get the current size of the queue.*/
  int count = 0;
  Node *curr = NULL;
  char **names = NULL;
  int i;

  count = queue_prio->size;
  curr = queue_prio->head;
  names = malloc(sizeof(queue_prio) * (count + 1));

  /*Iterate through the queue and copy the names into the names array.*/
  for (i = 0; i < count; i++) {
    names[i] = malloc(strlen(curr -> data)+1);
    strcpy(names[i], curr -> data);
    curr = curr -> next;
  }
  
  /*Set the last element of the name array to NULL to indicate the end.*/
  names[count] = NULL;
  return names;
}

/* 
 * Frees the memory allocated for an array of strings (name_list).
 * Returns 1 if the operation is successful, 0 otherwise.
 */
unsigned short free_name_list(char *name_list[]) {
  int i = 0;
  unsigned short ret = 0;

  /* Check if the name_list is not NULL */
  if (name_list != NULL) {
    /* Loop through each string in the array */
    while (name_list[i] != NULL) {
      /* Free the memory for each string */
      free(name_list[i]);
      i++;
    }
        
    /* Free the memory for the array of strings */
    free(name_list);

    /* Set the return value to 1 (success) */
    ret = 1;
  }

  return ret;
}

/* 
 * Clears the memory used by a priority queue.
 * Frees the memory of all nodes in the queue and resets the size to 0.
 * Returns 1 if the operation is successful, 0 otherwise.
 */
unsigned short clear_queue_prio(Queue_prio *const queue_prio) {
  unsigned short ret = 0;
  Node *curr = NULL;
  Node *prev = NULL;

  /* Check if the queue_prio is not NULL */
  if (queue_prio != NULL) {
    /* Set the current node to the head of the queue */
    curr = queue_prio -> head;

    /* Loop through each node in the queue */
    while (curr != NULL) {
      /* Free the memory of the data (string) in the node, if it exists */
      if (curr -> data != NULL)
	free(curr -> data);

      /* Save the current node */
      prev = curr;

      /* Move to the next node */
      curr = curr -> next;

      /* Free the memory of the current node */
      free(prev);
    }

    /* Reset the size of the queue to 0 */
    queue_prio -> size = 0;

    /* Set the return value to 1 (success) */
    ret = 1;
  }

  return ret;
}

/* 
 * Returns the highest priority of an element in the priority queue.
 * Returns -1 if the element is not found or if the priority queue is NULL.
 */
int get_priority(const Queue_prio *const queue_prio, const char element[]) {
  int ret = -1;
  Node *curr = NULL;

  /* Check if the queue_prio and element are not NULL */
  if (queue_prio != NULL && element != NULL) {
    /* Set the current node to the head of the queue */
    curr = queue_prio -> head;

    /* Loop through each node in the queue */
    while (curr != NULL) {
      /* Check if the data (string) in the current node matches the specified element */
      if (strcmp(curr -> data, element) == 0) {
	/* Update the highest priority if the current priority is greater */
	if (curr->priority > ret)
	  ret = curr -> priority;
      }

      /* Move to the next node */
      curr = curr -> next;
    }
  }

  return ret;
}

/* 
 * Removes elements from the priority queue whose priority is
 * greater than or equal to 'low' and less than or equal to 'high'.
 * Returns the number of elements removed.
 */
unsigned int remove_elements_between(Queue_prio *const queue_prio,
                                     unsigned int low, unsigned int high) {
  unsigned int count = 0;
  Node *curr;
  Node *prev;
  Node *test;

  /* Check if the queue_prio is NULL */
  if (queue_prio == NULL)
    return 0;

  /* Set the current node to the head of the queue */
  curr = queue_prio -> head;

  /* Initialize the previous node to NULL */
  prev = NULL;

  /* Loop through each node in the queue */
  while (curr != NULL) {
    /* Check if the priority of the current node is within the 
       specified range */
    if (curr -> priority >= low && curr -> priority <= high) {
      /* Remove the current node from the queue */
      if (prev == NULL)
	queue_prio -> head = curr -> next;
      else
	prev -> next = curr -> next;

      /* Save the current node for later memory deallocation */
      test = curr;

      /* Move to the next node */
      curr = curr -> next;

      /* Free the memory of the data (string) in the current node */
      free(test -> data);

      /* Free the memory of the current node */
      free(test);

      /* Update the size of the queue */
      queue_prio -> size--;

      /* Increment the count of removed elements */
      count++;
    } else {
      /* Move to the next node */
      prev = curr;
      curr = curr -> next;
    }
  }

  return count;
}

/* 
 * Changes the priority of an element in the priority queue.
 * Returns 1 if the operation is successful, 0 otherwise.
 */
unsigned int change_priority(Queue_prio *const queue_prio,
                             const char element[], unsigned int new_priority) {
  int element_test = 0;
  int priority_test = 0;
  Node *curr = NULL;
  Node *prev = NULL;

  /* Check if the queue_prio or element is NULL */
  if (queue_prio == NULL || element == NULL) {
    return 0;
  }

  /* Set the current node to the head of the queue */
  curr = queue_prio->head;

  /* Loop through each node in the queue */
  while (curr != NULL) {
    /* Check if the data (string) in the current node matches 
       the specified element */
    if (strcmp(curr -> data, element) == 0)
      element_test++;

    /* Check if the priority of the current node matches the 
       specified new_priority */
    if (curr -> priority == new_priority)
      priority_test++;

    /* Move to the next node */
    curr = curr -> next;
  }

  /* Check conditions for changing priority */
  if (element_test != 1 || priority_test > 0) {
    return 0;
  }

  /* Reset the current node to the head of the queue */
  curr = queue_prio->head;

  /* Initialize the previous node to NULL */
  prev = NULL;

  /* Loop through each node in the queue */
  while (curr != NULL) {
    /* Check if the data (string) in the current node matches 
       the specified element */
    if (strcmp(curr -> data, element) == 0) {
      /* Remove the current node from the queue */
      if (prev != NULL)
	prev -> next = curr->next;
      else
	queue_prio -> head = curr -> next;

      /* Free the memory of the data (string) in the current node */
      free(curr -> data);

      /* Free the memory of the current node */
      free(curr);

      /* Update the size of the queue */
      queue_prio -> size--;

      /* Add the element back to the queue with the new priority */
      en_queue(queue_prio, element, new_priority);

      /* Return 1 to indicate success */
      return 1;
    }

    /* Move to the next node */
    prev = curr;
    curr = curr -> next;
  }

  /* Return 0 to indicate failure (element not found) */
  return 0;
}
