/*
 * unitTests.cpp
 *
 *  Created on: 13 ����� 2017
 *      Author: Amit
 */

#include "unitTests.h"
#include "PhysMem.h"
#include "PageTableEntry.h"
#include "PageDirectoryEntry.h"
#include "PageTable.h"
#include "VirtualMemory.h"


/**
 * Very basic tests, just to make sure everything is okay.
 */
bool pageTableEntryTest() {
	PageTableEntry ent1, ent2, ent3;

	if(ent1.is_valid() || ent2.is_valid() || ent3.is_valid()) {
		ERROR_AND_PRINT("valid status at creation is bad");
	}
	if(ent1.get_page_address() || ent2.get_page_address() || ent3.get_page_address()) {
		ERROR_AND_PRINT("frame pointed status at creation is bad");
	}

	ent1.set_valid(true);
	ent2.set_valid(true);
	ASSERT_TRUE(ent1.is_valid());
	ASSERT_TRUE(ent2.is_valid());
	ASSERT_FALSE(ent3.is_valid());

	int ptrA = 1, ptrB = 2, ptrC = 3;
	ent1.set_page_address(&ptrA);
	ent2.set_page_address(&ptrB);
	ent3.set_page_address(&ptrC);
	if( *(ent1.get_page_address()) != 1 || *(ent2.get_page_address()) != 2 || *(ent3.get_page_address()) != 3 ) {
		ERROR_AND_PRINT("set_page_address in bad");
	}
	ent1.set_page_address(&ptrB);
	if( *(ent1.get_page_address()) != 2) {
		ERROR_AND_PRINT("set_page_address in bad");
	}
	return true;
}

/**
 * Test meant to check the outter table entries.
 */
bool pageDirectoryEntryTest() {
	PageDirectoryEntry ent1, ent2;

	if(ent1.is_valid() || ent2.is_valid()) {
			ERROR_AND_PRINT("valid status at creation is bad");
	}

	ent1.create_inner_table();
	ent1.set_valid(true);
	for(int i = 0; i < NUM_OF_ENTRIES ; i++) {
		if(ent1.is_inner_entry_valid(i)) {
			ERROR_AND_PRINT("inner entries are created and they are not supposed to.");
		}
	}

	int phys1 = 1, phys2 = 2, phys3 = 3;
	ent1.set_page_address(100, &phys1);
	ent1.set_page_address(200, &phys2);
	ent1.set_page_address(300, &phys3);
	ASSERT_FALSE(ent1.is_inner_entry_valid(99));
	ASSERT_TRUE(ent1.is_inner_entry_valid(100));
	ASSERT_TRUE(ent1.get_page_address(100) == &phys1);
	ASSERT_TRUE(ent1.is_inner_entry_valid(200));
	ASSERT_TRUE(ent1.get_page_address(200) == &phys2);
	ASSERT_TRUE(ent1.is_inner_entry_valid(300));
	ASSERT_TRUE(ent1.get_page_address(300) == &phys3);
	ASSERT_FALSE(ent2.is_inner_entry_valid(0));
	ASSERT_FALSE(ent2.is_inner_entry_valid(1023));
	ASSERT_FALSE(ent2.is_inner_entry_valid(100));

	return true;
}

bool pageTableTest() {
	//What we are doing here is not recommended. We'll create the virtual memory,
	//then create a page table and link it to the VM we created. It shouldn't be
	//done in program and it is done here only so we can test pageTable.
	VirtualMemory mem;
	PageTable PT(&mem);

	ASSERT_TRUE(PT.createMask(0,11) == 4095);
	ASSERT_TRUE(PT.createMask(12,21) == 4190208);
	ASSERT_TRUE(PT.createMask(22,31) == 4290772992);

	//Checking GetPage which is the major function. Because we can't use ourmalloc
	//here the only test possible is assigning random virtual addresses to physical addresses
	int* ptrStart = PT.GetPage(0);
	ASSERT_TRUE(ptrStart != NULL);
	int* ptr1 = PT.GetPage(1);
	ASSERT_TRUE(ptr1 != NULL);
	int* ptr1001 = PT.GetPage(1001);
	ASSERT_TRUE(ptr1001 != NULL);
	int* ptr10002 = PT.GetPage(10002);
	ASSERT_TRUE(ptr10002 != NULL);
	//Reaching the final virtual address - 2^20-1
	int* ptrEnd = PT.GetPage(1048576);
	ASSERT_TRUE(ptrEnd != NULL);

	return true;
}


int main() {
	RUN_TEST("pageTableEntryTest",pageTableEntryTest());
	RUN_TEST("pageDirectoryEntryTest",pageDirectoryEntryTest());
	RUN_TEST("pageTableTest",pageTableTest());
	return 0;
}


