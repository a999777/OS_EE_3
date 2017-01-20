/*
 * unitTests.h
 *
 *  Created on: 13 בינו׳ 2017
 *      Author: Amit
 */

#ifndef UNITTESTS_H_
#define UNITTESTS_H_


#include <iostream>

using std::cout;
using std::endl;

#define ERROR_AND_PRINT(a) do {\
		cout << "Error in line " << __LINE__ << " " << a << endl; \
		return false; \
	} while (0)

#define ASSERT_TRUE(a) do { \
		if((a) != true) { \
			cout << __LINE__ << ": expected 'true' but received something else." << endl; \
			return false; \
		} \
	} while (0)

#define ASSERT_FALSE(a) do { \
		if((a) != false) { \
			cout << __LINE__ << ": expected 'false' but received something else." << endl; \
			return false; \
		} \
	} while (0)

#define RUN_TEST(name, a) do { \
		if((a) != true) { \
			cout << __LINE__ << ": Test" << name << " has failed." << endl; \
		} else { \
			cout << __LINE__ << ": Test" << name << " has succeeded." << endl; \
		} \
	} while(0)

#endif /* UNITTESTS_H_ */
