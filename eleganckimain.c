#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "double_ended_list.h"
#include "self_sorting_list.h"
#include "tree.h"
#define MIN_USERID 0
#define MAX_USERID 65535
#define MIN_MOVIERATING 0
#define MAX_MOVIERATING 2147483647
#define MIN_K 0
#define MAX_K 2147483647
#define MAX_NUMLEN 10
#define MAX_INSTRUCTIONLEN 8

// Zwraca true, gdy zadane ciągi znaków są takie same
bool equals (char* str1, char* str2) {
	if (strlen(str1) != strlen(str2)) {
		return false;
	}

	bool diff = true;
	size_t len = strlen(str1);

	for (size_t i = 0; i < len; ++i) {
		if (str1[i] != str2[i]) {
			diff = false;
			break;
		}
	}

	return diff;
}

// Zwraca true, gdy znak jest cyfrą
bool isNum (char c) {
	if (c >= '0' && c <= '9') {
		return true;
	}

	return false;
}

// Zwraca true, gdy znak jest spacją, końcem linii lub końcem pliku
bool isWhite (char c) {
	if (c == ' ' || c == '\n' || c == EOF) {
		return true;
	}

	return false;
}

// Pomija tekst od znaku c do końca linii
void skipText (char c) {
	while (c != '\n' && c != EOF) {
		c = getchar();
	}
}

// Zamienia stringa z cyframi na liczbę
int strtonum (char* str) {
	int len = strlen(str);
	int pos = 1;
	int ret = 0;

	for (int i = len - 1; i >= 0; --i) {
		ret += (str[i] - '0') * (pos);
		pos *= 10;
	}

	free(str);
	
	return ret;
}

// Zwraca numer powstały z kolejnych numLen znaków lub -1, gdy znaki nie są cyframi
int getNum (int numLen) {
	char c = getchar();
	int i = 0;
	char* number = malloc((numLen+1)*sizeof(char));

	while (isNum(c) && i < numLen) {
		number[i++] = c;
		c = getchar();
	}

	number[i] = '\0';

	if (isWhite(c) && i != 0) {
		ungetc(c, stdin);

		return strtonum(number);
	}
	else {
		while (!isWhite(c)) {
			c = getchar();
		}

		ungetc(c, stdin);
		free(number);

		return -1;
	}
}

// Wczytuje liczbę i sprawdza, czy mieści się w podanym zakresie
int readOneNum (int from, int to) {
	char c = getchar();

	if (c == ' ') {
		int num1 = getNum(MAX_NUMLEN);
		
		if (num1 >= from && num1 <= to) {
			return num1;
		}
		else return -1;	
	}
	else {
		ungetc(c, stdin);
		return -1;
	}
}

// Serce tego rozwiązania - tytułowa funkcja generująca listę preferencji filmowych
ssList* marathon (treeTree* t, int userId, int k) {
	ssList* childrenRet = sslSetList();
	if (k == 0) {
		return childrenRet;
	}

	if (t->users[userId] != NULL) {
		delNode* n = (t->users[userId])->children->first->next;
		// Wywołujemy funkcję marathon dla każdego dziecka
		while (n != (t->users[userId])->children->last) {
			childrenRet = sslMerge(childrenRet, marathon(t, n->val, k), k);
			n = n->next;
		}
	}

	// Mergujemy wyniki wszystkich dzieci z preferencjami ojca w sposób opisany w tresci
	return sslPriorityMerge(childrenRet, t->users[userId]->movies, k);
}

// Wypisuje wszystkie filmy wszystkich użytkowników
void printMovies (treeTree* t) {
	for (int i = 0; i < MAX_USERID + 1; ++i) {
		if (t->users[i] != NULL) {
			printf("%d: ", i);
			sslPrintDSC(t->users[i]->movies);
		}
	}
}

int main() {
	char c;
	char* operation = malloc((MAX_INSTRUCTIONLEN + 1)*sizeof(char));
	treeTree* t = treeSetTree();

	while ((c = getchar()) != EOF) {
		// Obsługa pustego wiersza
		while (c == '\n') {
			c = getchar();
		}
		if (c == EOF) {
			break;
		}

		// Obsługa komentarza
		if (c == '#') {
			printf("Komentarz\n");
			skipText(c);

			if (c == EOF) {
				break;
			}

			continue;
		}		
		
		// Wczytywanie instrukcji
		int i = 0;

		while (!isWhite(c) && i < MAX_INSTRUCTIONLEN) {
			operation[i++] = c;
			c = getchar();
		}
		ungetc(c, stdin);

		operation[i] = '\0';

		// printf("%s\n", operation);

		if (i == 0) {
			fprintf(stderr, "ERROR\n");
			skipText(c);
			continue;
		}

		// Wczytanie reszty danych dla instrukcji i wykonanie jej
		if (equals(operation, "addUser")) {
			int num1 = readOneNum(MIN_USERID, MAX_USERID);
			int num2 = readOneNum(MIN_USERID, MAX_USERID);
			c = getchar();

			if (num1 != -1 && num2 != -1 && c == '\n') {
				// printf("Dodaj Uzytkownika ");
				// printf("%d %d\n", num1, num2);

				if (treeAddNode(t, num1, num2)) {
					printf("OK\n");
				}
				else fprintf(stderr, "ERROR: treeAddNode fail\n");
			}
			else fprintf(stderr, "ERROR: wrong input\n");
		}
		else if (equals(operation, "delUser")) {
			int num = readOneNum(MIN_USERID, MAX_USERID);
			c = getchar();

			if (num != -1 && c == '\n') {
				// printf("Usun Uzytkownika ");
				// printf("%d\n", num);

				if (treeDeleteNode(t, num)) {
					printf("OK\n");
				}
				else fprintf(stderr, "ERROR: treeDeleteNode fail\n");
			}
			else fprintf(stderr, "ERROR: wrong input\n");
		}
		else if (equals(operation, "addMovie")) {
			int num1 = readOneNum(MIN_USERID, MAX_USERID);
			int num2 = readOneNum(MIN_MOVIERATING, MAX_MOVIERATING);
			c = getchar();

			if (num1 != -1 && num2 != -1 && c == '\n') {
				// printf("Dodaj Film ");
				// printf("%d %d\n", num1, num2);

				if (t->users[num1] != NULL && sslAdd(t->users[num1]->movies, num2)) {
					printf("OK\n");
				}
				else fprintf(stderr, "ERROR: addMovie - user does not exist\n");
			}
			else fprintf(stderr, "ERROR: wrong input\n");
		}
		else if (equals(operation, "delMovie")) {
			int num1 = readOneNum(MIN_USERID, MAX_USERID);
			int num2 = readOneNum(MIN_MOVIERATING, MAX_MOVIERATING);
			c = getchar();

			if (num1 != -1 && num2 != -1 && c == '\n') {
				// printf("Usun Film ");
				// printf("%d %d\n", num1, num2);

				if(t->users[num1] != NULL && sslRemoveVal(t->users[num1]->movies, num2)) {
					printf("OK\n");
				}
				else fprintf(stderr, "ERROR: delMovie - user does not exist\n")
			}
			else fprintf(stderr, "ERROR: wrong input\n");
		}
		else if (equals(operation, "marathon")) {
			int num1 = readOneNum(MIN_USERID, MAX_USERID);
			int num2 = readOneNum(MIN_K, MAX_K);
			c = getchar();

			if (num1 != -1 && num2 != -1 && c == '\n') {
				// printf("Marathon ");
				// printf("%d %d\n", num1, num2);

				if(t->users[num1] != NULL) {
					ssList* marathonResult = marathon(t, num1, num2);
					sslPrintDSC(marathonResult);
					sslDeleteList(marathonResult);
				}
				else fprintf(stderr, "ERROR: marathon - user does not exist\n");
			}
			else fprintf(stderr, "ERROR: wrong input\n");
		}
		else {
			printf("ERRORUS MAXIMUS\n");	
		}

		// Zignorowanie reszty linii
		skipText(c);
	}

	// treePrintTree(t, 0);
	// printMovies(t);

	free(operation);
	treeDeleteTree(t);
}	