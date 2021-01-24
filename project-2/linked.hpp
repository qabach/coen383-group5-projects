
#ifndef LINKING2
#define LINKING2
#define CHAR_LEN 11
#include <string>
class Node;

//class for your basic Job;
class Job{	
	public:
	//public variables (yay?)
	std::string name;
	int arrivalTime, serviceTime, priority;
	struct stat{
		int waitTime;
		int responseTime;
		int turnaroundTime;
	} stats;
	
	//constructors
	Job();
	Job(int a, int b, int s, std::string name);
		
	//getter stuff
	std::string getName(){return name;}
	int getArr(){return arrivalTime;}
	int getServ(){return serviceTime;}
	int getPri(){return priority;}
	int getWait(){return stats.waitTime;}
	int getRes(){return stats.responseTime;}
	int getTurn(){return stats.turnaroundTime;}
	
};

//class for the Basic list;
class List{
	//private Variables
	private:
	Node * head;
	Node * tail;
	int len;
	
	public:
	//constructors
	List();
	~List();
	
	//insertion methods
	void pushDataNS(Job ok);
	void insertData(Job ok);
	
	//deletion methods
	void deleteNode(Node *prev);
	void deleteHeadNode();
	void clr();
	
	//printing methods
	void printList() const;
	void printListOnlyName() const;
	
	//checks and stuff
	bool notIdle() const;
	//just a getter
	const int length() const {return len;}
	
};

//class for the Node
class Node{
	//private variables
	private:
	Node * next;
	public:
	//public variables
	Job data;
	
	//constructors
	Node(Job d, Node * next);
	
	//printting methods
	void printData() const;
	
	//getters
	Job getJob(){return data;}
	Job getJob() const{return data;}
	const Node * getNext() const {return next;}
	Node * getNext() {return next;}
	
	//firend functions to allow stuff
	friend void List::insertData(Job ok);
	friend void List::pushDataNS(Job ok);
	friend void List::deleteNode(Node *prev);
	friend void List::deleteHeadNode();
	
};


#endif 
