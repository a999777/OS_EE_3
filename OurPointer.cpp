#include "OurPointer.h"
#include "VirtualMemory.h"

int& OurPointer::operator*() {
	unsigned int offset;
	GET_OFFSET_BITS(_adr, offset);
	if(_adr == 4096) {
		cout << "The offset is " << offset << endl;
		cout << "So we need to return " << _vrtlMem->GetPage(_adr) << " in hex + 0" << endl;
		cout << "However, we'll return " << (_vrtlMem->GetPage(_adr) + offset) << endl;
	}// TODO debug */
	return *(_vrtlMem->GetPage(_adr) + offset); //Since this is pointer arithmetic we don't need to shift back left
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
