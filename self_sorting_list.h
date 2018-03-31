#ifndef SELF_SORTING_LIST_H
#define SELF_SORTING_LIST_H
#define enter printf("\n");

typedef struct Node {
    int val;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct ssList {
	int size;
	Node* first;
	Node* last;
} ssList;

Node* setNode(int x);
ssList setList ();

void add (ssList* l, int x);

int getMax (ssList* l);
int getMin (ssList* l);

void removeFront (ssList* l);
void removeBack (ssList* l);

void removeVal (ssList* l, int x);

void deleteList (ssList* l);

void printDSC (ssList* l);
void printASC (ssList* l);

#endif /* SELF_SORTING_LIST_H */
