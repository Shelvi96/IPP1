#ifndef SELF_SORTING_LIST_H
#define SELF_SORTING_LIST_H

typedef struct sslNode {
    long long int val;
    struct sslNode* prev;
    struct sslNode* next;
} sslNode;

typedef struct ssList {
	sslNode* first;
	sslNode* last;
} ssList;

sslNode* sslSetNode(long long int x);
ssList* sslSetList ();

bool sslAdd (ssList* l, long long int x);

long long int sslGetMax (ssList* l);
long long sslGetMin (ssList* l);

void sslRemoveFront (ssList* l);
void sslRemoveBack (ssList* l);

bool sslRemoveVal (ssList* l, long long int x);

void sslDeleteList (ssList* l);

void sslPrintDSC (ssList* l);
void sslPrintASC (ssList* l);

ssList* sslMerge (ssList* l1, ssList* l2, int k);
ssList* sslPriorityMerge (ssList* l1, ssList* l2, int k);

#endif /* SELF_SORTING_LIST_H */
