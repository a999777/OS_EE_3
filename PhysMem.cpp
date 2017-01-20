/*
 * PhysMem.cpp
 *
 *  Created on: 11 αιπε 2017
 *      Author: ilanmisa
 */

#include "PhysMem.h"

int* PhysMem::physMem;

PhysMem & PhysMem::Access() {
	static PhysMem single;
	if (physMem == NULL) {
		physMem = (int*)malloc(PHYSMEMSZ);
	}
	return single;
}

int* PhysMem::GetFrame(int frameNumber) {
	if (frameNumber < 0 || frameNumber >= 64)
		throw "Invalid Frame Number";
	return &(physMem[1024 * frameNumber]);
}


