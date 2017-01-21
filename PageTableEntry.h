#ifndef  _PAGE_TABLE_ENTRY
#define  _PAGE_TABLE_ENTRY
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>


class PageTableEntry
{
public:
	PageTableEntry();
	int* get_page_address(); //Pointer to beginning of frame
	void set_page_address(int* adr); //Set the pointer to a frame
	bool is_valid(); //Returns whether the entry is valid
	bool is_swapped(); //Returns whether the entry is swapped
	void set_valid(bool _valid); //Allows to set whether the entry is valid
	void set_swapped(bool _valid);//Allows to set whether the entry is swapped
private:
	int* page_address;
	bool valid; //valid bit
	bool swapped;
};
#endif
