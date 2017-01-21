#ifndef _OUR_POINTER
#define _OUR_POINTER
#include "PageTable.h"

class VirtualMemory;

class OurPointer {
public:
	OurPointer(int adr, VirtualMemory* vrtlMem); //Constructor
	~OurPointer(){}; //Destructor
	int& operator*(); //Overload operator*
	OurPointer& operator++(); //Overload ++operator
	OurPointer operator++(int); //Overload operator++
	OurPointer& operator--(); //Overload operator??
	OurPointer operator--(int); //Overload ??operator
private:
	unsigned int _adr; //the virtual address
	VirtualMemory* _vrtlMem; //for requesting translations
};
#endif
