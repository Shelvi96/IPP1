#include <stdio.h>
#include <stdlib.h>
#include "double_ended_list.h"
#include "self_sorting_list.h"
#include "tree.h"
#include "utilities.h"

long long int pot (int pod, int wyk) {
	int wyn = 1;
	while (wyk > 0) {
		wyn *= pod;
		wyk--;
	}
	return wyn;
}

void doTheMarathon (int k, treeTree* t, int id, ssList* l) {
	treeNode* n = (t->users)[id];
	delNode* c = ((n->children)->first)->next;
	// if there are any movies to merge, merge them
	ssList* ret = sslMerge(n->movies, l, k);
	
	// go thorugh all children and merge them too
	while (c != (n->children)->last) {
		doTheMarathon(k, t, c->val, ret);
		c = c->next;
	}
	sslDeleteList(ret);
}

void marathon (int id, int k, treeTree* t) {
	if ((t->users)[id] == NULL) {
		fprintf(stderr, "ERROR\n");
	}
	else {
		ssList* l = sslSetList();
		doTheMarathon(k, t, id, l);
		ssList* wyn = sslPriorityMerge (l, (t->users)[id]->movies, k);
		if ((wyn->first)->next == wyn->last && k > 0) {
			printf("NONE\n");
		}
		else
			sslPrintDSC(wyn);
		sslDeleteList(wyn);
		sslDeleteList(l);
	}
}

// Watch out! Spaghetti code coming!

int main () {
	treeTree* t = treeSetTree();
	errorTree = t;

	/* #################################################### */
	/* ##################### INPUT ######################## */
	/* #################################################### */
	char c;
	while (1) {
		c = getchar();
		if (c == EOF)
			break;
		else if (c == '#') {
			// printf("Komentarz\n");
			while (c != EOF && c != '\n')
				c = getchar();
		}
		else if (c == '\n')
			continue;
			// printf("Empty\n");
		else if (c != 'a' && c != 'd' && c != 'm') {
			int is_empty = 1;
			while (c != EOF && c != '\n') {
					if (c != ' ')
						is_empty = 0;
					c = getchar();
				}
				if (is_empty == 1) continue;
				else fprintf(stderr, "ERROR\n");
		}
		else {
			char com[7];
			com[0] = c;
			for(int i = 1; i < 7; ++i) {
				com[i] = getchar();
				if (com[i] == '\n') {
					c = '\n';
					break;
				}
			}
			if (com[0] == 'a' && com[1] == 'd' && com[2] == 'd' && com[3] == 'U' && com[4] == 's' && com[5] == 'e' && com[6] == 'r') {
				c = getchar();
				if (c != ' ')
					fprintf(stderr, "ERROR\n");
				else {
					// "addUser "
					// 0 = 48, 9 = 57
					long long int num1 = -1, num2 = -1;
					int globalerror = 0;
					while (c != EOF && c != '\n') {
						char num[11];
						int i, is_error = 0;
						for (i = 0; i < 11; ++i) {
							c = getchar();
							if (c == ' ' || c == '\n') {
								break;
							}
							else if (c > 57 || c < 48) {
								is_error = 1;
								break;
							}
							else num[i] = c;
						}
						long long int number = 0;
						if (is_error == 0 && (c == ' ' || c == '\n')) {
							for(int j = 0; j < i; ++j) {
								number += pot(10,i-j-1) * (int)(num[j]-48);
							}
							if (num1 == -1 && i > 0) num1 = number;
							else if (num2 == -1 && i > 0) num2 = number;
							else globalerror = 1;
						}
						else {
							while (c != '\n' && c != EOF)
								c = getchar();
						}
						if (is_error == 1) 
							globalerror = 1;
					}
					/* #################################################### */
					/* ################## ADD USER ######################## */
					/* #################################################### */
					if (num1 != -1 && num2 != -1 && globalerror == 0 && num1 <= 65535 && num2 <= 65535) {
						// printf("addUser ");
						// printf("%lld %lld", num1, num2);
						// printf("\n");
						if ((t->users)[num1] != NULL && (t->users)[num2] == NULL) {
							treeAddNode(t, num2, num1);
							printf("OK\n");
						}
						else
							fprintf(stderr, "ERROR\n");
					}
					else
						fprintf(stderr, "ERROR\n");
				}
				while (c != EOF && c != '\n')
					c = getchar();
			}
			else if (com[0] == 'd' && com[1] == 'e' && com[2] == 'l' && com[3] == 'U' && com[4] == 's' && com[5] == 'e' && com[6] == 'r') {
				c = getchar();
				if (c != ' ')
					fprintf(stderr, "ERROR\n");
				else {
					// "delUser "
					long long int num1 = -1;
					int globalerror = 0;
					char num[11];
					int i, is_error = 0;
					for (i = 0; i < 11; ++i) {
						c = getchar();
						if (c == ' ' || c == '\n') {
							break;
						}
						else if (c > 57 || c < 48) {
							is_error = 1;
							break;
						}
						else num[i] = c;
					}
					long long int number = 0;
					if (is_error == 0 && (c == ' ' || c == '\n')) {
						for(int j = 0; j < i; ++j) {
							number += pot(10,i-j-1) * (int)(num[j]-48);
						}
						if (num1 == -1 && i > 0) num1 = number;
						else globalerror = 1;
					}
					else {
						while (c != '\n' && c != EOF)
							c = getchar();
					}
					if (is_error == 1) 
						globalerror = 1;
					/* #################################################### */
					/* ################## DEL USER ######################## */
					/* #################################################### */
					if (num1 != -1 && globalerror == 0 && num1 <= 65535 && c == '\n') {
						// printf("delUser ");
						// printf("%lld", num1);
						// printf("\n");
						if ((t->users)[num1] != NULL) {
							printf("OK\n");
							treeDeleteNode(t, num1);
						}
						else
							fprintf(stderr, "ERROR\n");
					}
					else
						fprintf(stderr, "ERROR\n");
				}
				while (c != EOF && c != '\n')
					c = getchar();
			}
			else if (com[0] == 'a' && com[1] == 'd' && com[2] == 'd' && com[3] == 'M' && com[4] == 'o' && com[5] == 'v' && com[6] == 'i') {
				c = getchar();
				if (c != '\n') {
					if (c != 'e')
						fprintf(stderr, "ERROR\n");
					else {
						c = getchar();
						if (c != ' ')
							fprintf(stderr, "ERROR\n");
						else {
							// "addMovie "
							long long int num1 = -1, num2 = -1;
							int globalerror = 0;
							while (c != EOF && c != '\n') {
								char num[11];
								int i, is_error = 0;
								for (i = 0; i < 11; ++i) {
									c = getchar();
									if (c == ' ' || c == '\n') {
										break;
									}
									else if (c > 57 || c < 48) {
										is_error = 1;
										break;
									}
									else num[i] = c;
								}
								long long int number = 0;
								if (is_error == 0 && (c == ' ' || c == '\n')) {
									for(int j = 0; j < i; ++j) {
										number += pot(10,i-j-1) * (int)(num[j]-48);
									}
									if (num1 == -1 && i > 0) num1 = number;
									else if (num2 == -1 && i > 0) num2 = number;
									else globalerror = 1;
								}
								else {
									while (c != '\n' && c != EOF)
										c = getchar();
								}
								if (is_error == 1) 
									globalerror = 1;
								}
							/* #################################################### */
							/* ################## ADD MOVIE ####################### */
							/* #################################################### */
							if (num1 != -1 && num2 != -1 && globalerror == 0 && num1 <= 65535 && num2 <= 2147483647) {
								// printf("addMovie ");
								// printf("%lld %lld", num1, num2);
								// printf("\n");
								if ((t->users)[num1] != NULL) {
									printf("OK\n");
									sslAdd((t->users)[num1]->movies, num2);
								}
								else
									fprintf(stderr, "ERROR\n");
							}
							else
								fprintf(stderr, "ERROR\n");
						}
					}
					while (c != EOF && c != '\n')
					c = getchar();
				}
				else 
					fprintf(stderr, "ERROR\n");
			}
			else if (com[0] == 'd' && com[1] == 'e' && com[2] == 'l' && com[3] == 'M' && com[4] == 'o' && com[5] == 'v' && com[6] == 'i') {
				c = getchar();
				if (c != '\n') {
					if (c != 'e')
						fprintf(stderr, "ERROR\n");
					else {
						c = getchar();
						if (c != ' ')
							fprintf(stderr, "ERROR\n");
						else {
							// "delMovie "
							long long int num1 = -1, num2 = -1;
							int globalerror = 0;
							while (c != EOF && c != '\n') {
								char num[11];
								int i, is_error = 0;
								for (i = 0; i < 11; ++i) {
									c = getchar();
									if (c == ' ' || c == '\n') {
										break;
									}
									else if (c > 57 || c < 48) {
										is_error = 1;
										break;
									}
									else num[i] = c;
								}
								long long int number = 0;
								if (is_error == 0 && (c == ' ' || c == '\n')) {
									for(int j = 0; j < i; ++j) {
										number += pot(10,i-j-1) * (int)(num[j]-48);
									}
									if (num1 == -1 && i > 0) num1 = number;
									else if (num2 == -1 && i > 0) num2 = number;
									else globalerror = 1;
								}
								else {
									while (c != '\n' && c != EOF)
										c = getchar();
								}
								if (is_error == 1) 
									globalerror = 1;
							}
							/* #################################################### */
							/* ################## DEL MOVIE ####################### */
							/* #################################################### */
							if (num1 != -1 && num2 != -1 && globalerror == 0 && num1 <= 65535 && num2 <= 2147483647) {
								// printf("delMovie ");
								// printf("%lld %lld", num1, num2);
								// printf("\n");
								if ((t->users)[num1] != NULL) {
									printf("OK\n");
									sslRemoveVal((t->users)[num1]->movies, num2);
								}
								else
									fprintf(stderr, "ERROR\n");
							}
							else
								fprintf(stderr, "ERROR\n");
						}
					}
					while (c != EOF && c != '\n')
						c = getchar();
				}
				else 
					fprintf(stderr, "ERROR\n");
			}
			else if (com[0] == 'm' && com[1] == 'a' && com[2] == 'r' && com[3] == 'a' && com[4] == 't' && com[5] == 'h' && com[6] == 'o') {
				c = getchar();
				if (c != '\n') {
					if (c != 'n')
						fprintf(stderr, "ERROR\n");
					else {
						c = getchar();
						if (c != ' ')
							fprintf(stderr, "ERROR\n");
						else {
							// "marathon "
							long long int num1 = -1, num2 = -1;
							int globalerror = 0;
							while (c != EOF && c != '\n') {
								char num[11];
								int i, is_error = 0;
								for (i = 0; i < 11; ++i) {
									c = getchar();
									if (c == ' ' || c == '\n') {
										break;
									}
									else if (c > 57 || c < 48) {
										is_error = 1;
										break;
									}
									else num[i] = c;
								}
								long long int number = 0;
								if (is_error == 0 && (c == ' ' || c == '\n')) {
									for(int j = 0; j < i; ++j) {
										number += pot(10,i-j-1) * (int)(num[j]-48);
									}
									if (num1 == -1 && i > 0) num1 = number;
									else if (num2 == -1 && i > 0) num2 = number;
									else globalerror = 1;
								}
								else {
									while (c != '\n' && c != EOF)
										c = getchar();
								}
								if (is_error == 1) 
									globalerror = 1;
							}
							/* #################################################### */
							/* ################## MARATHON ######################## */
							/* #################################################### */
							if (num1 != -1 && num2 != -1 && globalerror == 0 && num1 <= 65535 && num2 <= 2147483647) {
								// printf("marathon ");
								// printf("%lld %lld", num1, num2);
								// printf("\n");
								marathon(num1, num2, t);
							}
							else
								fprintf(stderr, "ERROR\n");
						}
					}
					while (c != EOF && c != '\n')
						c = getchar();
				}
				else 
					fprintf(stderr, "ERROR\n");
			}
			else {
				while (c != EOF && c != '\n') {
					c = getchar();
				}
				fprintf(stderr, "ERROR\n");
			}
		}
	}

	treeDeleteTree(t);

	return 0;
}
