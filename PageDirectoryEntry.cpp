/*
 * PageDirectoryEntry.cpp
 *
 *  Created on: 21 בינו׳ 2017
 *      Author: Amit
 */

#include "PageDirectoryEntry.h"

void PageDirectoryEntry::create_inner_table() {
	//_innerTable = (PageTableEntry*)malloc(sizeof(PageTableEntry)*NUM_OF_ENTRIES);
	//FIXME the pdf says malloc. But malloc does not call constructors. is new okay? check.
	_innerTable = new PageTableEntry[NUM_OF_ENTRIES];
}

bool PageDirectoryEntry::is_inner_entry_valid(int innerTableEntry) {
	if(_valid == false) {
		return false;
	}
	return _innerTable[innerTableEntry].is_valid();
}

void PageDirectoryEntry::set_inner_entry_invalid(int PageTableEntry) {
	_innerTable[PageTableEntry].set_valid(false);
}

bool PageDirectoryEntry::was_inner_entry_valid(int innerTableEntry) {
	if(_valid == false) {
		return false;
	}
	return _innerTable[innerTableEntry].was_linked();
}

int* PageDirectoryEntry::get_page_address(int innerTableEntry) {
	 int* frameAdr = _innerTable[innerTableEntry].get_page_address();
	 if(frameAdr == NULL) { //TODO
		 cout << "Detected unhandled mistake in line " << __LINE__ << endl;
		 exit(1);
	 }
	 return frameAdr;
}

void PageDirectoryEntry::set_page_address(int innerTableEntry, int* adr) {
	_innerTable[innerTableEntry].set_page_address(adr);
	_innerTable[innerTableEntry].set_valid(true);
	_innerTable[innerTableEntry].set_linked(true);
}

bool PageDirectoryEntry::is_valid() {
	//Returns whether the entry is valid
	return _valid;
}

void PageDirectoryEntry::set_valid(bool valid) {
	//Allows to set whether the entry is valid
	_valid = valid;
}


