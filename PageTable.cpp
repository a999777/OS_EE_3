#include "PageTable.h"
#include "VirtualMemory.h"
#include <bitset>
#include <fstream>
#include <iostream>
#include <stdio.h>
using namespace std;
using std::cout;
using std::endl;
using std::ofstream;
using std::string;


//***********************************************************************
// function name: convert_adr_to_directory
// Description: isolated the directory part of an address
// Parameters: adr vitrtual address
// Returns: directory number
//***********************************************************************
unsigned int convert_adr_to_directory(unsigned int adr)
{
	unsigned int tmp_val = BIT_WISE_AND_FOR_DIRECTORY & adr;
	tmp_val = tmp_val >> BIT_WISE_SHIFT_FOR_DIRECTORY;
	return tmp_val;
}
//***********************************************************************
// function name: convert_adr_to_page
// Description: isolated the page part of an address
// Parameters: adr vitrtual address
// Returns:page number
//***********************************************************************
unsigned int convert_adr_to_page(unsigned int adr)
{
	unsigned int tmp_val = BIT_WISE_AND_FOR_PAGE & adr;
	tmp_val = tmp_val >> BIT_WISE_SHIFT_FOR_PAGE;
	return tmp_val;
}

//***********************************************************************
// function name: convert_adr_to_offset
// Description: isolated the offset part of an address
// Parameters: adr vitrtual address
// Returns:offset number
//***********************************************************************
unsigned int convert_adr_to_offset(unsigned int adr)
{
	unsigned int tmp_val = BIT_WISE_AND_FOR_OFFSET & adr;
	tmp_val = tmp_val >> (INT_BYTE_SIZE/2);
 	return tmp_val;
}

unsigned int convert_adr_to_not_offset(unsigned int adr)
{
	return (adr>>BIT_WISE_SHIFT_FOR_PAGE);
}

//***********************************************************************
// function name: swapper
// Description: transfer from mem to swap device
// Parameters: VirtualMemory
// Returns: N/A
//***********************************************************************
int PageTable::swapper(VirtualMemory* mem)
{
	unsigned int swap_adr = usedPages.front();
	usedPages.pop();
	unsigned int swap_dir = convert_adr_to_directory(swap_adr); //directory number
	unsigned int swap_pg = convert_adr_to_page(swap_adr); //page number
	int* frame_out = _outerPageTable[swap_dir].get_table_address()[swap_pg].get_page_address();
	_outerPageTable[swap_dir].get_table_address()[swap_pg].set_swapped(true);
	mem->swapDevice.WriteFrameToSwapDevice(convert_adr_to_not_offset(swap_adr), frame_out);
	mem->ReleaseFrame(frame_out);
	return (swap_adr/PAGE_BYTES);
}


//***********************************************************************
// function name: write
// Description: log writing function
// Parameters: printline - a string with the description
// Returns: N/A
//***********************************************************************
void PageTable::write(string printline)
{
  if (pFile!=NULL)
    fputs (printline.c_str(),pFile);
}


//***********************************************************************
// function name: PageTable
// Description: constractor
// Parameters: mem reference to virtual memory
// Returns: N/A
//***********************************************************************
PageTable::PageTable()
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		_outerPageTable[i].set_valid(false);
		_outerPageTable[i].set_table_address(NULL);
	}
	pFile = fopen ("log.csv","w");
	std::stringstream tmp_str;
	tmp_str<<"Page Number,Virtual Address,Physical Address,Page Fault,Swap,Evicted,Allocated Page Table Entries"<<endl;
	write(tmp_str.str());
}


//***********************************************************************
// function name: ~PageDirectoryEntry
// Description: destractor - free the pte tables
// Parameters: N/A
// Returns: N/A
//***********************************************************************
PageTable::~PageTable()
{
    fclose (pFile);
}

//***********************************************************************
// function name: GetPage 
// Description: returns the correspond frame of an virtual address
// Parameters: adr vitrtual address
// Returns: pointer to the beginung of the frame
//***********************************************************************
int* PageTable::GetPage(unsigned int adr, VirtualMemory* mem)
{
	unsigned int dir = convert_adr_to_directory(adr); //directory number
	unsigned int pg = convert_adr_to_page(adr); //page number
	unsigned int ofst = convert_adr_to_offset(adr);//offset
	std::stringstream tmp_str;
	int page_fault;
	int is_swapped=0;
	int swap_out = -1;
	//checking if the directory exist

	if (!_outerPageTable[dir].is_valid()) //directory valid is 0
	{
		page_fault = 1;
		PageTableEntry* tmp_entry = new PageTableEntry[TABLE_SIZE];
		_outerPageTable[dir].set_table_address(tmp_entry); //directory is activated
		_outerPageTable[dir].set_valid(true);
		if(mem->freeFramesList.empty()) //check if there are avilable frame
		{
			swap_out = swapper(mem); //no avilable frames - going to swap
			is_swapped = 1;
		}
		_outerPageTable[dir].get_table_address()[pg].set_page_address(mem->GetFreeFrame());  //set phys adr to page
		_outerPageTable[dir].get_table_address()[pg].set_valid(true); //page is activated
		_outerPageTable[dir].get_table_address()[pg].set_swapped(false); // page pointed to mem in ram- not in swap device
		usedPages.push(adr);  // insert page use in frame
		tmp_str <<(adr/PAGE_BYTES) <<","<< adr <<","<< ((&_outerPageTable[dir].get_table_address()[pg].get_page_address()[ofst] - &PhysMem::Access().GetFrame(0)[0])+dir*TABLE_SIZE)*INT_BYTE_SIZE <<","<<page_fault<<","<<is_swapped<<","<<swap_out<<","<<"1"<<endl;
		write(tmp_str.str());
		return &tmp_entry[pg].get_page_address()[ofst];
	}
	//checking if the page exist
	else if (!((_outerPageTable[dir].get_table_address())[pg].is_valid())) //page valid is 0
	{
		page_fault = 1;
		if(mem->freeFramesList.empty())  //check if there are avilable frame
		{
			swap_out = swapper(mem);  //no avilable frames - going to swap
			is_swapped = 1;
		}
		_outerPageTable[dir].get_table_address()[pg].set_page_address(mem->GetFreeFrame());  //set phys adr to page
		_outerPageTable[dir].get_table_address()[pg].set_valid(true); //page is activated
		_outerPageTable[dir].get_table_address()[pg].set_swapped(false); // page pointed to mem in ram- not in swap device
		usedPages.push(adr);  // insert page use in frame
		tmp_str << (adr/PAGE_BYTES) <<","<< adr <<","<< ((&_outerPageTable[dir].get_table_address()[pg].get_page_address()[ofst] - &PhysMem::Access().GetFrame(0)[0])/*+dir*TABLE_SIZE*/)*INT_BYTE_SIZE<<","<<page_fault<<","<<is_swapped<<","<<swap_out<<","<<"0"<<endl;
		write(tmp_str.str());
		return &_outerPageTable[dir].get_table_address()[pg].get_page_address()[ofst];
	}
	else //directory and page exist
	{
		page_fault = 0;
		if(_outerPageTable[dir].get_table_address()[pg].is_swapped())  // check if page is pointed to swap device
		{
			swap_out = swapper(mem);  // case in swap device - swap out one page
			is_swapped = 1;
			page_fault =1;
			_outerPageTable[dir].get_table_address()[pg].set_page_address(mem->GetFreeFrame());  //set phys adr to page
			int* frame_in = _outerPageTable[dir].get_table_address()[pg].get_page_address();
			usedPages.push(adr); // insert page use in frame
			if(mem->swapDevice.ReadFrameFromSwapDevice(convert_adr_to_not_offset(adr),frame_in) == -1)
				cout<<"data for page number: " << convert_adr_to_not_offset(adr)<<" doesnt exist"<<endl;
		}
		tmp_str << (adr/PAGE_BYTES) <<","<< adr <<","<< ((&_outerPageTable[dir].get_table_address()[pg].get_page_address()[ofst] - &PhysMem::Access().GetFrame(0)[0])+dir*TABLE_SIZE)*INT_BYTE_SIZE<<","<<page_fault<<","<<is_swapped<<","<<swap_out<<","<<"0"<<endl;
		write(tmp_str.str());
		_outerPageTable[dir].get_table_address()[pg].set_swapped(false);  // page pointed to mem in ram- not in swap device
		return &_outerPageTable[dir].get_table_address()[pg].get_page_address()[ofst];
	}
}
