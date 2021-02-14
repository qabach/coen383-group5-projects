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
    
    if (freeMemSize >= 4)
    {
        Job process = myQueue.popProcess();
        
        std::cout << "Print Pages In Process" << std::endl;
        process.printProcessPages();
        
        std::cout << "Print Pages of Process Bool" << std::endl;
        process.printProcessPagesBool();
        
        
        myMem.insertPageToMem(process, 0);
        
        std::cout << "Print Pages of Process Bool" << std::endl;
        process.printProcessPagesBool();

    }
    
    
    myMem.printMem();
    myMem.printFreePageList();
    
    
}
