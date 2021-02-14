//
//  FIFO.cpp
//  Project_4_AT
//
//  Created by Anh Tuk on 2/13/21.
//

#include "LRU.hpp"

void LRU(CustomQueue myQueue)
{
//    CustomQueue myQueue;
//    queue.
    
    
    std::cout << std::endl <<"************************* LRU ****************************" << std::endl;
    
    // check memory free page size
    int globalTime = 0;
    Memory myMem;
    myMem = Memory();
    
    int freeMemSize = myMem.getFreeMemNum();
    
    std::cout << "freeMemSize: " << freeMemSize << std::endl;
    
    if (freeMemSize >= 4)
    {
        Job process = myQueue.popProcess();
        int memLoc = myMem.getFreePage(myMem);
        std::cout << "memLoc: " << memLoc << std::endl;
        myMem.insertPageToMem(process, 0, memLoc);

    }
    
    myMem.printMem();
    myMem.printFreePageList();
}
