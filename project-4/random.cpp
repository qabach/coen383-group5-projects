//
//  random.cpp
//  COEN383
//
//  Created by Pauldin Bebla on 2/14/21.
//

#include "random.hpp"
using namespace std;
void random(CustomQueue queue){
    srand(time(0));
    cout << endl <<"************************* Random ****************************" << endl;
    
    // check memory free page size
    Memory myMem;
    myMem = Memory();
    
    int freeMemSize = myMem.getFreeMemNum();
    
    vector<Job *> inMem;
    vector<Job *> processed;
    vector<int> lastAccessed;
    
    cout << "freeMemSize: " << freeMemSize << endl;
    //please put in memory until full?
    /*if (freeMemSize >= 4)
    {
        Job process = queue.popProcess();
        int memLoc = myMem.getFreePage();
        std::cout << "memLoc: " << memLoc << std::endl;
        myMem.insertPageToMem(&process, memLoc);
        inMem.push_back(process);
        lastAccessed.push_back(0);
    }*/
    for(int global=0;global<60;global++){
        cout<<"global: "<<global<<endl;
        /*for(int i =0 ; i< inMem.size(); ++i)
        {
            if(inMem[i]->getComp() >= inMem[i]->getServ())
            {
                cout<<"Removing process "<<inMem[i]->getName()<<endl;
                myMem.removeProcessFromMem(inMem[i]);
                //delete inMem[i];
                inMem.erase(inMem.begin() + i);
                --i;
                continue;
            }
        }*/
        while(myMem.getFreeMemNum()>=4 && !queue.isEmpty() && queue.front().getArr()<=global ){
            Job * process = new Job(queue.popProcess());
            int memLoc = myMem.getFreePage();
            cout<<"Adding a New Process "<<process->getName()<< endl;
            std::cout << process->getName()<< " memLoc: " << memLoc << std::endl;
            myMem.insertPageToMem(process, memLoc);
            inMem.push_back(process);
            lastAccessed.push_back(0);
        }
        for(int t=0;t<100;t++){
            for(vector<Job *>::iterator k=inMem.begin();k!=inMem.end();){
                int pos = k - inMem.begin();
                freeMemSize = myMem.getFreeMemNum();
                cout<< (*k)->getName()<<" "<<lastAccessed[pos]<<" to ";
                lastAccessed[pos] = locality_reference(lastAccessed[pos], (*k)->getSize());
                cout<<lastAccessed[pos]<<" "<<(*k)->getSize()<<endl;
                if(!(*k)->isListed(lastAccessed[pos])){
                    if(freeMemSize<=0){
                        cout<<"Random Replace: ";
                        int i = rand() % (*k)->getSize();
                        while(!(*k)->isListed(i)){
                            i = rand() % (*k)->getSize();
                        }
                        cout << "Chosen: " << i << endl;
                        myMem.removePageFromMem(*k, i);
                    }
                    myMem.insertPageToMem(*k,lastAccessed[pos]);
                }
                (*k)->incrementComp();
                if((*k)->getComp() == (*k)->getServ())
                {
                    cout<<"Removing process "<<(*k)->getName()<<endl;
                    myMem.removeProcessFromMem(*k);
                    //delete inMem[i];
                    inMem.erase(k);
                }else{
                    k++;
                }
            }
        }
        myMem.printMem();
        myMem.printFreePageList();
    }
    
}
