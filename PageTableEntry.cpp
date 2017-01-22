#include "PageTableEntry.h"

bool PageTableEntry::is_valid() {
	return _valid;
}

void PageTableEntry::set_valid(bool valid) {
	_valid = valid;
}

int* PageTableEntry::get_page_address() {
	return _physFrameAddress;
}

void PageTableEntry::set_page_address(int* adr) {
	_physFrameAddress = adr;
}

bool PageTableEntry::is_swapped() {
	return _swapped;
}

void PageTableEntry::set_swapped(bool swapped) {
	_swapped = swapped;
}
