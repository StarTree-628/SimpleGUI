﻿/*************************************************************************/
/** Copyright.															**/
/** FileName: List.c													**/
/** Author: Polarix														**/
/** Version: 1.0.0.0													**/
/** Description: HMI demo for list control interface.					**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "DemoProc.h"
#include "SGUI_List.h"
#include "SGUI_FlashData.h"
#include "HMI_Engine.h"
#include "Resource.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define					NOTICE_TEXT_BUFFER_SIZE				(64)

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static HMI_ENGINE_RESULT	HMI_DemoList_Initialize(SGUI_SCR_DEV* pstIFObj);
static HMI_ENGINE_RESULT	HMI_DemoList_Prepare(SGUI_SCR_DEV* pstIFObj, const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoList_RefreshScreen(SGUI_SCR_DEV* pstIFObj, const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoList_ProcessEvent(SGUI_SCR_DEV* pstIFObj, const HMI_EVENT_BASE* pstEvent, SGUI_INT* piActionID);
static HMI_ENGINE_RESULT	HMI_DemoList_PostProcess(SGUI_SCR_DEV* pstIFObj, HMI_ENGINE_RESULT eProcResult, SGUI_INT iActionID);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
static SGUI_ITEMS_ITEM		s_arrstListItems[] =		{	{"Variable box", NULL},
															{"Real-time Graph", NULL},
															{"啊啊啊", NULL},
															{"额滴神，终于好用了！", NULL},
															{"ぁあぃいぅうぇえぉ", NULL},
															{"ㄅㄆㄇㄈ", NULL},
															{"！@#￥%……&*（）", NULL},
														};
static SGUI_LIST_CONTROL	s_stDemoListObject = 		{0x00};

//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN_ACTION		s_stDemoListActions =			{	HMI_DemoList_Initialize,
															HMI_DemoList_Prepare,
															HMI_DemoList_RefreshScreen,
															HMI_DemoList_ProcessEvent,
															HMI_DemoList_PostProcess
														};
HMI_SCREEN_OBJECT       g_stHMIDemo_List =				{	HMI_SCREEN_ID_DEMO_LIST,
															&s_stDemoListActions
														};

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
HMI_ENGINE_RESULT HMI_DemoList_Initialize(SGUI_SCR_DEV* pstIFObj)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
    // Initialize list data.
    SGUI_SystemIF_MemorySet(&s_stDemoListObject, 0x00, sizeof(SGUI_LIST_CONTROL));
    SGUI_SystemIF_MemorySet(&s_stDemoListObject, 0x00, sizeof(SGUI_LIST_CONTROL));
    // Title and font size must set before initialize list object.
    s_stDemoListObject.stLayout.iPosX = 0;
    s_stDemoListObject.stLayout.iPosY = 0;
    s_stDemoListObject.stLayout.iWidth = 128;
    s_stDemoListObject.stLayout.iHeight = 64;
    s_stDemoListObject.szTitle = "新版测试列表";
     //Initialize list object.
	SGUI_List_Initialize(&s_stDemoListObject, &GB2312_FZXS12);
	SGUI_List_BindItemsData(&s_stDemoListObject, s_arrstListItems, sizeof(s_arrstListItems)/sizeof(SGUI_ITEMS_ITEM));
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoList_Prepare (SGUI_SCR_DEV* pstIFObj, const void* pstParameters)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	SGUI_List_Repaint(pstIFObj, &s_stDemoListObject);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoList_RefreshScreen(SGUI_SCR_DEV* pstIFObj, const void* pstParameters)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	SGUI_List_Repaint(pstIFObj, &s_stDemoListObject);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoList_ProcessEvent(SGUI_SCR_DEV* pstIFObj, const HMI_EVENT_BASE* pstEvent, SGUI_INT* piActionID)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_ENGINE_RESULT           eProcessResult;
	SGUI_UINT16					uiKeyCode;
	SGUI_UINT16					uiKeyValue;
	KEY_PRESS_EVENT*			pstKeyEvent;
	SGUI_INT					iProcessAction;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	eProcessResult =			HMI_RET_NORMAL;
	pstKeyEvent =				(KEY_PRESS_EVENT*)pstEvent;
	iProcessAction =			HMI_DEMO_PROC_NO_ACT;

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
			uiKeyCode = pstKeyEvent->Data.uiKeyValue;
			uiKeyValue = KEY_CODE_VALUE(uiKeyCode);
			switch(uiKeyValue)
			{
				case KEY_VALUE_ENTER:
				{
					iProcessAction = HMI_DEMO_PROC_CONFIRM;
					break;
				}
				case KEY_VALUE_ESC:
				{
					iProcessAction = HMI_DEMO_PROC_CANCEL;
					break;
				}
				case KEY_VALUE_UP:
				{
					if(s_stDemoListObject.stItems.iSelection > 0)
					{
						s_stDemoListObject.stItems.iSelection -= 1;
					}
					SGUI_List_Repaint(pstIFObj, &s_stDemoListObject);
					break;
				}
				case KEY_VALUE_DOWN:
				{
					if(s_stDemoListObject.stItems.iSelection < s_stDemoListObject.stItems.iCount-1)
					{
						s_stDemoListObject.stItems.iSelection += 1;
					}
					SGUI_List_Repaint(pstIFObj, &s_stDemoListObject);
					break;
				}
				default:
				{
					break;
				}
			}
		}
	}
	if(NULL != piActionID)
	{
		*piActionID = iProcessAction;
	}

	return eProcessResult;
}

HMI_ENGINE_RESULT HMI_DemoList_PostProcess(SGUI_SCR_DEV* pstIFObj, HMI_ENGINE_RESULT eProcResult, SGUI_INT iActionID)
{
	if(HMI_DEMO_PROC_CONFIRM == iActionID)
	{
        switch(s_stDemoListObject.stItems.iSelection)
        {
			case 0:
			{
				HMI_SwitchScreen(HMI_SCREEN_ID_DEMO_VARIABLE_BOX, NULL);
				break;
			}
			case 1:
			{
				HMI_SwitchScreen(HMI_SCREEN_ID_DEMO_REAL_TIME_GRAPH, NULL);
				break;
			}
			default:
			{

				/* do nothing. */
			}
        }
	}
	else if(HMI_DEMO_PROC_CANCEL == iActionID)
	{
		HMI_GoBack(NULL);
	}

	return HMI_RET_NORMAL;
}

