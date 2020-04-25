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
int main() {

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

}