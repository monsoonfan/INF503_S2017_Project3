#include <stdbool.h>
#include <iostream>

// ReadTaxStarting is -1 means null
bool ReadMatchTaxID(int ReadTaxStarting[unsigned int nof_readseed][unsigned int nof_startings],int MaxMM)
{
    bool MatchFound = false;
    // Find starting row in array
    unsigned int k = 0;
    bool StartRowFound = false;
    while(!StartRowFound && k < min(MaxMM + 2,nof_readseed)){
        if (ReadTaxStarting[k][0] == -1){
        }
        else{
           StartRowFound = true;
        }
        k++;
    }
    //
    unsigned int initial_distroyed_count = k - 1;
    unsigned int starting_row = k - 1;
    //
    if (StartRowFound == false && k > MaxMM){
        return false;
    }
    else if(StartRowFound == false && k < MaxMM + 1){
        return false; // Simply assume that this case is really rare otherwise
                      //      Needlebool(Read,TaxID)
    }
    else{
        while(starting_row < min(MaxMM + 2,nof_readseed) && !MatchFound){
            unsigned int distroyed_count = initial_distroyed_count
            // How many a_i we have in first line?
            unsigned int col_index = 0;
            while (ReadTaxStarting[starting_row][col_index] != -1){
                col_index++;
            }
            // store it in a vector
            unsigned int a_start_list[col_index + 1]
            for(unsigned int index = 0; index < col_index + 1; index++ ){
                a_start_list[index] = ReadTaxStarting[starting_row][index];
            }
            // start checking for all initial and give up if found
            index = 0;
            while (index < col_index + 1 && !MatchFound){
                a_0 = a_start_list[index];
                int Possible_match[nof_readseed];
                Possible_match[0] = a_0;
                unsigned int row_iter = starting_row + 1;
                unsigned int current = a_0;
                // check row by row for the next seed
                while(row_iter < min(MaxMM + 2,nof_readseed) && !MatchFound){
                    index = 0;
                    unsigned int next;
                    bool StartingExist = true;
                    bool StartingFound = false;
                    while (index < nof_startings && StartingExist && !StartingFound && !MatchFound){
                        next = ReadTaxStarting[row_iter][index];
                        if (next == -1){
                            StartingExist = false;
                            current++;
                        }
                        else if(next == current + 1)
                        index++;
                        current++;
                        Possible_match[index] = current;
                    }







                }
            }
            // assume null for this row and go to the next
            starting_row++;
            distroyed_count++;
        }
    }
}

