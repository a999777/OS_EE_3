/*
 * SwapDevice.cpp
 *
 *  Created on: 10 αιπε 2017
 *      Author: Eitan Levin
 */

#include "SwapDevice.h"
using namespace std;

void SwapDevice::WriteFrameToSwapDevice(int pageNumber, int* pageOut) {
	if (_data[pageNumber] == NULL) {
		if (++_size > MAX_SPACE_ALLOWED) {
			cerr << "The swap device seems to be using too much space, worth investigating" << endl;
		}
		_data[pageNumber] = (int*)malloc(PAGESIZE);
	}
	memcpy(_data[pageNumber], pageOut, PAGESIZE);
}
int SwapDevice::ReadFrameFromSwapDevice(int pageNumber, int* pageIn) {
	if (_data[pageNumber] == NULL) {
		return FRAME_NOT_ALLOCATED;
	}
	memcpy(pageIn, _data[pageNumber], PAGESIZE);
	return SUCCESS;
}

size_t SwapDevice::size() {
	return this->_size;
}
