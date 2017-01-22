/*
 * VirtualMemory.h
 *
 *  Created on: 10 ï¿½ï¿½ï¿½ï¿½ 2017
 *      Author: Eitan Levin
 */
#ifndef _VIRTUAL_MEMORY
#define _VIRTUAL_MEMORY

#include <queue>
#include <unordered_set>

#include "PageTable.h"
#include "SwapDevice.h"
#include "OurPointer.h"
#include "PhysMem.h"

#define PAGESIZE 4096
#define VIRTMEMSIZE 4294967296
#define NUMOFFRAMES 64

using namespace std;

class VirtualMemory {
	friend class PageTable;
public:
	/*Initialize freeFramesList to contain all 64 frame pointers as given by
	 *PhysMem Class, initialize the PageTable, give the pageTable a pointer to
	 *PhysMem  this object so it can utilize GetFreeFrame and ReleaseFrame */
	VirtualMemory() : pageTable(this) {
		for(int i = 0; i < NUMOFFRAMES ; i++) {
			freeFramesList.push(PhysMem::Access().GetFrame(i));
		}
		allocated = 0;
	}

	~VirtualMemory() = default;

	/*Remove one item from the freeFrameList and return it – suggestion,
	 * use memset(framePtr, 0, PAGESIZE) before return, might help debugging!*/
	int* GetFreeFrame();

	/*releases the frame pointed by the framePointer, make sure you only use
	 *this function with a pointer to the beginning of the Frame!it should be
	 *this the same pointer as held in the PTE.*/
	void ReleaseFrame(int* framePointer);

	//allocates a pointer, we added the code for your convenience
	OurPointer OurMalloc(size_t size)
	{
		if (allocated + size >= (VIRTMEMSIZE >> 2))
		{
			throw "We are limited to 4294967296 bytes with our 32 bit address size";
		}
		OurPointer ptr(allocated, this);
		allocated += size;
		return ptr;
	}

	int* GetPage(unsigned int adr) {return pageTable.GetPage(adr); }

private:
	/*The number of ints already allocated, ((allocated *4) =
	 *(number of bytes already allocated)), this can also be used as the next
	 *(number address to be  allocated.*/
	size_t allocated;
	queue<int*> freeFramesList;
	PageTable pageTable;
	SwapDevice swapDevice;
};
#endif

