# Makefile for the HW3
CCC = g++
CXXFLAGS = -g -std=c++0x -Wall 
CCXXLINK = $(CCC)
OBJS = PhysMem.o SwapDevice.o PageTableEntry.o PageDirectoryEntry.o PageTable.o VirtualMemory.o testProg2.o
RM = rm -f
# Creating the  executable
Bank: $(OBJS) 
	$(CCXXLINK) $(CXXFLAGS) -o testProg2 $(OBJS)
# Creating the object files
PhysMem.o: PhysMem.h PhysMem.cpp
SwapDevice.o: SwapDevice.h SwapDevice.cpp
PageTableEntry.o: PageTableEntry.h PageTableEntry.cpp
PageDirectoryEntry.o: PageDirectoryEntry.h PageDirectoryEntry.cpp
PageTable.o: PageTable.h PageTable.cpp
VirtualMemory.o: VirtualMemory.h VirtualMemory.cpp
testProg2.o : testProg2.cpp

# Cleaning old files before new make
clean: 
	$(RM) Bank *.o *~ "#"* core.*


