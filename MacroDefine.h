/*
 * MacroDefine.h
 *
 *  Created on: 13 αιπε 2017
 *      Author: Eitan Levin
 */

#ifndef _MACRODEFINE_H_
#define _MACRODEFINE_H_

#define NUMOFFRAMES 64
#define INT_SIZE 4
#define TABLE_SIZE 1024
#define PAGE_SIZE 4096
#define ERROR_RESULT -1
#define SUCCESS_RESULT 0

//TODO this file has to be changed too

#define GET_OFFSET_BITS(adr, saveto) do { \
		saveto = adr & 4095; \
		saveto = saveto >> 2; \
		} while(0)

#define GET_MIDDLE_BITS(adr, saveto) do { \
		saveto = adr & 4190208; \
		saveto = saveto >> 12; \
		} while(0)

#define GET_MSB_BITS(adr, saveto) do { \
		saveto = adr & 4290772992; \
		saveto = saveto >> 22; \
		} while(0)

#define CHANGE_ADR_INT_TO_ADR(adr) do { \
		adr = adr << 2; \
		} while(0)

#define LOG_PRINT(logName, a, b, c, d, e, f, g) do { \
		logName << a << "," << b << "," << c << "," << d <<"," << e << "," << f << "," << g; \
		logName << endl; \
		} while(0)

#define SET_SWAPPED_MACRO(a, b, c) do { \
		this->_outerPageTable[a].get_inner_table_address()[b].set_swapped(c); \
		} while(0)

#define WRITE_FRAME_TO_SWAP(a, b) do { \
		_vrtlMem->swapDevice.WriteFrameToSwapDevice((a >> 12), b); \
		} while(0)

#define GET_INNER_PAGE_ADDRESS(a, b) this->_outerPageTable[a].get_inner_table_address()[b].get_page_address();

#endif /* OS_HM3_MACRODEFINE_H_ */
