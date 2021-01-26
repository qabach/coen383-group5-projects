#ifndef HIGHEST_PRIRORITY_FIRST_NP
#define HIGHEST_PRIRORITY_FIRST_NP
#include "linked.hpp"
#include <iostream>
#include <string>
#include <vector>
void hpfnp(const List &a, std::vector<struct overStat> &stats);
void performJob(List &a, List &c, int &t);
const Node * fillQueues(const Node* ref,List &a1,List &a2,List &a3,List &a4, int time);
void computeStats(const List &a, std::vector<struct overStat> &stats);
#endif 
