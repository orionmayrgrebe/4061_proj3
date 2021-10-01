/*test machine: CSELAB_machine_name * date: mm/dd/yy
* name: full_name1 , [full_name2]
* x500: id_for_first_name , [id_for_second_name] */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

struct Node* newNode(char* buffer, int line) {
  // creates an empty node
  struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
  // set data
  for(int i = 0; i<strlen(buffer); i++) {
    temp->buf[i] = buffer[i];
  }
  temp->len = strlen(buffer);
  temp->line = line;
  // set next node
  temp->next = NULL;
  return temp;
}

// struct thread_id create_thread(int thread_num){
//
//   struct Queue *temp = (struct Queue*)malloc(sizeof(struct Queue));
//   temp->consumer_num = thread_num;
// }

struct Queue* makeQueue(char* file) {
  // creates an empty queue
  struct Queue *temp = (struct Queue*)malloc(sizeof(struct Queue));
  // set front to null, set rear to null
  temp->front = NULL;
  temp->rear = NULL;
  temp->end = 0;
  //try to open file
  FILE *fptr = fopen(file, "r");
  //set failure flag
  temp->fail = 0;
  if (fptr == NULL) {
      temp->fail++;
      fclose(fptr);
  }
  //set file of queue to be opened file
  temp->fp = fptr;
  //initialize the mutex and signals
  pthread_mutex_init(&temp->mutex, NULL);
  pthread_cond_init(&temp->can_consume, NULL);
  //return the queue
  return temp;
}

void enQueue(struct Queue* queue, char* buffer, int line) {
  // create a new node with data
  struct Node *temp = newNode(buffer, line);
  // if the rear of the queue is null, there are no elements yet
  if(queue->rear == NULL) {
    queue->front = queue->rear = temp;
    return;
  }
  // set the current rear's next to be temp
  queue->rear->next = temp;
  // set rear to be temp
  queue->rear = temp;
}

struct Node* deQueue(struct Queue* queue) {
  // queue is empty
  if(queue->front == NULL) {
    return NULL;
  }
  // save the first entry
  struct Node *temp = queue->front;
  // set the front to be the next node
  queue->front = temp->next;
  // if the front is now empty, that means there isn't a rear element
  if(queue->front == NULL) {
    queue->rear = NULL;
  }
  // return the first node
  return temp;
}
