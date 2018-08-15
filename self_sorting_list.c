#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "double_ended_list.h"
#include "self_sorting_list.h"
#include "tree.h"
#include "utl.h"

sslNode* sslSetNode(long long int x) {
	sslNode* v = (sslNode*)malloc(sizeof(sslNode));

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

ssList* sslSetList () {
	ssList* l = (ssList*)malloc(sizeof(ssList));

	l->first = sslSetNode(INT_MAX);
	l->last = sslSetNode(-1);
	(l->first)->next = l->last;
	(l->last)->prev = l->first;

	return l;
}

bool sslAdd (ssList* l, long long int x) { // descending list
	sslNode* n = sslSetNode(x);
	sslNode* el = l->first->next;

	while (el != l->last && (el->val) > x) {
		el = el->next;
	}

	if (el->val != x) {
		n->next = el;
		n->prev = (el->prev);
		(el->prev)->next = n;
		el->prev = n;
		return true;
	}
	else {
		free(n);
		return false;
	}
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
		// printf("Removed from the back\n");
	}
}

bool sslRemoveVal (ssList* l, long long int x) {
	sslNode* n = (l->first)->next;

	while (n != l->last && n->val > x) {
		n = n->next;
	}

	if (n->val == x) {
		(n->prev)->next = n->next;
		(n->next)->prev = n->prev;

		free(n);

		return true;
	}
	else {
		// Value does not exist
		return false;
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
	if ((l->first)->next == l->last) {
		printf("NONE\n");
	}
	else {
		sslNode* n = (l->first)->next;

		while (n != l->last) {
			printf("%lld", n->val);
			n = n->next;
			if (n != l->last) {
				printf(" ");
			}
		}

		printf("\n");
	}
}

void sslPrintASC (ssList* l) {
	if ((l->last)->prev == l->first) {
		printf("Empty\n");
	}
	else {
		sslNode* n = (l->last)->prev;

		while (n != l->first) {
			printf("%lld ", n->val);
			n = n->prev;
		}

		printf("\n");
	}
}

// Bierze dwie listy i merguje je ze sobą tworząc nową listę, zaś stare listy usuwa
ssList* sslMerge (ssList* l1, ssList* l2, int k) {
	ssList* l = sslSetList();
	long long int last = -1; // wartość wzięta w poprzednim kroku
	sslNode* n1 = (l1->first)->next;
	sslNode* n2 = (l2->first)->next;

	for (int i = 0; i < k; ++i) {
		// Przypadek 1: obie listy są niepuste
		if (n1 != l1->last && n2 != l2->last) {
			// bierzemy większy element z pierwszej listy...
			if (n1->val > n2->val) {
				if (n1->val != last) {
					sslAdd(l, n1->val);
					last = n1->val;
				}
				else {
					--i;
				}
				n1 = n1->next;
			}
			// ... lub z drugiej
			else {
				if (n2->val != last) {
					sslAdd(l, n2->val);
					last = n2->val;
				}
				else {
					--i;
				}
				n2 = n2->next;
			}
		}
		// Przypadek 2: lista #1 jest pusta
		else if (n2 != l2->last) {
			if (n2->val != last) {
				sslAdd(l, n2->val);
				last = n2->val;
			}
			else { 
				--i;
			}
			n2 = n2->next;
		}
		// Przypadek 3: lista #2 jest pusta
		else if (n1 != l1->last) {
			if (n1->val != last) {
				sslAdd(l, n1->val);
				last = n1->val;
			}
			else {
				--i;
			}
			n1 = n1->next;
		}
		// Przypadek 4: obie listy są puste
		else {
			// printf("ERROR: not enough movies");
			continue;
		}
	}

	sslDeleteList(l1);
	sslDeleteList(l2);
	return l;
}

// Bierze dwie listy i merguje je ze sobą, uznając przy tym listę drugą za ważniejszą.
// Wynikiem jest nowa lista. Usuwana zostaje tylko lista pierwsza.
ssList* sslPriorityMerge (ssList* l1, ssList* l2, int k) {
	// l1 to lista preferencji potomków, l2 zaś jest listą preferencji ojca
	ssList* l = sslSetList();
	int i = 0;
	sslNode* n1 = (l1->first)->next;
	sslNode* n2 = (l2->first)->next;

	// Jeśli lista ojca jest pusta, to bierzemy filmy dzieci
	if (n2 == l2->last) {
		while (n1 != l1->last  && i < k) {
			sslAdd(l, n1->val);
			n1 = n1->next;
			++i;
		}

		sslDeleteList(l1);
		return l;
	}

	// Jeśli lista dzieci jest pusta, to bierzemy filmy ojca
	if (n1 == l1->last) {
		while (n2 != l2->last  && i < k) {
			sslAdd(l, n2->val);
			n2 = n2->next;
			++i;
		}

		sslDeleteList(l1);
		return l;
	}

	// Jeśli zarówno lista ojca jak i dzieci jest niepusta,
	// to zaczynamy od wzięcia filmów dzieci o ocenach wyższych niż najwyższa ocena ojca.
	while (n1 != l1->last && n2 != l2->last && i < k && n1->val > n2->val) {
		sslAdd(l, n1->val);
		n1 = n1->next;
		++i;
	}

	// Dopełniamy tworzoną listę filmami ojca
	while (n2 != l2->last && i < k) {
		sslAdd(l, n2->val);
		n2 = n2->next;
		++i;
	}

	sslDeleteList(l1);
	return l;
}
