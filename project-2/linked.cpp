#include <iostream>
#include "linked.hpp"

//Makes the Default Job Class
Job::Job()
{
	arrivalTime = 0;
	serviceTime = 0;
	priority = 0;
	name = "None";	
}

//Makes the Job Class with parameters
//Param: a->arrival, b->service, nam-> name of service
Job::Job(int a, int b, int s, std::string nam = "None")
{
	arrivalTime = a;
	serviceTime = b;
	priority = s;
	name = nam;
	
}

//Makes the List Class
List::List()
{
	head = NULL;
	tail = NULL;
	len = 0;
}

//Deconstructs the List Class
List::~List()
{
	clr();
}

//Inserts some data inside list
//Params: need some Job or something
void List::insertData(Job data)
{
	Node * temp;
	Node * temp2;
	//if nothing is in the list or
	//if the new value arrivial time is less than the head, put it
	//at head and move head down
	temp = this->head;
	if(temp == NULL || temp->data.arrivalTime > data.arrivalTime)
	{
		this->head = new Node(data,temp);
		if(temp == NULL)
		{
			this->tail= this->head;
		}
		++(this->len);
		return;
	}
	//if there is nothing in the last spot or
	//if the new value arrivial time is less than the one that is next, put it
	//at next 
	for(temp = this->head; temp !=NULL; temp = temp->next)
	{
		if(temp->next == NULL || 
		temp->next->data.arrivalTime > data.arrivalTime)
		{
			temp2 = new Node(data, temp->next);
			//checks if this is the last element
			if(temp->next == NULL)
			{
				tail = temp2;
			}
			temp->next = temp2;
			++(this->len);
			return;
		}
	}
}

//insert at the tail of the list, no sorting
void List::pushDataNS(Job ok)
{
	//check to see if there is anything in the list
	if(head ==NULL)
	{
		this->head = new Node(ok,NULL);
		this->tail = this->head;
	}
	else{
		this->tail->next = new Node(ok,NULL);
		this->tail = this->tail->next;
	}
	++(this->len);
	return;
}

//deletes whatever is the node after the node specfifed
//Param: Need Like previous node
void List::deleteNode(Node *prev)
{
	Node *temp;
	temp = prev->next;
	if(temp == NULL){
		return;
	}
	prev->next= temp->next;
	if(temp->next == NULL)
	{
		this->tail = prev;
	}
	delete temp;
	--(this->len);

}
//delete what ever is at head
void List::deleteHeadNode()
{
	Node * temp;
	if(this->head == NULL || this->len ==0)
	{
		return;
	}
	temp = this->head;
	this->head= temp->next;
	delete temp;
	--(this->len);

}

//clear everything in the List
void List::clr()
{
	Node *temp;
	int size = this->len;
	//make the next one a head and free whatever was in head
	for(int i =0; i< size; ++i)
	{
		deleteHeadNode();
	}
}

//just print out a list of items
void List::printList() const
{
	const Node * temp;
	//print everything until it ends
	for(temp = this->head; temp !=NULL; temp = temp->getNext())
	{
		temp->printData();
		std::cout<< std::endl;
	}

}

void List::printListOnlyName() const
{
	
	const Node * temp;
	//print everything until it ends
	for(temp = this->head; temp !=NULL; temp = temp->getNext())
	{
		std::cout<< temp->getJob().getName();
		
	

}
}

//checks if there is enough jobs in t
bool List::notIdle() const
{
	int time = 0;
	const Node * temp;
	//check if head is empty or that lenght of linked list is 0
	if(head == NULL || len == 0)
	{
		return true;
	}
	//go through all the linked list
	for(temp = head; temp !=NULL; temp = temp->getNext())
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
//Generates a Node with Job inside
//Params: d-> the job, next-> the next node
Node::Node(Job d, Node * next)
{
	data = d;
	this->next = next;
}

//prints the data about a node
void Node::printData() const
{
	std::cout << "Name: " << data.name
	<< "\nArrival: " << data.arrivalTime 
	<< "\nService: " << data.serviceTime 
	<< "\nPriority: " << data.priority 
	<<std::endl;
}


