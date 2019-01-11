#ifndef __INCLUDED_SGUI_INTERFACE_H__
#define __INCLUDED_SGUI_INTERFACE_H__
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Typedef.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#if   defined ( __CC_ARM )
	#define SGUI_ASM			__asm						// asm keyword for ARM Compiler(Keil MDK).
	#define SGUI_INLINE			__inline					// inline keyword for ARM Compiler.
	#pragma	diag_suppress		870							// Disabled "multibyte character sequence" warning.

#elif defined ( __ICCARM__ )
  #define SGUI_ASM				__asm						// < asm keyword for IAR Compiler.
  #define SGUI_INLINE			inline						// inline keyword for IAR Compiler. Only available in High optimization mode!

#elif defined ( __GNUC__ )
  #define SGUI_ASM				__asm						// asm keyword for GNU Compiler.
  #define SGUI_INLINE			inline 						// inline keyword for GNU Compiler.

#elif defined ( __TASKING__ )
  #define SGUI_ASM				__asm 						// asm keyword for TASKING Compiler.
  #define SGUI_INLINE			inline						// inline keyword for TASKING Compiler.
#endif

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
#ifdef _SIMPLE_GUI_VIRTUAL_ENVIRONMENT_SIMULATOR_
 #ifdef _SIMPLE_GUI_ENABLE_ICONV_GB2312_
// Only used when running in simulated environment and text encode need convert to GB2312.
SGUI_SZSTR				SGUI_SystemIF_EncodeConvert(SGUI_CSZSTR szSourceEncode, SGUI_SZSTR szDestinationEncode, SGUI_SZSTR szSource);
  #define		SGUI_ENCODE_BUFFER_SIZE			(512)
  #define		ENCODE(S)						(SGUI_SystemIF_EncodeConvert("UTF-8", "GB2312", (char *)S))
 #else

 #endif
#else
 #define		ENCODE(S)						(S)
#endif

#ifdef _SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_
void*					SGUI_SystemIF_Allocate(SGUI_SIZE uiSize);
void					SGUI_SystemIF_Free(void* pFreePointer);
#endif
void*                   SGUI_SystemIF_MemoryCopy(void* pDest, const void* pSrc, SGUI_UINT uiSize);
void                    SGUI_SystemIF_MemorySet(void* pMemoryPtr, SGUI_BYTE iSetValue, SGUI_UINT uiSize);
SGUI_SIZE               SGUI_SystemIF_StringLength(SGUI_CSZSTR szString);
SGUI_SZSTR				SGUI_SystemIF_StringCopy(SGUI_SZSTR szDest, SGUI_CSZSTR szSrc);
SGUI_SZSTR				SGUI_SystemIF_StringLengthCopy(SGUI_SZSTR szDest, SGUI_CSZSTR szSrc, SGUI_SIZE uiSize);
void                    SGUI_SystemIF_GetNowTime(SGUI_TIME* pstTime);
SGUI_SIZE				SGUI_SystemIF_GetFlashData(SGUI_SCR_DEV* pstIFObj, SGUI_FLASH_DATA_SOURCE eDataSource, SGUI_ROM_ADDRESS adStartAddr, SGUI_SIZE sReadSize, SGUI_BYTE* pOutputBuffer);

#endif // __INCLUDED_SGUI_INTERFACE_H__
