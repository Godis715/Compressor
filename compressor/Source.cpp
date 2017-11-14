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
bool cmp(note<int> *a, note<int> *b) {
	return *(a->value) > *(b->value);
}

int main() {

	int *arr = createCountArray(8);
	char filename[] = "input.txt";

	toCountWords(filename, arr, 8, 3);

	for (int i = 0; i < 8; ++i) {
		cout << arr[i] << ' ';
	}


	system("pause");
	return 0;

	list<int> *newList = listspace::createList<int>();

	for (int i = 0; i < 100000; ++i) {
		listspace::pushBack(newList, new int{ rand() % 100 });
	}

	cout << endl;
	listspace::sort<int>(newList, cmp);
	for (auto i = newList->head->next; i != nullptr; i = i->next) {
		cout << *(i->value) << " ";
	}

	system("pause");
	return 0;

	node<int> *root1 = new node<int>{ nullptr, nullptr, nullptr, new int{ 1 } };
	node<int> *root2 = new node<int>{ nullptr, nullptr, nullptr, new int{ 2 } };

	tree<int> *tree1 = treespace::createSimpleTree<int>(root1);
	tree<int> *tree2 = treespace::createSimpleTree<int>(root2);

	tree<int> *newTree = treespace::mergeTrees(tree1, tree2, mergeValue);

	cout << *(newTree->root->leftChild->value) << *(newTree->root->rightCild->value) << *(newTree->root->value);

	system("pause");

	return 0;
}