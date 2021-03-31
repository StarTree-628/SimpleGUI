/*************************************************************************/
/** Copyright.															**/
/** FileName: Text.c													**/
/** Author: Polarix														**/
/** Description: HMI demo for text paint interface.						**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "DemoProc.h"
#include "SGUI_Text.h"
#include "SGUI_FontResource.h"
#include "Resource.h"

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static HMI_ENGINE_RESULT	HMI_DemoText_Prepare(SGUI_SCR_DEV* pstDeviceIF, const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoText_RefreshScreen(SGUI_SCR_DEV* pstDeviceIF, const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoText_ProcessEvent(SGUI_SCR_DEV* pstDeviceIF, const HMI_EVENT_BASE* pstEvent, SGUI_INT* piActionID);
static HMI_ENGINE_RESULT	HMI_DemoText_PostProcess(SGUI_SCR_DEV* pstDeviceIF, HMI_ENGINE_RESULT eProcResult, SGUI_INT iActionID);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
HMI_SCREEN_ACTION			s_stDemoTextActions =	{	NULL,
															HMI_DemoText_Prepare,
															HMI_DemoText_RefreshScreen,
															HMI_DemoText_ProcessEvent,
															HMI_DemoText_PostProcess
														};

//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN_OBJECT       g_stHMIDemo_TextPaint =			{	HMI_SCREEN_ID_DEMO_PAINT_TEXT,
															&s_stDemoTextActions
														};

//=======================================================================//
//= Function define.										            =//
//=======================================================================//

HMI_ENGINE_RESULT HMI_DemoText_Prepare (SGUI_SCR_DEV* pstDeviceIF, const void* pstParameters)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstDeviceIF->fnClear)
	{
		pstDeviceIF->fnClear();
	}
	else
	{
		SGUI_Basic_DrawRectangle(pstDeviceIF, 0, 0, pstDeviceIF->stSize.iWidth, pstDeviceIF->stSize.iHeight, SGUI_COLOR_BKGCLR, SGUI_COLOR_BKGCLR);
	}
	HMI_DemoText_RefreshScreen(pstDeviceIF, pstParameters);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoText_RefreshScreen(SGUI_SCR_DEV* pstDeviceIF, const void* pstParameters)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_RECT					stDisplayArea;
	SGUI_POINT					stInnerPos;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	stInnerPos.iX =			0;
	stInnerPos.iY =			0;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	stDisplayArea.iX = 1;
	stDisplayArea.iY = 1;
	stDisplayArea.iWidth = 62;
	stDisplayArea.iHeight = SGUI_FONT(MiniNum).iHeight+1;
	SGUI_Text_DrawText(pstDeviceIF, SCR3_TEXT_MIN_NUM, SGUI_FONT_REF(MiniNum), &stDisplayArea, &stInnerPos, 0x0D);

	stDisplayArea.iY += stDisplayArea.iHeight;
	stDisplayArea.iWidth = 62;
	stDisplayArea.iHeight = SGUI_FONT(FONT_8).iHeight+1;
	SGUI_Text_DrawText(pstDeviceIF, SCR3_TEXT_INNER_8, SGUI_FONT_REF(FONT_8), &stDisplayArea, &stInnerPos, 0x0E);

	stDisplayArea.iY += stDisplayArea.iHeight;
	stDisplayArea.iWidth = 62;
	stDisplayArea.iHeight = SGUI_FONT(FONT_12).iHeight+1;
	SGUI_Text_DrawText(pstDeviceIF, SCR3_TEXT_INNER_12, SGUI_FONT_REF(FONT_12), &stDisplayArea, &stInnerPos, 0x0F);

	stDisplayArea.iY += stDisplayArea.iHeight;
	stDisplayArea.iWidth = 62;
	stDisplayArea.iHeight = SGUI_FONT(FONT_16).iHeight+1;
	SGUI_Basic_DrawRectangle(pstDeviceIF,stDisplayArea.iX,stDisplayArea.iY,stDisplayArea.iWidth,stDisplayArea.iHeight,0x0D,0x0D);
	SGUI_Text_DrawText(pstDeviceIF, SCR3_TEXT_EXTEN_12, SGUI_FONT_REF(GB2312_FZXS12), &stDisplayArea, &stInnerPos, 0x00);

	stDisplayArea.iX = 64;
	stDisplayArea.iY = 1;
	stDisplayArea.iWidth = 62;
	stDisplayArea.iHeight = 62;
	SGUI_Text_DrawMultipleLinesText(pstDeviceIF, SCR3_TEXT_MULTILINE_12, SGUI_FONT_REF(GB2312_FZXS12), &stDisplayArea, 0, 0x0A);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoText_ProcessEvent(SGUI_SCR_DEV* pstDeviceIF, const HMI_EVENT_BASE* pstEvent, SGUI_INT* piActionID)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_ENGINE_RESULT           eProcessResult;
	SGUI_INT					iProcessAction;
	KEY_PRESS_EVENT*			pstKeyEvent;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	eProcessResult =			HMI_RET_NORMAL;
	iProcessAction =			HMI_DEMO_PROC_NO_ACT;
	pstKeyEvent =				(KEY_PRESS_EVENT*)pstEvent;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(pstEvent->iType == EVENT_TYPE_ACTION)
	{
		// Check event is valid.
		if(SGUI_FALSE == HMI_EVENT_SIZE_CHK(*pstKeyEvent, KEY_PRESS_EVENT))
		{
			// Event data is invalid.
			eProcessResult = HMI_RET_INVALID_DATA;
		}
		else if(EVENT_ID_KEY_PRESS == pstEvent->iID)
		{
			iProcessAction = HMI_DEMO_PROC_CANCEL;
		}
	}
	if(NULL != piActionID)
	{
		*piActionID = iProcessAction;
	}

	return eProcessResult;
}

HMI_ENGINE_RESULT HMI_DemoText_PostProcess(SGUI_SCR_DEV* pstDeviceIF, HMI_ENGINE_RESULT eProcResult, SGUI_INT iActionID)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(HMI_PROCESS_SUCCESSFUL(eProcResult))
	{
		if(HMI_DEMO_PROC_CANCEL == iActionID)
		{
			HMI_GoBack(NULL);
		}
	}

	return HMI_RET_NORMAL;
}

