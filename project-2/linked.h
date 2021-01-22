//Contains the linked list for keeping track of jobs

#ifndef LINKING
#define LINKING
#define CHAR_LEN 11
#include <stdbool.h>
struct job{
	char name[CHAR_LEN] ;
	int arrivalTime;
	int serviceTime;
	int priority;
};

struct node
{
	struct job data;
	struct node * next;	
};

struct head
{
	struct node * start;
	int len;
};
//inserts a job into the linked list, will be sorted by arrival
void insertData(struct head * n, int arrivial, int service, int prioirty);
void insertDataWN(struct head * n, int arrivial, int service, int prioirty,char *c);
////inserts a job into the linked list, no sorting;
void insertDataNS(struct head * n, int arrivial, int service, int prioirty);
void pushDataWNNS(struct head * n, int arrivial, int service, int prioirty,char *c);
//deletes the node at head
void deleteHeadNode(struct head *n);
//deletes a node from the list, specified from previous node
void deleteNode(struct head *n, struct node *prev);
//clears all data in a linked list
void clr(struct head *n);
//prints out a job entry;
void printEntry(struct node *node);
//prints the list out
void printList(struct head *n);
//checks if there is a sufficent amount of jobs such that the cpu is not idle
bool notIdle(struct head *n);
#endif


