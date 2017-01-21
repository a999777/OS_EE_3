#include "VirtualMemory.h"
#include <queue>

//***********************************************************************
// function name: VirtualMemory constructor
// Description: initiate phys mem
// Parameters: N/A
// Returns: VirtualMemory
//***********************************************************************
VirtualMemory::VirtualMemory() {
	int i;
	for (i = 0; i < 64; i++) {
		this->freeFramesList.push(PhysMem::Access().GetFrame(i));
	}
	this->allocated = 0;
}

//***********************************************************************
// function name: GetFreeFrame
// Description: returns free frame if avilable
// Parameters: N/A
// Returns: int*
//***********************************************************************
int* VirtualMemory::GetFreeFrame() {
	if (this->freeFramesList.empty()) {
		return NULL;
	}
	int* framePtr = this->freeFramesList.front(); //fornt is oldest item in the queue, back is the newest
	this->freeFramesList.pop();
	memset(framePtr, 0, PAGESIZE);
	return framePtr;
}

//***********************************************************************
// function name: ReleaseFrame
// Description: relese free frame after page swapped out
// Parameters: frame number
// Returns: N/A
//***********************************************************************
void VirtualMemory::ReleaseFrame(int* framePointer) {
	memset(framePointer, 0, PAGESIZE);
	this->freeFramesList.push(framePointer);
}
