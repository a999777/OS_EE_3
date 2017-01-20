/*
 * GivenTestFile.cpp
 *
 *  Created on: 14 ����� 2017
 *      Author: Amit
 */

#include <ostream>
#include <fstream>
#include "OurPointer.h"
#include "VirtualMemory.h"

#define VECSIZE 3

using namespace std;

//TODO just for debugging!!!
void printPhyMem(VirtualMemory* m, int maxframe) {
	for(int i = 0 ; i <= maxframe ; i++) {
		cout << "Memory Frame Number " << i << ". Address: " << m->mem->GetFrame(i) << " Values:" << endl;
		for(int j = 0; j < 1024 ; j+=4) {
			if(m->mem->GetFrame(i)[j] != 0) {
				cout << "(" << j << ")" << (m->mem->GetFrame(i)[j]) << " ";
			}
		}
		cout << endl;
	}

}

int main(){

	VirtualMemory vrtlMem;

	OurPointer matBase = vrtlMem.OurMalloc(VECSIZE*VECSIZE);
	OurPointer vecBase = vrtlMem.OurMalloc(VECSIZE);
	OurPointer resBase = vrtlMem.OurMalloc(VECSIZE);

	OurPointer mat = matBase;
	OurPointer vec = vecBase;
	OurPointer res = resBase;

	ofstream matricesFile;
	matricesFile.open("matrices.txt");

	srand(1);
	for (int i = 0; i < VECSIZE * VECSIZE; ++i) {
		//*(mat++) = rand() % 100;
		*mat = rand() % 100;
		cout << "MATRIX variable number " << i << ": " << (*mat) << " and address is " << mat._vrtlMem->GetPage(mat._adr) << endl;
		(mat++);
	}
	printPhyMem(&vrtlMem, 0 );
	mat = matBase;
	//cout << "mat address is " << mat._vrtlMem->GetPage(mat._adr) << endl;
	//cout << "matBase address is " << matBase._vrtlMem->GetPage(mat._adr) << endl;

	for (int i = 0; i < VECSIZE; ++i) {
		//*(vec++) = rand() % 20000;
		*vec = rand() % 20000;
		//cout << "VECTOR variable number " << i << ": " << " and address is " << vec._vrtlMem->GetPage(mat._adr) << endl;
		*(res++) = 0;
	}
	printPhyMem(&vrtlMem, 0 );
	vec = vecBase;
	res = resBase;

	for (int row = 0; row < VECSIZE; ++row) {
		for (int col = 0; col < VECSIZE; ++col) {
			//*res += (*(mat++)) * (*(vec++)); //it works, but accesses to operator* might happen in an unspecified order
			int mat_value = *(mat++); //our fix for log
			//cout << "<Printing >MATRIX variable (" << row << "," << col << ")"  << ": " << mat_value << " and address is " << mat._vrtlMem->GetPage(mat._adr) << endl;
			*res += (mat_value) * (*(vec++)); //log file consistency
		}
		vec = vecBase;
		++res;
	}

	mat = matBase;
	vec = vecBase;
	res = resBase;

	matricesFile << "Matrix:" << endl;
	for (int row = 0; row < VECSIZE; ++row) {
		for (int col = 0; col < VECSIZE; ++col)
			matricesFile << *(mat++) << " ";
		matricesFile << endl;
	}

	matricesFile << "Vector:" << endl;
	for (int col = 0; col < VECSIZE; ++col)
		matricesFile << *(vec++) << " ";
	matricesFile << endl;

	matricesFile << "Result:" << endl;
	for (int col = 0; col < VECSIZE; ++col)
		matricesFile << *(res++) << " ";
	matricesFile << endl;
}


