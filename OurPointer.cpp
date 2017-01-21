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
OurPointer :: OurPointer(int adr, VirtualMemory* vrtlMem)
{
  int adr_temp = adr << (BYTE_SIZE/2);
  _adr = adr_temp;
	_vrtlMem = vrtlMem;
}

//***********************************************************************
// function name: operator *
// Description: returns the value the pointer points to
// Parameters: N/A
// Returns: value by reference
//***********************************************************************
int& OurPointer :: operator*()
{
	return *(_vrtlMem->GetPage(_adr));
}

//***********************************************************************
// function name: operator++
// Description: increase the addr of the pointer by one
// Parameters: N/a
// Returns: Ourpointer after the increase
//***********************************************************************
OurPointer& OurPointer :: operator++()
{
	if ((_adr+BYTE_SIZE) > (VIRTMEMSIZE >> (BYTE_SIZE/2))){ // what to do in this case???
		throw "We are limited to 4294967296 bytes with our 32 bit address size";
	}
	_adr = _adr + BYTE_SIZE;
	return (*this);
}

//***********************************************************************
// function name: operator++
// Description: increase the addr of the pointer by one
// Parameters: N/a
// Returns: Ourpointer before the increase
//***********************************************************************
OurPointer OurPointer :: operator++(int)
{
	OurPointer Newpointer(_adr >> (BYTE_SIZE/2), _vrtlMem);
	operator++();
	return Newpointer;
}

//***********************************************************************
// function name: operator++
// Description: decrease the addr of the pointer by one
// Parameters: N/a
// Returns: Ourpointer after the decrease
//***********************************************************************
OurPointer& OurPointer :: operator--()
{
	if ((_adr - BYTE_SIZE) < 0 ){ // what to do in this case???
		throw "First of the memory";
	}
	_adr = _adr - BYTE_SIZE;
	return (*this);
}

//***********************************************************************
// function name: operator++
// Description: decrease the addr of the pointer by one
// Parameters: N/a
// Returns: Ourpointer before the decrease
//***********************************************************************
OurPointer OurPointer :: operator--(int)
{
	OurPointer Newpointer(_adr >> (BYTE_SIZE/2) , _vrtlMem);
	operator--();
	return Newpointer;
}
