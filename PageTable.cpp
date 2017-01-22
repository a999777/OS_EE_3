#include <iostream>
#include <stdio.h>
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

	//TODO below is nathans method, above is ours
	/*unsigned int swap_directoryNum = convert_adr_to_directoryNumectory(oldestAdr); //directoryNumectory number
	unsigned int swap_pageNum = convert_adr_to_page(oldestAdr); //page number
	int* swappedFrame = this->_outerPageTable[swap_directoryNum].get_inner_table_address()[swap_pageNum].get_page_address();
	this->_outerPageTable[swap_directoryNum].get_inner_table_address()[swap_pageNum].set_swapped(
			true);
	mem->swapDevice.WriteFrameToSwapDevice(convert_adr_to_not_offset(oldestAdr),
			swappedFrame);*/

	_vrtlMem->ReleaseFrame(swappedFrame);
	return (oldestAdr / PAGE_SIZE);
}

int* PageTable::GetPage(unsigned int adr) {

	/*unsigned int directoryNum = convert_adr_to_directory(adr); //directoryNumectory number
	unsigned int pageNum = convert_adr_to_page(adr); //page number
	unsigned int offsetNum = convert_adr_to_offset(adr); //offset*/

	unsigned int directoryNum, pageNum, offsetNum;
	GET_MSB_BITS(adr, directoryNum);
	GET_MIDDLE_BITS(adr, pageNum);
	GET_OFFSET_BITS(adr, offsetNum);

	int logPageFault;
	int logSwap = 0;
	int logEvicted = -1;

	if (!(_outerPageTable[directoryNum].is_valid())) {
		//That means the directory doesn't exist
		logPageFault = 1;

		PageTableEntry* innerTablePtr = new PageTableEntry[TABLE_SIZE];

		//Now we tell the directory where its inner table located and set it to valid
		_outerPageTable[directoryNum].set_inner_table_address(innerTablePtr);
		_outerPageTable[directoryNum].set_valid(true);

		//Now we check to see if we have a free frame to allocate for the new address
		if (_vrtlMem->freeFramesList.empty()) {
			logEvicted = swapOutPage();
			logSwap = 1;
		}

		//When we get here we have a frame. we tell the page which one is it and set
		//the page to be valid and not swapped. Then we insert to queue
		_outerPageTable[directoryNum].get_inner_table_address()[pageNum].set_page_address(_vrtlMem->GetFreeFrame());
		_outerPageTable[directoryNum].get_inner_table_address()[pageNum].set_valid(true);
		_outerPageTable[directoryNum].get_inner_table_address()[pageNum].set_swapped(false);
		usedPages.push(adr);

		//Printing the log before returning.
		LOG_PRINT(logFile, adr / PAGE_SIZE, adr,
				(((&(this->_outerPageTable[directoryNum].get_inner_table_address()[pageNum].get_page_address()[offsetNum]) - &PhysMem::Access().GetFrame(0)[0]) + directoryNum * TABLE_SIZE)* INT_SIZE),
				logPageFault, logSwap, logEvicted, "1"); //TODO Amit: I don't like it. Change it

		//TODO below is nathans method, above is ours
		/*tmp_str << (adr / PAGE_SIZE) << "," << adr << ","
		 << ((&this->_outerPageTable[directoryNum].get_inner_table_address()[pageNum].get_page_address()[offsetNum]
		 - &PhysMem::Access().GetFrame(0)[0]) + directoryNum * TABLE_SIZE)
		 * INT_SIZE << "," << logPageFault << ","
		 << logSwap << "," << logEvicted << "," << "1" << endl;
		 write(tmp_str.str());*/
		return &innerTablePtr[pageNum].get_page_address()[offsetNum];

	} else if (!((_outerPageTable[directoryNum].get_inner_table_address())[pageNum].is_valid())) {
		//If we get here that means that the page is not valid.
		logPageFault = 1;

		//Now we check to see if we have a free frame to allocate for the new address
		if (_vrtlMem->freeFramesList.empty()) {
			logEvicted = swapOutPage();
			logSwap = 1;
		}

		//When we get here we have a frame. we tell the page which one is it and set
		//the page to be valid and not swapped. Then we insert to queue
		_outerPageTable[directoryNum].get_inner_table_address()[pageNum].set_page_address(_vrtlMem->GetFreeFrame());
		_outerPageTable[directoryNum].get_inner_table_address()[pageNum].set_valid(true);
		_outerPageTable[directoryNum].get_inner_table_address()[pageNum].set_swapped(false);
		usedPages.push(adr);

		//Printing the log before returning.
		LOG_PRINT(this->logFile, adr / PAGE_SIZE, adr,
				(((&(this->_outerPageTable[directoryNum].get_inner_table_address()[pageNum].get_page_address()[offsetNum]) - &PhysMem::Access().GetFrame(0)[0]) + directoryNum * TABLE_SIZE)* INT_SIZE),
				logPageFault, logSwap, logEvicted, "0");
		//TODO below is nathans method, above is ours
		/*tmp_str << (adr / PAGE_SIZE) << "," << adr << ","
		 << ((&(this->_outerPageTable[directoryNum].get_inner_table_address()[pageNum].get_page_address()[offsetNum])
		 - &PhysMem::Access().GetFrame(0)[0]))
		 * INT_SIZE << "," << logPageFault << ","
		 << logSwap << "," << logEvicted << "," << "0" << endl;
		 write(tmp_str.str());*/
		return &_outerPageTable[directoryNum].get_inner_table_address()[pageNum].get_page_address()[offsetNum];
	} else {
		//The directory and the page are valid. We need to check if the page is swapped.
		logPageFault = 0;

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
						<< (adr >> 12) << " doesnt exist"
						<< endl;	//TODO fix
			}
		}

		//Printing the log before returning
		LOG_PRINT(this->logFile, adr / PAGE_SIZE, adr,
				(((&(this->_outerPageTable[directoryNum].get_inner_table_address()[pageNum].get_page_address()[offsetNum]) - &PhysMem::Access().GetFrame(0)[0]) + directoryNum * TABLE_SIZE)* INT_SIZE),
				logPageFault, logSwap, logEvicted, "0");

		//TODO below is nathans method, above is ours
		/*tmp_str << (adr / PAGE_SIZE) << "," << adr << ","
		 << (((&(this->_outerPageTable[directoryNum].get_inner_table_address()[pageNum].get_page_address()[offsetNum])
		 - &PhysMem::Access().GetFrame(0)[0]) + directoryNum * TABLE_SIZE)
		 * INT_SIZE) << "," << logPageFault << ","
		 << logSwap << "," << logEvicted << "," << "0" << endl;
		 write(tmp_str.str());*/

		return &(this->_outerPageTable[directoryNum].get_inner_table_address()[pageNum].get_page_address()[offsetNum]);
	}
}
