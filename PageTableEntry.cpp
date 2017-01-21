/*
 * PageTableEntry.cpp
 *
 *  Created on: 21 áéğå× 2017
 *      Author: Amit
 */

#include "PageTableEntry.h"

int* PageTableEntry::get_page_address() {
	//Pointer to beginning of frame  
	return this->_framePointedBegining;
}

void PageTableEntry::set_page_address(int* adr) {
	//Set the pointer to a frame
	//std::cout << "set page address: " << adr << std::endl;//TODO eitan test
	//TODO maby need to allocate?
	this->_framePointedBegining = adr;
}

bool PageTableEntry::is_valid() {
	//Returns whether the entry is valid
	return (this->_isValid.is_valid());//TODO
	//return this->_valid;
}

void PageTableEntry::set_valid(bool valid) {
	//Allows to set whether the entry is valid
	(this->_isValid).set_valid(valid);//TODO
	//this->_valid = valid;
}

bool PageTableEntry::was_linked() {
	//Returns whether the entry was linked sometime to a frame
	return this->_linked;
}

void PageTableEntry::set_linked(bool linked) {
	//Allows to set whether the entry is linked to a frame
	this->_linked = linked;
}
