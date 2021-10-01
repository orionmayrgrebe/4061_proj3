/*test machine: CSELAB_machine_name * date: mm/dd/yy
* name: full_name1 , [full_name2]
* x500: id_for_first_name , [id_for_second_name] */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "header.h"
int line = 1;

void* producer(void* arg) {
  // get queue
  struct Queue * queue = (struct Queue*)arg;
  char buffer[1024];
  // lock mutex
  pthread_mutex_lock(&queue->mutex);
  usleep(rand() % 2000);
  // while there's lines in the file, retrieve.
  while(fgets(buffer, 1024, (FILE*)queue->fp)) {
    enQueue(queue, buffer, line);
    // check print flag
    if(queue->print != 0) {
      FILE *logtxt;
      logtxt = fopen("log.txt", "a");
      fprintf(logtxt, "Producer: %d\n", line);
      fclose(logtxt);
      printf("Producer on line %d\n", line);
    }
    // signal to consumers
    pthread_cond_signal(&queue->can_consume);
    pthread_mutex_unlock(&queue->mutex);
    line++;
    pthread_mutex_lock(&queue->mutex);

  }
  fclose(queue->fp);
  queue->end++;
  FILE *logtxt;
  logtxt = fopen("log.txt", "a");
  fprintf(logtxt, "-1\n");
  pthread_mutex_unlock(&queue->mutex);
  printf("queue->end %d\n", queue->end );
  return 0;
}
