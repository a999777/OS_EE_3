#ifndef _PAGE_TABLE
#define _PAGE_TABLE

#include <fstream>
#include <queue>

#include "MacroDefine.h"
#include "PageDirectoryEntry.h"
#include "PageTableEntry.h"

#define INT_SIZE 4
#define TABLE_SIZE 1024
#define PAGE_SIZE 4096

using namespace std;
using std::cout;
using std::endl;
using std::ofstream;

//Forward declaration- so we'll able to use it.
class VirtualMemory;

class PageTable {
public:

	//Constructor.
	PageTable(VirtualMemory* vrtlMem) : _vrtlMem(vrtlMem) {
		/*for (int i = 0; i < TABLE_SIZE; i++) {
			_outerPageTable[i].set_valid(false);
			_outerPageTable[i].set_inner_table_address(NULL);
		} TODO I think this is not needed */
		logFile.open("log.csv");
		logFile <<"Page Number,Virtual Address,Physical Address,Page Fault,Swap,";
		logFile << "Evicted,Allocated Page Table Entries" << endl;
		//TODO below is nathans method, above is ours
		/*this->pFile = fopen("log.csv", "w");
		 std::stringstream tmp_str;
		 tmp_str
		 << "Page Number,Virtual Address,Physical Address,Page Fault,Swap,Evicted,Allocated Page Table Entries"
		 << endl;
		 write(tmp_str.str());*/
	}

	//Destructor. Closes the log file.
	~PageTable() {
		logFile.close();
		//fclose(this->pFile);//TODO nathans method, no need in ours
	}

	//Returns a pointer to the base of the frame which adr is linked to.
	int* GetPage(unsigned int adr);

	//Requesting the virtual memory to swap out a frame in order to get one.
	int swapOutPage();

private:
	PageDirectoryEntry _outerPageTable[TABLE_SIZE]; //cr3 - PDE array

	//FILE * pFile;//TODO nathans method, no need in ours

	VirtualMemory* _vrtlMem;

	ofstream logFile;

	queue<unsigned int> usedPages; // save all the pages in RAM by order


};
#endif
