
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
	
	public:
	Page();
	Page(int pageNum,int pageInMem );
	
	///getters
	int getPageNum(){return pNum;}
	int getPageInMemory(){return pageInMem;}
	
	//setters
	void setPageNum(int a){pNum = a;}
	void setInMemory(int a){pageInMem = a;}
};

class ExtPage: public Page
{
	private:
	std::string name;
	int time;
	
	public:
	ExtPage();
	ExtPage(Page a);
	ExtPage(int pageNum,int pageInMem, int timestamp, std::string name);
	
	///getters
	std::string getName(){return name;}
	int getTime(){return time;}
	
	//setters
	void setName(std::string a){name = a;}
	void setTime(int a){time = a;}

};

//class for your basic Job;
class Job{	
	private:
	std::vector<Page *> pages;

	public:
	//public variables (yay?)
	std::string processName;
	int arrivalTime, serviceTime, size, completion;
	struct stat stats;
	
	//constructors
	Job();
	Job(int a, int b, int s, std::string name);
	
	//destructor
	~Job();
	
	//More Methods.
	bool insertPage(int pageNum, int pageInMem);
	void insertPageNoCheck(int pageNum, int pageInMem);
	const Page * requestPage (int pn) const;
	void removePage(int pageNum);  
    bool isListed(int pageNum);
	
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
	
  
	//setter Stuff
	void setComp(int c) {completion =c;}
	void setWait(int w){stats.waitTime =w;}
	void setRes(int s){stats.responseTime =s;}
	void setTurn(int t){stats.turnaroundTime =t;}
    
};

class CustomQueue
{
	private:
	std::vector<Job> processes;
	
	public:

	//some functions
	void generateProcesses();
	Job popProcess();
	
	
	

};


#endif 
