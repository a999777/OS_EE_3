/*
 * PageTable.cpp
 *
 *  Created on: 13 ����� 2017
 *      Author: Amit
 */

#include "PageTable.h"
#include "VirtualMemory.h"
#include "MacroDefine.h"

//TODO support in log file should be added, as requested in pdf

int testCount = 0;//TODO eitan testing

int* PageTable::GetPage (unsigned int adr) {
	//Separating the virtual address into meaningful numbers.adr represents which number of int is about to be allocated.
	int pageDirectoryEntryNum;
	int pageTableEntryNum;
	int offsetNum;

	//CHANGE_ADR_INT_TO_ADR(adr); TODO not needed in new format
	GET_MSB_BITS(adr, pageDirectoryEntryNum);
	GET_MIDDLE_BITS(adr, pageTableEntryNum);
	GET_OFFSET_BITS(adr, offsetNum);

	unsigned int logPageNumber = adr / 4096;
	unsigned int logVirtualAddress = adr;
	int logPageFault = 0;
	int logSwapDevice = 0;
	int logEvicted = -1;
	int logAllocatedTableEntries = 0;

	//Checking if the inner table entry is valid. If not- allocating it.
	if(!_outerPageTable[pageDirectoryEntryNum].is_valid()) {
		_outerPageTable[pageDirectoryEntryNum].create_inner_table();
		logAllocatedTableEntries = 1;
		_outerPageTable[pageDirectoryEntryNum].set_valid(true);
	}

	//Checking if the inner table entry is valid. If not- linking it to a free address.
	if(!_outerPageTable[pageDirectoryEntryNum].is_inner_entry_valid(pageTableEntryNum)) {

		logPageFault = 1;

		if(_outerPageTable[pageDirectoryEntryNum].was_inner_entry_valid(pageTableEntryNum)) {
			/*If the inner entry is not valid and it was linked then we have to page it in.
			 Since we only swap out when we have no room left, and we never "delete" frames,
			 I think we can assume that we have to swap out a frame in order to make room for the new one */

			logSwapDevice = 1;
			//TODO logEvicted should be handled here
			int* freeAdr = _virtMem->GetFreeFrame();
			int frameToPullFromSwap = (GetPage(adr) - PhysMem::Access().GetFrame(0));
			frameToPullFromSwap /= 1024; //TODO make sure
			_virtMem->swap.ReadFrameFromSwapDevice(frameToPullFromSwap, freeAdr);
			_outerPageTable[pageDirectoryEntryNum].set_page_address(pageTableEntryNum, freeAdr);
			_virtMem->allocationOrder.push(adr);

		} else {
			//If the inner entry is not valid and the page was never linked
			int* freeAdr = _virtMem->GetFreeFrame();
			_outerPageTable[pageDirectoryEntryNum].set_page_address(pageTableEntryNum, freeAdr);
			_virtMem->allocationOrder.push(adr);
		}
	}

	int* physicalFrameAddress = _outerPageTable[pageDirectoryEntryNum].get_page_address(pageTableEntryNum);
	unsigned int logPhysicalAddress = (physicalFrameAddress - PhysMem::Access().GetFrame(0))*4 + offsetNum;

	LOG_PRINT(logFile,logPageNumber,logVirtualAddress,logPhysicalAddress,logPageFault,logSwapDevice,logEvicted,logAllocatedTableEntries);

	//Returning the physical address of the page
	return physicalFrameAddress;
}

void PageTable::setTableEntryInvalid(int PageDirectoryEntry, int PageTableEntry) {
	_outerPageTable[PageDirectoryEntry].set_inner_entry_invalid(PageTableEntry);
}
