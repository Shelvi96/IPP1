#include <stdio.h>
#include <stdlib.h>
#include "self_sorting_list.h"

Node* setNode(int x) {
	Node* v = (Node*)malloc(sizeof(Node));
	v->val = x;
	v->prev = NULL;
	v->next = NULL;
	return v;
}

ssList setList () {
	ssList l;
	l.size = 0;
	l.first = NULL;
	l.last = NULL;
	return l;
}

void add (ssList* l, int x) { // descending list
	Node* n = setNode(x);
	Node* el = l->first;
	Node* ell = l->last;

	if (el == NULL) { // list is empty
		l->first = n;
	}
	else if (ell == NULL) { // list has only 1 element
		if (x > el->val) { // x > head
			ell = el; ell->prev = n;
			el  = n; el->next = ell;
			l->first = el;
			l->last = ell;
		}
		else { // x <= head
			n->prev = el;
			el->next = n;
			l->first = el;
			l->last = n;
		}
	}
	else { // list has at least two elements
		while (el != NULL && (el->val) > x) {
			el = el->next;
		}
		if (el == NULL) { // new minimum
			ell->next = n;
			n->prev = ell;	
			l->last = n;
		}
		else if (el == l->first) { // new maximum
			n->next = el;
			el->prev = n;
			l->first = n;
		}
		else { // put new between two elements form the list
			n->next = el;
			n->prev = (el->prev);
			(el->prev)->next = n;
			el->prev = n;
		}
	}

	l->size++;
}

int getMax (ssList* l) {
	return (l->first)->val;
}

int getMin (ssList* l) {
	return (l->last)->val;
}

void removeFront (ssList* l) {
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

void removeBack (ssList* l) {
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

void removeVal (ssList* l, int x) {
	Node* n = l->first;
	if ((l->first)->val == x) 
		removeFront(l);
	else if ((l->last)->val == x) 
		removeBack(l);
	else {
		while (n != NULL && n->val > x) {
			n = n->next;
		}
		if (n == NULL)
			printf ("Value does not exist\n");
		else {
			if (n->val != x)
				printf ("Value does not exist\n");
			else { // removing n
				(n->prev)->next = n->next;
				(n->next)->prev = n->prev;
				free(n);
				l->size--;
				printf ("Removed element\n");
			}	
		}
	}
}

void deleteList (ssList* l) {
	while (l->size != 0) {
		removeFront(l);
	}
	printf("List removed\n");
}

void printDSC (ssList* l) { // old: printFront
	Node* n = l->first;
	for(int i = 0; i < l->size; ++i) {
		printf("%d ", n->val);
		n = n->next;
	}
	enter
}

void printASC (ssList* l) { // old: printBack
	Node* n = l->last;
	for(int i = 0; i < l->size; ++i) {
		printf("%d ", n->val);
		n = n->prev;
	}
	enter
}

int main() {
	ssList l = setList();

	int x;
	for(int i = 0; i < 5; ++i) {
		scanf("%d", &x);
		add(&l, x);
	}

	printDSC(&l);
	removeVal(&l, 5);
	getMin(&l);
	getMax(&l);
	printDSC(&l);
	deleteList(&l);

	return 0;
}
