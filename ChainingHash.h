/*
 *  Separate chaining hashtable
 */

#ifndef __CHAINING_HASH_H
#define __CHAINING_HASH_H

// Standard library includes
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <omp.h> 
#include <stdexcept>

// Custom project includes
#include "Hash.h"

// Namespaces to include
using std::vector;
using std::list;
using std::pair;

using std::cout;
using std::endl;

//
// Separate chaining based hash table - inherits from Hash
//
template<typename K, typename V>
class ChainingHash : public Hash<K,V> {
private:
    //Vector of Lists
    vector< list< pair<K,V> > > hash_table;
    //for the number of element currently in the hash table
    int cur_Size{0};
    //for calculatting the number of buckets
    int x_bucket_count;


public:
    ChainingHash(int n = 11) {
        cout << "Inside the Chaining Hash constructor" << endl;

        x_bucket_count = findNextPrime(n);
        hash_table.resize(x_bucket_count);
    }


    //Empties the Hash table
    ~ChainingHash() {
        cout << " Inside the Chaining Hash destructor " << endl;
        this->clear();
    }


    //check if hash table is empty
    bool empty() {
      return cur_Size == 0;
    }

    //returns the current size of the table
    int size() {
        return cur_Size;
    }

    //Returns the value with key k
    V& at(const K& key) {
        int index = hash(key);
        auto entry = hash_table[index];
        for(auto &val : entry){
            if(val.first == key)
                return val.second;
        }
        //throw std::out_of_range("Key not in hash");
        cout << "[WARNING!!!!] Key not found" << endl;
        //return 0;
    }

    //Returns the value with key k
    V& operator[](const K& key) {
        return this->at(key);
    }

    //Returns the number of elements with key k
    int count(const K& key) {
        int count = 0;
        int index = hash(key);
        auto entry = hash_table[index];
        for(auto & val : entry){
            if(val.first == key)
                return 1;
        }
        return 0;
    }

    //inserting based not Keys and Values
    void emplace(K key, V value) {
        while(load_factor() >= 0.75){
            rehash();
        }
        this->insert(std::make_pair(key,value));
    }

    //inserting based on pairs
    void insert(const std::pair<K, V>& pair) {
        int key = pair.first;
        int index = hash(key);
        auto& entry = hash_table[index];
        //checking if the key exist in the list
        if(count(key)){
            for(auto it = entry.begin(); it != entry.end(); it++){
                if(it->first == key){
                    *it = pair;
                    cout <<"[WARNING ] KEY EXIST, VALUE REPLACED" <<endl;
                    return;
                }
            }
        }
        else{
            //if key does not exist, pushing back into the list
            entry.push_back(pair);
            cur_Size++;
        }
    }

    //Erasing based on Key
   void erase(const K& key) {
       //return if hash table is empty
        if(this->empty()) return;
        //int index = hash(key);
        int index = bucket(key);
        auto &entry = hash_table[index];
        bool found = false;
        for(auto it = entry.begin(); it != entry.end(); it++){
            if(it->first == key){
                it = entry.erase(it);
                cur_Size--;
                cout <<"[WARNING!!!!] Item removed" <<endl;
                found = true;
            }
        }
        if (!found){// if the item was not removed 
            //throw std::out_of_range("Key not in hash");

            cout << "The key is not removed " << endl;

        }
        return;
    }

    



    //Clears the Hash table
    void clear() {
        hash_table.clear();
        cur_Size = 0;
        x_bucket_count = 0;
    }

    //returns the bucket count 
    int bucket_count() {
        return x_bucket_count;
    }

    //Returns the number of elements in bucket n (0, 1, or length of list if chaining)
    int bucket_size(int n) {
        if(n>=x_bucket_count){
            throw std::out_of_range("Input Bucket count out of range");
        }
        auto entry = hash_table[n];
        return entry.size();
    }

    //Returns the bucket number of key (or throws std::out_of_range if key not found)
    int bucket(const K& key) {
        int index = hash(key);
        auto entry = hash_table[index];
        for(auto &val : entry){
            if(val.first == key)
                return index;
        }
        //throw std::out_of_range("Key not in hash");
        cout << "Key not in the hash" << endl;
        return 0;
    }

    // calculates the load factor and returns the load factor
    float load_factor() {
        float f = (float)cur_Size;
        f = f/(float)x_bucket_count;
        return f;
    }

    //rehashing when the exceeds 0.75 
    void rehash() {
        cout << "REHASHING !!!" << endl;
        rehash(x_bucket_count + 1); 
    }

    //helper function for rehashing 
    void rehash(int n) {
        auto temp = hash_table;
        clear();

        x_bucket_count = findNextPrime(2*n); //made it resize to twice next prime
        hash_table.resize(x_bucket_count);
        std::cout<<"new tablesize:"<<hash_table.size()<<std::endl;
        for(uint i = 0; i < temp.size(); i++){
            auto entry = temp[i];
            for(auto val : entry){
                this->insert(val);
            }
        }
        temp.clear();
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

    int hash(const K& key) {
        int pos = key % hash_table.size();    
        return pos;       
    }

};

void testChainInsert(void)
{
    Hash<int, int> * garbage = new ChainingHash<int, int>;
    garbage->emplace(4,4);
    std::cout<<"loadFactor 4:"<<garbage->load_factor()<<std::endl;
    garbage->emplace(15,15);
        std::cout<<"loadFactor 15:"<<garbage->load_factor()<<std::endl;
    garbage->emplace(26,26);
        std::cout<<"loadFactor 26:"<<garbage->load_factor()<<std::endl;
garbage->emplace(7,7);
    std::cout<<"loadFactor 7:"<<garbage->load_factor()<<std::endl;
garbage->emplace(8,8);
    std::cout<<"loadFactor 8:"<<garbage->load_factor()<<std::endl;
garbage->emplace(9,9);
    std::cout<<"loadFactor 9:"<<garbage->load_factor()<<std::endl;
garbage->emplace(0,0);
    std::cout<<"loadFactor 0:"<<garbage->load_factor()<<std::endl;
garbage->emplace(16,16);
    std::cout<<"loadFactor 16:"<<garbage->load_factor()<<std::endl;
garbage->emplace(17, 17);
    std::cout<<"loadFactor 17:"<<garbage->load_factor()<<std::endl;
garbage->emplace(18, 18);
    std::cout<<"loadFactor 18:"<<garbage->load_factor()<<std::endl;

}
void test_Functions()
{   
    //Testing Insertions
    ChainingHash<int, int> Chains;
    Chains.insert(std::make_pair(5,5));
    Chains.insert(std::make_pair(7,7));
    Chains.insert(std::make_pair(13,13));
    Chains.insert(std::make_pair(9,9));
    Chains.insert(std::make_pair(4,4));
    Chains.emplace(1,1);
    Chains.emplace(2,2);
    Chains.emplace(6,6);
    Chains.emplace(10,10);

    //testing bucket count
    Chains.bucket_count();
    cout <<"The Bucket count after insertion is : " << Chains.bucket_count() << endl;

    //testing the content of a value based on a key
    cout <<"Inside bucket 5: " <<Chains.at(5)<< endl;

    //checking for specific buckets
    cout <<"Checking bucket 5: " << Chains.bucket(5) << endl;
    cout <<"Checking bucket 7: " << Chains.bucket(7) << endl;
    cout << "Checking bucket 9: " <<Chains.bucket(9) << endl;
    cout << "Checking bucket 1: " <<Chains.bucket(1) << endl;
    cout << "Checking bucket 2: " <<Chains.bucket(2) << endl;


    
    //testing overload[]
    cout << "h[13] is :" << Chains[13] << endl;


}

void test_Rehash()
{
    ChainingHash<int, int> Chains;
    for(int i = 0; i <= 100; i++)
        Chains.emplace(i,i);
    //testing bucket Size
    cout << "The bucket size of Bucket [1] is : " << Chains.bucket_size(1) <<endl;
    cout << "The bucket size of Bucket [10] is : " << Chains.bucket_size(10) <<endl;
    cout << "The bucket size of Bucket [50] is : " << Chains.bucket_size(50) <<endl;
    cout << "The bucket size of Bucket [40] is : " << Chains.bucket_size(40) <<endl;
    


}

void test_Erase()
{
    ChainingHash<int, int> Chains;
    Chains.insert(std::make_pair(5,5));
    Chains.insert(std::make_pair(7,7));
    Chains.insert(std::make_pair(13,13));
    //Erasing based on Key
    
   Chains.erase(5);
   cout <<"Checking bucket 5: " << Chains.bucket(5) << endl;
   

    //checking if key exists in the bucket
   // cout << "THe bucket size of 5 is : " << Chains.bucket(5) << endl;
    //cout << "THe bucket size of 9 is : " << Chains.bucket(9) << endl;
    //cout << "THe bucket size of 4 is : " << Chains.bucket(4) << endl;
    //cout << "THe bucket size of 1 is : " << Chains.bucket(1) << endl;

}

#endif //__CHAINING_HASH_H
