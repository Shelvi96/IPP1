#include <stdio.h>
#include <stdlib.h>
#include "self_sorting_list.h"

sslNode* sslSetNode(int x) {
	sslNode* v = (sslNode*)malloc(sizeof(sslNode));
	if (v == NULL) {
		printf("MALLOC ERROR");
		// free all allocs - delete tree
		exit(1);
	}
	v->val = x;
	v->prev = NULL;
	v->next = NULL;
	return v;
}

ssList* sslSetList () {
	ssList* l = (ssList*)malloc(sizeof(ssList));
	l->size = 0;
	l->first = NULL;
	l->last = NULL;
	return l;
}

void sslAdd (ssList* l, int x) { // descending list
	sslNode* n = sslSetNode(x);
	sslNode* el = l->first;
	sslNode* ell = l->last;

	if (el == NULL) { // list is empty
		l->first = n;
	}
	else if (ell == NULL) { // list has only 1 element
		if (x == el->val) {
			printf ("ERROR: element was on the list\n");
			l->size--;
		}
		else if (x > el->val) { // x > head
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
		else if (el->val == x) { // element was on the list
			printf ("ERROR: element was on the list\n");
			l->size--;
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

int sslGetMax (ssList* l) {
	if (l->size == 0) {
		printf("ERROR: List is empty\n");
		return -1;
	}
	return (l->first)->val;
}

int sslGetMin (ssList* l) {
	if (l->size < 2)
		return sslGetMax(l);
	return (l->last)->val;
}

void sslRemoveFront (ssList* l) {
	if (l->first == NULL) { // no elements
		printf("ERROR: List is empty!\n");
	}
	else {
		sslNode* n = l->first;
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

void sslRemoveBack (ssList* l) {
	if (l->last == NULL) { // at most 1 element
		sslRemoveFront(l);
	}
	else { // at least two elements
		sslNode* n = l->last;
		(n->prev)->next = NULL;
		l->last = n->prev;
		if (l->size == 2) 
			l->last = NULL;
		l->size--;
		free(n);
		printf("Removed from the back\n");
	}
}

void sslRemoveVal (ssList* l, int x) {
	sslNode* n = l->first;
	if ((l->first)->val == x) 
		sslRemoveFront(l);
	else if ((l->last)->val == x) 
		sslRemoveBack(l);
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

void sslDeleteList (ssList* l) {
	while (l->size != 0) {
		sslRemoveFront(l);
	}
	free(l);
	printf("List removed\n");
}

void sslPrintDSC (ssList* l) { // old: printFront
	if (l->size == 0)
		printf("ERROR: list is empty\n");
	else {
		sslNode* n = l->first;
		for(int i = 0; i < l->size; ++i) {
			printf("%d ", n->val);
			n = n->next;
		}
		enter
	}
}

void sslPrintASC (ssList* l) { // old: printBack
	if (l->size < 2)
		sslPrintDSC(l);
	else {
		sslNode* n = l->last;
		for(int i = 0; i < l->size; ++i) {
			printf("%d ", n->val);
			n = n->prev;
		}
		enter
	}
}
