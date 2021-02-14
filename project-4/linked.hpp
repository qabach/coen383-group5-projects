
#ifndef LINKING2
#define LINKING2
#define CHAR_LEN 11
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
class Page;
struct stat{
	int waitTime;
	int responseTime;
	int turnaroundTime;
};

class Page{
	private:
	int pNum;
	int pageInMem;
	bool inMem;
	int time;
	
	public:
	Page();
	Page(const Page &a);
	Page(int pageNum,int pageInMem, int t, bool b);
	
	//other
	void changeMem() { inMem = !inMem;}
	void incrementTime(){++time;}
	
	///getters
	int getPageNum(){return pNum;}
	int getPageInMemory(){return pageInMem;}
	bool isInMem(){return inMem;}
	int getTime(){return time;}
	const int getPageNum() const {return pNum;}
	const int getPageInMemory() const {return pageInMem;}
	const bool isInMem() const {return inMem;}
	const int getTime() const {return time;}
	
	//setters
	void setPageNum(int a){pNum = a;}
	void setInMemory(int a){pageInMem = a;}
	void setTime(int a){time = a;}
    //friend void setInMem{inMem = true;}

};

class ExtPage: public Page
{
	private:
	std::string name;
	
	public:
	ExtPage();
	ExtPage(Page a);
	ExtPage(int pageNum,int pageInMem, int timestamp, std::string name);
	
	///getters
	std::string getName(){return name;}
	
	//setters
	void setName(std::string a){name = a;}

};

//class for your basic Job;
class Job{	
	private:
	std::vector<Page> pages;

	public:
	//public variables (yay?)
	std::string processName;
	int arrivalTime, serviceTime, size, completion;
	struct stat stats;
	
	//constructors
	Job();
	//Job(const Job &b);
	Job(int a, int b, int s, std::string name);
	
	//destructor
	~Job();
	
	//More Methods.
	bool insertPage(int pageNum, int pageInMem);
	void insertPageNoCheck(int pageNum, int pageInMem);
	const Page requestPage (int pn) const;
	int removePage(int pageNum);  
    bool isListed(int pageNum);
    void resetTime(int pos){pages[pos].setTime(0);}
    void advTime();
    int returnTime(int pos){return pages[pos].getTime();}
	
	//getter stuff
	std::string getName(){return processName;}
	int getArr(){return arrivalTime;}
	const int getArr() const{return arrivalTime;}
	int getServ(){return serviceTime;}
	const int getServ() const{return serviceTime;}
	int getComp() {return completion;}
	int getSize() {return size;}
	int getWait(){return stats.waitTime;}
	const int getWait() const{return stats.waitTime;}
	int getRes() {return stats.responseTime;}
	const int getRes() const{return stats.responseTime;}
	int getTurn(){return stats.turnaroundTime;}
	const int getTurn() const{return stats.turnaroundTime;}
    std::vector<Page> * getPageVec() { return &pages;}
    
    void printProcessPages();       // ****** AT ******
    void printProcessPagesBool();    // ****** AT ******
	
  
	//setter Stuff
	void setComp(int c) {completion =c;}
	void setWait(int w){stats.waitTime =w;}
	void setRes(int s){stats.responseTime =s;}
	void setTurn(int t){stats.turnaroundTime =t;}
    
    //void setPageInMem(int pageNum);         // ***** AT ******
    
};

class CustomQueue
{
	private:
	std::vector<Job> processes;
	
	public:

	//some functions
	void generateProcesses();
	Job popProcess();
	bool isEmpty(){return processes.empty();}
	
	
	

};


#endif 
