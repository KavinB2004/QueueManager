# QueueManager
Developed a C library for dynamic priority queue management, equipped with numerous functions for complex queue manipulation, enabling optimized memory management and precise element prioritization with robust leak prevention.

queue-prio.c:

The queue-prio.c program is designed to manage a priority queue using a linked 
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
  names of all elements in the queue as an array of strings.

queue-prio-list.c:

The queue-prio-list.c program manages a collection of priority queues using a 
  linked list data structure. It offers a set of functions to 
  facilitate the management of these queues within the list. The 
  primary features of the program include initializing the list 
  of queues, adding new queues with unique names, checking the 
  number of queues in the list, and retrieving specific queues by 
  their names. These functionalities collectively allow users to 
  create and maintain a list of priority queues, each identified 
  by a distinct name, making it a useful tool for efficient organization.
