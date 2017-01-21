/*
 * PageTable.h
 *
 *  Created on: 10 ���� 2017
 *      Author: Eitan Levin
 */

#ifndef PAGETABLE_H_
#define PAGETABLE_H_

#include <fstream>
#include "PageDirectoryEntry.h"

//TODO support in log file should be added, as requested in pdf

//Incomplete declaration- so compiler won't scream when we use virtmem.
class VirtualMemory;

class PageTable {
private:
	VirtualMemory* _virtMem;
	PageDirectoryEntry* _outerPageTable;
	std::ofstream logFile;

public:
	//PageTable(VirtualMemory* virtMem) : _virtMem(virtMem) {
	PageTable(VirtualMemory* virtMem) {//TODO eitan
		this->_virtMem = virtMem;//TODO eitan
		//_outerPageTable = (PageDirectoryEntry*)malloc(sizeof(PageDirectoryEntry)*NUM_OF_ENTRIES);
		//FIXME the pdf says malloc. But malloc does not call constructors. is new okay?
		this->_outerPageTable = new PageDirectoryEntry[NUM_OF_ENTRIES];
		this->logFile.open("log.csv");
		this->logFile << "Page Number,Virtual Address,Physical Address,Page Fault,Swap,Evicted,Allocated Page Table Entries" << endl;
		//After that action we have 1024 un-initialized Page Directory Entries
	}

	~PageTable() {
		if(this->_outerPageTable != NULL) {
			delete[] this->_outerPageTable;
			this->_outerPageTable = NULL;//TODO eitan
		}
	}

	//Here we get a virtual address of a page and we are expected to return a
	//pointer to the frame where it is located.
	int* GetPage (unsigned int adr);

	void setTableEntryInvalid(int PageDirectoryEntry, int PageTableEntry);

};



#endif /* PAGETABLE_H_ */
