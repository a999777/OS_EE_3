#include <iostream>
#include <fstream>
#include "VirtualMemory.h"
#define VECSIZE 300
using namespace std;
int main() {
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
		*(mat) = rand() % 100;
		mat++;
	}
	mat = matBase;

	for (int i = 0; i < VECSIZE; ++i) {
		*(vec++) = rand() % 20000;
		*(res++) = 0;
	}
	vec = vecBase;
	res = resBase;
	for (int row = 0; row < VECSIZE; ++row)
	{
		for (int col = 0; col < VECSIZE; ++col)
		{
			//*res += (*(mat++)) * (*(vec++)); //it works, but accesses to operator*
			//might happen in an unspecified order
			int mat_value = *(mat++);//our fix for log
			int vecVal=*(vec++);
			//	*res += (mat_value)* (*(vec++)); //log file consistency
			*res+=mat_value*vecVal;
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
