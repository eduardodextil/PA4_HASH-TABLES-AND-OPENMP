#ifndef __PROBING_HASH_H
#define __PROBING_HASH_H

#include <vector>
#include <stdexcept>

#include "Hash.h"
#include <omp.h> 
#include <cmath> //sqrt()
#include <iostream>

using std::vector;
using std::pair;

// Can be used for tracking lazy deletion for each element in your table
enum EntryState {
    EMPTY = 0,
    VALID = 1,
    DELETED = 2,
    PROBED= 3 //key exists later on and doesn't match this slot so we need to keep searching for it
    
};

template<typename K, typename V>
class ProbingHash : public Hash<K,V> { // derived from Hash
private:
    // Needs a table and a size.
    // Table should be a vector of std::pairs for lazy deletion
   std::vector<std::pair<std::pair<K, V>, EntryState>> mTable; //moved to test

    int mNumElements; 

public:
    ProbingHash(int n = 11) { 
    std::cout<<"inside probing constructor"<<std::endl;

    mTable  =  std::vector<std::pair<std::pair<K, V>, EntryState>>(n);
    mNumElements =0;
    }

    ~ProbingHash() {
        // Needs to actually free all table contents
       std::cout<<"probing destructor"<<std::endl; //table not on heap
        clear();        
    }

    bool empty() {
        return mNumElements ==0; 
    }

    int size() { //number of elements
        return this->mNumElements; //
    }

    V& at(const K& key) {

        int slot =hash(key);
        if(mTable[slot].first.first == key){
            return slot;
        }
        else
        {
            if(mTable[slot].second == EMPTY)
            {
                throw std::out_of_range("Key not in hash");
            }
            else //PROBED or DELETED
            {
                while(slot != mTable.size()) //iterate through the while table until we find it
                {
                    if(mTable[slot].first.first = key)
                    {
                        return mTable[slot].first.second;
                    }
                    slot ++;
                }
                throw std::out_of_range("Key not in hash"); //happens if we didn't find it
            }
            
        }


     
    }
    //error: cannot bind non-const lvalue reference of type int& to an rvalue of type int
    V& operator[](const K& key) { //returns value of key
        //return V;
        int slot = hash(key);
        if(mTable[slot].first.first == key) //found where it's supposed to
        {
            return mTable[slot].first.second; //return value
        }
       else 
       {
           if(mTable[slot].second == PROBED) //state says it's probed 
           { //it exists so go up and look for it
                while(mTable[slot].first.first != key)
                {
                    slot++; 
                }
           }
       }

       return mTable[slot].first.second; //return value
       
    }

    int count(const K& key) { //num elements with key K  because we are allowed to insert duplicate keys
        int slot = hash(key);
        int count =0;
        if(mTable[slot].second != EMPTY) //either there or deleted or probed
        {
            while(slot != mTable.size())
            {
                if(mTable[slot].first.first == key){
                    count++;
                }
                slot ++;
            }
        }
            return count;
    }

    void emplace(K key, V value) { 
     insert(std::make_pair(key, value)); 
    }

    void insert(const std::pair<K, V>& pair) { 
        int slot = hash(pair.first); 
        if(load_factor() <.75)
        {

            if(mTable[slot].second ==EMPTY|| mTable[slot].second == DELETED) //empty or deleted
            {
                mTable[slot].first.first = pair.first;
                mTable[slot].first.second = pair.second;
                mTable[slot].second = VALID; 
                mNumElements++; 
            }
            else if(mTable[slot].second == VALID || mTable[slot].second ==PROBED) //its full, dp probing
            {
                //change state to probed
                mTable[slot].second = PROBED; //so we know this hash shows up later
                while(mTable[slot].second != EMPTY && mTable[slot].second !=DELETED)
                {
                    slot++; 
                        if(slot>mTable.size()){
                        slot =0;} //reset if we go too far
                }
                //now at a spot where we can insert, state is deleted or empty
                mTable[slot].first.first = pair.first;
                mTable[slot].first.second = pair.second;
                mTable[slot].second = VALID; 
                mNumElements++;
            }
        }
        else //rehash: 
        {
        rehash();
        insert(pair);
        }
        
    }

    //when erasing PROBED->DELETED, VALID->EMPTY
    void erase(const K& key) { //erase this key 
    int slot = bucket(key);
    if(slot!= -1) //is in table
    {

        if(mTable[slot].second == PROBED || mTable[slot].second==DELETED)
        {
            //change to deleted
            mTable[slot].first.first = -1;
            mTable[slot].first.second = -1;
            mTable[slot].second = DELETED;
            mNumElements--;
        }
        else //either valid or empty
        {
            mTable[slot].first.first = -1;
            mTable[slot].first.second = -1;
            mTable[slot].second = EMPTY;
            mNumElements--;
        }
        
    }
    else
        std::cout<<"key not found"<<std::endl;
    } //end erase

    void clear() { //clears entire table
        mTable.resize(0); //the rest of the elemtns just get thrown away
        for(int i=0; i<mTable.size(); i++)
        {
            mTable[i].first.first = -1;
            mTable[i].first.second = -1;
            mTable[i].second = EMPTY;
        }
        mNumElements=0; 
    }

    int bucket_count() { //returns number of buckets in table
    return this->mTable.size(); 
    }

    int bucket_size(int n) { //num elements in  bucket n, 0 or 1
    if(mTable[n].second ==VALID || mTable[n].second == PROBED)
    {
        return 1;
    }
    else return 0; 

    }

    int bucket(const K& key) { //
        bool found = false;
        int bucket = hash(key); //member function
        while( bucket <mTable.size() && found == false)
        {
           if(mTable[bucket].first.first == key)
           {
               found = true;
               return bucket;
           }
           bucket++;
        }
       return -1;
    }

    float load_factor() { //may be wrong
        return float(mNumElements)/float(mTable.size()); 
    }

    void rehash() { 
        rehash(findNextPrime(2*mTable.size()));

    }

    void rehash(int n) {
        int oldSize = mTable.size();
        mTable.resize(n);
       // std::cout<<"new table size: "<<n<<std::endl;
        int key =0, value =0;
        for(int i=0; i<oldSize; i++)
        {
            if(mTable[i].second!= EMPTY)
            {
            //save vallues
            key = mTable[i].first.first;
            value = mTable[i].first.second; 
           // erase  entry
            mTable[i].first.first = -1;
            mTable[i].first.second = -1;
            mTable[i].second = EMPTY;// ;mTable[i].
            mNumElements --;
           // insert(key, value); 
            emplace(key, value);
            }
        }
    }

private:
    int findNextPrime(int n)
    {
        while (!isPrime(n))
        {
            n++;
        }
        return n;
    }

    int isPrime(int n)
    {
        for (int i = 2; i <= sqrt(n); i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    int hash(const K& key) { //returns slot#
        int slot = key % this->mTable.size();
        return slot;       
    }
    
};

void testInsert(void)
{
    Hash<int, int> * h = new ProbingHash<int, int>;
    for(int i=0; i<100; i++)
    {
        h ->emplace(i,i);
        std::cout<< i << " load factor:" << h->load_factor() <<"numElements:" 
        << h->size()<< " TableSize:" <<h->bucket_count()<<std::endl;
    }

}

void testBracketOverload(void)
{
    ProbingHash<int, int> h;
    h.insert(std::make_pair(3,3));
    h.insert(std::make_pair(5,5));
    h.insert(std::make_pair(7,7));
    std::cout<<"h[3]: "<< h[3]<< std::endl;

}

void testRehash(void)
{
    ProbingHash<int, int> h;
    for(int i=0; i<1000000; i++)
    {
        h.emplace(i,i); 
    }
}

#endif __PROBING_HASH_H
