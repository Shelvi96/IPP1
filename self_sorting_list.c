#include <stdio.h>
#include <stdlib.h>
#include "double_ended_list.h"
#include "self_sorting_list.h"
#include "tree.h"
#include "utilities.h"

sslNode* sslSetNode(long long int x) {
	sslNode* v = (sslNode*)malloc(sizeof(sslNode));
	if (v == NULL) {
		// Malloc failure
		fprintf(stderr, "ERROR\n");
		emergencyExit();
		exit(1);
	}
	v->val = x;
	v->prev = NULL;
	v->next = NULL;
	return v;
}

ssList* sslSetList () {
	ssList* l = (ssList*)malloc(sizeof(ssList));
	l->first = sslSetNode(3000000000);
	l->last = sslSetNode(-1);
	(l->first)->next = l->last;
	(l->last)->prev = l->first;
	return l;
}

void sslAdd (ssList* l, long long int x) { // descending list
	sslNode* n = sslSetNode(x);
	sslNode* el = l->first->next;

	while (el != l->last && (el->val) > x) {
		el = el->next;
	}
	n->next = el;
	n->prev = (el->prev);
	(el->prev)->next = n;
	el->prev = n;
}

long long int sslGetMax (ssList* l) {
	if ((l->first)->next == l->last) {
		// printf("ERROR: List is empty\n");
		return -1;
	}
	return ((l->first)->next)->val;
}

long long int sslGetMin (ssList* l) {
	if ((l->last)->prev == l->first) {
		// printf("ERROR: List is empty\n");
		return -1;	
	}
	return ((l->last)->prev)->val;
}

void sslRemoveFront (ssList* l) {
	if ((l->first)->next == l->last) {
		printf("ERROR: List is empty!\n");
	}
	else {
		sslNode* n = (l->first)->next;
		(n->next)->prev = l->first;
		(l->first)->next = n->next;
		free(n);
		// printf("Removed from the front\n");
	}
}

void sslRemoveBack (ssList* l) {
	if ((l->last)->prev == l->first) {
		printf("ERROR: List is empty!\n");
	}
	else {
		sslNode* n = (l->last)->prev;
		(l->last)->prev = n->prev;
		(n->prev)->next = l->last;
		free(n);
		// printf("Removed from the front\n");
	}
}

void sslRemoveVal (ssList* l, long long int x) {
	sslNode* n = (l->first)->next;
	while (n != l->last && n->val > x) {
		n = n->next;
	}
	if (n->val == x) {
		(n->prev)->next = n->next;
		(n->next)->prev = n->prev;
		free(n);
		// printf ("Removed element\n");
	}
	else {
		// Value does not exist
		fprintf(stderr, "ERROR\n");
	}
}

void sslDeleteList (ssList* l) {
	sslNode* n = l->first->next;
	while (n != l->last) {
		n = n->next;
		sslRemoveFront(l);
	}
	free(l->first);
	free(l->last);
	free(l);
	// printf("List removed\n");
}

void sslPrintDSC (ssList* l) {
	if ((l->first)->next == l->last)
		printf("NONE\n");
	else {
		sslNode* n = (l->first)->next;
		while (n != l->last) {
			printf("%lld ", n->val);
			n = n->next;
		}
		enter
	}
}

void sslPrintASC (ssList* l) {
	if ((l->last)->prev == l->first)
		printf("Empty\n");
	else {
		sslNode* n = (l->last)->prev;
		while (n != l->first) {
			printf("%lld ", n->val);
			n = n->prev;
		}
		enter
	}
}

ssList* sslMerge (ssList* l1, ssList* l2, int k) {
	ssList* l = sslSetList();
	long long int last = -1; // value added in previous step
	sslNode* n1 = (l1->first)->next;
	sslNode* n2 = (l2->first)->next;
	for (int i = 0; i < k; ++i) {
		// case 1: both lists are not empty
		if (n1 != l1->last && n2 != l2->last) {
			// we choose element from list #1...
			if (n1->val > n2->val) {
				if (n1->val != last) {
					sslAdd(l, n1->val);
					last = n1->val;
				}
				else 
					--i;
				n1 = n1->next;
			}
			// ... or from list #2
			else {
				if (n2->val != last) {
					sslAdd(l, n2->val);
					last = n2->val;
				}
				else 
					--i;
				n2 = n2->next;
			}
		}
		// case 2: list #1 is empty
		else if (n2 != l2->last) {
			if (n2->val != last) {
				sslAdd(l, n2->val);
				last = n2->val;
			}
			else --i;
			n2 = n2->next;
		}
		// case 3: list #2 is empty
		else if (n1 != l1->last) {
			if (n1->val != last) {
				sslAdd(l, n1->val);
				last = n1->val;
			}
			else --i;
			n1 = n1->next;
		}
		// case 4: both lists are empty
		else {
			// printf("ERROR: not enough movies");
			continue;
		}
	}
	// sslDeleteList(l);
	return l;
}

ssList* sslPriorityMerge (ssList* l1, ssList* l2, int k) {
	ssList* l = sslSetList();
	int i = 0;
	sslNode* n1 = (l1->first)->next;
	sslNode* n2 = (l2->first)->next;
	if (n2 == l2->last) {
		// printf("ERROR: not enough movies\n");
		return l;
	}
	if (n1 == l1->last) {
		while (n2 != l2->last  && i < k) {
			sslAdd(l, n2->val);
			n2 = n2->next;
			++i;
		}
	}
	// first we take elements from more important list (#2)
	while (n1 != l1->last && n2 != l2->last && i < k && n1->val < n2->val) {
		sslAdd(l, n2->val);
		n2 = n2->next;
		++i;
	}
	// we check if first elements are equal
	// other elements cannot be equal
	if (n1 != l1->last && i < k && n1->val != sslGetMax(l)) {
		sslAdd(l, n1->val);
		n1 = n1->next;
		++i;
	}
	// then we take as many elements from list #1 as we can
	while (n1 != l1->last && i < k) {
		sslAdd(l, n1->val);
		n1 = n1->next;
		++i;
	}
	if (i < k) {
		sslDeleteList(l);
		return sslSetList();
	}
	return l;
}
