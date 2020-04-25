#include <iostream>
#include <time.h>
#include <ctime>
#include <fstream>
#include "Hash.h"
#include "ChainingHash.h"
#include "ProbingHash.h"
//#include "ChainingHash1.h"

std::ifstream inputFile;
std::ofstream Analysis;
//sing namespace std;


Hash<int, int> * c = new ChainingHash<int, int>;
Hash<int, int> * p = new ProbingHash<int, int>;
clock_t timeTaken;
//ProbingHash<int, int> p;
/*TODO:
1. search for 177 (record time )
2. Search for the value with key 2,000,000 in both tables.
3. Remove the value with key 177 from both tables
4. write to the file the final size()
5. write to the file the Bucket count()
6. write to the file the load factor()
7. Parallel Implementation
*/

Analysis.open("HashAnalysis.txt", std::ios::app);
timeTaken = clock();
#pragma omp for 
for(int i=0; i<1000; i++)
{
    p->emplace(i,i);
}
timeTaken = clock() - timeTaken;
Analysis<<"Linear Probing parallel time to insert 1000000 elements: "<< (float)timeTaken/CLOCKS_PER_SEC<<std::endl;

timeTaken = clock();
#pragma omp 
{ 
    p->bucket(177);
}
timeTaken = clock() - timeTaken;
Analysis<<"Linear Probing parallel time to search for 177: "<< (float)timeTaken/CLOCKS_PER_SEC<<std::endl;

timeTaken = clock();
    p->bucket(177);
timeTaken = clock() - timeTaken;
Analysis<<"Linear Probing serial time to search for 177: "<< (float)timeTaken/CLOCKS_PER_SEC<<std::endl;


timeTaken = clock();
#pragma omp 
{ 
    p->bucket(2000000);
}
timeTaken = clock() - timeTaken;
Analysis<<"Linear Probing parallel time to search for 2000000: "<< (float)timeTaken/CLOCKS_PER_SEC<<std::endl;

timeTaken = clock();
    p->bucket(2000000);
timeTaken = clock() - timeTaken;
Analysis<<"Linear Probing serial time to search for 2000000: "<< (float)timeTaken/CLOCKS_PER_SEC<<std::endl;


timeTaken = clock();
#pragma omp 
{ 
    p->erase(177);
}
timeTaken = clock() - timeTaken;
Analysis<<"Linear Probing parallel time to erase 177: "<< (float)timeTaken/CLOCKS_PER_SEC<<std::endl;

timeTaken = clock();
    p->erase(177);
timeTaken = clock() - timeTaken;
Analysis<<"Linear Probing serial time to erase 177: "<< (float)timeTaken/CLOCKS_PER_SEC<<std::endl;


Analysis<< "Linear Probing final table size: "<<p->bucket_count()<<std::endl;
Analysis<< "Linear Probing final number of elements: "<<p->size() <<std::endl;
Analysis<< "Linear Probing final load factor: "<<p->load_factor()<<std::endl;


// delete p;
p->~Hash();

    Analysis.close();
	return 0;
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