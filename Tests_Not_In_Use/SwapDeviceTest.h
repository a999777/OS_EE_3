/*
 * SwapDeviceTest.h
 *
 *  Created on: 13 αιπε 2017
 *      Author: Eitan Levin
 */

#ifndef SWAPDEVICETEST_H_
#define SWAPDEVICETEST_H_

#include "unitTests.h"
#include "SwapDevice.h"
#include "PhysMem.h"
#include "PageTableEntry.h"
#include "PageDirectoryEntry.h"
#include "MacroDefine.h"

/**
 * Testing Swap Device
 */
bool SwapDeviceTest() {
	SwapDevice swapDevice1;
	int randomNumber = rand();
	int* pageOut = &randomNumber;
	int pageNumber;
	for (unsigned int i = 0 ; i < MAX_SPACE_ALLOWED; i++) {
		if (swapDevice1.size() != i) {
			return false;
		}

	}
	/*PageDirectoryEntry ent1, ent2;

	if(ent1.is_valid() || ent2.is_valid()) {
			ERROR_AND_PRINT("valid status at creation is bad");
	}

	ent1.create_inner_table();
	ent1.set_valid(true);
	for(int i = 0; i < NUM_OF_ENTRIES ; i++) {
		if(ent1.is_inner_entry_valid(i)) {
			ERROR_AND_PRINT("inner entries are created and they are not supposed to.");
		}
	}*/
	return true;
}



void EitanTests() {
	RUN_TEST("SwapDeviceTest", SwapDeviceTest());
}




#endif /* SWAPDEVICETEST_H_ */
