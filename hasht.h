#pragma once
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

struct CountedString
{
	int count = 0;
	string str;

};


class hasht {

public:

	hasht(int size);
	~hasht();


	void insert(const string &str);
	void insert(const string &str, size_t hashIndex);


	unsigned long hash(const char *str);

	void print(int n);

	void betterfeed(const string &str);

	//after hashing

	void heapify(int heapsize, int index);
	void heapSort(int heapsize);

	void stopwordCleaner(string &stopwords);

	int gettablesize();


private:

	CountedString *htable; //array of string, count struct

	int length;
	int tablesize;

};
