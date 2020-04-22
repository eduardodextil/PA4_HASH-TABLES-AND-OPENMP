#include <iostream>
#include <time.h>
#include <ctime>
#include <fstream>
#include "Hash.h"
//#include "ChainingHash.h"
#include "ChainingHash1.h"

std::ifstream inputFile;
std::ofstream Analysis;
//sing namespace std;
int main() {

    //object implementation of chaining hash
    ChainingHash<int, int> Chaining;

    //test functions for the public members of the Chaining Hash class
    test_Functions();

    //testing insertion and Rehashing 
    test_Rehash();

    //test_Erase();
    
    //setting table size to 101
    //Chaining.set_CurrentSize(101);


    //clock timer starts recording
    clock_t start = clock();

    for (int index = 1; index <= 10; ++index)
    {
        Chaining.emplace(index, index);
    }
    //clock stop
    clock_t end = clock();

    //opening the hash analysis text file 
    Analysis.open("HashAnalysis.txt", std::ios::app);

    Analysis << "Time of Insertion" << std::endl;

    Analysis <<"CPU Elapsed time in seconds: " 
    << ((double)(end - start)/CLOCKS_PER_SEC) *1000  <<" Seconds"<< std::endl;
    Analysis << std::endl;

    std::cout <<"CPU Elapsed time in seconds: " 
    << ((double)(end - start)/CLOCKS_PER_SEC) *1000 << " Seconds"<< std::endl;

    /*TODO:
    1. search for 177 (record time )
    2. Search for the value with key 2,000,000 in both tables.
    3. Remove the value with key 177 from both tables
    4. write to the file the final size()
    5. write to the file the Bucket count()
    6. write to the file the load factor()
    7. Parallel Implementation


    */

	return 0;

}