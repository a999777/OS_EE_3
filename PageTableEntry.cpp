#include "PageTableEntry.h"


//***********************************************************************
// function name: PageTableEntry
// Description: constractor - initilaize PTE to 0
// Parameters: N/A
// Returns: N/A
//***********************************************************************
PageTableEntry::PageTableEntry()
{
	page_address = NULL;
	valid = false;
	swapped = false;
}

//***********************************************************************
// function name: get_page_address
// Description: returns a pointer to the begining of the frame
// Parameters: N/A
// Returns: pointer to the begining of the frame
//***********************************************************************
int* PageTableEntry::get_page_address()
{
	return page_address;
}

//***********************************************************************
// function name: set_page_address
// Description: Set the pointer to a frame
// Parameters: adr - new address
// Returns: N/A
//***********************************************************************
void PageTableEntry::set_page_address(int* adr)
{
	page_address = adr;
}

//***********************************************************************
// function name: is_valid
// Description: returns if the page is in the memory (valid) or not
// Parameters: N/A
// Returns: true - page is valid, false - page isn't valid
//***********************************************************************
bool PageTableEntry::is_valid()
{
	return valid;
}

//***********************************************************************
// function name: is_swapped
// Description: returns if the page is in the swap device or not
// Parameters: N/A
// Returns: true - page swapped, false - page isn't
//***********************************************************************
bool PageTableEntry::is_swapped()
{
	return swapped;
}

//***********************************************************************
// function name: set_valid
// Description: set validition of the fram
// Parameters: validition new value
// Returns: N/A
//***********************************************************************
void PageTableEntry::set_valid(bool _valid)
{
	valid = _valid;
}

//***********************************************************************
// function name: set_swapped
// Description: set page to swapped
// Parameters: swap new value
// Returns: N/A
//***********************************************************************
void PageTableEntry::set_swapped(bool _swapped)
{
	swapped = _swapped;
}
