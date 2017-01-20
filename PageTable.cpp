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

	CHANGE_ADR_INT_TO_ADR(adr);
	GET_MSB_BITS(adr, pageDirectoryEntryNum);
	GET_MIDDLE_BITS(adr, pageTableEntryNum);

	//Checking if the inner table is valid. If not- allocating it.
	if(!_outerPageTable[pageDirectoryEntryNum].is_valid()) {
		_outerPageTable[pageDirectoryEntryNum].create_inner_table();
		_outerPageTable[pageDirectoryEntryNum].set_valid(true);
	}

	//Checking if the inner table entry is valid. If not- linking it to a free address.
	if(!_outerPageTable[pageDirectoryEntryNum].is_inner_entry_valid(pageTableEntryNum)) {

		if(_outerPageTable[pageDirectoryEntryNum].was_inner_entry_valid(pageTableEntryNum)) {
			/*If the inner entry is not valid and it was linked then we have to page it in.
			 Since we only swap out when we have no room left, and we never "delete" frames,
			 I think we can assume that we have to swap out a frame in order to make room for the new one */
			cout << "try try try try try try try" << endl;//TODO eitan test
			int* freeAdr = _virtMem->GetFreeFrame();
			int frameToPullFromSwap = (GetPage(adr) - PhysMem::Access().GetFrame(0));
			frameToPullFromSwap /= 1024; //TODO make sure
			_virtMem->swap.ReadFrameFromSwapDevice(frameToPullFromSwap, freeAdr);
			_outerPageTable[pageDirectoryEntryNum].set_page_address(pageTableEntryNum, freeAdr);
			_virtMem->allocationOrder.push(adr);

		} else {
			//If the inner entry is not valid and the page was never linked
			//cout << "testCount = " << testCount++ << endl;//TODO eitan test
			int* freeAdr = _virtMem->GetFreeFrame();
			_outerPageTable[pageDirectoryEntryNum].set_page_address(pageTableEntryNum, freeAdr);
			_virtMem->allocationOrder.push(adr);
		}
	}


/*	if(pageTableEntryNum == 61)  { //FIXME debug
		int off ;
		GET_OFFSET_BITS(adr,off);
		off /= 4; //Now we have it in ints again
		if(off > 800)
		cout << "@@@@@ About to return from frame number 61. Int_Address number is " << off;
		cout << " and address of frame: " << hex << _outerPageTable[pageDirectoryEntryNum].get_page_address(pageTableEntryNum) << endl;
	}*/

	//FIXME debug
/*	if(pageTableEntryNum == 61) {
		int off ;
		GET_OFFSET_BITS(adr,off);
		if(off == 0) {
			cout << "when creating the entry number 61, sending byte
		}
	}*/

	//Returning the physical address
	return _outerPageTable[pageDirectoryEntryNum].get_page_address(pageTableEntryNum);
}

void PageTable::setTableEntryInvalid(int PageDirectoryEntry, int PageTableEntry) {
	_outerPageTable[PageDirectoryEntry].set_inner_entry_invalid(PageTableEntry);
}
