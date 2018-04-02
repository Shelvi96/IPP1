#ifndef DOUBLE_ENDED_LIST_H
#define DOUBLE_ENDED_LIST_H
#define enter printf("\n");

typedef struct delNode {
    int val;
    struct delNode* prev;
    struct delNode* next;
} delNode;

typedef struct deList {
	int size;
	delNode* first;
	delNode* last;
} deList;

delNode* delSetNode(int x);
deList* delSetList ();

void delAddFront (deList* l, int x);
void delAddBack (deList* l, int x);

int delGetFront (deList* l);
int delGetBack (deList* l);

void delAppend (deList* l1, deList* l2);

void delRemoveFront (deList* l);
void delRemoveBack (deList* l);

void delDeleteList (deList* l);

void delPrintFront (deList* l);
void delPrintBack (deList* l);

#endif /* DOUBLE_ENDED_LIST_H */
