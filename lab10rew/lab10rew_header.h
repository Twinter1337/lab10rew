#ifndef LAB10HEADER_H
#define LAB10HEADER_H
#define BOOK_NAME_LENGTH 50
#define AUTHOR_NAME_LENGTH 50
#define READ_FILE_STR_LENGTH 500
#define PAREMETERS_OF_BOOK_AMOUNT 5

struct sBook {
	char m_cAutor[AUTHOR_NAME_LENGTH];
	char m_cName[BOOK_NAME_LENGTH];
	int m_iYear;
	int m_iPages;
	int m_iPrice;
	struct sBook* m_pNext;
};

void PrintBookList(struct sBook* p_HeadOfBookList);
void PrintFilteredByABookList(struct sBook* p_HeadOfBookList);
struct sBook* DeLeteBook(struct sBook* p_HeadOfBookList);
struct sBook* ReadFromFile(char* string, struct sBook* Start);
struct sBook* CreateNode(char AuthorName[AUTHOR_NAME_LENGTH], char BookName[BOOK_NAME_LENGTH], char* Year, char* Pages, char* Price);
struct sBook* AddNode(struct sBook* Start, struct sBook* p_NodeOfBookList);
struct sBook* AddNewBook(struct sBook* Start);

#endif
