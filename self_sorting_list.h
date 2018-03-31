#ifndef SELF_SORTING_LIST_H
#define SELF_SORTING_LIST_H
#define enter printf("\n");

typedef struct sslNode {
    int val;
    struct sslNode* prev;
    struct sslNode* next;
} sslNode;

typedef struct ssList {
	int size;
	sslNode* first;
	sslNode* last;
} ssList;

sslNode* sslSetNode(int x);
ssList sslSetList ();

void sslAdd (ssList* l, int x);

int sslGetMax (ssList* l);
int sslGetMin (ssList* l);

void sslRemoveFront (ssList* l);
void sslRemoveBack (ssList* l);

void sslRemoveVal (ssList* l, int x);

void sslDeleteList (ssList* l);

void sslPrintDSC (ssList* l);
void sslPrintASC (ssList* l);

#endif /* SELF_SORTING_LIST_H */
