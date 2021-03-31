/*************************************************************************/
/** Copyright.															**/
/** FileName: SGUI_Text.c												**/
/** Author: XuYulin,Jerry												**/
/** Description: Text display interface									**/
/*************************************************************************/

//=======================================================================//
//= Include files.														=//
//=======================================================================//
#include "SGUI_Text.h"

//=======================================================================//
//= Public variable declaration.										=//
//=======================================================================//
SGUI_CSZSTR		SGUI_EMPTY_STRING = {""};

//=======================================================================//
//= Static function declaration.										=//
//=======================================================================//

//=======================================================================//
//= Function define.													=//
//=======================================================================//
/*************************************************************************/
/** Function Name:	SGUI_Text_GetTextExtent								**/
/** Purpose:		Get the area size if show given text completely.	**/
/** Params:																**/
/**	@ szText[in]:	Text array pointer.									**/
/**	@ pstFontRes[in]: Font resource, improve font size info.			**/
/**	@ pstTextExtent[out]: Text extent size.								**/
/** Return:			Next character X coordinate in current line.		**/
/** Limitation:		None.												**/
/*************************************************************************/
void SGUI_Text_GetTextExtent(SGUI_CSZSTR cszText, const SGUI_FONT_RES* pstFontRes, SGUI_AREA_SIZE* pstTextExtent)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	const SGUI_CHAR*			pcChar;
	SGUI_UINT32					uiCharacterCode;
	SGUI_BMP_RES				stCharBitmap;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	pcChar =					(SGUI_CSZSTR)ENCODE(cszText);

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pcChar) && (NULL != pstTextExtent))
	{
		pstTextExtent->iHeight = pstFontRes->iHeight;
		pstTextExtent->iWidth=0;
		while('\0' != *pcChar)
		{
			uiCharacterCode = 0;
			pcChar = pstFontRes->fnStepNext(pcChar, &uiCharacterCode);
			if('\0' !=uiCharacterCode)
			{
				pstFontRes->fnGetBitmap(&stCharBitmap,uiCharacterCode,true);
				pstTextExtent->iWidth+=stCharBitmap.iWidth;
			}
		}
	}
}

/*************************************************************************/
/** Function Name:	SGUI_Text_DrawSingleLineText						**/
/** Purpose:		Write a single line text in a fixed area.			**/
/** Params:																**/
/**	@ pstDeviceIF[in]:	SimpleGUI object pointer.							**/
/**	@ cszText[in]:	Text array pointer.									**/
/**	@ pstFontRes[in]: Font resource object.								**/
/**	@ pstDisplayArea[in]: Display area size.							**/
/**	@ pstInnerPos[in]: Text paint position in display area.				**/
/**	@ eFontMode[in]	Character display mode(normal or reverse color).	**/
/** Return:			None.												**/
/*************************************************************************/
void SGUI_Text_DrawText(SGUI_SCR_DEV* pstDeviceIF, SGUI_CSZSTR cszText, const SGUI_FONT_RES* pstFontRes, SGUI_RECT* pstDisplayArea, SGUI_POINT* pstInnerPos, SGUI_COLOR eFontColor)
{

	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	const SGUI_CHAR*			pcChar;							// Text character pointer.
	SGUI_UINT32					uiCharacterCode;				// Character byte, might be tow bytes.
	SGUI_BMP_RES				stCharBitmap;
	SGUI_POINT					stPaintPos;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	// Initialize variable.
	pcChar =					(SGUI_CSZSTR)ENCODE(cszText);

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pcChar) && (RECT_X_START(*pstDisplayArea) < RECT_WIDTH(pstDeviceIF->stSize)))
	{
		// Adapt text display area and data area.
		SGUI_Common_AdaptDisplayInfo(pstDisplayArea, pstInnerPos);
		// Initialize drawing area data.
		RECT_X_START(stPaintPos) = RECT_X_START(*pstInnerPos);
		RECT_Y_START(stPaintPos) = RECT_Y_START(*pstInnerPos);
		RECT_HEIGHT(stCharBitmap) = pstFontRes->iHeight;

		// Loop for Each char.
		while(((NULL != pcChar) && ('\0' != *pcChar)) && (RECT_X_START(stPaintPos) < RECT_WIDTH(*pstDisplayArea)))
		{
			uiCharacterCode = 0;
			pcChar = pstFontRes->fnStepNext(pcChar, &uiCharacterCode);
			//if(SGUI_IS_VISIBLE_CHAR(uiCharacterCode))
			{
				#if SGUI_CONF_BMP_DATA_BUFFER_SIZE>0
					stCharBitmap.pData=pstDeviceIF->arrBmpDataBuffer;
				#else
					stCharBitmap.pData=NULL;
				#endif
				pstFontRes->fnGetBitmap(&stCharBitmap,uiCharacterCode,false);
				if((stPaintPos.iX+stCharBitmap.iWidth-1) >= 0)
				{
					SGUI_Basic_DrawAlphaBitMap(pstDeviceIF, pstDisplayArea, &stPaintPos, &stCharBitmap, eFontColor);
				}
				RECT_X_START(stPaintPos) += RECT_WIDTH(stCharBitmap);
			}
		}
	}
}

/*************************************************************************/
/** Function Name:	GUI_DrawMultipleLinesText							**/
/** Purpose:		Write a mulitiplt line text in a rectangular area.	**/
/** Params:																**/
/**	@ pstDeviceIF[in]:	SimpleGUI object pointer.							**/
/**	@ cszText[in]:	Text array pointer.									**/
/**	@ pstFontRes[in]: Font resource object.								**/
/**	@ pstDisplayArea[in]: Display area size.							**/
/**	@ iTopOffset[in]: Text paint offset in vertical.					**/
/**	@ eFontMode[in]: Character display mode(normal or reverse color).	**/
/** Return:			Used line count.									**/
/** Notice:			None.												**/
/*************************************************************************/
SGUI_SIZE SGUI_Text_DrawMultipleLinesText(SGUI_SCR_DEV* pstDeviceIF, SGUI_CSZSTR cszText, const SGUI_FONT_RES* pstFontRes, SGUI_RECT* pstDisplayArea, SGUI_INT iTopOffset, SGUI_COLOR eFontColor)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	const SGUI_CHAR*			pcChar;
	SGUI_UINT32					uiCharacterCode;
	SGUI_SIZE					uiLines;
	SGUI_BMP_RES				stCharBitmap;
	SGUI_POINT					stPaintPos;
	SGUI_INT					iStartOffsetX;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	pcChar =					(SGUI_CSZSTR)ENCODE(cszText);
	uiCharacterCode =			0;
	uiLines =					0;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((cszText != NULL) && (RECT_X_START(*pstDisplayArea) < RECT_WIDTH(pstDeviceIF->stSize)))
	{
		// Initialize drawing position.
		RECT_X_START(stPaintPos) = 0;
		RECT_Y_START(stPaintPos) = iTopOffset;
		// Adapt text display area and data area.
		SGUI_Common_AdaptDisplayInfo(pstDisplayArea, &stPaintPos);
		iStartOffsetX = stPaintPos.iX;

		RECT_HEIGHT(stCharBitmap) = pstFontRes->iHeight;
		uiLines = 1;
		// Loop for each word in display area.
		while(((NULL != pcChar) && ('\0' != *pcChar)))
		{
			uiCharacterCode = 0;
			pcChar = pstFontRes->fnStepNext(pcChar, &uiCharacterCode);

			// Judge change line symbol.
			if(uiCharacterCode == '\n')
			{
				// Change lines.
				RECT_X_START(stPaintPos) = iStartOffsetX;
				RECT_Y_START(stPaintPos) += pstFontRes->iHeight;
				uiLines ++;
				continue;
			}
			#if SGUI_CONF_BMP_DATA_BUFFER_SIZE>0
				stCharBitmap.pData=pstDeviceIF->arrBmpDataBuffer;
			#else
				stCharBitmap.pData=NULL;
			#endif
			pstFontRes->fnGetBitmap(&stCharBitmap,uiCharacterCode,false);

			// Judge change line
			if((stPaintPos.iX+stCharBitmap.iWidth-1) >= RECT_WIDTH(*pstDisplayArea))
			{
				// Change lines.
				RECT_X_START(stPaintPos) = iStartOffsetX;
				RECT_Y_START(stPaintPos) += pstFontRes->iHeight;
				uiLines ++;
			}
			// Draw characters.
			if(((stPaintPos.iX+stCharBitmap.iWidth-1) >= 0) && (RECT_Y_START(stPaintPos) < RECT_HEIGHT(*pstDisplayArea)))
			{
				// Draw character.
				SGUI_Basic_DrawAlphaBitMap(pstDeviceIF, pstDisplayArea, &stPaintPos, &stCharBitmap, eFontColor);
			}
			else
			{
				// character is not in visible area, ignore.
			}
			RECT_X_START(stPaintPos) += RECT_WIDTH(stCharBitmap);
		}
	}
	return uiLines;
}

/*************************************************************************/
/** Function Name:	SGUI_Text_GetMultiLineTextLines						**/
/** Purpose:		Get a string's lines in a fixed width area.			**/
/** Resources:		None.												**/
/** Params:																**/
/**	@ cszText[in]:	Text array pointer.									**/
/**	@ pstFontRes[in]: Font resource object.								**/
/**	@ uiDisplayAreaWidth[in]: Display area width.						**/
/** Return:			String lines.										**/
/*************************************************************************/
SGUI_SIZE SGUI_Text_GetMultiLineTextLines(SGUI_CSZSTR cszText, const SGUI_FONT_RES* pstFontRes, SGUI_SIZE uiDisplayAreaWidth)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_SIZE					uiLineNumber, uiLineLength;
	SGUI_UINT32					uiCharacterCode;
	SGUI_CSZSTR					pcChar;
	SGUI_BMP_RES				stCharBitmap;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	uiLineLength =				0;
	uiLineNumber =				1;
	pcChar =					(SGUI_CSZSTR)ENCODE(cszText);

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	while('\0' != *pcChar)
	{
		uiCharacterCode = 0;
		pcChar = pstFontRes->fnStepNext(pcChar, &uiCharacterCode);
		if('\n' == uiCharacterCode)
		{
			uiLineNumber++;
			uiLineLength = 0;
		}
		else
		{
			pstFontRes->fnGetBitmap(&stCharBitmap,uiCharacterCode,true);
			if((uiLineLength+stCharBitmap.iWidth)>uiDisplayAreaWidth)
			{
				uiLineNumber++;
				uiLineLength  = stCharBitmap.iWidth;
			}
			else
			{
				uiLineLength += stCharBitmap.iWidth;
			}
		}
	}
	return uiLineNumber;
}

/*****************************************************************************/
/** Function Name:	SGUI_Text_StringLength	  							**/
/** Purpose:		Get string length in given font.						**/
/** Params:																	**/
/**	@ cszText[in]:	   String head pointer.   							**/
/**	@ pstFontRes[in]:	Font resource which will be used to parse string.	**/
/** Return:				The char block index inside of the library.		 **/
/*****************************************************************************/
SGUI_SIZE SGUI_Text_StringLength(SGUI_CSZSTR cszText,const SGUI_FONT_RES* pstFontRes)
{
	SGUI_SIZE	   sStrLen=0;
	SGUI_UINT32	 uiCharCode;
	while(*cszText!='\0')
	{
		cszText=pstFontRes->fnStepNext(cszText,&uiCharCode);
		sStrLen++;
	}
	return sStrLen;
}

/*****************************************************************************/
/** Function Name:	SGUI_Text_IndexMapper_Direct							**/
/** Purpose:		Directly use character code as the index while getting  **/
/**				 character index inside the mono space font library.	 **/
/** Params:																	**/
/**	@ uiCode[in]:	   Character code.										**/
/** Return:				The char block index inside of the library.		 **/
/*****************************************************************************/
SGUI_UINT32 SGUI_Text_IndexMapper_Direct(SGUI_UINT32 uiCode)
{
	return uiCode;
}

/*************************************************************************/
/** Function Name:	SGUI_Text_StepNext_ASCII							**/
/** Purpose:		Read current character code order by input pointer  **/
/**				 and step to next character start pointer in ASCII.  **/
/** Resources:		None.												**/
/** Params:																**/
/**	@ cszSrc[in]:	Current char pointer.								**/
/**	@ puiCode[in]:	Character code read from string(ASCII). 			**/
/** Return:			Next character start pointer.   					**/
/*************************************************************************/
SGUI_CSZSTR SGUI_Text_StepNext_ASCII(SGUI_CSZSTR cszSrc, SGUI_UINT32* puiCode)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	const SGUI_CHAR*			pcNextChar;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	pcNextChar =				cszSrc;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pcNextChar)
	{
		*puiCode = *pcNextChar;
		pcNextChar++;
	}

	return pcNextChar;
}

/*************************************************************************/
/** Function Name:	SGUI_Resource_StepNext_GB2312						**/
/** Purpose:		Read current character code order by input pointer  **/
/**				 and step to next character start pointer in GB2312. **/
/** Resources:		None.												**/
/** Params:																**/
/**	@ cszSrc[in]:	Current char pointer.								**/
/**	@ puiCode[out]:	Character code read from string.					**/
/** Return:			Next character start pointer.   					**/
/*************************************************************************/
SGUI_CSZSTR SGUI_Text_StepNext_GB2312(SGUI_CSZSTR cszSrc, SGUI_UINT32* puiCode)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	const SGUI_CHAR*			pcNextChar;
	SGUI_UINT32					uiCode;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	pcNextChar =				cszSrc;
	uiCode =					0;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pcNextChar)
	{
		do
		{
			uiCode = (SGUI_BYTE)(*pcNextChar++);
			if(uiCode < 0x7F)
			{
				break;
			}
			uiCode = uiCode<<8;
			uiCode |= (SGUI_BYTE)(*pcNextChar++);
		}
		while(0);
	}
	*puiCode = uiCode;

	return pcNextChar;
}

/*************************************************************************/
/** Function Name:	SGUI_Resource_StepNext_UTF8 						**/
/** Purpose:		Read current character code order by input pointer  **/
/**				 and step to next character start pointer in UTF8.   **/
/** Resources:		None.												**/
/** Params:																**/
/**	@ cszSrc[in]:	Current char pointer.								**/
/**	@ puiCode[out]:	Character code read from string.					**/
/** Return:			Next character start pointer.   					**/
/*************************************************************************/
SGUI_CSZSTR SGUI_Text_StepNext_UTF8(SGUI_CSZSTR cszSrc, SGUI_UINT32* puiCode)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	const SGUI_CHAR*			pcNextChar;
	SGUI_UINT32					uiCode;
	SGUI_UINT8				  uiTempByte;
	SGUI_UINT8				  uiCharacterLength;
	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	pcNextChar		  = cszSrc;
	uiCode			  = 0;
	uiCharacterLength   = 0;
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pcNextChar)
	{
		uiTempByte = *pcNextChar++;
		if(uiTempByte < 0x7F){
			uiCode = uiTempByte;
		}else{
			while(uiTempByte & 0x80){
				uiCharacterLength ++;
				uiTempByte <<= 1;
			}
			uiCode |= uiTempByte >> uiCharacterLength;
			while((--uiCharacterLength)>0){
				uiCode = (uiCode)<<6 | ((*pcNextChar++) & 0x3F);
			}
		}
	}
	*puiCode = uiCode;
	return pcNextChar;
}
