#include "OurPointer.h"
#include "VirtualMemory.h"

int& OurPointer::operator*() {
	return *((_vrtlMem)->GetPage(_adr));
}

//Prefix
OurPointer& OurPointer::operator++() {
	if (_adr + sizeof(int) > (VIRTMEMSIZE >> 2)) {
		throw "We are limited to 4294967296 bytes with our 32 bit address size";
	}
	_adr += sizeof(int);
	return *this;
}

//Postfix
OurPointer OurPointer::operator++(int) {
	OurPointer beforeIncrement((_adr >> 2), _vrtlMem);
	operator++();
	return beforeIncrement;
}

//Prefix (I think there is a mistake in the pdf TODO)
OurPointer& OurPointer::operator--() {
	if ((_adr - sizeof(int)) < 0) {
		throw "Illegal decrement!";
	}
	_adr -= sizeof(int);
	return *this;
}

//Postfix
OurPointer OurPointer::operator--(int) {
	OurPointer beforeDecrement((_adr >> 2),_vrtlMem);
	operator--();
	return beforeDecrement;
}
