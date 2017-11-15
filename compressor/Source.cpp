#include <iostream>
#include "list.h"
#include "binTree.h"
#include "hauffman.h"
#include <fstream>

using namespace std;

int *mergeValue(int *value1, int *value2) {
	int *value3 = new int;
	*value3 = *value1 + *value2;
	return value3;
}


int main() {

	char filename1[] = "Konfuciy.psd";
	int wordLength = 15;
	int sizeOfCountArray = 1 << wordLength;
	int *countArray = toFillCountArray(wordLength, filename1);

	//for (int i = 0; i < sizeOfCountArray; ++i) {
	//	cout << countArray[i] << ' ';
	//}

	list<tree<word> > *wordList = createTreeWordsList(countArray, wordLength);

	listspace::sort<tree<word> >(wordList, cmp);

	for (auto i = wordList->head->next; i != nullptr; i = i->next) {
		cout << "the word " << i->value->root->value->thisword << " frequency " << i->value->root->value->frequency << endl;
	}

	delete countArray;



	system("pause");
	return 0;

	//list<int> *newList = listspace::createList<int>();

	//for (int i = 0; i < 100000; ++i) {
	//	listspace::pushBack(newList, new int{ rand() % 100 });
	//}

	//cout << endl;
	//listspace::sort<int>(newList, cmp);
	//for (auto i = newList->head->next; i != nullptr; i = i->next) {
	//	cout << *(i->value) << " ";
	//}

	//system("pause");
	//return 0;

	//node<int> *root1 = new node<int>{ nullptr, nullptr, nullptr, new int{ 1 } };
	//node<int> *root2 = new node<int>{ nullptr, nullptr, nullptr, new int{ 2 } };

	//tree<int> *tree1 = treespace::createSimpleTree<int>(root1);
	//tree<int> *tree2 = treespace::createSimpleTree<int>(root2);

	//tree<int> *newTree = treespace::mergeTrees(tree1, tree2, mergeValue);

	//cout << *(newTree->root->leftChild->value) << *(newTree->root->rightCild->value) << *(newTree->root->value);

	//system("pause");

	//return 0;
}