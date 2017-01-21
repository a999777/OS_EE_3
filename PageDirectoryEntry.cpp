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
	this->_innerTable = new PageTableEntry[NUM_OF_ENTRIES];
}

bool PageDirectoryEntry::is_inner_entry_valid(int innerTableEntry) {
	if(this->_valid == false) {
		cout << "Detected unhandled mistake in line " << __LINE__ << endl;
		exit(1);//TODO should never happen according to implementation (according to usage)
		//return false;
	}
	return this->_innerTable[innerTableEntry].is_valid();
}

void PageDirectoryEntry::set_inner_entry_invalid(int innerTableEntry) {
	cout << "Detected unhandled mistake in line " << __LINE__ << endl;
	exit(7);//TODO should never happen according to implementation (according to usage)
	this->_innerTable[innerTableEntry].set_valid(false);
}

bool PageDirectoryEntry::was_inner_entry_valid(int innerTableEntry) {
	if(this->_valid == false) {
		cout << "Detected unhandled mistake in line " << __LINE__ << endl;
		exit(1);//TODO should never happen according to implementation (according to usage)
		//return false;
	}
	return this->_innerTable[innerTableEntry].was_linked();
}

int* PageDirectoryEntry::get_page_address(int innerTableEntry) {
	 int* frameAdr = this->_innerTable[innerTableEntry].get_page_address();
	 if(frameAdr == NULL) { //TODO
		 cout << "Detected unhandled mistake in line " << __LINE__ << endl;
		 exit(1);
	 }
	 return frameAdr;
}

void PageDirectoryEntry::set_page_address(int innerTableEntry, int* adr) {
	this->_innerTable[innerTableEntry].set_page_address(adr);
	this->_innerTable[innerTableEntry].set_valid(true);
	this->_innerTable[innerTableEntry].set_linked(true);
}

bool PageDirectoryEntry::is_valid() {
	//Returns whether the entry is valid
	return this->_valid;
}

void PageDirectoryEntry::set_valid(bool valid) {
	//Allows to set whether the entry is valid
	if (this->_valid == valid) {//FIXME for debugging
		cout << "set_valid but valid was already: " << valid << endl;
	}
	this->_valid = valid;
}


