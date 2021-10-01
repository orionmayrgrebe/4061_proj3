# pa3_4061
/* test machine: CSEL-KH1260-09 * date: 11/13/2019
   name: Sami Frank , Orion Grebe] 
   x500: fran0942, grebe013 */
 
Sami Frank: fran0942, Orion Grebe grebe013

Compile:
- use Makefile included; simply type make. 

Sami's contributions:
- part of consumer.c: counting of letters functionality, histogram, completed consumer functionality
- part of producer.c
- part of main.c
- log.txt implementation

Orion's contributions:
- part of consumer.c: began coding initial mutex unlocks + signalling
- part of producer.c: getting data from file > queue
- part of main.c: arguement checking , creating producers and consumers
- header.h
- utils.c: created queue and node structure

Assumptions
- delete log.txt and result.txt after every run to ensure fresh data


What the Program does:
- given a .txt file and a cmd line arg for number of consumers, create n consumers to divide up the work of counting the first letter in each word of the .txt file. put the result into a result.txt file and given the -p argument create a log.txt
