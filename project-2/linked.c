//Contains the linked list for keeping track of jobs
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "linked.h"

////refer to insert data WN. The only change is that name is initialized to none.
void insertData(struct head * n, int arrival, int service, int prioirty)
{
	insertDataWN(n, arrival, service, prioirty, "none");
}
//Assuming that head has already been generated.
//Insert a job into the list, sorted by arrivival time.
void insertDataWN(struct head * n, int arrival, int service, int prioirty, char *c)
{
	struct node * temp;
	struct node * temp2;
	//if there's no head just return
	if(n == NULL)
	{
		printf("err\n");
		return;
	}
	//if nothing is in the list or
	//if the new value arrivial time is less than the head, put it
	//at head and move head down
	temp = n->start;
	if(temp == NULL || temp->data.arrivalTime > arrival)
	{
		n->start = malloc(sizeof(struct node));
		n->start->data.arrivalTime = arrival;
		n->start->data.serviceTime = service;
		n->start->data.priority = prioirty;
		strcpy(n->start->data.name,c);
		n->start->next = temp;
		++(n->len);
		return;
	}
	//if there is nothing in the last spot or
	//if the new value arrivial time is less than the one that is next, put it
	//at next 
	for(temp = n->start; temp !=NULL; temp = temp->next)
	{
		if(temp->next == NULL || 
		temp->next->data.arrivalTime > arrival)
		{
			temp2 = malloc(sizeof(struct node));
			temp2->data.arrivalTime = arrival;
			temp2->data.serviceTime = service;
			temp2->data.priority = prioirty;
			strcpy(temp2->data.name,c);
			temp2->next = temp->next;
			temp->next = temp2;
			++(n->len);
			return;
		}
	}
}

//almost same as insertData except no sorting by arrival.
void insertDataNS(struct head * n, int arrival, int service, int prioirty)
{
	pushDataWNNS(n, arrival, service, prioirty, "none");
}
//Insert at only the head, no sorting by arrival
void pushDataWNNS(struct head * n, int arrival, int service, int prioirty, char *c)
{
	struct node * temp;
	struct node * temp2;
	//if there's no head just return
	if(n == NULL)
	{
		printf("err\n");
		return;
	}
	//insert node at head of list
	temp = n->start;
	n->start = malloc(sizeof(struct node));
	n->start->data.arrivalTime = arrival;
	n->start->data.serviceTime = service;
	n->start->data.priority = prioirty;
	strcpy(n->start->data.name,c);
	n->start->next = temp;
	++(n->len);
	return;

}

//delete what ever is at head
void deleteHeadNode(struct head *n)
{
	struct node *temp;
	if(n == NULL || n->len ==0)
	{
		return;
	}
	temp = n->start;
	n->start= temp->next;
	free(temp);
	--(n->len);
}
//deletes a node from the list
void deleteNode(struct head *n, struct node *prev)
{
	struct node *temp;
	temp = prev->next;
	if(temp == NULL || n == NULL){
		return;
	}
	prev->next= temp->next;
	free(temp);
	--(n->len);
}

//clears all values in linked list
void clr(struct head *n)
{
	struct node *temp;
	int size = n->len;
	if(n == NULL)
	{
		return;
	}
	//make the next one a head and free whatever was in head
	for(int i =0; i< size; ++i)
	{
		deleteHeadNode(n);
	}
	
}

//prints out an job, that located at the node.
void printEntry(struct node *node)
{
	if(node == NULL)
		return;
	printf("Name: %s \nArrival: %d Service: %d Priority: %d\n\n",
		node->data.name,
		node->data.arrivalTime,
		node->data.serviceTime,
		node->data.priority);
}

//just print ouf a list
void printList(struct head *n)
{
	struct node * temp;
	//print everything until it ends
	for(temp = n->start; temp !=NULL; temp = temp->next)
	{
		printEntry(temp);
	}
}
//checks if there is a sufficent amount of jobs such that the cpu is not idle
bool notIdle(struct head *n)
{
	int time = 0;
	struct node *temp;
	//check if head is empty or that lenght of linked list is 0
	if(n == NULL || n->len == 0)
	{
		return true;
	}
	//go through all the linked list
	for(temp = n->start; temp !=NULL; temp = temp->next)
	{
		//if time is greater than 100, return true;
		if( time >= 100)
		{
			return false;
		}
		//check if program idle for 2 quatumn, return false if true
		if(time + 2 < temp->data.arrivalTime)
		{
			return true;
		}
		//this is to adjust the time depending on the cicumstance.
		//if the time is less than arrival, make it equal to the arrival plus the service time
		else if(time < temp->data.arrivalTime)
		{
			time = temp->data.arrivalTime +
			temp->data.serviceTime;
		}
		//just add on the service time if none of the cases are fufiled
		else
		{
			time += temp->data.serviceTime;
		}
	}
	return true;
}
