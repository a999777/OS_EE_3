/*
 * SwapDevice.h
 *
 *  Created on: 10 áéðå 2017
 *      Author: Eitan Levin
 */

#ifndef SWAPDEVICE_H_
#define SWAPDEVICE_H_
#include <unordered_map>
#include <vector>
#include <string.h>
#include <iostream>
#include "MacroDefine.h"
#define PAGESIZE 4096

class SwapDevice
{
public:
	SwapDevice() : _size(0) {}
	 /*
	  * Write the content of page to the swap device,
	  * "pageOut" is the frame base pointer where the
	  * page is now allocated
	  */
	void WriteFrameToSwapDevice(int pageNumber, int* pageOut);
	/*
	 * Put the content of the page in "page". "pageIn" is the frame
	 * base pointer to where the page is about to be allocated,
	 * returns 1 if page is not stored in the swap device.
	 */
	int ReadFrameFromSwapDevice(int pageNumber, int* pageIn);
private:
	std::unordered_map<int, int*> _data;
	size_t _size;
};

#endif /* SWAPDEVICE_H_ */
