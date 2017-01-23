#include <iostream>
#include "PageTable.h"
#include "VirtualMemory.h"

int PageTable::swapOutPage() {
	//Saving the virtual address of the page allocated first in queue
	unsigned int oldestAdr = usedPages.front();
	usedPages.pop();

	unsigned int directoryBits, pageBits;
	GET_MSB_BITS(oldestAdr, directoryBits);
	GET_MIDDLE_BITS(oldestAdr, pageBits);

	//Getting the physical frame of oldestAdr, marking oldestAdr as swapped
	int* swappedFrame = GET_INNER_PAGE_ADDRESS(directoryBits, pageBits);
	SET_SWAPPED_MACRO(directoryBits, pageBits, true);
	WRITE_FRAME_TO_SWAP(oldestAdr, swappedFrame);

	_vrtlMem->ReleaseFrame(swappedFrame);
	return (oldestAdr / PAGE_SIZE);
}

int* PageTable::GetPage(unsigned int adr) {

	//Separating the address given into parts
	unsigned int directoryNum, pageNum, offsetNum;
	GET_MSB_BITS(adr, directoryNum);
	GET_MIDDLE_BITS(adr, pageNum);
	GET_OFFSET_BITS(adr, offsetNum);

	//Log file preparation
	int logPageNumber = adr / 4096;
	int logPageFault = 0;
	int logSwap = 0;
	int logEvicted = -1;
	int logAllocatedPageTableEntries = 0;

	//If the directory doesn't exist- we allocate it.
	if (_outerPageTable[directoryNum].is_valid() == false) {

		logPageFault = 1;
		logAllocatedPageTableEntries = 1;

		PageTableEntry* innerTablePtr = new PageTableEntry[TABLE_SIZE];

		//Now we tell the directory where its inner table located and set it to valid
		_outerPageTable[directoryNum].set_inner_table_address(innerTablePtr);
		_outerPageTable[directoryNum].set_valid(true);
	}

	//If the entry isn't valid.
	if ((_outerPageTable[directoryNum].get_inner_table_address())[pageNum].is_valid() == false) {
		logPageFault = 1;

		//Now we check to see if we have a free frame to allocate for the new address
		if (_vrtlMem->freeFramesList.empty() == true) {
			logEvicted = swapOutPage();
			logSwap = 1;
		}

		//When we get here we have a frame. we tell the page which one is it and set
		//the page to be valid and not swapped. Then we insert to queue
		_outerPageTable[directoryNum].get_inner_table_address()[pageNum].set_page_address(_vrtlMem->GetFreeFrame());
		_outerPageTable[directoryNum].get_inner_table_address()[pageNum].set_swapped(false);
		_outerPageTable[directoryNum].get_inner_table_address()[pageNum].set_valid(true);
		usedPages.push(adr);

	} else {
		//The directory and the page are both valid.
		// Now we need to check if the page is swapped.

		//Checking if our page is actually in the swap device
		if (_outerPageTable[directoryNum].get_inner_table_address()[pageNum].is_swapped()) {
			//If the page in the swap device, we need to swap it in. This is what we do.
			logEvicted = swapOutPage();
			logSwap = 1;
			logPageFault = 1;

			//Giving our page the free frame we got, getting the address of the frame
			//And inserting the page into the queue. Also telling the page it is not in swap
			_outerPageTable[directoryNum].get_inner_table_address()[pageNum].set_page_address(_vrtlMem->GetFreeFrame());
			_outerPageTable[directoryNum].get_inner_table_address()[pageNum].set_swapped(false);
			int* frameAdr = _outerPageTable[directoryNum].get_inner_table_address()[pageNum].get_page_address();
			usedPages.push(adr); // insert page use in frame

			//Now we actually swap the information using the swap device
			if (_vrtlMem->swapDevice.ReadFrameFromSwapDevice((adr >> 12), frameAdr) == -1){
				cout << "data for page number: "
						<< (adr >> 12) << " does'nt exist"
						<< endl;	//TODO fix
			}
		}
	}

	int* currentPhysAdd = _outerPageTable[directoryNum].get_inner_table_address()[pageNum].get_page_address();
	int* firstPhysAdd = PhysMem::Access().GetFrame(0);
	unsigned int logPhysAdd = ((currentPhysAdd - firstPhysAdd)*INT_SIZE + (offsetNum << 2));

	//Printing to the log before returning
	LOG_PRINT(logFile, logPageNumber, adr, logPhysAdd, logPageFault,logSwap,
			  logEvicted, logAllocatedPageTableEntries);

	return _outerPageTable[directoryNum].get_inner_table_address()[pageNum].get_page_address();
}

