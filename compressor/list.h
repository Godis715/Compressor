#pragma once

template<typename T> struct note {
	note *next = nullptr;
	T *value = nullptr;
};

template<typename T> struct list {

	note<T> *head = nullptr;
	note<T> *tail = nullptr;
};

namespace listspace {
	template<typename T> void pushBack(list<T> *thisList, T *thisValue);

	template<typename T> list<T> *createList();

	template<typename T> void deleteList(list<T> *thisList);

	template<typename T> void sort(list<T> *&thisList, bool(*cmp)(note<T>*, note<T>*));

	template<typename T> void mergeLists(list<T> *list1, list<T> *list2, bool(*cmp)(note<T>*, note<T>*));
}

template<typename T> void listspace::pushBack(list<T> *thisList, T *thisValue) {
	note<T> *newNote = new note<T>{ nullptr, thisValue };

	if (thisList->tail == nullptr) {
		thisList->tail = newNote;
		thisList->head->next = newNote;
		return;
	}

	thisList->tail->next = newNote;
	thisList->tail = newNote;
}

template<typename T> list<T> *listspace::createList() {
	list<T> *newList = new list<T>;
	note<T> *guardian = new note<T>;
	
	newList->head = guardian;
	return newList;
}

template<typename T> void listspace::deleteList(list<T> *thisList) {

	note<T> *temp = nullptr;
	for (note<T> *i = thisList->head; i != nullptr; i = temp) {
		temp = i->next;
		delete(i);
	}

	delete thisList;
}

template<typename T> void listspace::mergeLists(list<T> *list1, list<T> *list2, bool(*cmp)(note<T>*, note<T>*)) {
	note<T> *i = list1->head->next;
	note<T> *j = list2->head->next;
	note<T> *iPrev = list1->head;

	while (i != nullptr && j != nullptr) {
		if (cmp(i, j)) {
			iPrev->next = j;
			j = j->next;
			iPrev = iPrev->next;
			iPrev->next = i;
		}
		else {
			iPrev = i;
			i = i->next;
		}
	}
	if (i == nullptr) {
		iPrev->next = j;
		list1->tail = list2->tail;
	}
	list2->head->next = nullptr;
	list2->tail = nullptr;
}

template<typename T> void listspace::sort(list<T> *&thisList, bool(*cmp)(note<T>*, note<T>*)) {

	list<list<T> > *sortList = listspace::createList<list<T> >();

	for (note<T> *i = thisList->head->next; i != nullptr; i = i->next) {
		list<T> *newList = listspace::createList<T>();
		listspace::pushBack<T>(newList, i->value);
		listspace::pushBack<list<T> >(sortList, newList);
	}

	note<list<T> > *i = sortList->head->next;
	while (i->next != nullptr) {
		while (true) {
			note<list<T> > *list1 = i;
			i = i->next;
			if (i == nullptr) {
				break;
			}
			note<list<T> > *list2 = i;

			listspace::mergeLists(list1->value, list2->value, cmp); 
			list1->next = list2->next;

			if (list2->next == nullptr) {
				sortList->tail = list1;
				//delete list2->value;
				break;
			}
			else {
				i = i->next;
				list1->next = i;
				//delete list2->value;
			}
		}
		i = sortList->head->next;
	}
	thisList = sortList->head->next->value;

}