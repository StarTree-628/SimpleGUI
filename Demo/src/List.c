/*************************************************************************/
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
#include "HMI_Engine.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define					NOTICE_TEXT_BUFFER_SIZE				(64)

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static HMI_ENGINE_RESULT	HMI_DemoList_Initialize(void);
static HMI_ENGINE_RESULT	HMI_DemoList_Prepare(const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoList_RefreshScreen(const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoList_ProcessEvent(HMI_EVENT_TYPE eEvent, const HMI_EVENT* pstEvent);
static HMI_ENGINE_RESULT	HMI_DemoList_PostProcess(SGUI_INT iActionResult);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
static SGUI_PCSZSTR     s_szListTitle = 			"测试列表";
static SGUI_PCSZSTR		s_arrszNoticeType[] =		{	"文字消息", "系统时间"};
static SGUI_LIST_ITEM	s_arrstTestListItems[] =	{	{ 0, "简单列表项",			LIST_ITEM_NORMAL,		{0}, 					{0, 0, 0}, NULL},
														{ 1, "枚举类型列表项",		LIST_ITEM_ENUM,			{0, 0, 1},				{0, 0, 0}, s_arrszNoticeType},
														{ 2, "数字列表项",			LIST_ITEM_DIGIT,		{0, -50, 50},			{0, 0, 3}, NULL},
														{ 3, "带小数的数字列表项",	LIST_ITEM_DIGIT,		{1, -50, 50},			{2, 0, 5}, NULL},
														{ 4, "超长文字的简单列表项",	LIST_ITEM_NORMAL,		{0, 0, 0},				{0, 0, 0}, NULL},
														{ 5, "编辑框",				LIST_ITEM_NORMAL,		{0, 0, 0},				{0, 0, 0}, NULL},
														{ 6, "实时曲线",				LIST_ITEM_NORMAL,		{0, 0, 0},				{0, 0, 0}, NULL},
													};

#if (_SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_ > 0)
static SGUI_LIST_ITEM	s_arrstAppendListItems[] =	{	{ 8, "添加项1",				LIST_ITEM_NORMAL,		{0}, 					{0, 0, 0}, NULL},
														{ 9, "添加项2",				LIST_ITEM_ENUM,			{0, 0, 1},				{0, 0, 0}, s_arrszNoticeType},
														{10, "添加项3",				LIST_ITEM_DIGIT,		{0, -50, 50},			{0, 0, 3}, NULL}
													};
#endif

HMI_SCREEN_ACTION		s_stDemoListActions =		{	HMI_DemoList_Initialize,
														HMI_DemoList_Prepare,
														HMI_DemoList_RefreshScreen,
														HMI_DemoList_ProcessEvent,
														HMI_DemoList_PostProcess
													};

static SGUI_LIST_STRUCT	s_stDemoListObject;

static char				s_szNoticeTextBuffer[NOTICE_TEXT_BUFFER_SIZE] = {0x00};

//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN_OBJECT       g_stHMIDemo_List =			{	HMI_SCREEN_ID_DEMO_LIST,
														&s_stDemoListActions
													};

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
HMI_ENGINE_RESULT HMI_DemoList_Initialize(void)
{
#if (_SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_ > 0)
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	uint32_t					i;
#endif

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
    // Initialize list data.
    SGUI_Common_MemorySet(&s_stDemoListObject, 0x00, sizeof(SGUI_LIST_STRUCT));
    // Title and font size must set before initialize list object.
    s_stDemoListObject.Data.Title = s_szListTitle;
    s_stDemoListObject.FontSize = SGUI_FONT_SIZE_H12;
    //Initialize list object.
	SGUI_LIST_InitializeListData(&s_stDemoListObject);
#if (_SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_ > 0)
    s_stDemoListObject.Data.Items = NULL;
    s_stDemoListObject.Data.Count = 0;
    // Insert list item.
    for(i=0; i<(sizeof(s_arrstTestListItems)/sizeof(SGUI_LIST_ITEM)); i++)
	{
        SGUI_LIST_InsertItem(&s_stDemoListObject, &s_arrstTestListItems[i], s_stDemoListObject.Data.Count);
	}
#else
    s_stDemoListObject.Data.Items = s_arrstTestListItems;
    s_stDemoListObject.Data.Count = sizeof(s_arrstTestListItems)/sizeof(SGUI_LIST_ITEM);
#endif
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoList_Prepare (const void* pstParameters)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	SGUI_LIST_RefreshList(&s_stDemoListObject);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoList_RefreshScreen(const void* pstParameters)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	SGUI_LIST_RefreshList(&s_stDemoListObject);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoList_ProcessEvent(HMI_EVENT_TYPE eEvent, const HMI_EVENT* pstEvent)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_ENGINE_RESULT           eProcessResult;
	SGUI_UINT16*				parrKeyValue;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	eProcessResult =			HMI_RET_NORMAL;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(eEvent == HMI_ENGINE_EVENT_ACTION)
	{
		if(NULL != pstEvent)
		{
			parrKeyValue = (SGUI_UINT16*)pstEvent->Data;
			if(NULL != parrKeyValue)
			{
				switch(*(parrKeyValue+1))
				{
					case KEY_VALUE_ENTER:
					{
						eProcessResult = HMI_RET_CONFIRM;
						break;
					}
					case KEY_VALUE_ESC:
					{
						eProcessResult = HMI_RET_CANCEL;
						break;
					}
					case KEY_VALUE_UP:
					{
						SGUI_LIST_SelectUpItem(&s_stDemoListObject);
						break;
					}
					case KEY_VALUE_DOWN:
					{
						SGUI_LIST_SelectDownItem(&s_stDemoListObject);
						break;
					}
					case KEY_VALUE_RIGHT:
					{
						if((*(parrKeyValue+0) & KEY_OPTION_SHIFT) != 0)
						{
							SGUI_LIST_SetListItemValue(&s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex, SGUI_LIST_GetListItemPtr(&s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex)->Valid.Value, SGUI_LIST_GetListItemPtr(&s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex)->Decimal.Value-1);
						}
						else
						{
							SGUI_LIST_SetListItemValue(&s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex, SGUI_LIST_GetListItemPtr(&s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex)->Valid.Value+1, SGUI_LIST_GetListItemPtr(&s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex)->Decimal.Value);
						}
						break;
					}
					case KEY_VALUE_LEFT:
					{
						if((*(parrKeyValue+0) & KEY_OPTION_SHIFT) != 0)
						{
							SGUI_LIST_SetListItemValue(&s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex, SGUI_LIST_GetListItemPtr(&s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex)->Valid.Value, SGUI_LIST_GetListItemPtr(&s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex)->Decimal.Value+1);
						}
						else
						{
							SGUI_LIST_SetListItemValue(&s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex, SGUI_LIST_GetListItemPtr(&s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex)->Valid.Value-1, SGUI_LIST_GetListItemPtr(&s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex)->Decimal.Value);
						}
						break;
					}
#if (_SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_ > 0)
					case KEY_VALUE_F8:
					{
						SGUI_LIST_RemoveItem(&s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex);
						SGUI_LIST_RefreshList(&s_stDemoListObject);
						break;
					}
					case KEY_VALUE_F9:	// Insert to head.
					{
						SGUI_LIST_InsertItem(&s_stDemoListObject, &s_arrstAppendListItems[0], 0);
						SGUI_LIST_RefreshList(&s_stDemoListObject);
						break;
					}
					case KEY_VALUE_F10:	// Insert to intermediate.
					{
						SGUI_LIST_InsertItem(&s_stDemoListObject, &s_arrstAppendListItems[1], 5);
						SGUI_LIST_RefreshList(&s_stDemoListObject);
						break;
					}
					case KEY_VALUE_F11:	// Insert to end.
					{
						SGUI_LIST_InsertItem(&s_stDemoListObject, &s_arrstAppendListItems[2], s_stDemoListObject.Data.Count);
						SGUI_LIST_RefreshList(&s_stDemoListObject);
						break;
					}
#endif
					default:
					{
						break;
					}
				}
			}
		}
	}
	return eProcessResult;
}

HMI_ENGINE_RESULT HMI_DemoList_PostProcess(SGUI_INT iActionResult)
{
	uint32_t			uiSelectListIndex;
	SGUI_LIST_ITEM*		pstSelectedItem;
	int32_t				iListItemParameterValue;

	if(HMI_RET_CONFIRM == iActionResult)
	{
		uiSelectListIndex = s_stDemoListObject.ControlVariable.SelectIndex;
		switch(SGUI_LIST_GetListItemPtr(&s_stDemoListObject, uiSelectListIndex)->Sign)
		{
			case 1:
			{
				// Show notice.
				pstSelectedItem = SGUI_LIST_GetListItemPtr(&s_stDemoListObject, uiSelectListIndex);
				iListItemParameterValue = pstSelectedItem->Valid.Value;
				if(0 == iListItemParameterValue)
				{
					sprintf(s_szNoticeTextBuffer, "选择列表项%u.", uiSelectListIndex);
					HMI_Goto(HMI_SCREEN_ID_DEMO_TEXT_NOTICE, s_szNoticeTextBuffer);
				}
				else
				{
					HMI_Goto(HMI_SCREEN_ID_DEMO_RTC_NOTICE, NULL);
				}
				break;
			}
			case 5:
			{
				HMI_Goto(HMI_SCREEN_ID_DEMO_VARIABLE_BOX, NULL);
				break;
			}
			case 6:
			{
				HMI_Goto(HMI_SCREEN_ID_DEMO_REAL_TIME_GRAPH, NULL);
				break;
			}
			default:
			{
				sprintf(s_szNoticeTextBuffer, "选择列表项%u.", uiSelectListIndex);
				HMI_Goto(HMI_SCREEN_ID_DEMO_TEXT_NOTICE, s_szNoticeTextBuffer);
				break;
			}
		}
	}
	else if(HMI_RET_CANCEL == iActionResult)
	{
		HMI_GoBack(NULL);
	}
	return HMI_RET_NORMAL;
}


