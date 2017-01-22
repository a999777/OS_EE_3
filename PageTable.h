#ifndef _PAGE_TABLE
#define _PAGE_TABLE

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <queue>

#include "MacroDefine.h"
#include "PageDirectoryEntry.h"
#include "PageTableEntry.h"

#define TABLE_SIZE 1024
#define INT_BYTE_SIZE 4
#define PAGE_BYTES 4096

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
	//FILE * pFile;//TODO nathans method, no need in ours
	std::ofstream logFile;
	void write(string printline);
	queue<unsigned int> usedPages; // save all the pages in RAM by order
	int swapper(VirtualMemory* mem); // func to transfer page to swap device

};
#endif
