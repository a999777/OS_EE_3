#include "OurPointer.h"
#include "VirtualMemory.h"

#define PAGE_TABLE_FULL 1048576
#define BYTE_SIZE 4

//***********************************************************************
// function name: OurPointer consractor
// Description: initiate the adr value & virt mem
// Parameters: adr & vitrtual address
// Returns: OurPointer
//***********************************************************************
OurPointer::OurPointer(int adr, VirtualMemory* vrtlMem) {
	int adr_temp = adr << (BYTE_SIZE / 2);
	this->_adr = adr_temp;
	this->_vrtlMem = vrtlMem;
}

//***********************************************************************
// function name: operator *
// Description: returns the value the pointer points to
// Parameters: N/A
// Returns: value by reference
//***********************************************************************
int& OurPointer::operator*() {
	return *((this->_vrtlMem)->GetPage(this->_adr));
}

//***********************************************************************
// function name: operator++
// Description: increase the addr of the pointer by one
// Parameters: N/a
// Returns: Ourpointer after the increase
//***********************************************************************
OurPointer& OurPointer::operator++() {
	if ((this->_adr + BYTE_SIZE) > (VIRTMEMSIZE >> (BYTE_SIZE / 2))) {
		throw "We are limited to 4294967296 bytes with our 32 bit address size";
	}
	this->_adr = ((this->_adr) + BYTE_SIZE);
	return (*this);
}

//***********************************************************************
// function name: operator++
// Description: increase the addr of the pointer by one
// Parameters: N/a
// Returns: Ourpointer before the increase
//***********************************************************************
OurPointer OurPointer::operator++(int) {
	OurPointer Newpointer((this->_adr) >> (BYTE_SIZE / 2), this->_vrtlMem);
	operator++();
	return Newpointer;
}

//***********************************************************************
// function name: operator++
// Description: decrease the addr of the pointer by one
// Parameters: N/a
// Returns: Ourpointer after the decrease
//***********************************************************************
OurPointer& OurPointer::operator--() {
	if ((this->_adr - BYTE_SIZE) < 0) {
		throw "First of the memory";
	}
	this->_adr = ((this->_adr) - BYTE_SIZE);
	return (*this);
}

//***********************************************************************
// function name: operator++
// Description: decrease the addr of the pointer by one
// Parameters: N/a
// Returns: Ourpointer before the decrease
//***********************************************************************
OurPointer OurPointer::operator--(int) {
	OurPointer Newpointer((this->_adr) >> (BYTE_SIZE / 2), this->_vrtlMem);
	operator--();
	return Newpointer;
}
