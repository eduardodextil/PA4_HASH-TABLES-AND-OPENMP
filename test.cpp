#include <iostream>
#include "Hash.h"
#include "ChainingHash.h"
#include "ProbingHash.h"



int main(void)
{
  //  ProbingHash<int, int> chains; // = ProbingHash<int, int>();
    //testInsert();
    // testRehash();
    //testBracketOverload();
    Hash<int, int> * poop = new ProbingHash<int, int>;
    ProbingHash<int, int> blah;

    for(int i=0; i<10; i++)
    {
        blah.emplace(i,i);
        poop->emplace(i,i);
    }

    return 0;
}