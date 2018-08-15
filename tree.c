#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "double_ended_list.h"
#include "self_sorting_list.h"
#include "tree.h"
#include "utl.h"
#define MAX_USERS 65536

treeTree* treeSetTree () {
	treeTree* t = (treeTree*)malloc(sizeof(treeTree));

	if (t == NULL) {
		// Malloc failure
		fprintf(stderr, "MALLOC ERROR\n");
		exit(1);
	}

	treeNode* root = (treeNode*)malloc(sizeof(treeNode));

	if (root == NULL) {
		// Malloc failure
		fprintf(stderr, "MALLOC ERROR\n");
		emergencyExit();
		exit(1);
	}

	root->userID = 0;
	root->children = delSetList();
	root->movies = sslSetList();
	root->parent = NULL;
	t->node = root;

	// Tablica przechowująca wskaźniki do wszystkich użytkowników
	t->users = (treeNode**)malloc(MAX_USERS*sizeof(treeNode*));

	if ((t->users) == NULL) {
		// Malloc failure
		fprintf(stderr, "MALLOC ERROR\n");
		emergencyExit();
		exit(1);
	}

	for (int i = 0; i < MAX_USERS; ++i) {
		(t->users)[i] = NULL;
	}

	(t->users)[0] = root;

	return t;
}

bool treeAddNode (treeTree* t, int parent_id, int id) {
	if ((t->users)[id] != NULL) {
		// Dodano już takiego użytkownika
		return false;
	}
	else if ((t->users)[parent_id] == NULL) {
		// Nie istnieje użytkownik, który miał stworzyć potomka
		return false;
	}
	else {
		treeNode* v = (treeNode*)malloc(sizeof(treeNode));

		if (v == NULL) {
			// Malloc failure
			fprintf(stderr, "MALLOC ERROR\n");
			emergencyExit();
			exit(1);
		}

		v->userID = id;
		v->children = delSetList();
		v->movies = sslSetList();

		(t->users)[id] = v;	
		treeNode* parent = (t->users)[parent_id];

		delAddBack(parent->children, id);

		v->parent = ((parent->children)->last)->prev;
	}

	return true;
}

bool treeDeleteNode (treeTree* t, int id) {
	if (id == 0) {
		// Nie można usunąć korzenia drzewa!
		return false;
	}
	else if ((t->users)[id] == NULL)
		// Użytkownik zgłoszony do usunięcia nie istnieje
		return false;
	else {
		treeNode* n = (t->users)[id];
		delNode* l = n->parent;

		delSwapElementWithList (l, n->children);
		
		sslDeleteList(n->movies);
		free(n);
		(t->users)[id] = NULL;
	}

	return true;
}

void treePrintTree (treeTree* t, int root_id) {
	treeNode* n = (t->users)[root_id];

	printf("%d ", n->userID);
	delPrintFront(n->children);

	delNode* c = ((n->children)->first)->next;

	while (c != (n->children)->last) {
		treePrintTree(t, c->val);
		c = c->next;
	}
}

void treeDeleteTree (treeTree* t) {
	for (int i = 0; i < MAX_USERS; ++i) {
		if (t->users[i] != NULL) {
			delDeleteList((t->users)[i]->children);
			sslDeleteList((t->users)[i]->movies);
			free((t->users)[i]);
		}
	}
	
	free(t->users);
	free(t);
}
