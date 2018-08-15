#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "double_ended_list.h"
#include "self_sorting_list.h"
#include "tree.h"
#include "utl.h"

delNode* delSetNode(int x) {
	delNode* v = (delNode*)malloc(sizeof(delNode));

	if (v == NULL) {
		// Malloc failure
		fprintf(stderr, "MALLOC ERROR\n");
		emergencyExit();
		exit(1);
	}

	v->val = x;
	v->prev = NULL;
	v->next = NULL;

	return v;
}

deList* delSetList () {
	deList* l = (deList*)malloc(sizeof(delNode));

	l->first = delSetNode(-1);
	l->last = delSetNode(-1);
	(l->first)->next = l->last;
	(l->last)->prev = l->first;

	return l;
}

void delAddFront (deList* l, int x) {
	delNode* n = delSetNode(x);

	n->prev = (l->first);
	n->next = (l->first)->next;
	((l->first)->next)->prev = n;
	(l->first)->next = n;
}

void delAddBack (deList* l, int x) {
	delNode* n = delSetNode(x);

	n->prev = (l->last)->prev;
	n->next = l->last;
	((l->last)->prev)->next = n;
	(l->last)->prev = n;
}

int delGetFront (deList* l) {
	if ((l->first)->next == l->last) {
		printf("ERROR: List is empty!\n");
		return -1;
	}

	return ((l->first)->next)->val;
}

int delGetBack (deList* l) {
	if ((l->last)->prev == l->first) {
		printf("ERROR: List is empty!\n");
		return -1;
	}

	return ((l->last)->prev)->val;
}

// Na miejsce elementu z jednej listy wstawia inną listę
void delSwapElementWithList (delNode* el, deList* l) {
	if (el->val == -1) {
		printf("ERROR: cannot swap with nothing\n");
	}
	else if ((l->first)->next == l->last) {
		(el->prev)->next = el->next;
		(el->next)->prev = el->prev;
	}
	else {
		(el->prev)->next = (l->first)->next;
		(el->next)->prev = (l->last)->prev;
		((l->first)->next)->prev = el->prev;
		((l->last)->prev)->next = el->next;
	}

	free(el);
	free(l->first);
	free(l->last);
	free(l);
}

void delRemoveFront (deList* l) {
	if ((l->first)->next == l->last) {
		printf("ERROR: List is empty!\n");
	}
	else {
		delNode* n = l->first->next;

		(n->next)->prev = l->first;
		(l->first)->next = n->next;

		free(n);
		// printf("Removed from the front\n");
	}
}

void delRemoveBack (deList* l) {
	if ((l->last)->prev == l->first) {
		printf("ERROR: List is empty!\n");
	}
	else {
		delNode* n = l->last->prev;

		(n->prev)->next = l->last;
		(l->last)->prev = n->prev;

		free(n);
		// printf("Removed from the front\n");
	}
}

void delDeleteList (deList* l) {
	delNode* n = l->first->next;

	while (n != l->last) {
		n = n->next;
		delRemoveFront(l);
	}

	free(l->first);
	free(l->last);
	free(l);
	// printf("List removed\n");
}

void delPrintFront (deList* l) {
	if ((l->first)->next == l->last) {
		printf("Empty\n");
	}
	else {
		delNode* n = l->first->next;

		while (n != l->last) {
			printf("%d ", n->val);
			n = n->next;
		}
		
		printf("\n");
	}
}

void delPrintBack (deList* l) {
	if ((l->last)->prev == l->first){
		printf("Empty\n");
	}
	else {
		delNode* n = l->last->prev;

		while (n != l->first) {
			printf("%d ", n->val);
			n = n->prev;
		}

		printf("\n");
	}
}
