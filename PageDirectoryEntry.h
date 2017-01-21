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

	void create_inner_table();

	bool is_inner_entry_valid(int innerTableEntry);

	void set_inner_entry_invalid(int PageTableEntry);

	bool was_inner_entry_valid(int innerTableEntry);

	int* get_page_address(int innerTableEntry);

	void set_page_address(int innerTableEntry, int* adr);

	bool is_valid();

	void set_valid(bool valid);

private:
	bool _valid;
	PageTableEntry* _innerTable;
};



#endif /* OS_HW3_PAGEDIRECTORYENTRY_H_ */
