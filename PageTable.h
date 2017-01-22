#ifndef _PAGE_TABLE
#define _PAGE_TABLE

#include <fstream>
#include <queue>

#include "MacroDefine.h"
#include "PageDirectoryEntry.h"
#include "PageTableEntry.h"

/**
 * This class represents the outer page table. Each one of its 1024 entries
 * is a PageDirectoryEntry. In our system, this class has the mechanism to
 * translate virtual address into physical ones.
 */

using namespace std;
using std::cout;
using std::endl;
using std::ofstream;

//Forward declaration- so we'll able to use it here.
class VirtualMemory;

class PageTable {
public:

	//Constructor.
	PageTable(VirtualMemory* vrtlMem) : _vrtlMem(vrtlMem) {
		//Preparations for log file: open it and write first line.
		logFile.open("log.csv");
		logFile <<"Page Number,Virtual Address,Physical Address,Page Fault,Swap,";
		logFile <<"Evicted,Allocated Page Table Entries" << endl;
	}

	//Destructor. Closes the log file.
	~PageTable() {
		logFile.close();
	}

	//Returns a pointer to the base of the frame which adr is linked to.
	int* GetPage(unsigned int adr);

	//Requesting the virtual memory to swap out a frame in order to get one.
	int swapOutPage();

private:
	//This is basically our cr3- it points to where the page table is.
	PageDirectoryEntry _outerPageTable[TABLE_SIZE];
	VirtualMemory* _vrtlMem;
	ofstream logFile;
	//A queue to maintain the order of allocations in our system.
	queue<unsigned int> usedPages;
};

#endif
