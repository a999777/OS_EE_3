# Makefile for the HW3
CCC = g++
CXXFLAGS = -g -std=c++0x -Wall 
CCXXLINK = $(CCC)
OBJS = PhysMem.o SwapDevice.o PageTableEntry.o PageDirectoryEntry.o PageTable.o VirtualMemory.o OurPointer.o main.o
RM = rm -f
# Creating the  executable
Bank: $(OBJS) 
	$(CCXXLINK) $(CXXFLAGS) -o main $(OBJS)
# Creating the object files
PhysMem.o: PhysMem.h PhysMem.cpp
SwapDevice.o: SwapDevice.h SwapDevice.cpp
PageTableEntry.o: PageTableEntry.h PageTableEntry.cpp
PageDirectoryEntry.o: PageDirectoryEntry.h PageDirectoryEntry.cpp
PageTable.o: PageTable.h PageTable.cpp
VirtualMemory.o: VirtualMemory.h VirtualMemory.cpp
OurPointer.o: OurPointer.h OurPointer.cpp
main.o : main.cpp

# Cleaning old files before new make
clean: 
	$(RM) Bank *.o *~ "#"* core.*


