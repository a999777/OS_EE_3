/*
 * ourpointer.h
 *
 *  Created on: 10 ���� 2017
 *      Author: Eitan Levin
 */

#ifndef OS_HM3_OURPOINTER_H_
#define OS_HM3_OURPOINTER_H_

#include "PageTable.h"

class OurPointer {
public:
	//Constructor
	OurPointer(int adr, VirtualMemory* vrtlMem): _adr(adr){
		 _vrtlMem = vrtlMem;
	}
	//Destructor
	~OurPointer() = default;
	int& operator*(); //Overload operator*
	OurPointer& operator++(); //Overload ++operator
	OurPointer operator++(int); //Overload operator++
	OurPointer& operator--(); //Overload operator--
	OurPointer operator--(int); //Overload�--operator
	unsigned int _adr; //the virtual address TODO return to private
	//FIXME the way we implemented _adr saves the address but in ints. that means that when the offset is
	//2 for example, that means that the true offset is 8
	VirtualMemory* _vrtlMem; //for requesting translations TODO move to private

private:


};

#endif /* OS_HM3_OURPOINTER_H_ */
