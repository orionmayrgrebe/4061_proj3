/*test machine: CSELAB_machine_name * date: mm/dd/yy
* name: full_name1 , [full_name2]
* x500: id_for_first_name , [id_for_second_name] */

/*
header.h, header for all source files
it will:
- structure definition
- global variable, lock declaration (extern)
- function declarations
*/

#ifndef _HEADER_H_
#define _HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>


extern int consumer_number;
extern int count_let[26];
extern FILE *logtxt;

//utils.c
struct Node {
  char buf[1024];
  int line;
  long len;
  struct Node *next;
};



struct Queue {
  struct Node *front, *rear;
  pthread_mutex_t mutex; // needed to add/remove data from the buffer
  pthread_cond_t can_consume; // signals when items are added
  int end; // signals when we're at the end of the file
  int print; // flag if printing option has been used
  int fail;
  int consumer_num;

  //struct thread_id * num;
  FILE* fp; // file for the producer to use
};

// struct thread_id{
//   struct Queue * queue;
//   int thread_num;
// };


struct Node* newNode(char*, int);
struct Queue* makeQueue(char*);
void enQueue(struct Queue*, char*, int);
struct Node* deQueue(struct Queue*);

//producer.c
void* producer(void*);

//consumer
void* consumer(void*);
void count_letters(int* count_let, char * buf);


//misn.c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
int pthread_join(pthread_t thread, void **retval);

#endif
