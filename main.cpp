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

void testing_Module();

int main() {

    
    //test functions for the public members of the Chaining Hash class
    //test_Functions();

    //testing insertion and Rehashing 
    //test_Rehash();

    //test_Erase();
    
   
   testing_Module();

    

	return 0;

}









void testing_Module()
{
    //object implementation of chaining hash
    ChainingHash<int, int> Chaining;


    //clock timer starts recording
    clock_t start = clock();

    for (int index = 1; index <= 1000000; ++index)
    {
        Chaining.emplace(index, index);
    }
    //clock stop 
    clock_t end = clock();

    //searching for the value of key 177
    clock_t start1 = clock();
    cout <<"Value for key 177: " <<Chaining.at(177)<< endl;

    clock_t end1 = clock();

    //searching for the value with key 2000000
    clock_t start2 = clock();
    cout <<"Value for key 2000000: " <<Chaining.at(2000000)<< endl;
    clock_t end2 = clock();


    //removing the value with key 177
    clock_t start3 = clock();
    cout <<"Removing the value with key 177" << endl;
    Chaining.erase(177);
    clock_t end3 = clock();
    






    
    //opening the hash analysis text file 
    //********************************************************//
    Analysis.open("HashAnalysis.txt", std::ios::app);

    Analysis << "Time of Insertion for keys 1 - 1,000,000 " << std::endl;

    Analysis <<"CPU Elapsed time in seconds: " 
    << ((double)(end - start)/CLOCKS_PER_SEC)  <<" Seconds"<< std::endl;
    Analysis << std::endl;

    //***************************************************************************//

    Analysis << "Time elasped while searching for value with a key 177 " << std::endl;

    Analysis <<"CPU Elapsed time in seconds: " 
    << ((double)(end1 - start1)/CLOCKS_PER_SEC)  <<" Seconds"<< std::endl;
    Analysis << std::endl;

    //*************************************************************************//
    Analysis << "Time elasped while searching for value with a key 2000000 " << std::endl;

    Analysis <<"CPU Elapsed time in seconds: " 
    << ((double)(end2 - start2)/CLOCKS_PER_SEC)  <<" Seconds"<< std::endl;
    Analysis << std::endl;
    

    //************************************************************************//
    Analysis << "The time elasped for removing value with key 177" << endl;
    Analysis <<"CPU Elapsed time in seconds: " 
    << ((double)(end3 - start3)/CLOCKS_PER_SEC)  <<" Seconds"<< std::endl;
    Analysis << std::endl;


    //**************************************************************************//
    Analysis << "Final size of the hash tables is: " << Chaining.size() << endl;
    Analysis << std::endl;

    Analysis << "Final bucket count is " << Chaining.bucket_count() << endl;
    Analysis << std::endl;

    Analysis << "Final Load Factor is " << Chaining.load_factor() << endl;
    Analysis << std::endl;


   //**************************************************************************//





    cout<< "Time of Insertion" << std::endl;
    std::cout <<"CPU Elapsed time in seconds: " 
    << ((double)(end - start)/CLOCKS_PER_SEC) << " Seconds"<< std::endl;
    cout << std::endl;

    cout << "Time elasped while searching for value with a key 177 " << std::endl;

    std::cout <<"CPU Elapsed time in seconds: " 
    << ((double)(end1 - start1)/CLOCKS_PER_SEC) << " Seconds"<< std::endl;
    cout << std::endl;


    cout << "Final size of the hash tables is: " << Chaining.size() << endl;


    cout << "Final bucket count is " << Chaining.bucket_count() << endl;

    cout << "Final Load Factor is " << Chaining.load_factor() << endl;


    std::cout <<"CPU Elapsed time in seconds: " 
    << ((double)(end2 - start2)/CLOCKS_PER_SEC) << " Seconds"<< std::endl;

    /*TODO:
    1. Parallel Implementation
     */


   Analysis.close();


}