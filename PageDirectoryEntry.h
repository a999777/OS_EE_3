#ifndef _PAGE_DIRECTORY_ENTRY
#define _PAGE_DIRECTORY_ENTRY
#include "PageTableEntry.h"

class PageDirectoryEntry
{
private:
	PageTableEntry* page_table_address;// pointer to second level of the page table
	bool valid;
public:
	PageDirectoryEntry();
	~PageDirectoryEntry();
	void set_table_address(PageTableEntry* adr); //Set the pointer to a table
	PageTableEntry* get_table_address(); //Pointer to beginning of table
	bool is_valid(); //Returns whether the entry is valid
	void set_valid(bool _valid); //Allows to set whether the entry is valid
};
#endif
