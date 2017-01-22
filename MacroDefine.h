/*
 * MacroDefine.h
 *
 *  Created on: 13 αιπε 2017
 *      Author: Eitan Levin
 */

#ifndef _MACRODEFINE_H_
#define _MACRODEFINE_H_

#define NUMOFFRAMES 64
#define FRAME_NOT_ALLOCATED (-1)
#define SUCCESS 0
#define MAX_SPACE_ALLOWED (1048576)
#define ERROR_RESULT (-1)
#define SUCCESS_RESULT (0)
#define AND_FOR_DIRECTORY_BITS 4290772992 //for logical and - 11111111110000000000000000000000
#define SHIFT_FOR_DIRECTORY_BITS 22	//for logical shift right
#define AND_FOR_PAGE_BITS 4190208 //for logical and - 00000000001111111111000000000000
#define SHIFT_FOR_PAGE_BITS 12	//for logical shift right
#define AND_FOR_OFFSET_BITS 4095 //for logical and - 00000000000000000000111111111111

#define GET_OFFSET_BITS(adr, saveto) do { \
		saveto = adr & AND_FOR_OFFSET_BITS; \
		} while(0)

#define GET_MIDDLE_BITS(adr, saveto) do { \
		saveto = adr & AND_FOR_PAGE_BITS; \
		saveto = saveto >> SHIFT_FOR_PAGE_BITS; \
		} while(0)

#define GET_MSB_BITS(adr, saveto) do { \
		saveto = adr & AND_FOR_DIRECTORY_BITS; \
		saveto = saveto >> SHIFT_FOR_DIRECTORY_BITS; \
		} while(0)

#define CHANGE_ADR_INT_TO_ADR(adr) do { \
		adr = adr << 2; \
		} while(0)

#define LOG_PRINT(logName, a, b, c, d, e, f, g) do { \
		logName << a << "," << b << "," << c << "," << d <<"," << e << "," << f << "," << g; \
		logName << endl; \
		} while(0)

#define SET_SWAPPED_MACRO(a, b, c) do { \
		this->_outerPageTable[a].get_table_address()[b].set_swapped(c); \
		} while(0)

#define WRITE_FRAME_TO_SWAP(a, b) do { \
		mem->swapDevice.WriteFrameToSwapDevice(convert_adr_to_not_offset(a), b); \
		} while(0)

#define GET_INNER_PAGE_ADDRESS(a, b) this->_outerPageTable[a].get_table_address()[b].get_page_address();

#endif /* OS_HM3_MACRODEFINE_H_ */
