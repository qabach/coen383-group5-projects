
#ifndef LINKING2
#define LINKING2
#define CHAR_LEN 11
#include <string>
class Node;
struct stat{
	int waitTime;
	int responseTime;
	int turnaroundTime;
};

//class for your basic Job;
class Job{	
	public:
	//public variables (yay?)
	std::string name;
	int arrivalTime, serviceTime, priority, completion;
	struct stat stats;
	
	//constructors
	Job();
	Job(int a, int b, int s, std::string name);
    
		
	//getter stuff
	std::string getName(){return name;}
	int getArr(){return arrivalTime;}
	const int getArr() const{return arrivalTime;}
	int getServ(){return serviceTime;}
	const int getServ() const{return serviceTime;}
	int getPri(){return priority;}
	const int getPri() const{return priority;}
	int getComp() {return completion;}
	int getWait(){return stats.waitTime;}
	const int getWait() const{return stats.waitTime;}
	int getRes() {return stats.responseTime;}
	const int getRes() const{return stats.responseTime;}
	int getTurn(){return stats.turnaroundTime;}
	const int getTurn() const{return stats.turnaroundTime;}
	
  
	//setter Stuff
	void setComp(int c) {completion =c;}
	void setWait(int w){stats.waitTime =w;}
	void setRes(int s){stats.responseTime =s;}
	void setTurn(int t){stats.turnaroundTime =t;}
    
	
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
	void insertSjf(Job job);
	
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
	Node * getHead() {return head;}
	const Node * getHead() const {return head;}
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
    
    void setJobStats(int w, int r, int t)
    {
        data.setWait(w);
        data.setRes(r);
        data.setTurn(t);
    }
	
	//firend functions to allow stuff
	friend void List::insertData(Job ok);
	friend void List::pushDataNS(Job ok);
	friend void List::insertSjf(Job job);
	friend void List::deleteNode(Node *prev);
	friend void List::deleteHeadNode();
	
};


#endif 
