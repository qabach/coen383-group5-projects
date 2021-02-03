//
//  displayMatrix.cpp
//  Project 3
//
//  Created by Anh Tuk on 2/1/21.
//

#include "displayMatrix.hpp"

const int LARGETIME = 1000;




void displayMatrix(std::vector<std::tuple<std::string, Seat>> VectorLogH, std::vector<std::tuple<std::string, Seat>> VectorLogM, std::vector<std::tuple<std::string, Seat>> VectorLogL)
{
   
    
    std::cout << std::endl << "********************** DISPLAY MATRIX PROCESS *********************" << std::endl;
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
    auto sizeH = VectorLogH.size();
    auto sizeM = VectorLogM.size();
    auto sizeL = VectorLogL.size();
    
    // *** TESTING print out for testing only ***
    std:: cout << "Number of customers served by H: " << sizeH << std::endl;
    std:: cout << "Number of customers served by M: " << sizeM << std::endl;
    std:: cout << "Number of customers served by L: " << sizeL << std::endl;
    
    
    
    int timeH1 = LARGETIME;
    int timeM1 = LARGETIME;
    int timeL1 = LARGETIME;
            
    while (VectorLogH.size() != 0 || VectorLogM.size() != 0 || VectorLogL.size() != 0 )
    {
        // get first ticket of each seller type time if the seller log is not empty
        if (VectorLogH.size() >0)
        {
            timeH1 = std::get<1>(VectorLogH[0])._ticket_issued_time;
        }
        else
        {
            timeH1 = LARGETIME;
        }
        
        if (VectorLogM.size() >0)
        {
            timeM1 = std::get<1>(VectorLogM[0])._ticket_issued_time;
        }
        else
        {
            timeM1 = LARGETIME;
        }
                
        if (VectorLogL.size() >0)
        {
            timeL1 = std::get<1>(VectorLogL[0])._ticket_issued_time;
        }
        else
        {
            timeL1 = LARGETIME;
        }

        
        // ticket in front of log H has the smallest timestamp so get filled first
        if(timeH1 <= timeM1 && timeH1 <= timeL1 && timeH1 != LARGETIME && VectorLogH.size() >0)
        {
            bool gotSeat = false;
            for(int i = 0; i < 10; i++)         // access from top down
            {
                for(int j = 0; j < 10; j++)     // access from left to right
                {
                    if (matrix[i][j] == "----" && gotSeat == false)      // no seller fill this seat yet
                    {
                        matrix[i][j] = std::get<0>(VectorLogH[0]);
                        gotSeat = true;
                        break;
                    }
                    else
                    {
                        continue;               // find next available seat
                    }
                    
                }
            }
            VectorLogH.erase(VectorLogH.begin());           // delete the front ticket
        }
        
        
        
        // ticket in front of log M has the smallest timestamp so get filled first
        else if (timeM1 <= timeH1 && timeM1 <= timeL1 && timeM1 != LARGETIME && VectorLogM.size() >0)
        {
            bool gotSeat = false;
            
            for(int i = 4; i < 6; i++)         // access from row 5 to 6
            {
                for(int j = 0; j < 10; j++)     // access from left to right
                {
                    if (matrix[i][j] == "----" && gotSeat == false)      // no seller fill this seat yet
                    {
                        matrix[i][j] = std::get<0>(VectorLogM[0]);
                        gotSeat = true;
                        break;
                    }
                    else
                    {
                        continue;               // find next available seat
                    }
                    
                }
            }
            
            for(int i = 3; i < 4; i++)         // access from row 4
            {
                for(int j = 0; j < 10; j++)     // access from left to right
                {
                    if (matrix[i][j] == "----" && gotSeat == false)      // no seller fill this seat yet
                    {
                        matrix[i][j] = std::get<0>(VectorLogM[0]);
                        gotSeat = true;
                        break;
                    }
                    else
                    {
                        continue;               // find next available seat
                    }
                }
            }
            
            for(int i = 6; i < 7; i++)         // access from row 7
            {
                for(int j = 0; j < 10; j++)     // access from left to right
                {
                    if (matrix[i][j] == "----" && gotSeat == false)      // no seller fill this seat yet
                    {
                        matrix[i][j] = std::get<0>(VectorLogM[0]);
                        gotSeat = true;
                        break;
                        
                    }
                    else
                    {
                        continue;               // find next available seat
                    }
                }
            }
            
            for(int i = 2; i < 3; i++)         // access from row 3
            {
                for(int j = 0; j < 10; j++)     // access from left to right
                {
                    if (matrix[i][j] == "----" && gotSeat == false)      // no seller fill this seat yet
                    {
                        matrix[i][j] = std::get<0>(VectorLogM[0]);
                        gotSeat = true;
                        break;
                    }
                    else
                    {
                        continue;               // find next available seat
                    }
                }
            }
            
            
            for(int i = 7; i < 8; i++)         // access from row 8
            {
                for(int j = 0; j < 10; j++)     // access from left to right
                {
                    if (matrix[i][j] == "----" && gotSeat == false)      // no seller fill this seat yet
                    {
                        matrix[i][j] = std::get<0>(VectorLogM[0]);
                        gotSeat = true;
                        break;
                    }
                    else
                    {
                        continue;               // find next available seat
                    }
                }
            }
            
            for(int i = 1; i < 2; i++)         // access from row 2
            {
                for(int j = 0; j < 10; j++)     // access from left to right
                {
                    if (matrix[i][j] == "----" && gotSeat == false)      // no seller fill this seat yet
                    {
                        matrix[i][j] = std::get<0>(VectorLogM[0]);
                        gotSeat = true;
                        break;
                    }
                    else
                    {
                        continue;               // find next available seat
                    }
                }
            }
            
            for(int i = 8; i < 9; i++)         // access from row 9
            {
                for(int j = 0; j < 10; j++)     // access from left to right
                {
                    if (matrix[i][j] == "----" && gotSeat == false)      // no seller fill this seat yet
                    {
                        matrix[i][j] = std::get<0>(VectorLogM[0]);
                        gotSeat = true;
                        break;
                    }
                    else
                    {
                        continue;               // find next available seat
                    }
                }
            }
            
            for(int i = 0; i < 1; i++)         // access from row 1
            {
                for(int j = 0; j < 10; j++)     // access from left to right
                {
                    if (matrix[i][j] == "----" && gotSeat == false)      // no seller fill this seat yet
                    {
                        matrix[i][j] = std::get<0>(VectorLogM[0]);
                        gotSeat = true;
                        break;
                    }
                    else
                    {
                        continue;               // find next available seat
                    }
                    
                }
            }
            
            for(int i = 9; i < 10; i++)         // access from row 10
            {
                for(int j = 0; j < 10; j++)     // access from left to right
                {
                    if (matrix[i][j] == "----" && gotSeat == false)      // no seller fill this seat yet
                    {
                        matrix[i][j] = std::get<0>(VectorLogM[0]);
                        gotSeat = true;
                        break;
                    }
                    else
                    {
                        continue;               // find next available seat
                    }
                }
            }
            
            VectorLogM.erase(VectorLogM.begin());           // delete the front ticket
        }
    
    
        // ticket in front of log L has the smallest timestamp so get filled first
        else if (timeL1 <= timeM1 && timeL1 < timeH1 && VectorLogL.size() >0)
        {
            bool gotSeat = false;
            
            for(int i = 9; i >= 0; i--)         // access from bottom up
            {
                for(int j = 0; j < 10; j++)     // access from left to right
                {
                    if (matrix[i][j] == "----" &&  gotSeat == false)      // no seller fill this seat yet
                    {
                        matrix[i][j] = std::get<0>(VectorLogL[0]);
                        gotSeat = true;
                        break;
                    }
                    else
                    {
                        continue;           // find next available seat
                    }
                }
            }
            VectorLogL.erase(VectorLogL.begin());           // delete the front ticket
        }
        
        else
            break;
       
    }

    
    {
        std::cout << std::endl << "********************** TICKET SEATING MATRIX **********************" << std::endl;
        // display the matrix
        for(int i=0; i<row; i++)
        {
            std::cout << "Row " << int_to_string(i+1) << ":  ";
            for(int j=0; j<col; j++)
            {
                std::cout << matrix[i][j] << "  ";
            }
            std:: cout << std::endl;
        }
        
        std:: cout << std::endl << std::endl;
    }
    
   
}
