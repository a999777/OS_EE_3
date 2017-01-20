/*
 * PageDirectoryEntry.h
 *
 *  Created on: 11 αιπε 2017
 *      Author: ilanmisa
 */

#ifndef OS_HW3_PAGEDIRECTORYENTRY_H_
#define OS_HW3_PAGEDIRECTORYENTRY_H_

#include "PageTableEntry.h"
#include <iostream>

using std::cout;
using std::endl;

#define NUM_OF_ENTRIES 1024

/*
 * This file will be representing an entry in the outer page table. That means
 * each entry here is actually an inner page table containing 1024 PageTableEntry.
 * Note: This is an entry of the outer page table, but it is kind of an inner page
 * table itself.
 */

class PageDirectoryEntry {
public:
	//Notice the default constructor intentionally does !not allocate! entries.
	//This is done in order to mimic the behavior of a linux system.
	PageDirectoryEntry() : _valid(false),_innerTable(NULL) {}

	~PageDirectoryEntry() {
		if(_innerTable != NULL) {
			delete [] _innerTable;
		}
	}

	void create_inner_table() {
		//_innerTable = (PageTableEntry*)malloc(sizeof(PageTableEntry)*NUM_OF_ENTRIES);
		//FIXME the pdf says malloc. But malloc does not call constructors. is new okay? check.
		_innerTable = new PageTableEntry[NUM_OF_ENTRIES];
	}

	bool is_inner_entry_valid(int innerTableEntry) {
		if(_valid == false) {
			return false;
		}
		return _innerTable[innerTableEntry].is_valid();
	}

	void set_inner_entry_invalid(int PageTableEntry) {
		_innerTable[PageTableEntry].set_valid(false);
	}

	bool was_inner_entry_valid(int innerTableEntry) {
		if(_valid == false) {
			return false;
		}
		return _innerTable[innerTableEntry].was_linked();
	}

	int* get_page_address(int innerTableEntry) {
 		 int* frameAdr = _innerTable[innerTableEntry].get_page_address();
		 if(frameAdr == NULL) { //TODO
			 cout << "Detected unhandled mistake in line " << __LINE__ << endl;
			 exit(1);
		 }
		 return frameAdr;
	}

	void set_page_address(int innerTableEntry, int* adr) {
		_innerTable[innerTableEntry].set_page_address(adr);
		_innerTable[innerTableEntry].set_valid(true);
		_innerTable[innerTableEntry].set_linked(true);
	}

	bool is_valid() {
		//Returns whether the entry is valid
		return _valid;
	}
	void set_valid(bool valid) {
		//Allows to set whether the entry is valid
		_valid = valid;
	}

private:
	bool _valid;
	PageTableEntry* _innerTable;
};



#endif /* OS_HW3_PAGEDIRECTORYENTRY_H_ */
