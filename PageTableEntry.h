#ifndef  _PAGE_TABLE_ENTRY
#define  _PAGE_TABLE_ENTRY

#include <iostream>

/**
 * This class implements an inner page table entry. Each one of these represent
 * a page of the virtual memory. Therefore there are 1024*1024 of these.
 * Each entry is connected directly to a frame in memory.
 */

class PageTableEntry {

public:
	//Constructor
	PageTableEntry(): _physFrameAddress(NULL),_valid(false),_swapped(false) {}

	~PageTableEntry() = default;

	//Pointer to beginning of frame
	int* get_page_address();

	//Set the pointer to a frame
	void set_page_address(int* adr);

	//Returns whether the entry is swapped
	bool is_swapped();

	//Allows to set whether the entry is swapped
	void set_swapped(bool valid);

	//Returns whether the entry is valid
	bool is_valid();

	//Allows to set whether the entry is valid
	void set_valid(bool valid);

private:
	int* _physFrameAddress;
	bool _valid;
	bool _swapped;
};
#endif
