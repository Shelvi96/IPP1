#include <stdio.h>
#include <stdlib.h>
#include "double_ended_list.h"
#include "self_sorting_list.h"
#include "tree.h"

treeTree* treeSetTree () {
	treeTree* t = (treeTree*)malloc(sizeof(treeTree));
	if (t == NULL) {
		printf("MALLOC ERROR");
		// free all allocs - delete tree
		exit(1);
	}

	treeNode* root = (treeNode*)malloc(sizeof(treeNode));
	if (root == NULL) {
		printf("MALLOC ERROR");
		// free all allocs - delete tree
		exit(1);
	}
	root->userID = 0;
	root->children = delSetList();
	root->movies = sslSetList();
	t->node = root;

	// creating array to store pointers to all users from the tree
	t->users = (treeNode**)malloc(65535*sizeof(treeNode*));
	if ((t->users) == NULL) {
		printf("MALLOC ERROR");
		// free all allocs - delete tree
		exit(1);
	}
	for (int i = 0; i < 65535; ++i)
		(t->users)[i] = NULL;

	(t->users)[0] = root;

	return t;
}

void treeAddNode (treeTree* t, int id, int parentid) {
	if ((t->users)[id] != NULL) {
		printf ("User already in database\n");
	}
	else {
		treeNode* v = (treeNode*)malloc(sizeof(treeNode));
		if (v == NULL) {
			printf("MALLOC ERROR");
			// free all allocs - delete tree
			exit(1);
		}
		v->userID = id;
		v->children = delSetList();
		v->movies = sslSetList();
		(t->users)[id] = v;	
		delAddBack( (((t->users)[parentid]) -> children), id);
	}
}

// void treeDeleteNode (treeTree* t, int id) {

// }

void treePrintTree (treeTree* t, int root_id) {
	treeNode* n = (t->users)[root_id];
	printf("%d ", n->userID);
	delPrintFront(n->children);
	delNode* c = (n->children)->first;
	for (int i = 0; i <(n->children)->size; ++i) {
		treePrintTree(t, c->val);
		c = c->next;
	}
}

// void treeDeleteTree (treeTree* t) {
// 	for (int i = 0; i < 65535; ++i) {
// 		if (usr[i] != NULL) {
// 			delDeleteList(&usr[i]->children);
// 			sslDeleteList(&usr[i]->movies);
// 			free(usr[i]);
// 		}
// 	}
// }

// int main () {
// 	// creating array to store pointers to users
// 	users = (treeNode**)malloc(65535*sizeof(treeNode*));
// 	for (int i = 0; i < 65535; ++i)
// 		users[i] = NULL;

// 	int x;
// 	scanf("%d", &x);

// 	treeNode* n = treeSetNode(x);
// 	treeNode* n1 = treeSetNode(x);

// 	treePrintArr(x);
	
// 	treeDeleteTree(users);
// 	free(users);

// 	return 0;
// }
