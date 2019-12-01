/*************************************************************************/
/** Copyright.															**/
/** FileName: SGUI_Text.c												**/
/** Author: XuYulin														**/
/** Version: 1.0.0.0													**/
/** Description: Text display interface									**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Text.h"

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//

//=======================================================================//
//= Function define.										            =//
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
	const SGUI_CHAR*            pcChar;
	SGUI_UINT32					uiCharacterCode;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	pcChar =				    cszText;

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
			if(SGUI_IS_VISIBLE_CHAR(uiCharacterCode))
			{
                pstTextExtent->iWidth+=(pstFontRes->fnIsFullWidth(uiCharacterCode)?pstFontRes->iFullWidth:pstFontRes->iHalfWidth);
			}
		}
	}
}

/*************************************************************************/
/** Function Name:	SGUI_Text_DrawSingleLineText						**/
/** Purpose:		Write a single line text in a fixed area.			**/
/** Params:																**/
/**	@ pstIFObj[in]:	SimpleGUI object pointer.							**/
/**	@ cszText[in]:	Text array pointer.									**/
/**	@ pstFontRes[in]: Font resource object.								**/
/**	@ pstDisplayArea[in]: Display area size.							**/
/**	@ pstInnerPos[in]: Text paint position in display area.				**/
/**	@ eFontMode[in]	Character display mode(normal or reverse color).	**/
/** Return:			None.												**/
/*************************************************************************/
void SGUI_Text_DrawText(SGUI_SCR_DEV* pstIFObj, SGUI_CSZSTR cszText, const SGUI_FONT_RES* pstFontRes, SGUI_RECT_AREA* pstDisplayArea, SGUI_POINT* pstInnerPos, SGUI_DRAW_MODE eFontMode)
{

	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	const SGUI_CHAR*            pcChar;							// Text character pointer.
	SGUI_UINT32					uiCharacterCode;				// Character byte, might be tow bytes.
	SGUI_COLOR					eBackColor;
	SGUI_BMP_RES				stCharBitmap;
	SGUI_POINT					stPaintPos;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	// Initialize variable.
	pcChar =				    cszText;
	uiCharacterCode =			0x00000000;
	eBackColor =				(eFontMode == SGUI_DRAW_NORMAL)?SGUI_COLOR_BKGCLR:SGUI_COLOR_FRGCLR;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pcChar) && (RECT_X_START(*pstDisplayArea) < RECT_WIDTH(pstIFObj->stSize)))
    {
        // Adapt text display area and data area.
        SGUI_Common_AdaptDisplayInfo(pstDisplayArea, pstInnerPos);
		// Clear text area.
        SGUI_Basic_DrawRectangle(pstIFObj, RECT_X_START(*pstDisplayArea), RECT_Y_START(*pstDisplayArea),
						RECT_WIDTH(*pstDisplayArea), RECT_HEIGHT(*pstDisplayArea),
						eBackColor, eBackColor);
		// Initialize drawing area data.
		RECT_X_START(stPaintPos) = RECT_X_START(*pstInnerPos);
		RECT_Y_START(stPaintPos) = RECT_Y_START(*pstInnerPos);
		RECT_HEIGHT(stCharBitmap) = pstFontRes->iHeight;
		stCharBitmap.pData = pstIFObj->arrBmpDataBuffer;

		// Loop for Each char.
		while(((NULL != pcChar) && ('\0' != *pcChar)) && (RECT_X_START(stPaintPos) < RECT_WIDTH(*pstDisplayArea)))
		{
		    uiCharacterCode = 0;
            pcChar = pstFontRes->fnStepNext(pcChar, &uiCharacterCode);
            if(SGUI_IS_VISIBLE_CHAR(uiCharacterCode))
			{
				RECT_WIDTH(stCharBitmap) = pstFontRes->fnIsFullWidth(uiCharacterCode)?pstFontRes->iFullWidth:pstFontRes->iHalfWidth;
				if(RECT_X_END(stCharBitmap, stPaintPos) >= 0)
				{
					SGUI_Text_GetCharacterData(pstFontRes, uiCharacterCode, pstIFObj->arrBmpDataBuffer, SGUI_BMP_DATA_BUFFER_SIZE);
					SGUI_Basic_DrawBitMap(pstIFObj, pstDisplayArea, &stPaintPos, &stCharBitmap, eFontMode);
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
/**	@ pstIFObj[in]:	SimpleGUI object pointer.							**/
/**	@ cszText[in]:	Text array pointer.									**/
/**	@ pstFontRes[in]: Font resource object.								**/
/**	@ pstDisplayArea[in]: Display area size.							**/
/**	@ iTopOffset[in]: Text paint offset in vertical.					**/
/**	@ eFontMode[in]: Character display mode(normal or reverse color).	**/
/** Return:			Used line count.									**/
/** Notice:			None.												**/
/*************************************************************************/
SGUI_SIZE SGUI_Text_DrawMultipleLinesText(SGUI_SCR_DEV* pstIFObj, SGUI_CSZSTR cszText, const SGUI_FONT_RES* pstFontRes, SGUI_RECT_AREA* pstDisplayArea, SGUI_INT iTopOffset, SGUI_DRAW_MODE eFontMode)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	const SGUI_CHAR*            pcChar;
	SGUI_UINT32					uiCharacterCode;
	SGUI_SIZE					uiLines;
	SGUI_COLOR					eBackColor;
	SGUI_BMP_RES				stCharBitmap;
	SGUI_POINT					stPaintPos;
	SGUI_INT					iStartOffsetX;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	pcChar =					cszText;
	uiCharacterCode =			0;
	uiLines =					0;
	eBackColor =				(eFontMode == SGUI_DRAW_NORMAL)?SGUI_COLOR_BKGCLR:SGUI_COLOR_FRGCLR;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((cszText != NULL) && (RECT_X_START(*pstDisplayArea) < RECT_WIDTH(pstIFObj->stSize)))
	{
		// Initialize drawing position.
		RECT_X_START(stPaintPos) = 0;
		RECT_Y_START(stPaintPos) = iTopOffset;
		// Adapt text display area and data area.
        SGUI_Common_AdaptDisplayInfo(pstDisplayArea, &stPaintPos);
        iStartOffsetX = stPaintPos.iPosX;
		// Clear text area.
        SGUI_Basic_DrawRectangle(pstIFObj,
						RECT_X_START(*pstDisplayArea), RECT_Y_START(*pstDisplayArea),
						RECT_WIDTH(*pstDisplayArea), RECT_HEIGHT(*pstDisplayArea),
						eBackColor, eBackColor);

		RECT_HEIGHT(stCharBitmap) = pstFontRes->iHeight;
		uiLines = 1;
		stCharBitmap.pData = pstIFObj->arrBmpDataBuffer;
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
			// Get character width;
			RECT_WIDTH(stCharBitmap) = pstFontRes->fnIsFullWidth(uiCharacterCode)?pstFontRes->iFullWidth:pstFontRes->iHalfWidth;

			// Judge change line
			if(RECT_X_END(stCharBitmap, stPaintPos) >= RECT_WIDTH(*pstDisplayArea))
			{
				// Change lines.
				RECT_X_START(stPaintPos) = iStartOffsetX;
				RECT_Y_START(stPaintPos) += pstFontRes->iHeight;
				uiLines ++;
			}
			// Draw characters.
			if((RECT_Y_END(stCharBitmap, stPaintPos) >= 0) && (RECT_Y_START(stPaintPos) < RECT_HEIGHT(*pstDisplayArea)))
			{
				// Draw character.
				SGUI_Text_GetCharacterData(pstFontRes, uiCharacterCode, pstIFObj->arrBmpDataBuffer, SGUI_BMP_DATA_BUFFER_SIZE);
                SGUI_Basic_DrawBitMap(pstIFObj, pstDisplayArea, &stPaintPos, &stCharBitmap, eFontMode);
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
	SGUI_UINT16					uiCharWidth;
	SGUI_CSZSTR					pcChar;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	uiLineLength =				0;
	uiLineNumber =				1;
	pcChar =					cszText;

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
			uiCharWidth = pstFontRes->fnIsFullWidth(uiCharacterCode)?pstFontRes->iFullWidth:pstFontRes->iHalfWidth;
            if((uiLineLength+uiCharWidth)>uiDisplayAreaWidth)
			{
				uiLineNumber++;
				uiLineLength = uiCharWidth;
			}
			else
			{
				uiLineLength+=uiCharWidth;
			}
		}
	}
	return uiLineNumber;
}

/*****************************************************************************/
/** Function Name:	SGUI_Text_GetCharacterData								**/
/** Purpose:		Get character data form font resource by char code.     **/
/** Params:																	**/
/**	@ pstFontRes[in]:	Font resource structure pointer.					**/
/**	@ uiCode[in]:       Character code.										**/
/**	@ pDataBuffer[out]:	Buffer for output char data.					    **/
/**	@ sBufferSize[in]:	Output buffer size.             					**/
/** Return:				Number of read data, return 0 when error occurred.  **/
/*****************************************************************************/
SGUI_SIZE SGUI_Text_GetCharacterData(const SGUI_FONT_RES* pstFontRes, SGUI_UINT32 uiCode, SGUI_BYTE* pDataBuffer, SGUI_SIZE sBufferSize)
{
    /*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_SIZE                   sGetDataSize;
	SGUI_SIZE					sReadDataSize;
	SGUI_SIZE                   sDataBlockSize;
	SGUI_SIZE                   sCharIndex;
	SGUI_BOOL                   bIsFullWidth;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	sGetDataSize =              0;
	bIsFullWidth =              SGUI_FALSE;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pstFontRes) && (NULL != pDataBuffer) && (0 != sBufferSize))
    {
		sCharIndex = pstFontRes->fnGetIndex(uiCode);
        if(SGUI_INVALID_INDEX != sCharIndex)
        {
            sDataBlockSize = SGUI_USED_BYTE(pstFontRes->iHeight) * pstFontRes->iHalfWidth;
            sReadDataSize = bIsFullWidth?(sDataBlockSize*2):sDataBlockSize;
            sGetDataSize = pstFontRes->fnGetData(sCharIndex*sDataBlockSize, pDataBuffer, sReadDataSize>sBufferSize?sBufferSize:sReadDataSize);
        }
    }

	return sGetDataSize;
}
