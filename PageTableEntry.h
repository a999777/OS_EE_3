/*
 * PageTableEntry.h
 *
 *  Created on: 11 בינו׳ 2017
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

	int* get_page_address();

	void set_page_address(int* adr);

	bool is_valid();

	void set_valid(bool valid);

	bool was_linked();

	void set_linked(bool linked);

private:
	bool _valid;
	int* _framePointedBegining;
	bool _linked;
};


#endif /* PAGETABLEENTRY_H_ */
