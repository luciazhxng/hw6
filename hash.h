#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include <vector>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        std::vector<HASH_INDEX_T> mapping; 
        std::vector<unsigned long long> w;
        for(int i = 0; i < k.size(); i++) {
            mapping.push_back(letterDigitToNumber(k[i]));
        }
        for(int i = mapping.size() - 1; i >= 0; i -= 6) {
            unsigned long long wi = 0;
            for(int j = i - 5; j <= i; j++) {
                if(j < 0) {
                    continue;
                }
                wi = (wi * 36 + mapping[j]);
            }
            
            w.push_back(wi);
        }
        for(int i = 0; i < w.size(); i++) {
        }
        HASH_INDEX_T result = 0;
        int w_ind = w.size() - 1;
        for(int i =  5 - w.size(); i < 5; i++) {
            result = result + rValues[i] * w[w_ind];
            w_ind--;
        }
        return result; 
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {   
        if(isdigit(letter)) {
            return letter - '0' + 26;
        }
        else if (isalpha(letter)) {
            return tolower(letter) - 'a';
        }
        return 0;

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
