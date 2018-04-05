#include <stdio.h>
#include <stdlib.h>
#include "double_ended_list.h"
#include "self_sorting_list.h"
#include "tree.h"
#include "utilities.h"

treeTree* treeSetTree () {
	treeTree* t = (treeTree*)malloc(sizeof(treeTree));
	if (t == NULL) {
		// Malloc failure
		fprintf(stderr, "ERROR\n");
		emergencyExit();
		exit(1);
	}

	treeNode* root = (treeNode*)malloc(sizeof(treeNode));
	if (root == NULL) {
		// Malloc failure
		fprintf(stderr, "ERROR\n");
		emergencyExit();
		exit(1);
	}
	root->userID = 0;
	root->children = delSetList();
	root->movies = sslSetList();
	root->parent = NULL;
	t->node = root;

	// creating array to store pointers to all users from tree
	t->users = (treeNode**)malloc(65535*sizeof(treeNode*));
	if ((t->users) == NULL) {
		// Malloc failure
		fprintf(stderr, "ERROR\n");
		emergencyExit();
		exit(1);
	}
	for (int i = 0; i < 65535; ++i)
		(t->users)[i] = NULL;

	(t->users)[0] = root;

	return t;
}

void treeAddNode (treeTree* t, int id, int parentid) {
	if ((t->users)[id] != NULL) {
		// User already in database
		fprintf(stderr, "ERROR\n");
	}
	else {
		treeNode* v = (treeNode*)malloc(sizeof(treeNode));
		if (v == NULL) {
			// Malloc failure
			fprintf(stderr, "ERROR\n");
			emergencyExit();
			exit(1);
		}
		v->userID = id;
		v->children = delSetList();
		v->movies = sslSetList();
		(t->users)[id] = v;	
		treeNode* parent = (t->users)[parentid];
		delAddBack(parent->children, id);
		v->parent = ((parent->children)->last)->prev;
	}
}

void treeDeleteNode (treeTree* t, int id) {
	if (id == 0) {
		// You cannot delete root
		fprintf(stderr, "ERROR\n");
	}
	else if ((t->users)[id] == NULL)
		// User does not exist
		fprintf(stderr, "ERROR\n");
	else {
		treeNode* n = (t->users)[id];
		delNode* l = n->parent;

		delSwapElementWithList (l, n->children);
		
		sslDeleteList(n->movies);
		free(n);
		(t->users)[id] = NULL;
	}
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
	for (int i = 0; i < 65535; ++i) {
		if (t->users[i] != NULL) {
			delDeleteList((t->users)[i]->children);
			sslDeleteList((t->users)[i]->movies);
			free((t->users)[i]);
		}
	}
	free(t->users);
	free(t);
}
