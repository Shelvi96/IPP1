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
}

int sslGetMax (ssList* l) {
	if (l->first == NULL) {
		printf("ERROR: List is empty\n");
		return -1;
	}
	return (l->first)->val;
}

int sslGetMin (ssList* l) {
	if (l->last == NULL)
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
			if ((l->first)->next == l->last)
				l->last = NULL;
		}
		else { // just 1 element
			l->first = NULL;
		}
		free(n);
		// printf("Removed from the front\n");
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
		if ((l->first)->next == l->last) 
			l->last = NULL;
		free(n);
		// printf("Removed from the back\n");
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
				// printf ("Removed element\n");
			}	
		}
	}
}

void sslDeleteList (ssList* l) {
	sslNode* n = l->first;
	while (n != NULL) {
		n = n->next;
		sslRemoveFront(l);
	}
	free(l);
	// printf("List removed\n");
}

void sslPrintDSC (ssList* l) { // old: printFront
	if (l->first == NULL)
		printf("Empty\n");
	else {
		sslNode* n = l->first;
		while (n != NULL) {
			printf("%d ", n->val);
			n = n->next;
		}
		enter
	}
}

void sslPrintASC (ssList* l) { // old: printBack
	if (l->last == NULL)
		sslPrintDSC(l);
	else {
		sslNode* n = l->last;
		while (n != NULL) {
			printf("%d ", n->val);
			n = n->prev;
		}
		enter
	}
}

ssList* sslMerge (ssList* l1, ssList* l2, int k) {
	ssList* l = sslSetList();
	int last = -1;
	sslNode* n1 = l1->first;
	sslNode* n2 = l2->first;
	for (int i = 0; i < k; ++i) {
		if (n1 != NULL && n2 != NULL) {
			if (n1->val > n2->val) {
				if (n1->val != last) {
					sslAdd(l, n1->val);
					last = n1->val;
				}
				else --i;
				n1 = n1->next;
			}
			else {
				if (n2->val != last) {
					sslAdd(l, n2->val);
					last = n2->val;
				}
				else --i;
				n2 = n2->next;
			}
		}
		else if (n2 != NULL) {
			if (n2->val != last) {
				sslAdd(l, n2->val);
				last = n2->val;
			}
			else --i;
			n2 = n2->next;
		}
		else if (n1 != NULL) {
			if (n1->val != last) {
				sslAdd(l, n1->val);
				last = n1->val;
			}
			else --i;
			n1 = n1->next;
		}
		else {
			printf("ERROR: not enough movies");
			return l;
		}
	}
	return l;

}

ssList* sslPriorityMerge (ssList* l1, ssList* l2, int k) {
	ssList* l = sslSetList();
	int i = 0;
	sslNode* n1 = l1->first;
	sslNode* n2 = l2->first;
	if (n1 == NULL && k > 0) {
		printf("ERROR: not enough movies");
		return l;
	}
	while (n1 != NULL && n2 != NULL && i < k && n1->val < n2->val) {
		sslAdd(l, n2->val);
		n2 = n2->next;
		++i;
	}
	if (n1 != NULL && i < k && n1->val != sslGetMax(l))
		sslAdd(l, n1->val);
	n1 = n1->next;
	++i;
	while (n1 != NULL && i < k) {
		sslAdd(l, n1->val);
		++i;
		n1 = n1->next;
	}
	if (i < k) printf("ERROR: not enough movies");
	return l;
}

int main() {
	ssList* l = sslSetList();
	ssList* m = sslSetList();

	sslAdd(l, 1);
	sslAdd(l, 3);
	sslAdd(l, 2);
	sslAdd(l, 7);
	sslAdd(l, 8);
	sslAdd(l, 10);
	
	sslPrintDSC(l);
	
	sslAdd(m, 12);
	sslAdd(m, 10);
	sslAdd(m, 9);
	sslAdd(m, 6);

	sslPrintDSC(m);

	ssList* k = sslMerge(l, m, 3);
	ssList* n = sslPriorityMerge(l, m, 3);

	sslPrintDSC(k);
	sslPrintDSC(n);

	sslDeleteList(l);
	sslDeleteList(m);
	sslDeleteList(k);
	sslDeleteList(n);

	return 0;
}