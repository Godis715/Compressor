#pragma once
#include "list.h"

template<typename T>
struct node {

	node *leftChild = nullptr;
	node *rightCild = nullptr;

	node *parent = nullptr;

	T *value = nullptr;
};


template<typename T>
struct tree {
	node<T> *root = nullptr;
	list<node<T> > *leaves = nullptr;
};

namespace treespace {
	template<typename T>
	tree<T> *createSimpleTree(node<T> *thisRoot);

	template<typename T>
	tree<T> *mergeTrees(tree<T> *tree1, tree<T> *tree2, T* (*mergeValue)(T*, T*));
}

template<typename T>
tree<T> *treespace::createSimpleTree(node<T> *thisRoot) {
	tree<T> *newTree = new tree<T>;

	newTree->root = thisRoot;
	newTree->leaves = listspace::createList<node<T> >();
	listspace::pushBack<node<T> >(newTree->leaves, thisRoot);

	return newTree;
}

template<typename T>
tree<T> *treespace::mergeTrees(tree<T> *tree1, tree<T> *tree2, T* (*mergeValue)(T*, T*)) {

	node<T> *newRoot = new node<T>;

	// root merging
	newRoot->leftChild = tree1->root;
	newRoot->rightCild = tree2->root;
	newRoot->leftChild->parent = newRoot;
	newRoot->rightCild->parent = newRoot;

	// merging of leaves list
	list <node<T> > *newLeaves = tree1->leaves;
	newLeaves->tail->next = tree2->leaves->head;
	newLeaves->tail = tree2->leaves->tail;

	tree<T> *newTree = treespace::createSimpleTree(newRoot);
	newTree->leaves = newLeaves;
	newTree->root = newRoot;
	newTree->root->value = mergeValue(tree1->root->value, tree2->root->value);

	delete tree1;
	delete tree2;

	return newTree;
}