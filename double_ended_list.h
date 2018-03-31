#ifndef DOUBLE_ENDED_LIST_H
#define DOUBLE_ENDED_LIST_H
#define enter printf("\n");

typedef struct Node {
    int val;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct deList {
	int size;
	Node* first;
	Node* last;
} deList;

Node* setNode(int x);
deList setList ();

void addFront (deList* l, int x);
void addBack (deList* l, int x);

int getFront (deList* l);
int getBack (deList* l);

void removeFront (deList* l);
void removeBack (deList* l);

void deleteList (deList* l);

void printFront (deList* l);
void printBack (deList* l);

#endif /* DOUBLE_ENDED_LIST_H */
