/*
 * SwapDevice.cpp
 *
 *  Created on: 10 αιπε 2017
 *      Author: Eitan Levin
 */

#include "SwapDevice.h"
using namespace std;

void SwapDevice::WriteFrameToSwapDevice(int pageNumber, int* pageOut) {
	if (this->_data[pageNumber] == NULL) {
		if (++(this->_size) > 1048576) {
			cerr << "The swap device seems to be using too much space,worth investigating" << endl;
		}
		this->_data[pageNumber] = (int*) malloc(PAGESIZE);
	}
	memcpy(_data[pageNumber], pageOut, PAGESIZE);
}

int SwapDevice::ReadFrameFromSwapDevice(int pageNumber, int* pageIn) {
	if (this->_data[pageNumber] == NULL) {
		return ERROR_RESULT;
	}
	memcpy(pageIn, this->_data[pageNumber], PAGESIZE);
	return SUCCESS_RESULT;
}
