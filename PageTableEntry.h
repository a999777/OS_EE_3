/*
 * PageTableEntry.h
 *
 *  Created on: 11 áéðå× 2017
 *      Author: Amit
 */

#ifndef PAGETABLEENTRY_H_
#define PAGETABLEENTRY_H_

#include <cstdlib>
#include <iostream> //TODO remove, debug


/*
 * This file will represent each entry in the inner page table. That means that
 * each PageTableEntry has a pointer to a specific frame representing where the
 * page is kept- either in memory or in swap area
 */

class PageTableEntry {
public:
	PageTableEntry() : _valid(false),_framePointedBegining(NULL), _linked(false) {}
		//When invoking this constructor that means we are creating an entry
		//inside the inner page table

	~PageTableEntry() = default;

	int* get_page_address() {
		//Pointer to beginning of frame  
		return _framePointedBegining;
	}

	void set_page_address(int* adr) {
		//Set the pointer to a frame
		std::cout << "set page address: " << adr << std::endl;//TODO eitan test
		_framePointedBegining = adr;
	}

	bool is_valid() {
		//Returns whether the entry is valid
		return _valid;
	}

	void set_valid(bool valid) {
		//Allows to set whether the entry is valid
		_valid = valid;
	}

	bool was_linked() {
		//Returns whether the entry was linked sometime to a frame
		return _linked;
	}

	void set_linked(bool linked) {
		//Allows to set whether the entry is linked to a frame
		_linked = linked;
	}

private:
	bool _valid;
	int* _framePointedBegining;
	bool _linked;
};








#endif /* PAGETABLEENTRY_H_ */
