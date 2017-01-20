/*
 * PageTable.h
 *
 *  Created on: 10 ���� 2017
 *      Author: Eitan Levin
 */

#ifndef PAGETABLE_H_
#define PAGETABLE_H_

#include "PageDirectoryEntry.h"

//TODO support in log file should be added, as requested in pdf

//Incomplete declaration- so compiler won't scream when we use virtmem.
class VirtualMemory;

class PageTable {
private:
	VirtualMemory* _virtMem;
	PageDirectoryEntry* _outerPageTable;

public:
	PageTable(VirtualMemory* virtMem) : _virtMem(virtMem) {
		//_outerPageTable = (PageDirectoryEntry*)malloc(sizeof(PageDirectoryEntry)*NUM_OF_ENTRIES);
		//FIXME the pdf says malloc. But malloc does not call constructors. is new okay?
		_outerPageTable = new PageDirectoryEntry[NUM_OF_ENTRIES];
		//After that action we have 1024 un-initialized Page Directory Entries
	}

	~PageTable() {
		if(_outerPageTable != NULL) {
			delete [] _outerPageTable;
		}
	}

	//Here we get a virtual address of a page and we are expected to return a
	//pointer to the frame where it is located.
	int* GetPage (unsigned int adr);

	void setTableEntryInvalid(int PageDirectoryEntry, int PageTableEntry);

};



#endif /* PAGETABLE_H_ */
