#ifndef HIGHEST_PRIRORITY_FIRST_NP
#define HIGHEST_PRIRORITY_FIRST_NP
#include "linked.hpp"
#include <iostream>
#include <string>
void hpfnp(const List &a);
void performJob(List &a, List &c, int &t);
const Node * fillQueues(const Node* ref,List &a1,List &a2,List &a3,List &a4, int time);
void computeStats(const List &a);
#endif 
