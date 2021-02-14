//
//  FIFO.cpp
//  Project_4_AT
//
//  Created by Anh Tuk on 2/13/21.
//

#include "FIFO.hpp"

void FIFO(CustomQueue myQueue)
{
//    CustomQueue myQueue;
//    queue.
    
    
    std::cout << std::endl <<"************************* FIFO ****************************" << std::endl;
    
    // check memory free page size
    Memory myMem;
    myMem = Memory();
    
    int freeMemSize = myMem.getFreeMemNum();
    
    std::cout << "freeMemSize: " << freeMemSize << std::endl;
    
    Job process = myQueue.popProcess();
    if (freeMemSize >= 4)
    {
        
        std::cout << "Pages In Process Virtual Address" << std::endl;
        process.printProcessPages();
        
        process.printProcessPagesBool();
        
        myMem.insertPageToMem(&process, 0);
        
        process.printProcessPagesBool();
        myMem.printMem();
        myMem.printFreePageList();
    }
    
   
    
    myMem.removePageFromMem(&process, 0);
    myMem.printMem();
    myMem.printFreePageList();
    process.printProcessPagesBool();
    
    
}
