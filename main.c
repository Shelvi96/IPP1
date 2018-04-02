#include <stdio.h>
#include <stdlib.h>
#include "double_ended_list.h"
#include "self_sorting_list.h"
#include "tree.h"

int main () {
	treeTree* t = treeSetTree();
	treeAddNode(t, 12, 0);
	treeAddNode(t, 10, 0);
	treeAddNode(t, 8, 0);
	treeAddNode(t, 4, 8);
	treeAddNode(t, 6, 8);
	treePrintTree(t, 0);

	treeDeleteTree(t);

	// deList* l1 = delSetList();
	// deList* l3 = delSetList();
	// ssList* l2 = sslSetList();

	// delAddFront(l3, 2);
	// delAddFront(l3, 2);

	// int x, y;	
	// while (1) {
	// 	scanf("%d", &x);
	// 	if (x == -1)
	// 		break;
	// 	else if (x == 1) {
	// 		scanf("%d", &y);
	// 		delAddFront(l1, y);
	// 	}
	// 	else if (x == 2) {
	// 		scanf("%d", &y);
	// 		delAddBack(l1, y);
	// 	}
	// 	else if (x == 3) {
	// 		delRemoveFront(l1);
	// 	}
	// 	else if (x == 4) {
	// 		delRemoveBack(l1);
	// 	}
	// 	else if (x == 5) {
	// 		printf("%d", delGetFront(l1));
	// 	}
	// 	else if (x == 6) {
	// 		printf("%d", delGetBack(l1));
	// 	}
	// 	else if (x == 7) {
	// 		delPrintFront(l1);
	// 	}
	// 	else if (x == 8) {
	// 		delPrintBack(l1);
	// 	}
	// 	else if (x == 9) {
	// 		delDeleteList(l1);
	// 	}
	// 	else if (x == 10) {
	// 		delAppend(l1, l3);
	// 	}
	// 	else if(x == 11) {
	// 		delPrintFront(l3);
	// 	}
	// 	else {
	// 		;
	// 	}
	// }

	// while (1) {
	// 	scanf("%d", &x);
	// 	if (x == -1)
	// 		break;
	// 	else if (x == 1) {
	// 		scanf("%d", &y);
	// 		sslAdd(&l2, y);
	// 	}
	// 	else if (x == 3) {
	// 		sslRemoveFront(&l2);
	// 	}
	// 	else if (x == 4) {
	// 		sslRemoveBack(&l2);
	// 	}
	// 	else if (x == 5) {
	// 		printf("%d", sslGetMin(&l2));
	// 	}
	// 	else if (x == 6) {
	// 		printf("%d", sslGetMax(&l2));
	// 	}
	// 	else if (x == 7) {
	// 		sslPrintDSC(&l2);
	// 	}
	// 	else if (x == 8) {
	// 		sslPrintASC(&l2);
	// 	}
	// 	else if (x == 9) {
	// 		sslDeleteList(&l2);
	// 	}
	// 	else {
	// 		;
	// 	}
	// }

	return 0;
}