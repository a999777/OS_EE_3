#ifndef _PAGE_TABLE
#define _PAGE_TABLE
#include "PageDirectoryEntry.h"
#include "PageTableEntry.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#define TABLE_SIZE 1024
#define INT_BYTE_SIZE 4
#define PAGE_BYTES 4096
#define BIT_WISE_AND_FOR_DIRECTORY 4290772992 //for logical and - 11111111110000000000000000000000
#define BIT_WISE_SHIFT_FOR_DIRECTORY 22	//for logical shift right
#define BIT_WISE_AND_FOR_PAGE 4190208 //for logical and - 00000000001111111111000000000000
#define BIT_WISE_SHIFT_FOR_PAGE 12	//for logical shift right
#define BIT_WISE_AND_FOR_OFFSET 4095 //for logical and - 00000000000000000000111111111111
#include <queue>
using namespace std;
using std::cout;
using std::endl;
using std::ofstream;
using std::string;

class VirtualMemory;
class PageTable {
public:
	PageTable();
	~PageTable();
	int* GetPage(unsigned int adr, VirtualMemory* mem);
private:
	PageDirectoryEntry _outerPageTable[TABLE_SIZE]; //cr3 - PDE array
	FILE * pFile;
	void write(string printline);
	queue<unsigned int> usedPages; // save all the pages in RAM by order
	int swapper(VirtualMemory* mem); // func to transfer page to swap device

};
#endif
