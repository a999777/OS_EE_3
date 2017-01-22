#include <bitset>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include "PageTable.h"
#include "VirtualMemory.h"

using namespace std;
using std::cout;
using std::endl;
using std::ofstream;
using std::string;

//***********************************************************************
// function name: convert_adr_to_directory
// Description: isolated the directory part of an address
// Parameters: adr- virtual address
// Returns: directory number
//***********************************************************************
unsigned int convert_adr_to_directory(unsigned int adr) {
	unsigned int directoryBits;
	GET_MSB_BITS(adr, directoryBits);
	return directoryBits;
	//TODO below is nathans method, above is ours
	/*unsigned int tmp_val = AND_FOR_DIRECTORY_BITS & adr;
	 tmp_val = tmp_val >> SHIFT_FOR_DIRECTORY_BITS;
	 return tmp_val;*/
}
//***********************************************************************
// function name: convert_adr_to_page
// Description: isolated the page part of an address
// Parameters: adr- virtual address
// Returns:page number
//***********************************************************************
unsigned int convert_adr_to_page(unsigned int adr) {
	unsigned int pageBits;
	GET_MIDDLE_BITS(adr, pageBits);
	return pageBits;
	//TODO below is nathans method, above is ours
	/*unsigned int tmp_val = AND_FOR_PAGE_BITS & adr;
	 tmp_val = tmp_val >> SHIFT_FOR_PAGE_BITS;
	 return tmp_val;*/
}

//***********************************************************************
// function name: convert_adr_to_offset
// Description: isolated the offset part of an address
// Parameters: adr- virtual address
// Returns:offset number
//***********************************************************************
unsigned int convert_adr_to_offset(unsigned int adr) {
	unsigned int offset;
	GET_OFFSET_BITS(adr, offset);
	offset = offset >> (INT_BYTE_SIZE / 2);
	return offset;
	//TODO below is nathans method, above is ours
	/*unsigned int tmp_val = AND_FOR_OFFSET_BITS & adr;
	 tmp_val = tmp_val >> (INT_BYTE_SIZE / 2);
	 return tmp_val;*/
}

unsigned int convert_adr_to_not_offset(unsigned int adr) {
	return (adr >> SHIFT_FOR_PAGE_BITS);
}

//***********************************************************************
// function name: swapper
// Description: transfer from memory to swap device
// Parameters: VirtualMemory
// Returns: N/A
//***********************************************************************
int PageTable::swapper(VirtualMemory* mem) {
	unsigned int swap_adr = this->usedPages.front();
	this->usedPages.pop();
	unsigned int directoryBits, pageBits;
	GET_MSB_BITS(swap_adr, directoryBits);//Directory number
	GET_MIDDLE_BITS(swap_adr, pageBits);//Page bits
	int* frameOut = GET_INNER_PAGE_ADDRESS(directoryBits, pageBits);
	SET_SWAPPED_MACRO(directoryBits, pageBits, true);//Set page swapped to true
	WRITE_FRAME_TO_SWAP(swap_adr, frameOut);//Write frame to swap device
	//TODO below is nathans method, above is ours
	/*unsigned int swap_dir = convert_adr_to_directory(swap_adr); //directory number
	unsigned int swap_pg = convert_adr_to_page(swap_adr); //page number
	int* frameOut = this->_outerPageTable[swap_dir].get_table_address()[swap_pg].get_page_address();
	this->_outerPageTable[swap_dir].get_table_address()[swap_pg].set_swapped(
			true);
	mem->swapDevice.WriteFrameToSwapDevice(convert_adr_to_not_offset(swap_adr),
			frameOut);*/
	mem->ReleaseFrame(frameOut);
	return (swap_adr / PAGE_BYTES);
}

//***********************************************************************
// function name: write
// Description: log writing function
// Parameters: printline - a string with the description
// Returns: N/A
//***********************************************************************
//TODO nathans method, no need in ours
/*void PageTable::write(string printline) {
 if (this->pFile != NULL) {
 fputs(printline.c_str(), this->pFile);
 }
 }*/

//***********************************************************************
// function name: PageTable
// Description: constractor
// Parameters: mem reference to virtual memory
// Returns: N/A
//***********************************************************************
PageTable::PageTable() {
	for (int i = 0; i < TABLE_SIZE; i++) {
		this->_outerPageTable[i].set_valid(false);
		this->_outerPageTable[i].set_table_address(NULL);
	}
	this->logFile.open("log.csv");
	//TODO below is nathans method, above is ours
	/*this->pFile = fopen("log.csv", "w");
	 std::stringstream tmp_str;
	 tmp_str
	 << "Page Number,Virtual Address,Physical Address,Page Fault,Swap,Evicted,Allocated Page Table Entries"
	 << endl;
	 write(tmp_str.str());*/
}

//***********************************************************************
// function name: ~PageDirectoryEntry
// Description: destractor - free the pte tables
// Parameters: N/A
// Returns: N/A
//***********************************************************************
PageTable::~PageTable() {
	this->logFile.close();
	//fclose(this->pFile);//TODO nathans method, no need in ours
}

//***********************************************************************
// function name: GetPage 
// Description: returns the correspond frame of an virtual address
// Parameters: adr vitrtual address
// Returns: pointer to the beginung of the frame
//***********************************************************************
int* PageTable::GetPage(unsigned int adr, VirtualMemory* mem) {
	unsigned int dir = convert_adr_to_directory(adr); //directory number
	unsigned int pg = convert_adr_to_page(adr); //page number
	unsigned int ofst = convert_adr_to_offset(adr); //offset
	std::stringstream tmp_str;
	int page_fault;
	int is_swapped = 0;
	int swap_out = -1;
	//Check if the directory and inner page exist, or one of them doesn't:
	if (!(this->_outerPageTable[dir].is_valid())) { //Directory isn't valid
		page_fault = 1;
		PageTableEntry* tmp_entry = new PageTableEntry[TABLE_SIZE];
		this->_outerPageTable[dir].set_table_address(tmp_entry); //directory is activated
		this->_outerPageTable[dir].set_valid(true);
		if (mem->freeFramesList.empty()) { //check if there are available frames
			swap_out = swapper(mem); //no avilable frames - going to swap
			is_swapped = 1;
		}
		this->_outerPageTable[dir].get_table_address()[pg].set_page_address(
				mem->GetFreeFrame()); //set phys adr to page
		this->_outerPageTable[dir].get_table_address()[pg].set_valid(true); //page is activated
		this->_outerPageTable[dir].get_table_address()[pg].set_swapped(false); // page pointed to mem in ram- not in swap device
		this->usedPages.push(adr); // insert page use in frame
		LOG_PRINT(this->logFile, adr / PAGE_BYTES, adr,
				(((&(this->_outerPageTable[dir].get_table_address()[pg].get_page_address()[ofst]) - &PhysMem::Access().GetFrame(0)[0]) + dir * TABLE_SIZE)* INT_BYTE_SIZE),
				page_fault, is_swapped, swap_out, "1");
		//TODO below is nathans method, above is ours
		/*tmp_str << (adr / PAGE_BYTES) << "," << adr << ","
		 << ((&this->_outerPageTable[dir].get_table_address()[pg].get_page_address()[ofst]
		 - &PhysMem::Access().GetFrame(0)[0]) + dir * TABLE_SIZE)
		 * INT_BYTE_SIZE << "," << page_fault << ","
		 << is_swapped << "," << swap_out << "," << "1" << endl;
		 write(tmp_str.str());*/
		return &tmp_entry[pg].get_page_address()[ofst];
	} else if (!((this->_outerPageTable[dir].get_table_address())[pg].is_valid())) { //Page isn't valid
		page_fault = 1;
		if (mem->freeFramesList.empty()) { //check if there are available frames
			swap_out = swapper(mem); //no avilable frames - going to swap
			is_swapped = 1;
		}
		this->_outerPageTable[dir].get_table_address()[pg].set_page_address(
				mem->GetFreeFrame()); //set phys adr to page
		this->_outerPageTable[dir].get_table_address()[pg].set_valid(true); //page is activated
		this->_outerPageTable[dir].get_table_address()[pg].set_swapped(false); // page pointed to mem in ram- not in swap device
		this->usedPages.push(adr); // insert page use in frame
		LOG_PRINT(this->logFile, adr / PAGE_BYTES, adr,
				(((&(this->_outerPageTable[dir].get_table_address()[pg].get_page_address()[ofst]) - &PhysMem::Access().GetFrame(0)[0]) + dir * TABLE_SIZE)* INT_BYTE_SIZE),
				page_fault, is_swapped, swap_out, "0");
		//TODO below is nathans method, above is ours
		/*tmp_str << (adr / PAGE_BYTES) << "," << adr << ","
		 << ((&(this->_outerPageTable[dir].get_table_address()[pg].get_page_address()[ofst])
		 - &PhysMem::Access().GetFrame(0)[0]))
		 * INT_BYTE_SIZE << "," << page_fault << ","
		 << is_swapped << "," << swap_out << "," << "0" << endl;
		 write(tmp_str.str());*/
		return &_outerPageTable[dir].get_table_address()[pg].get_page_address()[ofst];
	} else { //Directory and page are valid
		page_fault = 0;
		//Check if page is pointed to swap device:
		if (this->_outerPageTable[dir].get_table_address()[pg].is_swapped()) {
			swap_out = swapper(mem); // case in swap device - swap out one page
			is_swapped = 1;
			page_fault = 1;
			this->_outerPageTable[dir].get_table_address()[pg].set_page_address(
					mem->GetFreeFrame()); //set phys adr to page
			int* frame_in =
					this->_outerPageTable[dir].get_table_address()[pg].get_page_address();
			this->usedPages.push(adr); // insert page use in frame
			if (mem->swapDevice.ReadFrameFromSwapDevice(
					convert_adr_to_not_offset(adr), frame_in) == -1)
				cout << "data for page number: "
						<< convert_adr_to_not_offset(adr) << " doesnt exist"
						<< endl;
		}
		LOG_PRINT(this->logFile, adr / PAGE_BYTES, adr,
				(((&(this->_outerPageTable[dir].get_table_address()[pg].get_page_address()[ofst]) - &PhysMem::Access().GetFrame(0)[0]) + dir * TABLE_SIZE)* INT_BYTE_SIZE),
				page_fault, is_swapped, swap_out, "0");
		//TODO below is nathans method, above is ours
		/*tmp_str << (adr / PAGE_BYTES) << "," << adr << ","
		 << (((&(this->_outerPageTable[dir].get_table_address()[pg].get_page_address()[ofst])
		 - &PhysMem::Access().GetFrame(0)[0]) + dir * TABLE_SIZE)
		 * INT_BYTE_SIZE) << "," << page_fault << ","
		 << is_swapped << "," << swap_out << "," << "0" << endl;
		 write(tmp_str.str());*/
		this->_outerPageTable[dir].get_table_address()[pg].set_swapped(false); // page pointed to mem in ram- not in swap device
		return &(this->_outerPageTable[dir].get_table_address()[pg].get_page_address()[ofst]);
	}
}
