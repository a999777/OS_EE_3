/*
 * VirtualMemory.cpp
 *
 *  Created on: 13 ����� 2017
 *      Author: Amit
 */

#include "VirtualMemory.h"

/*
 * GetFreeFrame:
 * Remove one item from the freeFrameList and return it � suggestion,
 * use memset(framePtr, 0, PAGESIZE) before return, might help debugging!
 */

int countFreeFrames = 0;//TODO testing
int* VirtualMemory::GetFreeFrame() {
//	cout << "GetFreeFrame was asked for a frame. The list still has " << freeFramesList.size() << endl; //FIXME debug only
	cout << "countFreeFrames: " << countFreeFrames++ << endl;//TODO eitan testing
	cout << "free frames queue size before pop: " << freeFramesList.size() << endl;//TODO eitan testing
	if(freeFramesList.empty() == true) {
		cout << "freeFramesList.empty() == true" << endl;//TODO eitan testing
		exit(3);//TODO eitan testing
		unsigned int oldestPage = allocationOrder.front();
		int* oldestFrame = pageTable.GetPage(oldestPage);

		int directoryEntryNum;
		int tableEntryNum;
		GET_MSB_BITS(oldestPage, directoryEntryNum);
		GET_MIDDLE_BITS(oldestPage, tableEntryNum);

		ReleaseFrame(oldestFrame);
		pageTable.setTableEntryInvalid(directoryEntryNum, tableEntryNum);
		allocationOrder.pop();
	}

	//Now we are sure we still have free frames in memory
	int* freeFramePtr = freeFramesList.front();
	cout << "A.freeFramePtr: " << freeFramePtr << endl;//TODO eitan
	freeFramesList.pop();
	cout << "B.freeFramePtr: " << freeFramePtr << endl;//TODO eitan
	//void* memsetRes = memset(freeFramePtr, 0 ,PAGESIZE);//TODO eitan testing
	//cout << (int*)memsetRes << endl;//TODO eitan testing
	memset((void*)freeFramePtr, 0 ,PAGESIZE); //Now the entire page would be 0s
	return freeFramePtr;
}

/*
 * ReleaseFrame:
 * Releases the frame pointed by the framePointer, make sure you only
 * use this function with a pointer to the beginning of the Frame!
 * it should be the same pointer as held in the PTE.
 */

void VirtualMemory::ReleaseFrame(int* framePointer) {
	cout << "ReleaseFrame" << endl;//TODO eitan testing
	exit(4);//TODO eitan testing
	//TODO this function should be used when we want to swap out. we can use it
	//to utilize some of the work done in GetFreeFrame.
	int frameNumber = framePointer - PhysMem::Access().GetFrame(0);
	//TODO should we alter the result we get?? here we did it with frame size
	frameNumber /= 1024;
	swap.WriteFrameToSwapDevice(frameNumber, framePointer);
	freeFramesList.push(framePointer);
}


