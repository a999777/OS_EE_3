/*
 * PageTableEntry.cpp
 *
 *  Created on: 21 áéğå× 2017
 *      Author: Amit
 */

#include "PageTableEntry.h"

int* PageTableEntry::get_page_address() {
	//Pointer to beginning of frame  
	return _framePointedBegining;
}

void PageTableEntry::set_page_address(int* adr) {
	//Set the pointer to a frame
	//std::cout << "set page address: " << adr << std::endl;//TODO eitan test
	_framePointedBegining = adr;
}

bool PageTableEntry::is_valid() {
	//Returns whether the entry is valid
	return _valid;
}

void PageTableEntry::set_valid(bool valid) {
	//Allows to set whether the entry is valid
	_valid = valid;
}

bool PageTableEntry::was_linked() {
	//Returns whether the entry was linked sometime to a frame
	return _linked;
}

void PageTableEntry::set_linked(bool linked) {
	//Allows to set whether the entry is linked to a frame
	_linked = linked;
}
