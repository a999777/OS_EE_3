#include "PageDirectoryEntry.h"


//***********************************************************************
// function name: PageDirectoryEntry
// Description: constractor - initilaize PDE to 0
// Parameters: N/A
// Returns: N/A
//***********************************************************************
PageDirectoryEntry::PageDirectoryEntry()
{
	page_table_address = NULL;
	valid = false;
}

//***********************************************************************
// function name: ~PageDirectoryEntry
// Description: destractor - free the pte table
// Parameters: N/A
// Returns: N/A
//***********************************************************************
PageDirectoryEntry::~PageDirectoryEntry()
{
	if (page_table_address != NULL)
		delete(page_table_address);
}

//***********************************************************************
// function name: set_table_address
// Description: set the PTE table address
// Parameters: PTE table pointer
// Returns: N/A
//***********************************************************************
void PageDirectoryEntry::set_table_address(PageTableEntry* adr)
{
	page_table_address = adr;
}

//***********************************************************************
// function name: get_page_address
// Description: returns a pointer to the begining PTE table
// Parameters: N/A
// Returns: pointer to the begining of the PTE table
//***********************************************************************
PageTableEntry* PageDirectoryEntry::get_table_address()
{
	return page_table_address;
}

//***********************************************************************
// function name: is_valid
// Description: returns if the Directory valid
// Parameters: N/A
// Returns: true -  Directory is valid, false -  Directory isn't valid
//***********************************************************************
bool PageDirectoryEntry::is_valid()
{
	return valid;
}


//***********************************************************************
// function name: set_valid
// Description: set validition of the  Directory
// Parameters: validition new value
// Returns: N/A
//***********************************************************************
void PageDirectoryEntry::set_valid(bool _valid)
{
	valid = _valid;
}

