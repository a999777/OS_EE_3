/*
 * OurPointer.cpp
 *
 *  Created on: 14 ����� 2017
 *      Author: Amit
 */

#include "OurPointer.h"
#include "VirtualMemory.h"

//Operator that returns the int pointed by OurPointer
int& OurPointer::operator*() {
	/*unsigned int address = _adr;
	unsigned int offset;
	CHANGE_ADR_INT_TO_ADR(address);
	GET_OFFSET_BITS(address,offset);
	int* physmemFrame = _vrtlMem->GetPage(_adr); //TODO debug
	return *(physmemFrame + offset); TODO old address format*/
	int offset;
	GET_OFFSET_BITS(_adr, offset);
	return *((_vrtlMem->GetPage(_adr)) + offset);
}

//Overload ++operator
OurPointer& OurPointer::operator++() {
	/*
	_adr++;
	return *this; TODO old format */
	_adr += sizeof(int);
	return *this;
}

//Overload operator++ means we increment the virtual address.
OurPointer OurPointer::operator++(int) {
	/*OurPointer beforeAddition(_adr,_vrtlMem);
	this->operator++(); //Using the pre-fix operator we already overloaded
	return beforeAddition; TODO old format */
	OurPointer beforeAddition(_adr >> 2, _vrtlMem);
	this->operator++();
	return beforeAddition;
}

//Overload --operator TODO mistake in pdf??
OurPointer& OurPointer::operator--() {
	/*//_adr -= sizeof(_adr);
	_adr--;
	return *this; TODO old format */
	_adr -= sizeof(int);
	return *this;
}

//Overload operator--
OurPointer OurPointer::operator--(int) {
	/*OurPointer beforeDecrement(_adr,_vrtlMem);
	this->operator--(); //Using the pre-fix operator we already overloaded
	return beforeDecrement; TODO old format */
	OurPointer beforeDecrement(_adr >> 2, _vrtlMem);
	operator--();
	return beforeDecrement;
}
