/*
 * PhysMem.h
 *
 *  Created on: 10 αιπε 2017
 *      Author: Eitan Levin
 */

#ifndef PHYSMEM_H_
#define PHYSMEM_H_

#include <stdlib.h>
#include <iostream>

using namespace std;

#define PHYSMEMSZ 262144

class PhysMem {
friend class VirtualMemory;
public:
	static PhysMem& Access();
private:
	PhysMem() {}
	static int* physMem;
public:
	PhysMem(PhysMem const&) = delete;
	void operator=(PhysMem const&) = delete;
	int* GetFrame(int frameNumber);
};

#endif /* PHYSMEM_H_ */
