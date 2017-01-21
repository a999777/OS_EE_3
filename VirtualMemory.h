/*
 * VirtualMemory.h
 *
 *  Created on: 10 ���� 2017
 *      Author: Eitan Levin
 */

#ifndef OS_HM3_VIRTUALMEMORY_H_
#define OS_HM3_VIRTUALMEMORY_H_

#include <queue>
#include <unordered_set>
#include <cstring>

#include "OurPointer.h"
#include "PhysMem.h"
#include "PageTable.h"
#include "SwapDevice.h"
#include "MacroDefine.h"
#include <map>//TODO eitan

#define PAGESIZE 4096
#define VIRTMEMSIZE 4294967296

using namespace std;

class VirtualMemory {
	friend class PageTable;
private:
	/*
	 * allocated:
	 * The number of ints already allocated, ((allocated * 4) = (number of bytes already allocated)),
	 * this can also be used as the next address to be allocated.
	 */

public:
	size_t allocated; //TODO move all this stuff to private
		queue<int*> freeFramesList;
		PageTable pageTable;
		SwapDevice swap;
		queue<unsigned int> allocationOrder;

		//int* physmemAdds[NUMOFFRAMES]; //TODO debug
		int** physmemAdds;//TODO eitan
		//map<int, int*> freeFramesMap;//TODO eitan
	/*
	 * VirtualMemory: Initialize freeFramesList to contain all 64 frame	pointers as given by PhysMem Class,
	 * initialize the PageTable, give the pageTable a pointer to this object so it can
	 * utilize GetFreeFrame and	ReleaseFrame
	 */
	VirtualMemory(): allocated(0), freeFramesList(), pageTable(this), swap(SwapDevice()), \
			allocationOrder(){
		physmemAdds = new int*[NUMOFFRAMES];//TODO eitan
		//map<int, int*>::value_type pair();
		for(int i = 0; i < NUMOFFRAMES ; i++) {
			freeFramesList.push(PhysMem::Access().GetFrame(i));	//Now our list will contain pointers to all frames
			physmemAdds[i] = PhysMem::Access().GetFrame(i); //TODO debug only
			//map<int, int*>::value_type mapPair(i, PhysMem::Access().GetFrame(i));
			//freeFramesMap.insert(mapPair);
		}
	}
	/*VirtualMemory(const VirtualMemory& obj) {
		this->allocated = obj.allocated;
		free
		physmemAdds = new int*[NUMOFFRAMES];//TODO eitan
		for(int i = 0; i < NUMOFFRAMES ; i++) {
			freeFramesList.push(PhysMem::Access().GetFrame(i));	//Now our list will contain pointers to all frames
			physmemAdds[i] = PhysMem::Access().GetFrame(i); //TODO debug only
		}
	}*/

	~VirtualMemory() {
		allocated = 0;
		while(!(freeFramesList.empty())) {
			freeFramesList.pop();
		}
		while(!(freeFramesMap.empty())) {
			freeFramesMap.clear();
		}
		//TODO might leak because we didn't free it?
	}

	/*
	 * GetFreeFrame:
	 * Remove one item from the freeFrameList and return it � suggestion,
	 * use memset(framePtr, 0, PAGESIZE) before return, might help debugging!
	 */
	int* GetFreeFrame();

	/*
	 * ReleaseFrame:
	 * Releases the frame pointed by the framePointer, make sure you only
	 * use this function with a pointer to the beginning of the Frame!
	 * it should be the same pointer as held in the PTE.
	 */
	void ReleaseFrame(int* framePointer);

	/*
	 * OurPointer:
	 * Allocates a pointer, we added the code for your convenience.
	 */
	OurPointer OurMalloc(size_t size) {
		if (allocated + size >= (VIRTMEMSIZE >> 2)) {
			throw "We are limited to 4294967296 bytes with our 32 bit address size";
		}
		OurPointer ptr(allocated, this);
		//allocated += size;
		allocated += (size*4);//TODO why not this?
		return ptr;
	}

	int* GetPage(unsigned int adr) {
		return pageTable.GetPage(adr);
	}

};

#endif /* OS_HM3_VIRTUALMEMORY_H_ */
