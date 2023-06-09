/*************************************************************************/
/** Copyright.                                                          **/
/** FileName: SGUI_VariableBox.c                                        **/
/** Author: XuYulin                                                     **/
/** Description: Show and change variable box.                          **/
/*************************************************************************/

//=======================================================================//
//= Include files.                                                      =//
//=======================================================================//
#include "SGUI_VariableBox.h"

//=======================================================================//
//= Global variable declaration.                                        =//
//=======================================================================//


//=======================================================================//
//= Static function declaration.                                        =//
//=======================================================================//
static void SGUI_TextVariableBox_UpdateFocusCharIndex(SGUI_TEXT_VARBOX_STRUCT* pstObj);

//=======================================================================//
//= Function define.                                                    =//
//=======================================================================//
/*************************************************************************/
/** Function Name:  SGUI_NumberVariableBox_Initialize                   **/
/** Purpose:        Initialize a integer value edit box structure.      **/
/** Params:                                                             **/
/** @ pstObj[in]:   Number variable box object pointer.                 **/
/** @ pcstInitParam[in]: Initialize parameter for initialize.           **/
/** Return:         None.                                               **/
/** Notice:         iValue will be changed when more then max value or  **/
/**                 less then minimum value.                            **/
/*************************************************************************/
void SGUI_NumberVariableBox_Initialize(SGUI_NUM_VARBOX_STRUCT* pstObj, const SGUI_NUM_VARBOX_PARAM* pcstInitParam)
{
    /*----------------------------------*/
    /* Process                          */
    /*----------------------------------*/
    if((NULL != pstObj) && (NULL != pcstInitParam))
    {
        SGUI_SystemIF_MemorySet(pstObj, 0x00, sizeof(SGUI_NUM_VARBOX_STRUCT));
        SGUI_SystemIF_MemoryCopy(&(pstObj->stParam), (void*)pcstInitParam, sizeof(SGUI_NUM_VARBOX_PARAM));
    }
}

/*************************************************************************/
/** Function Name:  SGUI_NumberVariableBox_Repaint                      **/
/** Purpose:        Display or refresh a integer value edit box.        **/
/** Params:                                                             **/
/** @ pstDeviceIF[in]:  Device driver object pointer.                   **/
/** @ pstObj[in]:   Value structure, include max value, min value and   **/
/**                 current value.                                      **/
/** @ eMode[in]:    Display mode, normal or reveres.                    **/
/** Return:         None.                                               **/
/** Notice:         None.                                               **/
/*************************************************************************/
void SGUI_NumberVariableBox_Repaint(SGUI_SCR_DEV* pstDeviceIF, SGUI_NUM_VARBOX_STRUCT* pstObj, SGUI_DRAW_MODE eMode)
{
    /*----------------------------------*/
    /* Variable Declaration             */
    /*----------------------------------*/
    SGUI_AREA_SIZE      stTextExtentSize;
    SGUI_INT            iPaintX, iPaintY;
    SGUI_COLOR          eBackColor = ((eMode==SGUI_DRAW_NORMAL)?SGUI_COLOR_BKGCLR:SGUI_COLOR_FRGCLR);
    SGUI_CHAR           szTextBuffer[VARBOX_TEXT_BUFFER_SIZE];

    /*----------------------------------*/
    /* Initialize                       */
    /*----------------------------------*/
    SGUI_SystemIF_MemorySet(szTextBuffer, 0x00, VARBOX_TEXT_BUFFER_SIZE);

    /*----------------------------------*/
    /* Process                          */
    /*----------------------------------*/

    if(NULL != pstObj)
    {
        /* Set mask area */
        SGUI_Basic_SetMask4(pstDeviceIF, &(pstObj->stParam.stLayout));
        // Clean background
        SGUI_Basic_DrawRectangle3(pstDeviceIF, &(LAYOUT(pstObj)), eBackColor, eBackColor);
        // Convert number to string
        (void)SGUI_Common_IntegerToString(pstObj->stData.iValue, szTextBuffer, 10, -1, ' ');
        SGUI_Text_GetTextExtent(szTextBuffer, pstObj->stParam.pstFontRes, &stTextExtentSize);
        switch(pstObj->stParam.eAlignment)
        {
            case SGUI_RIGHT:
            {
                iPaintX = LAYOUT(pstObj).iX + LAYOUT(pstObj).iWidth - stTextExtentSize.iWidth;
                break;
            }
            case SGUI_CENTER:
            {
                iPaintX = LAYOUT(pstObj).iX + (LAYOUT(pstObj).iWidth - stTextExtentSize.iWidth) / 2;
                break;
            }
            default:
            {
                iPaintX = LAYOUT(pstObj).iX;
            }
        }
        iPaintY = LAYOUT(pstObj).iY+(LAYOUT(pstObj).iHeight - pstObj->stParam.pstFontRes->iHeight);
        SGUI_Text_DrawText(pstDeviceIF, szTextBuffer, pstObj->stParam.pstFontRes, iPaintX, iPaintY, eMode);
    }
}

/*************************************************************************/
/** Function Name:  SGUI_TextVariableBox_Initialize                     **/
/** Purpose:        Initialize a text value edit box structure.         **/
/** Params:                                                             **/
/** @ pstObj[in]:   Text variable box object pointer.                   **/
/** @ pcstInitParam[in]: Parameter data for initialize.                 **/
/** @ szTextBuffer[in]: Text buffer for text variable.                  **/
/** Return:         None.                                               **/
/** Notice:         TextBuffer length cannot less then sMaxTextLength.  **/
/*************************************************************************/
void SGUI_TextVariableBox_Initialize(SGUI_TEXT_VARBOX_STRUCT* pstObj, const SGUI_TEXT_VARBOX_PARAM* pcstInitParam, SGUI_SZSTR szTextBuffer)
{
    /*----------------------------------*/
    /* Process                          */
    /*----------------------------------*/
    if((NULL != pstObj) && (NULL != pcstInitParam))
    {
        SGUI_SystemIF_MemorySet(pstObj, 0x00, sizeof(SGUI_TEXT_VARBOX_STRUCT));
        SGUI_SystemIF_MemoryCopy(&(pstObj->stParam), (void*)pcstInitParam, sizeof(SGUI_TEXT_VARBOX_PARAM));
        pstObj->stData.szValue = szTextBuffer;
        pstObj->stData.iVisibleCharNum = (pstObj->stParam.stLayout.iWidth - 1)/pstObj->stParam.pstFontRes->iHalfWidth + 1;
        pstObj->stData.iFirstVisibleIndex = 0;
		pstObj->stData.iLastVisibleIndex = pstObj->stData.iVisibleCharNum - 1;
		if(pstObj->stData.iLastVisibleIndex >= pstObj->stParam.iTextLength)
		{
			pstObj->stData.iLastVisibleIndex = pstObj->stParam.iTextLength - 1;
		}
        pstObj->stData.iFocusCharIndex = -1;
        for(SGUI_INT iCharIdx=0; iCharIdx<pstObj->stParam.stCharSet.iSize; iCharIdx++)
        {
            if(pstObj->stData.szValue[0] == pstObj->stParam.stCharSet.cszCharSet[iCharIdx])
            {
                pstObj->stData.iFocusCharIndex = iCharIdx;
                break;
            }
        }
		pstObj->stData.iOffset = 0;
    }
}

/*************************************************************************/
/** Function Name:  SGUI_TextVariableBox_UpdateFocusCharIndex           **/
/** Purpose:        Inner function, used for match and update focused   **/
/**                 character index in char-set.                        **/
/** Params:                                                             **/
/** @ pstObj[in]:   Text value edit box pointer.                        **/
/** Return:         None.                                               **/
/** Notice:         Focused char index will set to -1 if char is not in **/
/**                 char-set.                                           **/
/*************************************************************************/
static void SGUI_TextVariableBox_UpdateFocusCharIndex(SGUI_TEXT_VARBOX_STRUCT* pstObj)
{
    /*----------------------------------*/
    /* Process                          */
    /*----------------------------------*/
    pstObj->stData.iFocusCharIndex = VARBOX_TEXT_INVALID_CHAR_IDX;
    for(SGUI_INT iCharIdx=0; iCharIdx<pstObj->stParam.stCharSet.iSize; iCharIdx++)
    {
        if(pstObj->stParam.stCharSet.cszCharSet[iCharIdx] == pstObj->stData.szValue[pstObj->stData.iFocusIndex])
        {
            pstObj->stData.iFocusCharIndex = iCharIdx;
            break;
        }
    }
}

/*************************************************************************/
/** Function Name:  SGUI_TextVariableBox_Paint                          **/
/** Purpose:        Display or refresh a integer value edit box.        **/
/** Params:                                                             **/
/** @ pstDeviceIF[in]: Device driver object pointer.                    **/
/** @ pstObj[in]:   Text value edit box pointer.                        **/
/** @ cNewCharacters[in]: New character of value.                       **/
/** @ cMask[in]:    Mask character, unfocused characters are displayed  **/
/**                 as this character if this is not '\0'.              **/
/** @ eMode[in]:    Display mode, normal or reveres.                    **/
/** Return:         None.                                               **/
/** Notice:         If cMask is not '\0', all of unfocused character    **/
/**                 will displayed as cMask character. This is usually  **/
/**                 used when entering a password.                      **/
/*************************************************************************/
void SGUI_TextVariableBox_Repaint(SGUI_SCR_DEV* pstDeviceIF, SGUI_TEXT_VARBOX_STRUCT* pstObj, SGUI_CHAR cMask, SGUI_DRAW_MODE eMode)
{
    /*----------------------------------*/
    /* Variable Declaration             */
    /*----------------------------------*/
    SGUI_COLOR              eBackColor = ((eMode==SGUI_DRAW_NORMAL)?SGUI_COLOR_BKGCLR:SGUI_COLOR_FRGCLR);
    SGUI_INT                iCharPosX;
    SGUI_INT				iCharIdx;
    SGUI_CHAR				cPaintChar;

    /*----------------------------------*/
    /* Process                          */
    /*----------------------------------*/
    if((NULL != pstObj) && (NULL != pstObj->stData.szValue))
    {
        // Clear background.
        SGUI_Basic_DrawRectangle3(pstDeviceIF, &(LAYOUT(pstObj)), eBackColor, eBackColor);

        if(pstObj->stData.iFocusIndex >= pstObj->stParam.iTextLength)
		{
			/* Focus character index cannot greater then ending index. */
			pstObj->stData.iFocusIndex = pstObj->stParam.iTextLength - 1;
		}
		else if(pstObj->stData.iFocusIndex < 0)
		{
			pstObj->stData.iFocusIndex = 0;
		}
		/* Update first & last visible character index. */
		if(pstObj->stData.iFocusIndex > pstObj->stData.iLastVisibleIndex)
		{
			pstObj->stData.iLastVisibleIndex = pstObj->stData.iFocusIndex;
			pstObj->stData.iFirstVisibleIndex = pstObj->stData.iLastVisibleIndex - pstObj->stData.iVisibleCharNum + 1;

		}
        else if(pstObj->stData.iFocusIndex < pstObj->stData.iFirstVisibleIndex)
		{
			pstObj->stData.iFirstVisibleIndex = pstObj->stData.iFocusIndex;
			pstObj->stData.iLastVisibleIndex = pstObj->stData.iFirstVisibleIndex + pstObj->stData.iVisibleCharNum - 1;
		}
		/* Setup display offset. */
		if(pstObj->stParam.iTextLength < pstObj->stData.iVisibleCharNum)
		{
			pstObj->stData.iOffset = 0;
		}
		else if(pstObj->stData.iFocusIndex == pstObj->stData.iLastVisibleIndex)
		{
			pstObj->stData.iOffset = ((pstObj->stParam.stLayout.iWidth % pstObj->stParam.pstFontRes->iHalfWidth) - pstObj->stParam.pstFontRes->iHalfWidth)%pstObj->stParam.pstFontRes->iHalfWidth;
		}
		else if (pstObj->stData.iFocusIndex == pstObj->stData.iFirstVisibleIndex)
		{
			pstObj->stData.iOffset = 0;
		}
		/* Prepare paint text position. */
        iCharPosX = pstObj->stParam.stLayout.iX + pstObj->stData.iOffset;

        /* Set mask */
        SGUI_Basic_SetMask4(pstDeviceIF, &(pstObj->stParam.stLayout));
        /* Loop for paint each visible character. */
        iCharIdx = pstObj->stData.iFirstVisibleIndex;
        while((pstObj->stData.szValue[iCharIdx] != '\0') && (iCharPosX < SGUI_RECT_X_END(LAYOUT(pstObj))))
		{
			cPaintChar = ('\0' == cMask)?pstObj->stData.szValue[iCharIdx]:(iCharIdx == pstObj->stData.iFocusIndex)?pstObj->stData.szValue[iCharIdx]:cMask;
			if(eMode==SGUI_DRAW_NORMAL)
			{
				SGUI_Text_DrawASCIICharacter(pstDeviceIF, cPaintChar, pstObj->stParam.pstFontRes, iCharPosX, LAYOUT(pstObj).iY, (iCharIdx == pstObj->stData.iFocusIndex)?SGUI_DRAW_REVERSE:SGUI_DRAW_NORMAL);
			}
			else
			{
				SGUI_Text_DrawASCIICharacter(pstDeviceIF, cPaintChar, pstObj->stParam.pstFontRes, iCharPosX, LAYOUT(pstObj).iY, (iCharIdx == pstObj->stData.iFocusIndex)?SGUI_DRAW_NORMAL:SGUI_DRAW_REVERSE);
			}
			iCharPosX += pstObj->stParam.pstFontRes->iHalfWidth;
			iCharIdx++;
		}
		/* Reset mask */
		SGUI_Basic_ResetMask(pstDeviceIF);
    }
}

/*************************************************************************/
/** Function Name:  SGUI_TextVariableBox_SetFocusIndex                  **/
/** Purpose:        Set a character focus according to given index.     **/
/** Params:                                                             **/
/** @ pstObj[in]:   Text value edit box pointer.                        **/
/** @ iNewFocus[in]: New focus index, means character index in c-style  **/
/**                 string.                                             **/
/** Return:         None.                                               **/
/*************************************************************************/
void SGUI_TextVariableBox_SetFocusIndex(SGUI_TEXT_VARBOX_STRUCT* pstObj, SGUI_INT iNewFocus)
{
    /*----------------------------------*/
    /* Process                          */
    /*----------------------------------*/
    if((NULL != pstObj) && (NULL != pstObj->stData.szValue))
    {
        if(iNewFocus < pstObj->stParam.iTextLength)
        {
            pstObj->stData.iFocusIndex = iNewFocus;
            SGUI_TextVariableBox_UpdateFocusCharIndex(pstObj);
        }
    }
}

/*************************************************************************/
/** Function Name:  SGUI_TextVariableBox_IncreaseChar                   **/
/** Purpose:        Replace the focused character to next in char-set.  **/
/** Params:                                                             **/
/** @ pstObj[in]:   Text value edit box pointer.                        **/
/** Return:         None.                                               **/
/** Notice:         Focused char will replace to the first char if it   **/
/**                 is the last in char set.                            **/
/*************************************************************************/
void SGUI_TextVariableBox_IncreaseChar(SGUI_TEXT_VARBOX_STRUCT* pstObj)
{
    /*----------------------------------*/
    /* Process                          */
    /*----------------------------------*/
    if((NULL != pstObj) && (NULL != pstObj->stData.szValue))
    {
        if(VARBOX_TEXT_INVALID_CHAR_IDX == pstObj->stData.iFocusCharIndex)
        {
            pstObj->stData.iFocusCharIndex = 0;

        }
        else
        {
            ++(pstObj->stData.iFocusCharIndex);
            pstObj->stData.iFocusCharIndex = pstObj->stData.iFocusCharIndex % pstObj->stParam.stCharSet.iSize;
        }
        pstObj->stData.szValue[pstObj->stData.iFocusIndex] = pstObj->stParam.stCharSet.cszCharSet[pstObj->stData.iFocusCharIndex];
    }
}

/*************************************************************************/
/** Function Name:  SGUI_TextVariableBox_DecreaseChar                   **/
/** Purpose:        Replace the focused character to previous in char-  **/
/**                 set.                                                **/
/** Params:                                                             **/
/** @ pstObj[in]:   Text value edit box pointer.                        **/
/** Return:         None.                                               **/
/** Notice:         Focused char will replace to the last char if it    **/
/**                 is the first in char set.                           **/
/*************************************************************************/
void SGUI_TextVariableBox_DecreaseChar(SGUI_TEXT_VARBOX_STRUCT* pstObj)
{
    /*----------------------------------*/
    /* Process                          */
    /*----------------------------------*/
    if((NULL != pstObj) && (NULL != pstObj->stData.szValue))
    {
        if(VARBOX_TEXT_INVALID_CHAR_IDX == pstObj->stData.iFocusCharIndex)
        {
            pstObj->stData.iFocusCharIndex = pstObj->stParam.stCharSet.iSize - 1;
            pstObj->stData.szValue[pstObj->stData.iFocusIndex] = pstObj->stParam.stCharSet.cszCharSet[pstObj->stData.iFocusCharIndex];
        }
        else
        {
            if(0 == pstObj->stData.iFocusCharIndex)
            {
                pstObj->stData.iFocusCharIndex = pstObj->stParam.stCharSet.iSize-1;
            }
            else
            {
                --(pstObj->stData.iFocusCharIndex);
            }
        }
        pstObj->stData.szValue[pstObj->stData.iFocusIndex] = pstObj->stParam.stCharSet.cszCharSet[pstObj->stData.iFocusCharIndex];
    }
}
