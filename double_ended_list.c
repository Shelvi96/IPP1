#include <stdio.h>
#include <stdlib.h>
#include "double_ended_list.h"

Node* setNode(int x) {
	Node* v = (Node*)malloc(sizeof(Node));
	v->val = x;
	v->prev = NULL;
	v->next = NULL;
	return v;
}

deList setList () {
	deList l;
	l.size = 0;
	l.first = NULL;
	l.last = NULL;
	return l;
}

void addFront (deList* l, int x) {
	Node* n = setNode(x);
	Node* fst = l->first;
	if (fst == NULL) {
		l->first = n;
	}
	else {
		Node* lst = l->last;
		if (lst == NULL)
			lst = fst;
		n->next = fst;
		fst->prev = n;
		l->first = n;
		l->last = lst;
	}
	l->size++;
}

void addBack (deList* l, int x) {
	Node* n = setNode(x);
	Node* lst = l->last;
	if (lst == NULL) {
		if (l->first == NULL)
			l->first = n;
		else {
			n->prev = l->first;
			l->last = n;
			(l->first)->next = n;
		}
	}
	else {
		Node* fst = l->first;
		if (fst == NULL)
			fst = lst;
		n->prev = lst;
		lst->next = n;
		l->last = n;
		l->first = fst;
	}
	l->size++;
}

int getFront (deList* l) {
	if (l->first == NULL) {
		printf("ERROR: List is empty!\n");
		return -1;
	}
	return (l->first)->val;
}

int getBack (deList* l) {
	if (l->last == NULL)
		return getFront(l);
	return (l->last)->val;
}

void removeFront (deList* l) {
	if (l->first == NULL) { // no elements
		printf("ERROR: List is empty!\n");
	}
	else {
		Node* n = l->first;
		if (n->next != NULL) { // at least 2 elements
			(n->next)->prev = NULL;
			l->first = n->next;
			if (l->size == 2)
				l->last = NULL;
		}
		else { // just 1 element
			l->first = NULL;
		}
		l->size--;
		free(n);
		printf("Removed from the front\n");
	}
}

void removeBack (deList* l) {
	if (l->last == NULL) { // at most 1 element
		removeFront(l);
	}
	else { // at least two elements
		Node* n = l->last;
		(n->prev)->next = NULL;
		l->last = n->prev;
		if (l->size == 2) 
			l->last = NULL;
		l->size--;
		free(n);
		printf("Removed from the back\n");
	}
}

void deleteList (deList* l) {
	while (l->size != 0) {
		removeFront(l);
	}
	printf("List removed\n");
}

void printFront (deList* l) {
	Node* n = l->first;
	if (l->size > 0) {
		for(int i = 0; i < l->size; ++i) {
			printf("%d ", n->val);
			n = n->next;
		}
		enter
	}
	else
		printf("Empty\n");
}

void printBack (deList* l) {
	Node* n = l->last;
	if (l->size > 0) {
		if (l->last == NULL)
			n = l->first;
		for(int i = 0; i < l->size; ++i) {
			printf("%d ", n->val);
			n = n->prev;
		}
		enter
	}
	else
		printf("Empty\n");
}

int main() {
	deList l = setList();

	int x;
	for(int i = 0; i < 5; ++i) {
		scanf("%d", &x);
		addFront(&l, x);
	}

	deleteList(&l);

	return 0;
}
