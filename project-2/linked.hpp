
#ifndef LINKING2
#define LINKING2
#define CHAR_LEN 11
#include <string>
class Node;

//class for your basic Job;
class Job{	
	public:
	std::string name;
	int arrivalTime;
	double serviceTime;
	int priority;
	
	Job();
	Job(int a, double b, int s, std::string name);
	std::string getName(){return name;}
	int getArr(){return arrivalTime;}
	double getServ(){return serviceTime;}
	int getPri(){return priority;}
};

//class for the Basic list;
class List{
	private:
	Node * head;
	int len;
	public:
	List();
	~List();
	const int length() const {return len;}
	void insertData(Job ok);
	void deleteNode(Node *prev);
	void deleteHeadNode();
	void printList() const;
	void clr();
	bool notIdle() const;
	
};

//class for the Node
class Node{
	private:
	Node * next;
	public:
	Job data;
	Node(Job d, Node * next);
	void printData() const;
	Job getJob(){return data;}
	const Node * getNext() const {return next;}
	
	friend void List::insertData(Job ok);
	friend void List::deleteNode(Node *prev);
	friend void List::deleteHeadNode();
	
};


#endif 
