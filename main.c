/*test machine: CSELAB_machine_name * date: mm/dd/yy
* name: full_name1 , [full_name2]
* x500: id_for_first_name , [id_for_second_name] */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <pthread.h>
#include "header.h"

int main(int argc, char *argv[]) {
  // check if a flag was provided
  if(argc == 4) {
    if(strcmp(argv[3], "-b") == 0) {
      printf("Extra credit not supported!\n");
      exit(-1);
    }
    else if(strcmp(argv[3], "-bp") == 0) {
      printf("Extra credit not supported! Running -p argument instead.\n");
    }
    else if(strcmp(argv[3], "-p") != 0) {
      printf("Invalid option provided. Please provide either -p or -bp.\n");
      exit(-1);
    }
  }
  // check for wrong num of arguements
  else if(argc != 3) {
    printf("Error, wrong number of command line arguments. Expected 4 or 3 but found %d.\n", argc);
    printf("Please provide number of consumers, filename and/or an option (-p or -bp).\n");
		exit(-1);
  }
  else if(*argv[1]<1) {
    printf("Error, not enough consumers. Please have at least 1.\n");
    exit(-1);
  }
  // initialize queue
  struct Queue* queue = makeQueue(argv[2]);
  // check if file opened
  if(queue->fail != 0) {
    printf("Error, file does not exist.\n");
    exit(-1);
  }
  queue->print = 0;
  if(argc>3) {
    if(strcmp(argv[3], "-p") == 0 || strcmp(argv[3], "-bp") == 0) {
      queue->print++;
    }
  }
  int num_consumer = atoi(argv[1]);
  pthread_t cons[num_consumer];
  pthread_t prod;
  FILE *logtxt;

  //check print flag
  if(queue->print != 0) {
    logtxt = fopen("log.txt", "a");
    fprintf(logtxt, "Producer\n");
    fclose(logtxt);
    //prints out that the producer has been launched
    printf("Producer\n");
  }
  //create producer
  pthread_create(&prod, NULL, &producer, (void *)queue);
  int consumer_num = 0;
  //create consumers
  for(int i = 0; i<num_consumer; i++) {
    //sets the consumer number
    consumer_num = i;

    //checks print flag
    if(queue->print != 0) {
      //prints out consumer number upon launch
      logtxt = fopen("log.txt", "a");

      fprintf(logtxt, "consumer %d\n", consumer_num);
      fclose(logtxt);
      printf("consumer %d\n", consumer_num);
    }
    pthread_create(&cons[i], NULL, &consumer, (void *)queue);
  }
  // wait for threads
  pthread_join(prod, NULL);

  for(int i = 0; i<num_consumer; i++) {
    printf("waiting...\n");
    pthread_join(cons[i], NULL);
    printf("%s\n", "weighted" );
  }

  FILE *result;
  result = fopen("result.txt", "w");
  char c = 'a';
  int i = 0;
  while(i<26){
    fputc(c,result);
    fprintf(result, ": %d\n", count_let[i]);
    c++;
    i++;
  }
  fclose(result);

  return 0;
}
