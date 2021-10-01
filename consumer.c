/*test machine: CSELAB_machine_name * date: mm/dd/yy
* name: full_name1 , [full_name2]
* x500: id_for_first_name , [id_for_second_name] */

#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "header.h"

int num_consumer = 0;
int count_let[26] ={0};
int consumer_number = 0;

void* consumer(void* arg) {
  // retrieve queue
  struct Queue * queue = (struct Queue*)arg;
  // lock mutex
  pthread_mutex_lock(&queue->mutex);
  usleep(rand() % 2000);
  // lock mutex
  // check to see if there is data to consume

  while(queue->front == NULL) {
    pthread_cond_wait(&queue->can_consume, &queue->mutex);
  }
  pthread_mutex_unlock(&queue->mutex);
  //pthread_mutex_unlock(&queue->mutex);
  if((queue->end == 0) || (queue->end !=0 && queue->front !=NULL)) {
    printf("%s\n", "in if");
    //pthread_mutex_lock(&queue->mutex);

    printf("\t\t\tConsumer does stuff!\n");
    // if we get to this point, that means there's something in the queue to use
    pthread_mutex_lock(&queue->mutex);
    int count = 0;
    //consumer_number++;
    //pthread_mutex_unlock(&queue->mutex);

    while(queue->front != NULL) {
      // retrieve line from queue
      struct Node *item = deQueue(queue);
      // check if print flag has been set
      if(queue->print != 0) {
        FILE * logtxt;
        logtxt = fopen("log.txt", "a");
        fprintf(logtxt, "consumer %d: %d\n", consumer_number ,count);
        fclose(logtxt);
        printf("consumer %d: %d\n", consumer_number, item->line);

      }
      consumer_number++;
      // count letters
      count_letters(count_let, item->buf);
      pthread_mutex_unlock(&queue->mutex);
      count++;
      pthread_mutex_lock(&queue->mutex);
    }
    pthread_mutex_unlock(&queue->mutex);
    num_consumer++;
  }
  else if( queue->end != 0){
    printf("%s\n","producer thread reached EOF" );
    char c = 'A';
    int i = 0;
    while(i<26){
      printf("%c %d\n", c, count_let[i]);
      c++;
      i++;
    }
  }
  pthread_mutex_unlock(&queue->mutex);
  return 0;
}

void count_letters(int* count_let, char * buf){
  int ch;
  char delim[] = " ,.,-,_,1,2,3,4,5,6,7,8,9,0,!,@,#,$,%,^,&,*,(,),+,=,/, \',\", ~, `, >, <, ;, :, {, }, |, \\";
  char *ptr = strtok(buf,delim);
  while(ptr != NULL){
    ch = ptr[0];
    if('a' <= ch && ch <= 'z'){
      count_let[ch-'a']++;
    }
    else if ('A' <= ch && ch <= 'Z'){
      count_let[ch-'A']++;
    }
    ptr = strtok(NULL,delim);
  }

}
