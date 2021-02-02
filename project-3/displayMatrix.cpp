//
//  displayMatrix.cpp
//  Project 3
//
//  Created by Anh Tuk on 2/1/21.
//

#include "displayMatrix.hpp"




void displayMatrix(std::vector<std::string> logH, std::vector<std::string> logM, std::vector<std::string> logL)
{
    // seating matrix of 10 rows and 10 columns
    int row = 10;
    int col = 10;
    
    std::string matrix[10][10];
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            matrix[i][j] = "----";
        }
    
    }
    
    // size of each logs
    int sizeH = logH.size();
    int sizeM = logM.size();
    int sizeL = logL.size();
    
    // *** TESTING print out for testing only ***
    std:: cout << "sizeH: " << sizeH << std::endl;
    std:: cout << "sizeM: " << sizeM << std::endl;
    std:: cout << "sizeL: " << sizeL << std::endl;
    
    // number of rows occupy by each seller type
    int rowH = int(ceil(sizeH / 10.0));
    int rowM = int(ceil(sizeM / 10.0));
    int rowL = int(ceil(sizeL / 10.0));
    
    // *** TESTING print out for testing only ***
    std:: cout << "rowH: " << rowH << std::endl;
    std:: cout << "rowM: " << rowM << std::endl;
    std:: cout << "rowL: " << rowL << std::endl;
    
    std::cout << std::endl << "*********** TICKET SEATING MATRIX ***********" << std::endl;
   
    // inserting seats for seller H into matrix
    for(int i=0; i < rowH; i++)
    {
        if(i < rowH-1)
        {
            for(int j=0; j<col; j++)
            {
                matrix[i][j] = logH.at(i*10+j);
            }
            
        }
        else
        {
            for(int j=0; j< sizeH % 10; j++)
            {
                matrix[i][j] = logH.at(i*10+j);
            }
            for(int j=sizeH % 10; j< 10; j++)
            {
                matrix[i][j] = "----";
            }
            
        }
    }
    
    // inserting seats for seller M into matrix
    // checking how many rows has seller H and L has already fill
    int rowLeftM = 10 - rowH - rowL;
  
    // filling row 5 partially
    if(sizeM > 10 && sizeM < 20)
    {
        // filling row 5 partially
        for(int j=0; j<sizeM % 10; j++)
        {
            matrix[4][j] = logM.at(j);
        }
        
    }
    
    // filling row 5
    if(sizeM > 10 && sizeM < 20)
    {
        // filling row 5
        for(int j=0; j<col; j++)
        {
            matrix[4][j] = logM.at(j);
        }
        // filling row 6 partially
        for(int j=0; j<sizeM % 10; j++)
        {
            matrix[5][j] = logM.at(1*10+j);
        }
        
    }
    // filling row 5 => 6
    if(sizeM > 20 && sizeM < 30)
    {
        // filling row 5
        for(int j=0; j<col; j++)
        {
            matrix[4][j] = logM.at(j);
        }
        // filling row 6
        for(int j=0; j<col; j++)
        {
            matrix[5][j] = logM.at(1*10+j);
        }
        // filling row 4 partially
        for(int j=0; j<sizeM % 10; j++)
        {
            matrix[3][j] = logM.at(2*10+j);
        }
    }
    
    
    // filling row 5 => 6 => 4
    if(sizeM > 30 && sizeM < 40)
    {
        // filling row 5
        for(int j=0; j<col; j++)
        {
            matrix[4][j] = logM.at(j);
        }
        // filling row 6
        for(int j=0; j<col; j++)
        {
            matrix[5][j] = logM.at(1*10+j);
        }
        // filling row 4
        for(int j=0; j<col; j++)
        {
            matrix[3][j] = logM.at(2*10+j);
        }
        // filling row 7 partially
        for(int j=0; j<sizeM % 10; j++)
        {
            matrix[6][j] = logM.at(3*10+j);
        }
    }
    
    // filling row 5 => 6 => 4 => 7
    if(sizeM > 40 && sizeM < 50)
    {
        // filling row 5
        for(int j=0; j<col; j++)
        {
            matrix[4][j] = logM.at(j);
        }
        // filling row 6
        for(int j=0; j<col; j++)
        {
            matrix[5][j] = logM.at(1*10+j);
        }
        // filling row 4
        for(int j=0; j<col; j++)
        {
            matrix[3][j] = logM.at(2*10+j);
        }
        // filling row 7
        for(int j=0; j<col; j++)
        {
            matrix[6][j] = logM.at(3*10+j);
        }
        // filling row 3 partially
        for(int j=0; j<sizeM % 10; j++)
        {
            matrix[6][j] = logM.at(4*10+j);
        }
    }
    
    
    
    // inserting seats for seller L into matrix
    for(int i=0; i < rowL; i++)
    {
        if(i < rowL-1)
        {
            for(int j=0; j<col; j++)
            {
                matrix[9-i][j] = logL.at(i*10+j);
            }
        }
        else
        {
            for(int j=0; j< sizeL % 10; j++)
            {
                matrix[9-i][j] = logL.at(i*10+j);
            }
            for(int j=sizeL % 10; j< 10; j++)
            {
                matrix[9-i][j] = "----";
            }
            
        }
    }
    
    
    // display the matrix
    for(int i=0; i<row; i++)
    {
        std::cout << "Row " << i << ": ";
        for(int j=0; j<col; j++)
        {
            std::cout << matrix[i][j] << "  ";
        }
        std:: cout << std::endl;
    }
    
    std:: cout << std::endl << std::endl;
}
