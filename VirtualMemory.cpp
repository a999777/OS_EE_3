#include "VirtualMemory.h"

int* VirtualMemory :: GetFreeFrame() {
	if (freeFramesList.empty()) {
		throw "GetFreeFrame was called but there are no free frames!";
		//Shouldn't get here. For debug.
	}
	int* freeFrame = freeFramesList.front();
	freeFramesList.pop();
    memset(freeFrame, 0, PAGESIZE);
	return freeFrame;
}

void VirtualMemory :: ReleaseFrame (int* framePointer)
{
	memset(framePointer, 0, PAGESIZE);
	freeFramesList.push(framePointer);
}
