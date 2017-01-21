/*
 * MySwapTest.cpp
 *
 *  Created on: 19 בינו׳ 2017
 *      Author: Amit
 */

#include<iostream>
#include<fstream>
#include "OurPointer.h"
#include "VirtualMemory.h"

using namespace std;

int bugIndicator = 0;

#define STOP_POINT 1024*64

int main(){
    VirtualMemory vrtlMem;

    OurPointer ptr = vrtlMem.OurMalloc(1024*64); //That means we take everything possible in Physical memory + 1

    //cout << "Hello is there anyoe out there" << endl;

    srand(1);
    for (int i = 0; i < 1024*63; i++) {
    	*ptr = (rand() % 100);
    	ptr++;
    	if(i > 63000)
    		cout << "i = " << i << " which means the frame is " << i / 1024 << " and the location within the frame is " << i - (i / 1024 )*1024 << endl;
    }


/*
    //This one should cause swap out
    *ptr = 777;
    ptr++;*/

    return 0;
}

