#pragma once
#include <fstream>
#include <iostream>
#include "binTree.h"
#include "list.h"

struct word {
	int thisword = 0;
	int frequency = 0;
	bool isOne = false;
};

// create an empty int array
int *createCountArray(int size) {
	int *newArray = new int[size];
	for (int i = 0; i < size; ++i) {
		newArray[i] = 0;
	}
	return newArray;
}

// counts the words in file and fill the countArray (auxiliary)
bool toCountWords(char* filename, int *countArray, int size, int wordLength) {

	std::ifstream inp;
	inp.open(filename, std::ios::binary);

	if (!inp.is_open()) {
		return false;
	}

	// char buffer for reading bytes
	const int buffSize = 4;
	char buff[buffSize]{0};

	// ..merge bytes into single sequence of bits
	unsigned long long bits = 0;

	// bit mask for selecting words in the bit-sequence 
	int mask = (1 << wordLength) - 1;

	// shift bits at this value, to save them into 'bits'
	// or pointer on the end of bit sequence into 'bits'
	int shiftBitsAt = 0;

	while (!inp.eof()) {
		inp.read(buff, buffSize);

		// we want to know the real number of bytes read
		int realBuffSize = buffSize;
		if (inp.eof()) {
			realBuffSize = inp.gcount();
		}

		// temp buffer for merging read bytes and saving them into 'bits'
		unsigned long long bitsBuffer = 0;
		for (int i = 0; i < realBuffSize; ++i) {
			int maskForByte = 0x0000FF;
			bitsBuffer = bitsBuffer + (((unsigned long long)buff[i] & maskForByte) << 8 * i);
		}

		// saving read bits into 'bits'
		bits = bits + (bitsBuffer << shiftBitsAt);
		// changing value of shifBitsAt
		shiftBitsAt = shiftBitsAt + 8 * realBuffSize;

		// renaming
		int sequenceSize = shiftBitsAt;

		while (sequenceSize >= wordLength) {
			
			// count number of the word in the count array
			int word = bits & mask;

			++countArray[word];

			bits = bits >> wordLength;
			sequenceSize -= wordLength;
		}

		shiftBitsAt = sequenceSize;

	}

	inp.close();
	return true;
}

// fill the countArray using previous function
int *toFillCountArray(int wordLength, char *filename) {

	int size = 1 << wordLength;
	int *countArray = createCountArray(size);

	if (!toCountWords(filename, countArray, size, wordLength)) {
		std::cout << "Error" << std::endl;
	}

	return countArray;
}

// create the LIST of SIMPLE TREES OF WORDS - NOT SORTED
list<tree<word> > *createTreeWordsList(int *countArray, int wordLength) {
	list<tree<word> > *newTreeOfWords = listspace::createList<tree<word> >();
	int size = 1 << wordLength;
	for (int i = 0; i < size; ++i) {
		// exept words with null frequency
		if (countArray[i] != 0) {
			word *newWord = new word{ i, countArray[i], false };
			node<word> *newRoot = new node<word>{nullptr, nullptr, nullptr, newWord};
			tree<word> *newTree = treespace::createSimpleTree<word>(newRoot);
			listspace::pushBack<tree<word> >(newTreeOfWords, newTree);
		}
	}

	return newTreeOfWords;
}

// comporator for sorting treeWordsList
bool cmp(note<tree<word> > *a, note<tree<word> > *b) {
	return a->value->root->value->frequency > b->value->root->value->frequency;
}

void sortTreeWordsList(list<tree<word> > *treeWordsList) {
	listspace::sort<tree<word> >(treeWordsList, cmp);
}

