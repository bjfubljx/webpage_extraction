#pragma once
#include <iostream>
#include <cstdio>
#include <bitset>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <cstring>
 
using namespace std;
using std::bitset;
 
typedef unsigned int uint;
#define N 1<<20

class BloomFilter
{
public:
    BloomFilter(int m, int n):m_m(m), m_n(n)
	{
		m_k = ceil((m/n) * log(2.0));
	}
    virtual ~BloomFilter()
	{}
	
	uint RSHash(const char *str, int seed);
	void SetKey(const char* str);
	int VaryExist(const char* str);
 
private:
	int m_k, m_m, m_n; //k:number of the hash functions //m:the size of bitset //n:number of strings to hash (k = [m/n]*ln2)
	bitset<N> bit;
};
 