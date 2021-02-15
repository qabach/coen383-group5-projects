//
//  FIFO_2.hpp
//  Project_4_AT
//
//  Created by Anh Tuk on 2/14/21.
//

#ifndef FIFO_hpp
#define FIFO_hpp

#include <stdio.h>
#include <stdio.h>
#include "memory.hpp"
#include "utils.hpp"
#include <deque>

std::tuple<int,int,int> FIFO (CustomQueue queue);
void print_time_log (Job *job, int time, int tick, int last_reference,Memory *memory_map, int free_space, Job * ptr, int page_to_evict);

#endif /* FIFO_2_hpp */
