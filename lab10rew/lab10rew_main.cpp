#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "lab10rew_header.h"

int main(void) {
	struct sBook* StartOfBookList = NULL;
	char* string = (char*)malloc(1000 * sizeof(char));

	printf("-------------------------------------------------------\n");
	StartOfBookList = ReadFromFile(string, StartOfBookList);

	system("cls");
	printf("-------------------------------------------------------\n");
	while (true) {
		char ans[100];
		char NumOfBooks[100];

		printf("\t\t   Menu:\n");
		printf("-------------------------------------------------------\n");
		printf("What do you want to do?:\n");
		printf("(1) Add new books;\n");
		printf("(2) Delete books whit year < 1980 and pages < 90;\n");
		printf("(3) Filter books by 'A';\n");
		printf("(4) Print List;\n");
		printf("(5) Exit.\n");
		printf("Answer: ");
		gets_s(ans, 100);

		ans[strlen(ans) + 1] = '\0';
		int ans1;
		ans1 = atoi(ans);

		while (ans1 > 5 || ans1 < 1 || strlen(ans) > 1) {
			printf("Oops! Error!\nTry again: ");
			gets_s(ans, 100);
			ans[strlen(ans) + 1] = '\0';
			ans1 = atoi(ans);
		}


		int NumB;
		switch (ans1) {
		case(1):
			system("cls");
			printf("-------------------------------------------------------\n");
			printf("How many books you want to add?(to back enter 'b'): ");
			gets_s(NumOfBooks, 100);
			printf("-------------------------------------------------------\n");
			NumOfBooks[strlen(NumOfBooks) + 1] = '\0';
			if (NumOfBooks[0] == 'b' && strlen(NumOfBooks) == 1) {
				system("cls");
				printf("-------------------------------------------------------\n");
				break;
			}
			NumB = atoi(NumOfBooks);
			while (NumB > 500 or NumB < 1 or strlen(NumOfBooks) > 3
				or (strlen(NumOfBooks) == 3 and ((isdigit(NumOfBooks[1]) == false) or (isdigit(NumOfBooks[2]) == false)))
				or (strlen(NumOfBooks) == 2 and (isdigit(NumOfBooks[1]) == false))) {
				printf("Oops! Error!\nTry again: ");
				gets_s(NumOfBooks, 100);
				if (NumOfBooks[0] == 'b' && strlen(NumOfBooks) == 1) {
					system("cls");
					break;
				}
				NumOfBooks[strlen(NumOfBooks) + 1] = '\0';
				NumB = atoi(NumOfBooks);
			}
			if (NumOfBooks[0] == 'b' && strlen(NumOfBooks) == 1) {
				system("cls");
				printf("-------------------------------------------------------\n");
				break;
			}
			for (int i = 0; i < NumB; i++) {
				StartOfBookList = AddNewBook(StartOfBookList);
			}
			system("cls");
			PrintBookList(StartOfBookList);
			break;
		case(2):
			system("cls");
			printf("-------------------------------------------------------\n");
			printf("List wihtout books with year < 1980 and pages < 90:\n");
			StartOfBookList = DeLeteBook(StartOfBookList);
			break;
		case(3):
			system("cls");
			PrintFilteredByABookList(StartOfBookList);
			break;
		case(4):
			system("cls");
			PrintBookList(StartOfBookList);
			break;
		case(5):
			char exit[100];
			system("cls");
			printf("-------------------------------------------------------\n");
			printf("Do you really want to exit(1 - yes, 2 - no): ");
			gets_s(exit, 100);
			exit[strlen(exit) + 1] = '\0';
			int ex = atoi(exit);
			if (ex != 2 && ex != 1 || strlen(exit) > 1) {
				while (ex != 2 && ex != 1 || strlen(exit) > 1) {
					printf("Oops! Error!\nTry again: ");
					gets_s(exit, 100);
					exit[strlen(exit) + 1] = '\0';
					ex = atoi(exit);
				}
			}
			if (ex == 1 || ex == 2) {
				if (ex == 1) {
					system("cls");
					printf("-------------------------------------------------------\n");
					printf("\n\t\t  Good bye!\n\n");
					printf("-------------------------------------------------------\n");
					return 0;
				}
				else if (ex == 2) {
					system("cls");
					printf("-------------------------------------------------------\n");
					break;
				}
			}
		}
	}
}
