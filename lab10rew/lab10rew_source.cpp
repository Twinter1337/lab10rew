#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lab10rew_header.h"
#define AUTHOR_NAME_LENGTH 50
#define BOOK_NAME_LENGTH 50
#define DELETE_YEAR 1980
#define DELETE_PAGES_AMOUNT 90

char* FileName = (char*)malloc(10000 * sizeof(char));

/*-------------------------------------------------------------------------------------
Функція PrintBookList виводить однозв'язний список книг у консоль, функція
приймає адресу на початок списку і нічого не повертає*/
void PrintBookList(struct sBook* p_HeadOfBookList) {
	struct sBook* Start = p_HeadOfBookList;
	int i_CounterOfBooks = 1;
	FILE* F_Lib = fopen(FileName, "wt");
	printf("-------------------------------------------------------\n");
	if (p_HeadOfBookList == NULL) {
		printf("\n\t  There is no books in list!\n\n");
		printf("-------------------------------------------------------\n");
		fprintf(F_Lib, "");
		return;
	}
	while (p_HeadOfBookList != NULL) {
		printf("\t\t  Book #%d\n", i_CounterOfBooks);
		printf("-------------------------------------------------------\n");
		printf("Autor:\t%s\nName:\t\"%s\"\nyear:\t%d\nPages:\t%d\nPrice:\t%d UAH\n",
			p_HeadOfBookList->m_cAutor, p_HeadOfBookList->m_cName,
			p_HeadOfBookList->m_iYear, p_HeadOfBookList->m_iPages,
			p_HeadOfBookList->m_iPrice);
		printf("-------------------------------------------------------\n");
		p_HeadOfBookList = p_HeadOfBookList->m_pNext;
		i_CounterOfBooks++;
	}

	p_HeadOfBookList = Start;
	while (p_HeadOfBookList != NULL) {
		fprintf(F_Lib, "%s\\%s\\%d\\%d\\%d\n",
			p_HeadOfBookList->m_cAutor, p_HeadOfBookList->m_cName,
			p_HeadOfBookList->m_iYear, p_HeadOfBookList->m_iPages,
			p_HeadOfBookList->m_iPrice);
		p_HeadOfBookList = p_HeadOfBookList->m_pNext;
	}

	fclose(F_Lib);
}
/*-------------------------------------------------------------------------------------
Функція PrintFilteredByBookList фільтрує однозв'язний список книг за літерою A
(в імені/призвищі автора) і виводить його у консоль, функція приймає адресу
на початок списку і нічого не повертає*/
void PrintFilteredByABookList(struct sBook* p_HeadOfBookList) {
	char c_AuthorFirstLetterOfName;
	int i_CounterOfBooks = 1;
	printf("-------------------------------------------------------\n");
	printf("\t     filtered by letter A:\n");
	printf("-------------------------------------------------------\n");
	while (p_HeadOfBookList != NULL) {
		c_AuthorFirstLetterOfName = *p_HeadOfBookList->m_cAutor;
		if (c_AuthorFirstLetterOfName == 'A' || c_AuthorFirstLetterOfName == 'a') {
			printf("\t\t  Book #%d\n", i_CounterOfBooks);
			printf("Autor: %s\nName: \"%s\"\nyear: %d\nPages: %d\nPrice: %d"
				" UAH\n", p_HeadOfBookList->m_cAutor, p_HeadOfBookList->m_cName,
				p_HeadOfBookList->m_iYear, p_HeadOfBookList->m_iPages,
				p_HeadOfBookList->m_iPrice);
			printf("-------------------------------------------------------\n");
			i_CounterOfBooks++;
		}
		p_HeadOfBookList = p_HeadOfBookList->m_pNext;
	}
	if (i_CounterOfBooks == 1) {
		printf("\n      There is no books with Author on A\n\n");
		printf("-------------------------------------------------------\n");
	}
}
/*-------------------------------------------------------------------------------------
фукнція DeleteBook видаляє елемент однозв'язного списку книг, поля m_iYear і
m_iPages якого менші за 1980 і 90 відповідно.Приймає адресу на початок списку і
повертає адресу на початковий елемент списку*/
struct sBook* DeLeteBook(struct sBook* p_HeadOfBookList) {
	struct sBook* p_StartOfBookList = p_HeadOfBookList;
	struct sBook* p_StartOfBookList1 = p_StartOfBookList;
	int counter = 0;
	int counter1 = 0;
	if (p_HeadOfBookList == NULL) {
		printf("-------------------------------------------------------\n");
		printf("\n\t  There is no books in list!\n\n");
		printf("-------------------------------------------------------\n");
		return p_StartOfBookList;
	}
	while (p_HeadOfBookList != NULL) {
		p_HeadOfBookList = p_HeadOfBookList->m_pNext;
		counter++;
	}
	p_HeadOfBookList = p_StartOfBookList;
	while (true) {
		struct sBook* pp_HeadOfBookList = p_HeadOfBookList;
		p_HeadOfBookList = p_HeadOfBookList->m_pNext;
		if (!p_HeadOfBookList) break;
		if (p_HeadOfBookList->m_iYear < DELETE_YEAR &&
			p_HeadOfBookList->m_iPages < DELETE_PAGES_AMOUNT) {
			if (!p_HeadOfBookList->m_pNext) {
				pp_HeadOfBookList->m_pNext = NULL;
				break;
			}
			pp_HeadOfBookList->m_pNext = p_HeadOfBookList->m_pNext;
			free(p_HeadOfBookList);
			p_HeadOfBookList = pp_HeadOfBookList;
		}
	}
	p_HeadOfBookList = p_StartOfBookList;
	if (p_HeadOfBookList->m_iYear < DELETE_YEAR &&
		p_HeadOfBookList->m_iPages < DELETE_PAGES_AMOUNT) {
		if (p_HeadOfBookList->m_pNext) {
			p_StartOfBookList = p_HeadOfBookList->m_pNext;
		}
		else {
			p_StartOfBookList = NULL;
		}
	}

	p_StartOfBookList1 = p_StartOfBookList;

	while (p_StartOfBookList != NULL) {
		p_StartOfBookList = p_StartOfBookList->m_pNext;
		counter1++;
	}
	if (counter1 == counter) {
		printf("-------------------------------------------------------\n");
		printf("\n  There is no books with year < 1980 and pages < 90\n\n");
		printf("-------------------------------------------------------\n");
	}
	else {
		PrintBookList(p_StartOfBookList1);
	}
	return p_StartOfBookList1;
}

struct sBook* AddNewBook(struct sBook* Start) {
	char* AuthorName = (char*)malloc(10000 * sizeof(char));
	char* BookName = (char*)malloc(10000 * sizeof(char));
	char Year[100];
	char Pages[100];
	char Price[100];

	struct sBook* NewBook = (struct sBook*)malloc(sizeof(struct sBook));

	printf("Enter the name of Author: ");

	gets_s(AuthorName, 10000);
	while (strlen(AuthorName) > AUTHOR_NAME_LENGTH or strlen(AuthorName) < 1) {
		printf("Name of the author can`t be longer then 50 symbols or lower than 1!\nEnter again: ");
		gets_s(AuthorName, 10000);
	}
	printf("Enter the name of Book: ");

	gets_s(BookName, 10000);
	while (strlen(BookName) > BOOK_NAME_LENGTH or strlen(BookName) < 1) {
		printf("Name of the book can`t be longer then 50 symbols or lower than 1!\nEnter again: ");
		gets_s(BookName, 10000);
	}
	printf("Enter the Year: ");

	gets_s(Year, 100);
	Year[strlen(Year) + 1] = '\0';
	while (atoi(Year) > 2023 or atoi(Year) < 1 or strlen(Year) > 4
		or (strlen(Year) == 4 and ((isdigit(Year[1]) == false) or (isdigit(Year[2]) == false) or (isdigit(Year[3]) == false)))
		or (strlen(Year) == 3 and ((isdigit(Year[1]) == false) or (isdigit(Year[2]) == false)))
		or (strlen(Year) == 2 and (isdigit(Year[1]) == false))) {
		printf("Year can`t be bigger than 2023 or be lower than 1!\nEnter again: ");
		gets_s(Year, 100);
		Year[strlen(Year) + 1] = '\0';
	}
	printf("Enter the Pages: ");

	gets_s(Pages, 100);
	Pages[strlen(Pages) + 1] = '\0';
	while (atoi(Pages) > 9999 or atoi(Pages) < 48 or strlen(Pages) > 4
		or (strlen(Pages) == 4 and ((isdigit(Pages[1]) == false) or (isdigit(Pages[2]) == false) or (isdigit(Pages[3]) == false)))
		or (strlen(Pages) == 3 and ((isdigit(Pages[1]) == false) or (isdigit(Pages[2]) == false)))
		or (strlen(Pages) == 2 and (isdigit(Pages[1]) == false))) {
		printf("Number of pages can`t be bigger then 9999 or lower than 48!\nEnter again: ");
		gets_s(Pages, 100);
		Pages[strlen(Pages) + 1] = '\0';
	}
	printf("Enter the Price: ");

	gets_s(Price, 100);
	Price[strlen(Price) + 1] = '\0';
	while (atoi(Price) > 9999 or atoi(Price) < 1 or strlen(Price) > 4
		or (strlen(Price) == 4 and ((isdigit(Price[1]) == false) or (isdigit(Price[2]) == false) or (isdigit(Price[3]) == false)))
		or (strlen(Price) == 3 and ((isdigit(Price[1]) == false) or (isdigit(Price[2]) == false)))
		or (strlen(Price) == 2 and (isdigit(Price[1]) == false))) {
		printf("Price can`t be bigger then 9999 or be lower than 1!\nEnter again: ");
		gets_s(Price, 100);
		Price[strlen(Price) + 1] = '\0';
	}

	NewBook = CreateNode(AuthorName, BookName, Year, Pages, Price);

	return AddNode(Start, NewBook);
}
/*-------------------------------------------------------------------------------------
*/
struct sBook* CreateNode(char AuthorName[AUTHOR_NAME_LENGTH],
	char BookName[BOOK_NAME_LENGTH],
	char* Year,
	char* Pages,
	char* Price) {
	struct sBook* p_NodeOfBookList = (struct sBook*)malloc(sizeof(struct sBook));

	strcpy(p_NodeOfBookList->m_cAutor, AuthorName);
	strcpy(p_NodeOfBookList->m_cName, BookName);
	p_NodeOfBookList->m_iYear = atoi(Year);
	p_NodeOfBookList->m_iPages = atoi(Pages);
	p_NodeOfBookList->m_iPrice = atoi(Price);

	p_NodeOfBookList->m_pNext = NULL;

	return p_NodeOfBookList;
}
/*-------------------------------------------------------------------------------------*/
struct sBook* AddNode(struct sBook* Start, struct sBook* p_NodeOfBookList) {
	struct sBook* StartPtr = Start;

	if (Start == NULL) {
		StartPtr = p_NodeOfBookList;

	}
	else {
		do {

			if (Start->m_iPrice >= p_NodeOfBookList->m_iPrice) {
				p_NodeOfBookList->m_pNext = Start;
				StartPtr = p_NodeOfBookList;
				break;
			}
			if (Start->m_pNext == NULL) {
				Start->m_pNext = p_NodeOfBookList;
				break;
			}
			if (Start->m_pNext->m_iPrice >= p_NodeOfBookList->m_iPrice) {
				p_NodeOfBookList->m_pNext = Start->m_pNext;
				Start->m_pNext = p_NodeOfBookList;
				break;
			}
			if (Start->m_pNext->m_pNext == NULL) {
				Start->m_pNext->m_pNext = p_NodeOfBookList;
				break;
			}

			Start = Start->m_pNext;

		} while (Start->m_pNext != NULL);
	}
	return StartPtr;
}
/*-------------------------------------------------------------------------------------*/
struct sBook* ReadFromFile(char* string, struct sBook* Start) {
	printf("Enter the full path to .txt file: ");
	gets_s(FileName, 10000);

	while (FileName[strlen(FileName) - 1] != 't'
		or FileName[strlen(FileName) - 2] != 'x'
		or FileName[strlen(FileName) - 3] != 't'
		or FileName[strlen(FileName) - 4] != '.') {
		printf("Oops! File isn`t .txt, try again: ");
		gets_s(FileName, 10000);
	}
	FILE* F_Library = fopen(FileName, "rt");

	while (!F_Library) {
		printf("Oops! Wrong path to file, try again: ");
		gets_s(FileName, 10000);
		while (FileName[strlen(FileName) - 1] != 't'
			or FileName[strlen(FileName) - 2] != 'x'
			or FileName[strlen(FileName) - 3] != 't'
			or FileName[strlen(FileName) - 4] != '.') {
			printf("Oops! File isn`t .txt, try again: ");
			gets_s(FileName, 10000);
		}
		F_Library = fopen(FileName, "rt");
	}

	struct sBook* StartPtr = Start;

	char* AuthorName = (char*)malloc(1000 * sizeof(char));
	char* BookName = (char*)malloc(1000 * sizeof(char));
	char* Year = (char*)malloc(1000 * sizeof(char));
	char* Pages = (char*)malloc(1000 * sizeof(char));
	char* Price = (char*)malloc(1000 * sizeof(char));
	char* token;

	int coun = 0;

	while (fgets(string, 1000, F_Library)) {
		coun++;
		token = strtok(string, "\\\n");
		int counter = 1;
		while (token != NULL) {
			switch (counter) {
			case(1):
				for (int i = 0; i < strlen(token); i++) {
					AuthorName[i] = token[i];
					AuthorName[i + 1] = '\0';
				}
				while (strlen(AuthorName) > 51) {
					printf("Oops! Error! The Name of Author in line #%d in file is incorrect\nEnter Name of the Author correctly: ", coun);
					gets_s(AuthorName, 1000);
					AuthorName[strlen(AuthorName) + 1] = '\0';
				}
				break;
			case(2):
				for (int i = 0; i < strlen(token); i++) {
					BookName[i] = token[i];
					BookName[i + 1] = '\0';
				}
				while (strlen(BookName) > 51) {
					printf("Oops! Error! The Name of Book in line #%d in file is incorrect\nEnter Name of the Book correctly: ", coun);
					gets_s(BookName, 1000);
					BookName[strlen(BookName) + 1] = '\0';
				}
				break;
			case(3):
				for (int i = 0; i < strlen(token); i++) {
					Year[i] = token[i];
					Year[i + 1] = '\0';
				}
				while (atoi(Year) > 2023 or atoi(Year) < 1 or strlen(Year) > 4
					or (strlen(Year) == 4 and ((isdigit(Year[1]) == false) or (isdigit(Year[2]) == false) or (isdigit(Year[3]) == false)))
					or (strlen(Year) == 3 and ((isdigit(Year[1]) == false) or (isdigit(Year[2]) == false)))
					or (strlen(Year) == 2 and (isdigit(Year[1]) == false))) {
					printf("Oops! Error! The Year in line #%d in file is incorrect\nEnter Year correctly: ", coun);
					gets_s(Year, 1000);
					Year[strlen(Year) + 1] = '\0';
				}
				break;
			case(4):
				for (int i = 0; i < strlen(token); i++) {
					Pages[i] = token[i];
					Pages[i + 1] = '\0';
				}
				while (atoi(Pages) > 9999 or atoi(Pages) < 48 or strlen(Pages) > 4
					or (strlen(Pages) == 4 and ((isdigit(Pages[1]) == false) or (isdigit(Pages[2]) == false) or (isdigit(Pages[3]) == false)))
					or (strlen(Pages) == 3 and ((isdigit(Pages[1]) == false) or (isdigit(Pages[2]) == false)))
					or (strlen(Pages) == 2 and (isdigit(Pages[1]) == false))) {
					printf("Oops! Error! The number of pages in line #%d in file is incorrect\nEnter number of pages correctly: ", coun);
					gets_s(Pages, 1000);
					Pages[strlen(Pages) + 1] = '\0';
				}
				break;
			case(5):
				for (int i = 0; i < strlen(token); i++) {
					Price[i] = token[i];
					Price[i + 1] = '\0';
				}
				while (atoi(Price) > 9999 or atoi(Price) < 1 or strlen(Price) > 4
					or (strlen(Price) == 4 and ((isdigit(Price[1]) == false) or (isdigit(Price[2]) == false) or (isdigit(Price[3]) == false)))
					or (strlen(Price) == 3 and ((isdigit(Price[1]) == false) or (isdigit(Price[2]) == false)))
					or (strlen(Price) == 2 and (isdigit(Price[1]) == false))) {
					printf("Oops! Error! The price in line #%d in file is incorrect!\nEnter the price correctly: ", coun);
					gets_s(Price, 1000);
					Price[strlen(Price) + 1] = '\0';
				}
				break;
			}

			token = strtok(NULL, "\\\n");

			counter++;
		}

		struct sBook* Node = CreateNode(AuthorName, BookName, Year, Pages, Price);
		StartPtr = AddNode(StartPtr, Node);

		counter = 1;
	}

	fclose(F_Library);
	return StartPtr;
}
//-------------------------------------------------------------------------------------