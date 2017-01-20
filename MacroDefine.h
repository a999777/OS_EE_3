/*
 * MacroDefine.h
 *
 *  Created on: 13 αιπε 2017
 *      Author: Eitan Levin
 */

#ifndef _MACRODEFINE_H_
#define _MACRODEFINE_H_

#define FRAME_NOT_ALLOCATED (-1)
#define SUCCESS 0
#define MAX_SPACE_ALLOWED (1048576)

#define NUMOFFRAMES 64

#define GET_OFFSET_BITS(adr, saveto) do { \
		saveto = adr & 4095; \
		} while(0)

#define GET_MIDDLE_BITS(adr, saveto) do { \
		saveto = adr & 4190208; \
		saveto = saveto >> 12; \
		} while(0)

#define GET_MSB_BITS(adr, saveto) do { \
		saveto= adr & 4290772992; \
		saveto = saveto >> 22; \
		} while(0)

#define CHANGE_ADR_INT_TO_ADR(adr) do { \
		adr = adr << 2; \
		} while(0)



#endif /* OS_HM3_MACRODEFINE_H_ */
