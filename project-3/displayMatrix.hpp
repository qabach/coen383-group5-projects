//
//  displayMatrix.hpp
//  Project 3
//
//  Created by Anh Tuk on 2/1/21.
//

#ifndef displayMatrix_hpp
#define displayMatrix_hpp

#include <stdio.h>
#include <cmath>
#include "multithreads_seller.hpp"
#include "seat.hpp"
//using namespace std;

void displayMatrix(std::vector<std::tuple<std::string, Seat>> logH, std::vector<std::tuple<std::string, Seat>> logM, std::vector<std::tuple<std::string, Seat>> logL);


#endif /* displayMatrix_hpp */
