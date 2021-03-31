/*************************************************************************/
/** Copyright.															**/
/** FileName: HMI_Demo04_Graph.c										**/
/** Author: Polarix														**/
/** Version: 1.0.0.0													**/
/** Description: HMI demo for graph interface.							**/
/*************************************************************************/
//=======================================================================//
//= Include files.														=//
//=======================================================================//
#include "DemoProc.h"
#include "Resource.h"
#include "SGUI_Notice.h"
#include "SGUI_VariableBox.h"
#include "SGUI_FontResource.h"
#include "SGUI_IconResource.h"

//=======================================================================//
//= User Macro definition.												=//
//=======================================================================//
#define						TEXT_VARIABLE_LENGTH				(20)

#define						VARIABLE_BOX_WIDTH					(100)
#define						VARIABLE_NUMBER_BOX_HEIGHT			(8)
#define						VARIABLE_TEXT_BOX_HEIGHT			(12)
#define						VARIABLE_BOX_POSX					(10)
#define						VARIABLE_BOX_NUMBER_POSY			(24)
#define						VARIABLE_BOX_TEXT_POSY				(40)
//=======================================================================//
//= Static function declaration.										=//
//=======================================================================//
static HMI_ENGINE_RESULT	HMI_DemoVariableBox_Initialize(SGUI_SCR_DEV* pstDeviceIF);
static HMI_ENGINE_RESULT	HMI_DemoVariableBox_Prepare(SGUI_SCR_DEV* pstDeviceIF, const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoVariableBox_RefreshScreen(SGUI_SCR_DEV* pstDeviceIF, const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoVariableBox_ProcessEvent(SGUI_SCR_DEV* pstDeviceIF, const HMI_EVENT_BASE* pstEvent, SGUI_INT* piActionID);
static HMI_ENGINE_RESULT	HMI_DemoVariableBox_PostProcess(SGUI_SCR_DEV* pstDeviceIF, HMI_ENGINE_RESULT eProcResult, SGUI_INT iActionID);
static void					HMI_DemoVariableBox_DrawFrame(SGUI_SCR_DEV* pstDeviceIF, SGUI_SZSTR szTitle);

//=======================================================================//
//= Static variable declaration.										=//
//=======================================================================//
static SGUI_NUM_VARBOX_STRUCT	s_stNumberVariableBox =		{0x00};
static SGUI_CHAR				s_szTextVariableBuffer[TEXT_VARIABLE_LENGTH+1] = {"ABCDEFG1234567890"};
static SGUI_TEXT_VARBOX_STRUCT	s_stTextVariableBox =		{0x00};
static SGUI_CHAR				s_szDefaultFrameTitle[] =	SCR4_VAR_BOX_TITLE;
static SGUI_SZSTR				s_szFrameTitle =			s_szDefaultFrameTitle;
static SGUI_INT					s_uiFocusedFlag;
static SGUI_CSZSTR				s_szHelpNoticeText =		SCR4_HELP_NOTICE;
static SGUI_INT					s_uiAutoConfirmTimer =		5;
HMI_SCREEN_ACTION				s_stDemoVariableBoxActions = {
																HMI_DemoVariableBox_Initialize,
																HMI_DemoVariableBox_Prepare,
																HMI_DemoVariableBox_RefreshScreen,
																HMI_DemoVariableBox_ProcessEvent,
																HMI_DemoVariableBox_PostProcess,
															};

//=======================================================================//
//= Global variable declaration.										=//
//=======================================================================//
HMI_SCREEN_OBJECT	   		g_stHMIDemo_VariableBox =	{	HMI_SCREEN_ID_DEMO_VARIABLE_BOX,
																&s_stDemoVariableBoxActions
															};

//=======================================================================//
//= Function define.													=//
//=======================================================================//
HMI_ENGINE_RESULT HMI_DemoVariableBox_Initialize(SGUI_SCR_DEV* pstDeviceIF)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_NUM_VARBOX_PARAM	stNumBoxInitParam;
	SGUI_TEXT_VARBOX_PARAM	stTextBoxInitParam;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/


	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	s_uiFocusedFlag = 0;

	stNumBoxInitParam.eAlignment = SGUI_CENTER;
	stNumBoxInitParam.iMin = -50;
	stNumBoxInitParam.iMax = 100;
	stNumBoxInitParam.pstFontRes = SGUI_FONT_REF(FONT_8);
	stNumBoxInitParam.stLayout.iX = VARIABLE_BOX_POSX+2;
	stNumBoxInitParam.stLayout.iY = VARIABLE_BOX_NUMBER_POSY+2;
	stNumBoxInitParam.stLayout.iWidth = pstDeviceIF->stSize.iWidth - (VARIABLE_BOX_POSX*2)-4;
	stNumBoxInitParam.stLayout.iHeight = SGUI_FONT(FONT_8).iHeight;
	#if SGUI_CONF_GRAYSCALE_DEPTH_BITS==1
	stNumBoxInitParam.stPalette.stFocus.eBackgroundColor	= 0x01;
	stNumBoxInitParam.stPalette.stFocus.eTextColor		  = 0x00;
	stNumBoxInitParam.stPalette.stNormal.eBackgroundColor   = 0x00;
	stNumBoxInitParam.stPalette.stNormal.eTextColor		 = 0x01;
	#elif SGUI_CONF_GRAYSCALE_DEPTH_BITS==4 || defined(SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED)
	#ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
	stNumBoxInitParam.stPalette.uiDepthBits = 4;
	#endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
	stNumBoxInitParam.stPalette.stFocus.eBackgroundColor	= 0x0F;
	stNumBoxInitParam.stPalette.stFocus.eTextColor		  = 0x00;
	stNumBoxInitParam.stPalette.stNormal.eBackgroundColor   = 0x00;
	stNumBoxInitParam.stPalette.stNormal.eTextColor		 = 0x0F;
	#else
		#error Demo only support 1bit and 4bits screen, for other gray scale bits, please add more palette or turn on color mapping.
	#endif // SGUI_CONF_GRAYSCALE_DEPTH_BITS

	SGUI_NumberVariableBox_Initialize(&s_stNumberVariableBox, &stNumBoxInitParam);


	stTextBoxInitParam.pstFontRes = SGUI_FONT_REF(FONT_12);
	stTextBoxInitParam.stLayout.iX = VARIABLE_BOX_POSX+2;
	stTextBoxInitParam.stLayout.iY = VARIABLE_BOX_TEXT_POSY+2;
	stTextBoxInitParam.stLayout.iWidth = pstDeviceIF->stSize.iWidth-(VARIABLE_BOX_POSX*2)-4;
	stTextBoxInitParam.stLayout.iHeight = SGUI_FONT(FONT_12).iHeight;
	#if SGUI_CONF_GRAYSCALE_DEPTH_BITS==1
	stTextBoxInitParam.stPalette.stNormal.eBackgroundColor = 0x00;
	stTextBoxInitParam.stPalette.stNormal.eTextColor	   = 0x01;
	stTextBoxInitParam.stPalette.stFocus.eBackgroundColor  = 0x01;
	stTextBoxInitParam.stPalette.stFocus.eTextColor		= 0x00;
	#elif SGUI_CONF_GRAYSCALE_DEPTH_BITS==4 || defined(SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED)
	#ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
	stTextBoxInitParam.stPalette.uiDepthBits = 4;
	#endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
	stTextBoxInitParam.stPalette.stNormal.eBackgroundColor = 0x00;
	stTextBoxInitParam.stPalette.stNormal.eTextColor	   = 0x0F;
	stTextBoxInitParam.stPalette.stFocus.eBackgroundColor  = 0x0F;
	stTextBoxInitParam.stPalette.stFocus.eTextColor		= 0x00;
	#else
		#error Demo only support 1bit and 4bits screen, for other gray scale bits, please add more palette or turn on color mapping.
	#endif // SGUI_CONF_GRAYSCALE_DEPTH_BITS
	stTextBoxInitParam.sTextLengthMax = TEXT_VARIABLE_LENGTH;

	SGUI_TextVariableBox_Initialize(&s_stTextVariableBox, &stTextBoxInitParam, s_szTextVariableBuffer);

	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoVariableBox_Prepare(SGUI_SCR_DEV* pstDeviceIF, const void* pstParameters)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_NOTICE_BOX		   	stNoticeBox;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	stNoticeBox.pstIcon = &SGUI_RES_ICON_INFORMATION_16;
	stNoticeBox.cszNoticeText = s_szHelpNoticeText;
	#if SGUI_CONF_GRAYSCALE_DEPTH_BITS==1
	stNoticeBox.stPalette.eEdgeColor  = 0x01;
	stNoticeBox.stPalette.eFillColor  = 0x00;
	stNoticeBox.stPalette.eTextColor  = 0x01;
	#elif SGUI_CONF_GRAYSCALE_DEPTH_BITS==4 || defined(SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED)
	#ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
	stNoticeBox.stPalette.uiDepthBits = 4;
	#endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
	stNoticeBox.stPalette.eEdgeColor  = 0x0A;
	stNoticeBox.stPalette.eFillColor  = 0x01;
	stNoticeBox.stPalette.eTextColor  = 0x0F;
	#else
		#error Demo only support 1bit and 4bits screen, for other gray scale bits, please add more palette or turn on color mapping.
	#endif // SGUI_CONF_GRAYSCALE_DEPTH_BITS
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Draw frame
	s_szFrameTitle = s_szDefaultFrameTitle;
	HMI_DemoVariableBox_DrawFrame(pstDeviceIF, (SGUI_SZSTR)s_szFrameTitle);
	// Show notice
	SGUI_Notice_FitArea(pstDeviceIF, &(stNoticeBox.stLayout));
	SGUI_Notice_Repaint(pstDeviceIF, &stNoticeBox, SGUI_FONT_REF(FONT_8), 0);
	// Start RTC
	RTCTimerEnable(true);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoVariableBox_RefreshScreen(SGUI_SCR_DEV* pstDeviceIF, const void* pstParameters)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Draw frame
	HMI_DemoVariableBox_DrawFrame(pstDeviceIF, (SGUI_SZSTR)s_szFrameTitle);
	// Draw number box
	SGUI_Basic_DrawRectangle(pstDeviceIF, VARIABLE_BOX_POSX, VARIABLE_BOX_NUMBER_POSY,
							s_stNumberVariableBox.stParam.stLayout.iWidth+4, s_stNumberVariableBox.stParam.stLayout.iHeight+4,
							 0x0A, SGUI_COLOR_BKGCLR);
	s_stNumberVariableBox.stData.iFocused = (s_uiFocusedFlag==0)?SGUI_TRUE:SGUI_FALSE;
	SGUI_NumberVariableBox_Repaint(pstDeviceIF, &s_stNumberVariableBox);
	// Draw text box
	s_stTextVariableBox.stData.iFocused = (s_uiFocusedFlag==0)?SGUI_FALSE:SGUI_TRUE;
	SGUI_Basic_DrawRectangle(pstDeviceIF, VARIABLE_BOX_POSX, VARIABLE_BOX_TEXT_POSY,
							s_stTextVariableBox.stParam.stLayout.iWidth+4, s_stTextVariableBox.stParam.stLayout.iHeight+4,
							0x0A, SGUI_COLOR_BKGCLR);
	SGUI_TextVariableBox_Repaint(pstDeviceIF, &s_stTextVariableBox);

	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoVariableBox_ProcessEvent(SGUI_SCR_DEV* pstDeviceIF, const HMI_EVENT_BASE* pstEvent, SGUI_INT* piActionID)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_ENGINE_RESULT		   eProcessResult;
	SGUI_UINT16					uiKeyValue;
	KEY_PRESS_EVENT*			pstKeyEvent;
	SGUI_INT					iProcessAction;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	eProcessResult =			HMI_RET_NORMAL;
	iProcessAction =			HMI_DEMO_PROC_NO_ACT;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(s_uiAutoConfirmTimer > 0)
	{
		if(EVENT_TYPE_ACTION == pstEvent->iType)
		{
			if(EVENT_ID_KEY_PRESS == pstEvent->iID)
			{
				pstKeyEvent = (KEY_PRESS_EVENT*)pstEvent;
				uiKeyValue = KEY_CODE_VALUE(pstKeyEvent->Data.uiKeyValue);

				if(KEY_VALUE_SPACE == uiKeyValue)
				{
					// Stop count down when press space.
					s_uiAutoConfirmTimer = 0;
				}
			}
		}
		else if(EVENT_TYPE_DATA == pstEvent->iType)
		{
			if(EVENT_ID_RTC == pstEvent->iID)
			{
				//Count down five seconds
				s_uiAutoConfirmTimer--;
			}
		}

		// Redraw screen if time out.
		if(0 == s_uiAutoConfirmTimer)
		{
			eProcessResult = HMI_DemoVariableBox_RefreshScreen(pstDeviceIF, NULL);
			RTCTimerEnable(false);
		}
	}
	else
	{
		if(EVENT_ID_KEY_PRESS == pstEvent->iID)
		{
			pstKeyEvent = (KEY_PRESS_EVENT*)pstEvent;
			uiKeyValue = KEY_CODE_VALUE(pstKeyEvent->Data.uiKeyValue);

			switch(uiKeyValue)
			{
				case KEY_VALUE_TAB:
				{
					s_uiFocusedFlag = ((s_uiFocusedFlag+1)%2);

					s_stNumberVariableBox.stData.iFocused = (0 == s_uiFocusedFlag)?SGUI_TRUE:SGUI_FALSE;
					s_stTextVariableBox.stData.iFocused = (0 == s_uiFocusedFlag)?SGUI_FALSE:SGUI_TRUE;

					SGUI_NumberVariableBox_Repaint(pstDeviceIF, &s_stNumberVariableBox);
					SGUI_TextVariableBox_Repaint(pstDeviceIF, &s_stTextVariableBox);
					break;
				}
				case KEY_VALUE_ESC:
				{
					iProcessAction = HMI_DEMO_PROC_CANCEL;
					break;
				}
				case KEY_VALUE_LEFT:
				{
					if(1 == s_uiFocusedFlag)
					{
						SGUI_TextVariableBox_DecreaseIndex(&s_stTextVariableBox);
						SGUI_TextVariableBox_Repaint(pstDeviceIF, &s_stTextVariableBox);
					}
					break;
				}
				case KEY_VALUE_UP:
				{
					if(1 == s_uiFocusedFlag)
					{
						SGUI_TextVariableBox_IncreaseChar(&s_stTextVariableBox);
						SGUI_TextVariableBox_Repaint(pstDeviceIF, &s_stTextVariableBox);
					}
					else
					{
						SGUI_NumberVariableBox_SetValue(&s_stNumberVariableBox, SGUI_NumberVariableBox_GetValue(&s_stNumberVariableBox)+1);
						SGUI_NumberVariableBox_Repaint(pstDeviceIF, &s_stNumberVariableBox);
					}
					break;
				}
				case KEY_VALUE_RIGHT:
				{
					if(1 == s_uiFocusedFlag)
					{
						SGUI_TextVariableBox_IncreaseIndex(&s_stTextVariableBox);
						SGUI_TextVariableBox_Repaint(pstDeviceIF, &s_stTextVariableBox);
					}
					break;
				}
				case KEY_VALUE_DOWN:
				{
					if(1 == s_uiFocusedFlag)
					{
						SGUI_TextVariableBox_DecreaseChar(&s_stTextVariableBox);
						SGUI_TextVariableBox_Repaint(pstDeviceIF, &s_stTextVariableBox);
					}
					else
					{
						SGUI_NumberVariableBox_SetValue(&s_stNumberVariableBox, SGUI_NumberVariableBox_GetValue(&s_stNumberVariableBox)-1);
						SGUI_NumberVariableBox_Repaint(pstDeviceIF, &s_stNumberVariableBox);
					}
					break;
				}
				case KEY_VALUE_ENTER:
				{
					if(1 == s_uiFocusedFlag)
					{
						s_szFrameTitle = SGUI_TextVariableBox_GetText(&s_stTextVariableBox);
						HMI_DemoVariableBox_DrawFrame(pstDeviceIF, (SGUI_SZSTR)s_szFrameTitle);
						// Draw number box
						SGUI_Basic_DrawRectangle(pstDeviceIF, VARIABLE_BOX_POSX, VARIABLE_BOX_NUMBER_POSY, VARIABLE_BOX_WIDTH+4, VARIABLE_NUMBER_BOX_HEIGHT+4, SGUI_COLOR_FRGCLR, SGUI_COLOR_BKGCLR);
						SGUI_NumberVariableBox_Repaint(pstDeviceIF, &s_stNumberVariableBox);
						// Draw text box
						SGUI_Basic_DrawRectangle(pstDeviceIF, VARIABLE_BOX_POSX, VARIABLE_BOX_TEXT_POSY, VARIABLE_BOX_WIDTH+4, VARIABLE_TEXT_BOX_HEIGHT+4, SGUI_COLOR_FRGCLR, SGUI_COLOR_BKGCLR);
						SGUI_TextVariableBox_Repaint(pstDeviceIF, &s_stTextVariableBox);
					}
					break;
				}
				default:
				{
					/* No process. */
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

HMI_ENGINE_RESULT HMI_DemoVariableBox_PostProcess(SGUI_SCR_DEV* pstDeviceIF, HMI_ENGINE_RESULT eProcResult, SGUI_INT iActionID)
{
	if(HMI_PROCESS_SUCCESSFUL(eProcResult))
	{
		if(HMI_DEMO_PROC_CANCEL == iActionID)
		{
			s_uiAutoConfirmTimer = 5;
			HMI_GoBack(NULL);
		}
	}

	return HMI_RET_NORMAL;
}

void HMI_DemoVariableBox_DrawFrame(SGUI_SCR_DEV* pstDeviceIF, SGUI_SZSTR szTitle)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_RECT				stTextDisplayArea;
	SGUI_POINT				stInnerPos;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	stTextDisplayArea.iX = 4;
	stTextDisplayArea.iY = 4;
	stTextDisplayArea.iHeight = 12;
	stInnerPos.iX = 0;
	stInnerPos.iY = 0;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstDeviceIF)
	{
		stTextDisplayArea.iWidth = pstDeviceIF->stSize.iWidth-8;
		SGUI_Basic_DrawRectangle(pstDeviceIF, 0, 0, RECT_WIDTH(pstDeviceIF->stSize), RECT_HEIGHT(pstDeviceIF->stSize), 0x0F, 0x00);
		SGUI_Basic_DrawRectangle(pstDeviceIF, 2, 2, RECT_WIDTH(pstDeviceIF->stSize)-4, RECT_HEIGHT(pstDeviceIF->stSize)-4, 0x0F, 0x00);
		SGUI_Basic_DrawLine(pstDeviceIF, 3, 17, 124, 17, 0x0F);
		SGUI_Text_DrawText(pstDeviceIF, szTitle, SGUI_FONT_REF(GB2312_FZXS12), &stTextDisplayArea, &stInnerPos, 0x0F);
	}
}
