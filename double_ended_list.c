#include <stdio.h>
#include <stdlib.h>
#include "double_ended_list.h"

delNode* delSetNode(int x) {
	delNode* v = (delNode*)malloc(sizeof(delNode));
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

deList* delSetList () {
	deList* l = (deList*)malloc(sizeof(delNode));
	l->size = 0;
	l->first = NULL;
	l->last = NULL;
	return l;
}

void delAddFront (deList* l, int x) {
	delNode* n = delSetNode(x);
	delNode* fst = l->first;
	if (fst == NULL) {
		l->first = n;
	}
	else {
		delNode* lst = l->last;
		if (lst == NULL)
			lst = fst;
		n->next = fst;
		fst->prev = n;
		l->first = n;
		l->last = lst;
	}
	l->size++;
}

void delAddBack (deList* l, int x) {
	delNode* n = delSetNode(x);
	delNode* lst = l->last;
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
		delNode* fst = l->first;
		if (fst == NULL)
			fst = lst;
		n->prev = lst;
		lst->next = n;
		l->last = n;
		l->first = fst;
	}
	l->size++;
}

int delGetFront (deList* l) {
	if (l->first == NULL) {
		printf("ERROR: List is empty!\n");
		return -1;
	}
	return (l->first)->val;
}

int delGetBack (deList* l) {
	if (l->last == NULL)
		return delGetFront(l);
	return (l->last)->val;
}

void delAppend (deList* l1, deList* l2) {
	if (l1->size > 1 && l2->size > 1 ) {
		(l1->last)->next = l2->first;
		(l2->first)->prev = l1->last;
		l1->last = l2->last;
		l1->size += l2->size;
	}
	else if (l1->size == 1 && l2->size == 1) {
		(l2->first)->prev = l1->first;
		l1->last = l2->first;
		(l1->first)->next = l2->first;
	}
	else if (l1->size == 0) {
		l1->first = l2->first;
		l1->last = l2->last;
		l1->size = l2->size;
	}
	else {;}
	if(l2 != NULL)
		free(l2);
}

void delRemoveFront (deList* l) {
	if (l->first == NULL) { // no elements
		printf("ERROR: List is empty!\n");
	}
	else {
		delNode* n = l->first;
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

void delRemoveBack (deList* l) {
	if (l->last == NULL) { // at most 1 element
		delRemoveFront(l);
	}
	else { // at least two elements
		delNode* n = l->last;
		(n->prev)->next = NULL;
		l->last = n->prev;
		if (l->size == 2) 
			l->last = NULL;
		l->size--;
		free(n);
		printf("Removed from the back\n");
	}
}

void delDeleteList (deList* l) {
	while (l->size != 0) {
		delRemoveFront(l);
	}
	printf("List removed\n");
}

void delPrintFront (deList* l) {
	delNode* n = l->first;
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

void delPrintBack (deList* l) {
	delNode* n = l->last;
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
