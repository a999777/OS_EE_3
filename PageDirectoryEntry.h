#ifndef _PAGE_DIRECTORY_ENTRY
#define _PAGE_DIRECTORY_ENTRY

#include "PageTableEntry.h"

class PageDirectoryEntry {

public:

	//Constructor
	PageDirectoryEntry() : _innerTable(NULL),_valid(false) {}

	//Destructor. Makes sure that the inner table is deleted if allocated.
	~PageDirectoryEntry() {
		if (this->_innerTable != NULL)
			delete (this->_innerTable);
	}

	//Link the outer table to an inner table by address of array.
	void set_inner_table_address(PageTableEntry* innerTableAdr);

	 //Return a pointer to the beginning of the inner table
	PageTableEntry* get_inner_table_address();

	//Returns whether the entry is valid
	bool is_valid();

	 //Allows to set whether the entry is valid
	void set_valid(bool valid);

private:
	//Pointer to an innerTable.
	PageTableEntry* _innerTable;
	bool _valid;
};

#endif
