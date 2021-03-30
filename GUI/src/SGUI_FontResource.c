/*************************************************************************/
/** Copyright.															**/
/** FileName: SGUI_FontResource.c										**/
/** Author: Polarix,Jerry												**/
/** Description: Internal font data.									**/
/*************************************************************************/
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Common.h"
#include "SGUI_FontResource.h"
#include "SGUI_Basic.h"
#include "SGUI_Text.h"
//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define	SGUI_FONT_RES_DECLARE(NAME)				SGUI_SIZE SGUI_Resource_GetFontData_##NAME(SGUI_SIZE sStartAddr, SGUI_BYTE* pDataBuffer, SGUI_SIZE sReadSize)
#define	SGUI_FONT_RES_DEFINE(NAME, SRC)			SGUI_SIZE SGUI_Resource_GetFontData_##NAME(SGUI_SIZE sStartAddr, SGUI_BYTE* pDataBuffer, SGUI_SIZE sReadSize)\
												{\
													SGUI_SIZE sReadCount;\
													const SGUI_BYTE* pSrc = SRC+sStartAddr;\
													SGUI_BYTE* pDest = pDataBuffer;\
													if(NULL != pDataBuffer)\
													{\
														for(sReadCount=0; sReadCount<sReadSize; sReadCount++)\
														{\
															*pDest++ = *pSrc++;\
														}\
													}\
													return sReadCount;\
												}
#define	SGUI_FONT_RES_DATA_FUNC_NAME(NAME)		SGUI_Resource_GetFontData_##NAME

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static SGUI_UINT32 SGUI_Resource_IndexMapper_MiniNum(SGUI_UINT32 uiCode);
static SGUI_UINT32 SGUI_Resource_IndexMapper_Default(SGUI_UINT32 uiCode);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//


//======================================================================//
//= 5 Pix mono space font library.								   =//
//======================================================================//
SGUI_INTERNAL_MONOSPACE_FONT_RESOURCE_DEFINE(
        MiniNum,4,5,
        #ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
        1,
        #endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
        4,
        SGUI_TEXT_DECODER_ASCII,
        SGUI_Resource_IndexMapper_MiniNum,
        SGUI_BMP_SCAN_MODE_DHPV,
        0x1F, 0x11, 0x1F, 0x00,	//0
        0x00, 0x1F, 0x00, 0x00,	//1
        0x1D, 0x15, 0x17, 0x00,	//2
        0x15, 0x15, 0x1F, 0x00,	//3
        0x07, 0x04, 0x1F, 0x00,	//4
        0x17, 0x15, 0x1D, 0x00,	//5
        0x1F, 0x15, 0x1D, 0x00,	//6
        0x19, 0x05, 0x03, 0x00,	//7
        0x1F, 0x15, 0x1F, 0x00,	//8
        0x17, 0x15, 0x1F, 0x00,	//9
        0x00, 0x10, 0x00, 0x00,	//.
        0x04, 0x0E, 0x04, 0x00,	//+
        0x04, 0x04, 0x04, 0x00,	//-
        0x0A, 0x04, 0x0A, 0x00,	//**
        0x18, 0x04, 0x03, 0x00, ///
        0x00, 0x0E, 0x11, 0x00, //(
        0x11, 0x0E, 0x00, 0x00, //)
        0x00, 0x00, 0x00, 0x00, //space
        0x1A, 0x04, 0x0B, 0x00, //%
        0x0A, 0x0A, 0x0A, 0x00, //=
);
//======================================================================//
//= 8 Pix mono space font library.													//
//======================================================================//
SGUI_INTERNAL_MONOSPACE_FONT_RESOURCE_DEFINE(
        FONT_8,6,8,
        #ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
        1,
        #endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
        6,
        SGUI_TEXT_DECODER_ASCII,
        SGUI_Resource_IndexMapper_Default,
        SGUI_BMP_SCAN_MODE_DHPV,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// space	index 0
        0x00, 0x00, 0x5F, 0x00, 0x00, 0x00,	// !
        0x00, 0x07, 0x00, 0x07, 0x00, 0x00,	// "
        0x14, 0x7F, 0x14, 0x7F, 0x14, 0x00,	// #
        0x24, 0x2A, 0x7F, 0x2A, 0x12, 0x00,	// $
        0x23, 0x13, 0x08, 0x64, 0x62, 0x00,	// %
        0x36, 0x49, 0x55, 0x22, 0x50, 0x00,	// &
        0x00, 0x05, 0x03, 0x00, 0x00, 0x00,	// '
        0x00, 0x1C, 0x22, 0x41, 0x00, 0x00,	// (
        0x00, 0x41, 0x22, 0x1C, 0x00, 0x00,	// )
        0x08, 0x2A, 0x1C, 0x2A, 0x08, 0x00,	// *
        0x08, 0x08, 0x3E, 0x08, 0x08, 0x00,	// +
        0x00, 0x50, 0x30, 0x00, 0x00, 0x00,	// ,
        0x08, 0x08, 0x08, 0x08, 0x08, 0x00,	// -
        0x00, 0x30, 0x30, 0x00, 0x00, 0x00,	// .
        0x20, 0x10, 0x08, 0x04, 0x02, 0x00,	// /
        0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00,	// 0
        0x00, 0x42, 0x7F, 0x40, 0x00, 0x00,	// 1
        0x42, 0x61, 0x51, 0x49, 0x46, 0x00,	// 2
        0x21, 0x41, 0x45, 0x4B, 0x31, 0x00,	// 3
        0x18, 0x14, 0x12, 0x7F, 0x10, 0x00,	// 4
        0x27, 0x45, 0x45, 0x45, 0x39, 0x00,	// 5
        0x3C, 0x4A, 0x49, 0x49, 0x30, 0x00,	// 6
        0x01, 0x71, 0x09, 0x05, 0x03, 0x00,	// 7
        0x36, 0x49, 0x49, 0x49, 0x36, 0x00,	// 8
        0x06, 0x49, 0x49, 0x29, 0x1E, 0x00,	// 9
        0x00, 0x36, 0x36, 0x00, 0x00, 0x00,	// :
        0x00, 0x56, 0x36, 0x00, 0x00, 0x00,	// ;
        0x00, 0x08, 0x14, 0x22, 0x41, 0x00,	// <
        0x14, 0x14, 0x14, 0x14, 0x14, 0x00,	// =
        0x41, 0x22, 0x14, 0x08, 0x00, 0x00,	// >
        0x02, 0x01, 0x51, 0x09, 0x06, 0x00,	// ?
        0x32, 0x49, 0x79, 0x41, 0x3E, 0x00,	// @
        0x7E, 0x11, 0x11, 0x11, 0x7E, 0x00,	// A
        0x7F, 0x49, 0x49, 0x49, 0x36, 0x00,	// B
        0x3E, 0x41, 0x41, 0x41, 0x22, 0x00,	// C
        0x7F, 0x41, 0x41, 0x22, 0x1C, 0x00,	// D
        0x7F, 0x49, 0x49, 0x49, 0x41, 0x00,	// E
        0x7F, 0x09, 0x09, 0x01, 0x01, 0x00,	// F
        0x3E, 0x41, 0x41, 0x51, 0x32, 0x00,	// G
        0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00,	// H
        0x00, 0x41, 0x7F, 0x41, 0x00, 0x00,	// I
        0x20, 0x40, 0x41, 0x3F, 0x01, 0x00,	// J
        0x7F, 0x08, 0x14, 0x22, 0x41, 0x00,	// K
        0x7F, 0x40, 0x40, 0x40, 0x40, 0x00,	// L
        0x7F, 0x02, 0x04, 0x02, 0x7F, 0x00,	// M
        0x7F, 0x04, 0x08, 0x10, 0x7F, 0x00,	// N
        0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00,	// O
        0x7F, 0x09, 0x09, 0x09, 0x06, 0x00,	// P
        0x3E, 0x41, 0x51, 0x21, 0x5E, 0x00,	// Q
        0x7F, 0x09, 0x19, 0x29, 0x46, 0x00,	// R
        0x46, 0x49, 0x49, 0x49, 0x31, 0x00,	// S
        0x01, 0x01, 0x7F, 0x01, 0x01, 0x00,	// T
        0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00,	// U
        0x1F, 0x20, 0x40, 0x20, 0x1F, 0x00,	// V
        0x7F, 0x20, 0x18, 0x20, 0x7F, 0x00,	// W
        0x63, 0x14, 0x08, 0x14, 0x63, 0x00,	// X
        0x03, 0x04, 0x78, 0x04, 0x03, 0x00,	// Y
        0x61, 0x51, 0x49, 0x45, 0x43, 0x00,	// Z
        0x00, 0x00, 0x7F, 0x41, 0x41, 0x00,	// [
        0x02, 0x04, 0x08, 0x10, 0x20, 0x00,	// "\"
        0x41, 0x41, 0x7F, 0x00, 0x00, 0x00,	// ]
        0x04, 0x02, 0x01, 0x02, 0x04, 0x00,	// ^
        0x40, 0x40, 0x40, 0x40, 0x40, 0x00,	// _
        0x00, 0x01, 0x02, 0x04, 0x00, 0x00,	// `
        0x20, 0x54, 0x54, 0x54, 0x78, 0x00,	// a
        0x7F, 0x48, 0x44, 0x44, 0x38, 0x00,	// b
        0x38, 0x44, 0x44, 0x44, 0x20, 0x00,	// c
        0x38, 0x44, 0x44, 0x48, 0x7F, 0x00,	// d
        0x38, 0x54, 0x54, 0x54, 0x18, 0x00,	// e
        0x08, 0x7E, 0x09, 0x01, 0x02, 0x00,	// f
        0x08, 0x14, 0x54, 0x54, 0x3C, 0x00,	// g
        0x7F, 0x08, 0x04, 0x04, 0x78, 0x00,	// h
        0x00, 0x44, 0x7D, 0x40, 0x00, 0x00,	// i
        0x20, 0x40, 0x44, 0x3D, 0x00, 0x00,	// j
        0x00, 0x7F, 0x10, 0x28, 0x44, 0x00,	// k
        0x00, 0x41, 0x7F, 0x40, 0x00, 0x00,	// l
        0x7C, 0x04, 0x18, 0x04, 0x78, 0x00,	// m
        0x7C, 0x08, 0x04, 0x04, 0x78, 0x00,	// n
        0x38, 0x44, 0x44, 0x44, 0x38, 0x00,	// o
        0x7C, 0x14, 0x14, 0x14, 0x08, 0x00,	// p
        0x08, 0x14, 0x14, 0x18, 0x7C, 0x00,	// q
        0x7C, 0x08, 0x04, 0x04, 0x08, 0x00,	// r
        0x48, 0x54, 0x54, 0x54, 0x20, 0x00,	// s
        0x04, 0x3F, 0x44, 0x40, 0x20, 0x00,	// t
        0x3C, 0x40, 0x40, 0x20, 0x7C, 0x00,	// u
        0x1C, 0x20, 0x40, 0x20, 0x1C, 0x00,	// v
        0x3C, 0x40, 0x30, 0x40, 0x3C, 0x00,	// w
        0x44, 0x28, 0x10, 0x28, 0x44, 0x00,	// x
        0x0C, 0x50, 0x50, 0x50, 0x3C, 0x00,	// y
        0x44, 0x64, 0x54, 0x4C, 0x44, 0x00,	// z
        0x00, 0x08, 0x36, 0x41, 0x00, 0x00,	// {
        0x00, 0x00, 0x7F, 0x00, 0x00, 0x00,	// |
        0x00, 0x41, 0x36, 0x08, 0x00, 0x00,	// }
        0x00, 0x01, 0x02, 0x00, 0x00, 0x00	// `		index 94
);
//======================================================================//
//= 12 Pix mono space font library.									   =//
//======================================================================//
SGUI_INTERNAL_MONOSPACE_FONT_RESOURCE_DEFINE(
        FONT_12,6,12,
        #ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
        1,
        #endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
        12,
        SGUI_TEXT_DECODER_ASCII,
        SGUI_Resource_IndexMapper_Default,
        SGUI_BMP_SCAN_MODE_DHPV,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// space	Index 0
        0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,	// !
        0x00, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// "
        0x90, 0xD0, 0xBC, 0xD0, 0xBC, 0x90, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00,	// #
        0x18, 0x24, 0xFE, 0x44, 0x88, 0x00, 0x01, 0x02, 0x07, 0x02, 0x01, 0x00,	// $
        0x18, 0x24, 0xD8, 0xB0, 0x4C, 0x80, 0x00, 0x03, 0x00, 0x01, 0x02, 0x01,	// %
        0xC0, 0x38, 0xE4, 0x38, 0x80, 0x00, 0x01, 0x02, 0x02, 0x01, 0x02, 0x02,	// &
        0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// '
        0x00, 0x00, 0x00, 0xF0, 0x0C, 0x02, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04,	// (
        0x02, 0x0C, 0xF0, 0x00, 0x00, 0x00, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00,	// )
        0x90, 0x60, 0xF8, 0x60, 0x90, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,	// *
        0x20, 0x20, 0xFC, 0x20, 0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,	// +
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x06, 0x00, 0x00, 0x00, 0x00,	// ,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// -
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,	// .
        0x00, 0x80, 0x60, 0x18, 0x06, 0x00, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00,	// /
        0xF8, 0x04, 0x04, 0x04, 0xF8, 0x00, 0x01, 0x02, 0x02, 0x02, 0x01, 0x00,	// 0
        0x00, 0x08, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x02, 0x00, 0x00,	// 1
        0x18, 0x84, 0x44, 0x24, 0x18, 0x00, 0x03, 0x02, 0x02, 0x02, 0x02, 0x00,	// 2
        0x08, 0x04, 0x24, 0x24, 0xD8, 0x00, 0x01, 0x02, 0x02, 0x02, 0x01, 0x00,	// 3
        0x40, 0xB0, 0x88, 0xFC, 0x80, 0x00, 0x00, 0x00, 0x02, 0x03, 0x02, 0x00,	// 4
        0x3C, 0x24, 0x24, 0x24, 0xC4, 0x00, 0x01, 0x02, 0x02, 0x02, 0x01, 0x00,	// 5
        0xF8, 0x24, 0x24, 0x24, 0xC8, 0x00, 0x01, 0x02, 0x02, 0x02, 0x01, 0x00,	// 6
        0x0C, 0x04, 0xE4, 0x14, 0x0C, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,	// 7
        0xD8, 0x24, 0x24, 0x24, 0xD8, 0x00, 0x01, 0x02, 0x02, 0x02, 0x01, 0x00,	// 8
        0x38, 0x44, 0x44, 0x44, 0xF8, 0x00, 0x01, 0x02, 0x02, 0x02, 0x01, 0x00,	// 9
        0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,	// :
        0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x04, 0x03, 0x00, 0x00, 0x00,	// ;
        0x00, 0x20, 0x50, 0x88, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02,	// <
        0x90, 0x90, 0x90, 0x90, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// =
        0x00, 0x02, 0x04, 0x88, 0x50, 0x20, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00,	// >
        0x18, 0x04, 0xC4, 0x24, 0x18, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,	// ?
        0xF8, 0x04, 0xE4, 0x94, 0x78, 0x00, 0x01, 0x02, 0x02, 0x02, 0x02, 0x00,	// @
        0x00, 0xF0, 0x9C, 0x9C, 0xF0, 0x00, 0x02, 0x03, 0x00, 0x00, 0x03, 0x02,	// A
        0x04, 0xFC, 0x24, 0x24, 0xD8, 0x00, 0x02, 0x03, 0x02, 0x02, 0x01, 0x00,	// B
        0xF8, 0x04, 0x04, 0x04, 0x08, 0x00, 0x01, 0x02, 0x02, 0x02, 0x01, 0x00,	// C
        0x04, 0xFC, 0x04, 0x04, 0xF8, 0x00, 0x02, 0x03, 0x02, 0x02, 0x01, 0x00,	// D
        0x04, 0xFC, 0x24, 0x74, 0x0C, 0x00, 0x02, 0x03, 0x02, 0x02, 0x03, 0x00,	// E
        0x04, 0xFC, 0x24, 0x74, 0x0C, 0x00, 0x02, 0x03, 0x02, 0x00, 0x00, 0x00,	// F
        0xF8, 0x04, 0x04, 0x44, 0xCC, 0x40, 0x01, 0x02, 0x02, 0x02, 0x01, 0x00,	// G
        0x04, 0xFC, 0x20, 0x20, 0xFC, 0x04, 0x02, 0x03, 0x00, 0x00, 0x03, 0x02,	// H
        0x04, 0x04, 0xFC, 0x04, 0x04, 0x00, 0x02, 0x02, 0x03, 0x02, 0x02, 0x00,	// I
        0x00, 0x04, 0x04, 0xFC, 0x04, 0x04, 0x02, 0x04, 0x04, 0x03, 0x00, 0x00,	// J
        0x04, 0xFC, 0x24, 0xD0, 0x0C, 0x04, 0x02, 0x03, 0x02, 0x00, 0x03, 0x02,	// K
        0x04, 0xFC, 0x04, 0x00, 0x00, 0x00, 0x02, 0x03, 0x02, 0x02, 0x02, 0x03,	// L
        0xFC, 0x3C, 0xC0, 0x3C, 0xFC, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00,	// M
        0x04, 0xFC, 0x30, 0xC4, 0xFC, 0x04, 0x02, 0x03, 0x02, 0x00, 0x03, 0x02,	// N
        0xF8, 0x04, 0x04, 0x04, 0xF8, 0x00, 0x01, 0x02, 0x02, 0x02, 0x01, 0x00,	// O
        0x04, 0xFC, 0x24, 0x24, 0x18, 0x00, 0x02, 0x03, 0x02, 0x00, 0x00, 0x00,	// P
        0xF8, 0x84, 0x84, 0x04, 0xF8, 0x00, 0x01, 0x02, 0x02, 0x07, 0x04, 0x00,	// Q
        0x04, 0xFC, 0x24, 0x64, 0x98, 0x00, 0x02, 0x03, 0x02, 0x00, 0x03, 0x02,	// R
        0x18, 0x24, 0x24, 0x44, 0x88, 0x00, 0x01, 0x02, 0x02, 0x02, 0x01, 0x00,	// S
        0x0C, 0x04, 0xFC, 0x04, 0x0C, 0x00, 0x00, 0x02, 0x03, 0x02, 0x00, 0x00,	// T
        0x04, 0xFC, 0x00, 0x00, 0xFC, 0x04, 0x00, 0x01, 0x02, 0x02, 0x01, 0x00,	// U
        0x04, 0x7C, 0x80, 0x80, 0x7C, 0x04, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00,	// V
        0x1C, 0xE0, 0x3C, 0xE0, 0x1C, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00,	// W
        0x04, 0x9C, 0x60, 0x9C, 0x04, 0x00, 0x02, 0x03, 0x00, 0x03, 0x02, 0x00,	// X
        0x04, 0x1C, 0xE0, 0x1C, 0x04, 0x00, 0x00, 0x02, 0x03, 0x02, 0x00, 0x00,	// Y
        0x0C, 0x84, 0x64, 0x1C, 0x04, 0x00, 0x02, 0x03, 0x02, 0x02, 0x03, 0x00,	// Z
        0x00, 0x00, 0xFE, 0x02, 0x02, 0x00, 0x00, 0x00, 0x07, 0x04, 0x04, 0x00,	// [
        0x00, 0x0E, 0x30, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00,	// '\'
        0x00, 0x02, 0x02, 0xFE, 0x00, 0x00, 0x00, 0x04, 0x04, 0x07, 0x00, 0x00,	// ]
        0x00, 0x04, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// ^
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,	// _
        0x00, 0x00, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// `
        0x00, 0x40, 0xA0, 0xA0, 0xC0, 0x00, 0x00, 0x01, 0x02, 0x02, 0x01, 0x02,	// a
        0x04, 0xFC, 0x20, 0x20, 0xC0, 0x00, 0x00, 0x03, 0x02, 0x02, 0x01, 0x00,	// b
        0x00, 0xC0, 0x20, 0x20, 0x60, 0x00, 0x00, 0x01, 0x02, 0x02, 0x02, 0x00,	// c
        0x00, 0xC0, 0x20, 0x24, 0xFC, 0x00, 0x00, 0x01, 0x02, 0x02, 0x01, 0x02,	// d
        0x00, 0xC0, 0xA0, 0xA0, 0xC0, 0x00, 0x00, 0x01, 0x02, 0x02, 0x02, 0x00,	// e
        0x00, 0x20, 0xF8, 0x24, 0x24, 0x04, 0x00, 0x02, 0x03, 0x02, 0x02, 0x00,	// f
        0x00, 0x40, 0xA0, 0xA0, 0x60, 0x20, 0x00, 0x07, 0x0A, 0x0A, 0x0A, 0x04,	// g
        0x04, 0xFC, 0x20, 0x20, 0xC0, 0x00, 0x02, 0x03, 0x00, 0x00, 0x03, 0x02,	// h
        0x00, 0x20, 0xE4, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x02, 0x00, 0x00,	// i
        0x00, 0x00, 0x20, 0xE4, 0x00, 0x00, 0x08, 0x08, 0x08, 0x07, 0x00, 0x00,	// j
        0x04, 0xFC, 0x80, 0xA0, 0x60, 0x20, 0x02, 0x03, 0x02, 0x00, 0x03, 0x02,	// k
        0x04, 0x04, 0xFC, 0x00, 0x00, 0x00, 0x02, 0x02, 0x03, 0x02, 0x02, 0x00,	// l
        0xE0, 0x20, 0xE0, 0x20, 0xC0, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00,	// m
        0x20, 0xE0, 0x20, 0x20, 0xC0, 0x00, 0x02, 0x03, 0x02, 0x00, 0x03, 0x02,	// n
        0x00, 0xC0, 0x20, 0x20, 0xC0, 0x00, 0x00, 0x01, 0x02, 0x02, 0x01, 0x00,	// o
        0x20, 0xE0, 0x20, 0x20, 0xC0, 0x00, 0x08, 0x0F, 0x0A, 0x02, 0x01, 0x00,	// p
        0x00, 0xC0, 0x20, 0x20, 0xE0, 0x00, 0x00, 0x01, 0x02, 0x0A, 0x0F, 0x08,	// q
        0x20, 0xE0, 0x40, 0x20, 0x20, 0x00, 0x02, 0x03, 0x02, 0x00, 0x00, 0x00,	// r
        0x00, 0x40, 0xA0, 0xA0, 0x20, 0x00, 0x00, 0x02, 0x02, 0x02, 0x01, 0x00,	// s
        0x00, 0x20, 0xF8, 0x20, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x02, 0x00,	// t
        0x20, 0xE0, 0x00, 0x20, 0xE0, 0x00, 0x00, 0x01, 0x02, 0x02, 0x01, 0x02,	// u
        0x20, 0xE0, 0x00, 0x00, 0xE0, 0x20, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00,	// v
        0x60, 0x80, 0xE0, 0x80, 0x60, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00,	// w
        0x20, 0x60, 0x80, 0x60, 0x20, 0x00, 0x02, 0x03, 0x00, 0x03, 0x02, 0x00,	// x
        0x20, 0xE0, 0x20, 0x80, 0x60, 0x20, 0x08, 0x08, 0x07, 0x01, 0x00, 0x00,	// y
        0x00, 0x20, 0xA0, 0x60, 0x20, 0x00, 0x00, 0x02, 0x03, 0x02, 0x02, 0x00,	// z
        0x00, 0x00, 0x60, 0x9E, 0x02, 0x00, 0x00, 0x00, 0x00, 0x07, 0x04, 0x00,	// {
        0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00,	// |
        0x00, 0x02, 0x9E, 0x60, 0x00, 0x00, 0x00, 0x04, 0x07, 0x00, 0x00, 0x00,	// }
        0x04, 0x02, 0x02, 0x04, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// ~		Index 94
);
//======================================================================//
//= 16 Pix font library.												//
//======================================================================//
SGUI_INTERNAL_MONOSPACE_FONT_RESOURCE_DEFINE(
        FONT_16,8,16,
        #ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
        1,
        #endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
        16,
        SGUI_TEXT_DECODER_ASCII,
        SGUI_Resource_IndexMapper_Default,
        SGUI_BMP_SCAN_MODE_DHPV,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// space	Index 0
        0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x33,0x00,0x00,0x00,0x00,	//"!"
        0x00,0x00,0x1E,0x06,0x00,0x1E,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//"""
        0x40,0x40,0xF8,0x40,0x40,0xF8,0x40,0x00,0x04,0x3F,0x04,0x04,0x3F,0x04,0x04,0x00,	//"#"
        0x00,0x70,0x88,0xFC,0x08,0x30,0x00,0x00,0x00,0x18,0x20,0xFF,0x21,0x1E,0x00,0x00,	//"$"
        0xF0,0x08,0xF0,0x00,0xE0,0x18,0x00,0x00,0x00,0x21,0x1C,0x03,0x1E,0x21,0x1E,0x00,	//"%"
        0x00,0xF0,0x08,0x88,0x70,0x00,0x00,0x00,0x1E,0x21,0x23,0x24,0x19,0x27,0x21,0x10,	//"&"
        0x00,0x1E,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//"'"
        0x00,0x00,0x00,0xE0,0x18,0x04,0x02,0x00,0x00,0x00,0x00,0x07,0x18,0x20,0x40,0x00,	//"("
        0x00,0x02,0x04,0x18,0xE0,0x00,0x00,0x00,0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00,	//")"
        0x40,0x40,0x80,0xF0,0x80,0x40,0x40,0x00,0x02,0x02,0x01,0x0F,0x01,0x02,0x02,0x00,	//"*"
        0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x1F,0x01,0x01,0x01,0x00,	//"+"
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xB0,0x70,0x00,0x00,0x00,0x00,0x00,	//","
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,	//"-"
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,	//"."
        0x00,0x00,0x00,0x00,0x80,0x60,0x18,0x06,0x00,0x60,0x18,0x06,0x01,0x00,0x00,0x00,	//"/"
        0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,	//"0"
        0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,	//"1"
        0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00,	//"2"
        0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00,	//"3"
        0x00,0x00,0x80,0x60,0x10,0xF8,0x00,0x00,0x00,0x06,0x05,0x24,0x24,0x3F,0x24,0x00,	//"4"
        0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00,	//"5"
        0x00,0xE0,0x10,0x88,0x88,0x08,0x10,0x00,0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00,	//"6"
        0x00,0x38,0x08,0x08,0xC8,0x28,0x18,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,	//"7"
        0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00,	//"8"
        0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x10,0x21,0x22,0x22,0x11,0x0F,0x00,	//"9"
        0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,	//":"
        0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x80,0xE0,0x60,0x00,0x00,0x00,	//";"
        0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00,	//"<"
        0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,	//"="
        0x00,0x08,0x10,0x20,0x40,0x80,0x00,0x00,0x00,0x20,0x10,0x08,0x04,0x02,0x01,0x00,	//">"
        0x00,0x70,0x08,0x08,0x08,0x08,0xF0,0x00,0x00,0x00,0x00,0x00,0x36,0x01,0x00,0x00,	//"?"
        0xC0,0x30,0xC8,0x28,0xC8,0x10,0xE0,0x00,0x07,0x18,0x27,0x24,0x23,0x14,0x0B,0x00,	//"@"
        0x00,0x00,0xC0,0x38,0x38,0xC0,0x00,0x00,0x20,0x3C,0x23,0x02,0x02,0x23,0x3C,0x20,	//"A"
        0x08,0xF8,0x88,0x88,0x88,0x70,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x11,0x0E,0x00,	//"B"
        0xC0,0x30,0x08,0x08,0x08,0x08,0x30,0x00,0x07,0x18,0x20,0x20,0x20,0x10,0x08,0x00,	//"C"
        0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,0x20,0x3F,0x20,0x20,0x20,0x10,0x0F,0x00,	//"D"
        0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x20,0x23,0x20,0x18,0x00,	//"E"
        0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x00,0x03,0x00,0x00,0x00,	//"F"
        0xC0,0x30,0x08,0x08,0x08,0x18,0x00,0x00,0x07,0x18,0x20,0x20,0x22,0x1E,0x02,0x00,	//"G"
        0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x20,0x3F,0x21,0x01,0x01,0x21,0x3F,0x20,	//"H"
        0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,	//"I"
        0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,0x00,	//"J"
        0x08,0xF8,0x88,0xC0,0x28,0x18,0x08,0x00,0x20,0x3F,0x20,0x01,0x26,0x38,0x20,0x00,	//"K"
        0x08,0xF8,0x08,0x00,0x00,0x00,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x20,0x30,0x00,	//"L"
        0x08,0xF8,0xF8,0x00,0xF8,0xF8,0x08,0x00,0x20,0x3F,0x00,0x3F,0x00,0x3F,0x20,0x00,	//"M"
        0x08,0xF8,0x30,0xC0,0x00,0x08,0xF8,0x08,0x20,0x3F,0x20,0x00,0x07,0x18,0x3F,0x00,	//"N"
        0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x10,0x20,0x20,0x20,0x10,0x0F,0x00,	//"O"
        0x08,0xF8,0x08,0x08,0x08,0x08,0xF0,0x00,0x20,0x3F,0x21,0x01,0x01,0x01,0x00,0x00,	//"P"
        0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x18,0x24,0x24,0x38,0x50,0x4F,0x00,	//"Q"
        0x08,0xF8,0x88,0x88,0x88,0x88,0x70,0x00,0x20,0x3F,0x20,0x00,0x03,0x0C,0x30,0x20,	//"R"
        0x00,0x70,0x88,0x08,0x08,0x08,0x30,0x00,0x00,0x18,0x20,0x21,0x21,0x22,0x1C,0x00,	//"S"
        0x18,0x08,0x08,0xF8,0x08,0x08,0x18,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,	//"T"
        0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,	//"U"
        0x08,0x78,0x88,0x00,0x00,0xC8,0x38,0x08,0x00,0x00,0x07,0x38,0x38,0x07,0x00,0x00,	//"V"
        0xF8,0x08,0x00,0xF0,0x00,0x08,0xF8,0x00,0x03,0x3C,0x07,0x00,0x07,0x3C,0x03,0x00,	//"W"
        0x08,0x18,0x68,0x80,0x80,0x68,0x18,0x08,0x20,0x30,0x2C,0x03,0x03,0x2C,0x30,0x20,	//"X"
        0x08,0x38,0xC8,0x00,0xC8,0x38,0x08,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,	//"Y"
        0x18,0x08,0x08,0x08,0xC8,0x38,0x08,0x00,0x20,0x38,0x26,0x21,0x20,0x20,0x38,0x00,	//"Z"
        0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00,	//"["
        0x00,0x0C,0x30,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x0C,0x30,0xC0,	//"\"
        0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,	//"]"
        0x00,0x00,0x04,0x02,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//"^"
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,	//"_"
        0x00,0x02,0x06,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//"`"
        0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x19,0x24,0x22,0x22,0x22,0x1F,0x20,	//"a"
        0x08,0xF8,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x3F,0x11,0x20,0x20,0x11,0x0E,0x00,	//"b"
        0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x0E,0x11,0x20,0x20,0x20,0x11,0x00,	//"c"
        0x00,0x00,0x00,0x80,0x80,0x88,0xF8,0x00,0x00,0x0E,0x11,0x20,0x20,0x10,0x3F,0x20,	//"d"
        0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x22,0x22,0x22,0x22,0x13,0x00,	//"e"
        0x00,0x80,0x80,0xF0,0x88,0x88,0x88,0x18,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,	//"f"
        0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x6B,0x94,0x94,0x94,0x93,0x60,0x00,	//"g"
        0x08,0xF8,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,	//"h"
        0x00,0x80,0x98,0x98,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,	//"i"
        0x00,0x00,0x00,0x80,0x98,0x98,0x00,0x00,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,	//"j"
        0x08,0xF8,0x00,0x00,0x80,0x80,0x80,0x00,0x20,0x3F,0x24,0x02,0x2D,0x30,0x20,0x00,	//"k"
        0x00,0x08,0x08,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,	//"l"
        0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x20,0x3F,0x20,0x00,0x3F,0x20,0x00,0x3F,	//"m"
        0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,	//"n"
        0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,	//"o"
        0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x00,0x80,0xFF,0xA1,0x20,0x20,0x11,0x0E,0x00,	//"p"
        0x00,0x00,0x00,0x80,0x80,0x00,0x80,0x00,0x00,0x0E,0x11,0x20,0x20,0xA1,0xFF,0x80,	//"q"
        0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x20,0x20,0x3F,0x21,0x20,0x00,0x01,0x00,	//"r"
        0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x13,0x24,0x24,0x24,0x24,0x19,0x00,	//"s"
        0x00,0x80,0x80,0xE0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x1F,0x20,0x20,0x00,0x00,	//"t"
        0x80,0x80,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20,	//"u"
        0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x00,0x01,0x0E,0x30,0x30,0x0E,0x01,0x00,	//"v"
        0x80,0x80,0x00,0x00,0x00,0x80,0x80,0x80,0x0F,0x30,0x0C,0x03,0x0C,0x30,0x0F,0x00,	//"w"
        0x00,0x80,0x80,0x00,0x00,0x80,0x80,0x00,0x00,0x20,0x31,0x0E,0x0E,0x31,0x20,0x00,	//"x"
        0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x80,0x81,0x8E,0x70,0x18,0x06,0x01,0x00,	//"y"
        0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x21,0x30,0x2C,0x22,0x21,0x30,0x00,	//"z"
        0x00,0x00,0x00,0x00,0x80,0x7C,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x3F,0x40,0x40,	//"{"
        0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,	//"|"
        0x00,0x02,0x02,0x7C,0x80,0x00,0x00,0x00,0x00,0x40,0x40,0x3F,0x00,0x00,0x00,0x00,	//"}"
        0x00,0x06,0x01,0x01,0x02,0x02,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//"~"		Index 94
)

SGUI_UINT32 SGUI_Resource_IndexMapper_MiniNum(SGUI_UINT32 uiCode)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_INT					iIndex;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if('0'<=uiCode && uiCode <= '9')
	{
		iIndex = uiCode - '0';
	}
	else
	{
		switch(uiCode)
		{
		case '.':
		{
			iIndex = 10;
			break;
		}
		case '+':
		{
			iIndex = 11;
			break;
		}
		case '-':
		{
			iIndex = 12;
			break;
		}
		case '*':
		{
			iIndex = 13;
			break;
		}
		case '/':
		{
			iIndex = 14;
			break;
		}
		case '(':
		{
			iIndex = 15;
			break;
		}
		case ')':
		{
			iIndex = 16;
			break;
		}
		case ' ': // Space.
		{
			iIndex = 17;
			break;
		}
		case '%':
		{
			iIndex = 18;
			break;
		}
		case '=':
		{
			iIndex = 19;
			break;
		}
		default:
		{
			iIndex = SGUI_INVALID_INDEX;
			break;
		}
		}
	}
	return iIndex;
}

SGUI_UINT32 SGUI_Resource_IndexMapper_Default(SGUI_UINT32 uiCode)
{
    /*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_INT					iIndex;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	// Initialize variable.
	iIndex =				    SGUI_INVALID_INDEX;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((uiCode > 0x19) && (uiCode < 0x7F))
	{
		iIndex = uiCode - (0x20);
	}
	return iIndex;
}

