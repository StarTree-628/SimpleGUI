/*************************************************************************/
/** Copyright.															**/
/** FileName: SGUI_VariableBox.c										**/
/** Author: XuYulin,Jerry													**/
/** Description: Show and change variable box.							**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_VariableBox.h"

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
/*************************************************************************/
/** Function Name:	SGUI_NumberVariableBox_Initialize					**/
/** Purpose:		Initialize a integer value edit box structure.		**/
/** Params:																**/
/**	@ pstObj[in]:	Number variable box object pointer.					**/
/**	@ pcstInitParam[in]: Initialize parameter for initialize.			**/
/** Return:			None.												**/
/** Notice:			iValue will be changed when more then max value or	**/
/**					less then minimum value.							**/
/*************************************************************************/
void SGUI_NumberVariableBox_Initialize(SGUI_NUM_VARBOX_STRUCT* pstObj, const SGUI_NUM_VARBOX_PARAM* pcstInitParam)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pstObj) && (NULL != pcstInitParam))
	{
		SGUI_SystemIF_MemorySet(pstObj, 0x00, sizeof(SGUI_NUM_VARBOX_STRUCT));
		SGUI_SystemIF_MemoryCopy(&(pstObj->stParam), (void*)pcstInitParam, sizeof(SGUI_NUM_VARBOX_PARAM));
        pstObj->stData.iFocused=SGUI_FALSE;
	}
}

/*************************************************************************/
/** Function Name:	SGUI_NumberVariableBox_Repaint						**/
/** Purpose:		Display or refresh a integer value edit box.		**/
/** Params:																**/
/**	@ pstDeviceIF[in]:	Device driver object pointer.					**/
/**	@ pstObj[in]:	Value structure, include max value, min value and	**/
/**					current value.										**/
/**	@ eMode[in]:	Display mode, normal or reveres.					**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_NumberVariableBox_Repaint(SGUI_SCR_DEV* pstDeviceIF, SGUI_NUM_VARBOX_STRUCT* pstObj)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_AREA_SIZE				stTextExtentSize;
	SGUI_POINT					stTextInnerPos;
	SGUI_CHAR					szTextBuffer[VARBOX_TEXT_BUFFER_SIZE];
	SGUI_VARBOX_PALETTE*        pstPalette;
	SGUI_VARBOX_SUB_PALETTE*    pstSubPalette;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	SGUI_SystemIF_MemorySet(szTextBuffer, 0x00, VARBOX_TEXT_BUFFER_SIZE);

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/

	if(NULL != pstObj)
	{
        pstPalette = &(pstObj->stParam.stPalette);
        #ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
        // Mapping Color
        if(pstPalette->uiDepthBits != pstDeviceIF->uiDepthBits)
        {
            pstPalette->stNormal.eBackgroundColor   = SGUI_Basic_MapColor(pstPalette->uiDepthBits,pstPalette->stNormal.eBackgroundColor,pstDeviceIF->uiDepthBits);
            pstPalette->stNormal.eTextColor         = SGUI_Basic_MapColor(pstPalette->uiDepthBits,pstPalette->stNormal.eTextColor,pstDeviceIF->uiDepthBits);
            pstPalette->stFocus.eBackgroundColor    = SGUI_Basic_MapColor(pstPalette->uiDepthBits,pstPalette->stFocus.eBackgroundColor,pstDeviceIF->uiDepthBits);
            pstPalette->stFocus.eTextColor          = SGUI_Basic_MapColor(pstPalette->uiDepthBits,pstPalette->stFocus.eTextColor,pstDeviceIF->uiDepthBits);
            pstPalette->uiDepthBits                 = pstDeviceIF->uiDepthBits;
        }
        #endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
        // select sub palette
        pstSubPalette = pstObj->stData.iFocused ? &(pstPalette->stFocus) : &(pstPalette->stNormal);

		// Draw edge
		SGUI_Basic_DrawRectangle(pstDeviceIF, LAYOUT(pstObj).iX, LAYOUT(pstObj).iY, LAYOUT(pstObj).iWidth, LAYOUT(pstObj).iHeight, pstSubPalette->eBackgroundColor, pstSubPalette->eBackgroundColor);

		// Convert number to string
		(void)SGUI_Common_IntegerToString(pstObj->stData.iValue, szTextBuffer, 10, -1, ' ');
		SGUI_Text_GetTextExtent(szTextBuffer, pstObj->stParam.pstFontRes, &stTextExtentSize);
		switch(pstObj->stParam.eAlignment)
		{
			case SGUI_RIGHT:
			{
				stTextInnerPos.iX = LAYOUT(pstObj).iWidth - stTextExtentSize.iWidth;
				break;
			}
			case SGUI_CENTER:
			{
				stTextInnerPos.iX = (LAYOUT(pstObj).iWidth - stTextExtentSize.iWidth) / 2;
				break;
			}
			default:
			{
				stTextInnerPos.iX = 0;
			}
		}
		stTextInnerPos.iY = 0;
		SGUI_Basic_DrawRectangle(pstDeviceIF, LAYOUT(pstObj).iX,LAYOUT(pstObj).iY,LAYOUT(pstObj).iWidth,LAYOUT(pstObj).iHeight,pstSubPalette->eBackgroundColor,pstSubPalette->eBackgroundColor);
		SGUI_Text_DrawText(pstDeviceIF, szTextBuffer, pstObj->stParam.pstFontRes, &(LAYOUT(pstObj)), &stTextInnerPos, pstSubPalette->eTextColor);
	}
}

/*************************************************************************/
/** Function Name:	SGUI_TextVariableBox_Initialize						**/
/** Purpose:		Initialize a text value edit box structure.			**/
/** Params:																**/
/**	@ pstObj[in]:	Text variable box object pointer.					**/
/**	@ pcstInitParam[in]: Parameter data for initialize.					**/
/**	@ szTextBuffer[in]: Text buffer for text variable.					**/
/** Return:			None.												**/
/** Notice:			TextBuffer length cannot less then sMaxTextLength.	**/
/*************************************************************************/
void SGUI_TextVariableBox_Initialize(SGUI_TEXT_VARBOX_STRUCT* pstObj, const SGUI_TEXT_VARBOX_PARAM* pcstInitParam, SGUI_SZSTR szTextBuffer)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pstObj) && (NULL != pcstInitParam))
	{
		SGUI_SystemIF_MemorySet(pstObj, 0x00, sizeof(SGUI_TEXT_VARBOX_STRUCT));
		SGUI_SystemIF_MemoryCopy(&(pstObj->stParam), (void*)pcstInitParam, sizeof(SGUI_TEXT_VARBOX_PARAM));
		pstObj->stData.szValue = szTextBuffer;
	}
}

/*************************************************************************/
/** Function Name:	SGUI_TextVariableBox_Paint							**/
/** Purpose:		Display or refresh a integer value edit box.		**/
/** Params:																**/
/**	@ pstDeviceIF[in]: Device driver object pointer.					**/
/** @ pstObj[in]:	Text value edit box pointer.						**/
/** @ cNewCharacters[in]: New character of value.						**/
/**	@ eMode[in]:			Display mode, normal or reveres.			**/
/** Return:			None.												**/
/** Notice:			Static function, call by others interface.			**/
/*************************************************************************/
void SGUI_TextVariableBox_Repaint(SGUI_SCR_DEV* pstDeviceIF, SGUI_TEXT_VARBOX_STRUCT* pstObj)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_POINT					stTextInnerPos;
	SGUI_RECT					stFocusArea;
	SGUI_SIZE					uiTextLength, uiFocusIndexMax;
	SGUI_SZSTR					pstStrPointer;
    SGUI_SIZE					uiTextIndex;
    SGUI_UINT32					uiCharCode;
    SGUI_BMP_RES				stBmpRes;
    SGUI_VARBOX_PALETTE*		pstPalette;
    SGUI_VARBOX_SUB_PALETTE*	pstNormalPalette;
	SGUI_VARBOX_SUB_PALETTE*	pstFocusPalette;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pstObj) && (NULL != pstObj->stData.szValue))
	{
        pstPalette = &(pstObj->stParam.stPalette);
        #ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
        // Mapping Color
        if(pstPalette->uiDepthBits != pstDeviceIF->uiDepthBits)
        {
            pstPalette->stNormal.eBackgroundColor   = SGUI_Basic_MapColor(pstPalette->uiDepthBits,pstPalette->stNormal.eBackgroundColor,pstDeviceIF->uiDepthBits);
            pstPalette->stNormal.eTextColor         = SGUI_Basic_MapColor(pstPalette->uiDepthBits,pstPalette->stNormal.eTextColor,pstDeviceIF->uiDepthBits);
            pstPalette->stFocus.eBackgroundColor    = SGUI_Basic_MapColor(pstPalette->uiDepthBits,pstPalette->stFocus.eBackgroundColor,pstDeviceIF->uiDepthBits);
            pstPalette->stFocus.eTextColor          = SGUI_Basic_MapColor(pstPalette->uiDepthBits,pstPalette->stFocus.eTextColor,pstDeviceIF->uiDepthBits);
            pstPalette->uiDepthBits                 = pstDeviceIF->uiDepthBits;
        }
        #endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED

        pstNormalPalette    = &(pstPalette->stNormal);
        pstFocusPalette     = &(pstPalette->stFocus);

		// Clear background.
		SGUI_Basic_DrawRectangle(pstDeviceIF, LAYOUT(pstObj).iX, LAYOUT(pstObj).iY, LAYOUT(pstObj).iWidth, LAYOUT(pstObj).iHeight, pstNormalPalette->eBackgroundColor, pstNormalPalette->eBackgroundColor);

		// Get max text length and graphics width.
		uiFocusIndexMax = pstObj->stParam.sTextLengthMax-1;
		// Ignore too long text string.
		uiTextLength = SGUI_Text_StringLength(pstObj->stData.szValue,pstObj->stParam.pstFontRes);
		if(uiTextLength > pstObj->stParam.sTextLengthMax)
		{
			uiTextLength = pstObj->stParam.sTextLengthMax;
			pstStrPointer= ENCODE(pstObj->stData.szValue);
            while(uiTextLength-->0)
			{
				pstStrPointer = (SGUI_SZSTR)pstObj->stParam.pstFontRes->fnStepNext(pstStrPointer,&uiCharCode);
			}
			*(pstStrPointer) = '\0';
			// Point at to last character position if index is more then string length.
			pstObj->stData.sFocusIndex = SGUI_MIN_OF(uiFocusIndexMax,pstObj->stData.sFocusIndex);
		}
		// Set text display area.
		stTextInnerPos.iX = 0;
		stTextInnerPos.iY = 0;
		// Set focus character area.
		stFocusArea.iX = LAYOUT(pstObj).iX;
		stFocusArea.iY = LAYOUT(pstObj).iY;
		pstStrPointer = (SGUI_SZSTR)ENCODE(pstObj->stData.szValue);
		stFocusArea.iWidth  = 0;
		stFocusArea.iHeight = pstObj->stParam.pstFontRes->iHeight;
		uiTextIndex = 0;
		do
		{
            uiTextIndex++;
            pstStrPointer=(SGUI_SZSTR)pstObj->stParam.pstFontRes->fnStepNext(pstStrPointer,&uiCharCode);
            #if SGUI_CONF_BMP_DATA_BUFFER_SIZE>0
                stBmpRes.pData = pstDeviceIF->arrBmpDataBuffer;
            #else
                stBmpRes.pData=NULL;
			#endif
            pstObj->stParam.pstFontRes->fnGetBitmap(&stBmpRes,uiCharCode,(uiTextIndex<pstObj->stData.sFocusIndex));
            stFocusArea.iX += stFocusArea.iWidth;
            stFocusArea.iWidth = stBmpRes.iWidth;
        }
        while(uiTextIndex <= pstObj->stData.sFocusIndex);

		if(RECT_X_END(stFocusArea) > RECT_X_END(LAYOUT(pstObj)))
		{
			stTextInnerPos.iX = RECT_X_END(LAYOUT(pstObj)) - RECT_X_END(stFocusArea);
			stFocusArea.iX = stFocusArea.iX + stTextInnerPos.iX;
		}
		// Display text normally.
		SGUI_Text_DrawText(pstDeviceIF, pstObj->stData.szValue, pstObj->stParam.pstFontRes, &LAYOUT(pstObj), &stTextInnerPos, pstNormalPalette->eTextColor);

		// Focus character.
        if(pstObj->stData.iFocused)
		{
			stTextInnerPos.iX = 0;
			stTextInnerPos.iY = 0;

			SGUI_Basic_DrawRectangle(pstDeviceIF, stFocusArea.iX,stFocusArea.iY,stFocusArea.iWidth,stFocusArea.iHeight,pstFocusPalette->eBackgroundColor,pstFocusPalette->eBackgroundColor);
			SGUI_Basic_DrawAlphaBitMap(pstDeviceIF,&stFocusArea,&stTextInnerPos,&stBmpRes,pstFocusPalette->eTextColor);
		}
	}
}
