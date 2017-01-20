# Makefile for the HW3
CC = g++
CFLAGS = -g -Wall -std=c++0x
CCLINK = $(CC)
OBJS = PhysMem.o SwapDevice.o PageTableEntry.o PageDirectoryEntry.o PageTable.o VirtualMemory.o MySwapTest.o
RM = rm -f
# Creating the  executable
Bank: $(OBJS) 
	$(CCLINK) $(CFLAGS) -o swapTest $(OBJS)
# Creating the object files
PhysMem.o: PhysMem.h PhysMem.cpp
SwapDevice.o: SwapDevice.h SwapDevice.cpp
PageTableEntry.o: PagePageTableEntry.h
PageDirectoryEntry.o: PageDirectoryEntry.h
PageTable.o: PageTable.h PageTable.cpp
VirtualMemory.o: VirtualMemory.h VirtualMemory.cpp
MySwapTest.o : MySwapTest.cpp

# Cleaning old files before new make
clean: 
	$(RM) Bank *.o *~ "#"* core.*


