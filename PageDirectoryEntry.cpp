
#include "PageDirectoryEntry.h"


PageTableEntry* PageDirectoryEntry::get_inner_table_address() {
	return _innerTable;
}

void PageDirectoryEntry::set_inner_table_address(PageTableEntry* innerTableAdr) {
	_innerTable = innerTableAdr;
}

bool PageDirectoryEntry::is_valid() {
	return _valid;
}

void PageDirectoryEntry::set_valid(bool valid) {
	_valid = valid;
}

