#ifndef _OUR_POINTER
#define _OUR_POINTER

class VirtualMemory;

class OurPointer {
public:
	//Constructor
	OurPointer(int adr, VirtualMemory* vrtlMem) {
		_adr = adr << 2;
		_vrtlMem = vrtlMem;
	}

	 //Destructor
	~OurPointer() = default;

	//Overload operator*
	int& operator*();

	//Overload ++operator
	OurPointer& operator++();

	//Overload operator++
	OurPointer operator++(int);

	//Overload --operator
	OurPointer& operator--();

	//Overload operator--
	OurPointer operator--(int);
private:
	//Storing the virtual address
	unsigned int _adr;
	VirtualMemory* _vrtlMem;
};
#endif
