/*************************************************************************/
/** Copyright.                                                          **/
/** FileName: DemoProc.c                                                **/
/** Author: Polarix                                                     **/
/** Description: User operation interface.                              **/
/*************************************************************************/
//=======================================================================//
//= Include files.                                                      =//
//=======================================================================//
#include "DemoProc.h"
#include "SGUI_Basic.h"

#ifdef _SIMPLE_GUI_IN_VIRTUAL_SDK_
#include "simulator_if.h"
#include "SGUI_FontResource.h"
#else
#include "screen.h"
#include "usart.h"
#include "rtc.h"
#include "base_timer.h"
#include "DemoActions.h"
#include "trigger_flags.h"
#include "keyboard.h"
#endif

//=======================================================================//
//= Macro definition.                                                   =//
//=======================================================================//
#define     BMP_DATA_BUFFER_SIZE    (512)

//=======================================================================//
//= Static variable declaration.                                        =//
//=======================================================================//
SGUI_SCR_DEV                g_stDeviceInterface;
HMI_SCREEN_OBJECT*          g_arrpstScreenObjs[] =
                            {
                                &g_stHMIDemo_List,
                                &g_stHMIDemo_TextPaint,
                                &g_stHMIDemo_VariableBox,
                                &g_stHMIDemo_RealtimeGraph,
                                &g_stHMIDemo_Menu,
                                &g_stHMIDemo_Notice,
                                &g_stHMIDemo_BasicPaint,
                                &g_stHMIDemo_Curve,
                                &g_stHMIDemo_PolorCoord
                            };
HMI_ENGINE_OBJECT           g_stDemoEngine;

SGUI_BYTE                   s_pBmpDataBuffer[BMP_DATA_BUFFER_SIZE];
//=======================================================================//
//= Static function declare.                                            =//
//=======================================================================//
static void                 KeyPressEventProc(void);
static void                 RTCEventProc(void);
static void                 SysTickTimerEventProc(void);
#ifdef _SIMPLE_GUI_IN_VIRTUAL_SDK_
static bool                 CheckEventFlag(ENV_FLAG_INDEX eIndex);
#endif //_SIMPLE_GUI_IN_VIRTUAL_SDK_

//=======================================================================//
//= Function define.                                                    =//
//=======================================================================//

/*****************************************************************************/
/** Function Name:  InitializeHMIEngineObj                                  **/
/** Purpose:        Simple GUI HMI engine and interface demo process.       **/
/** Parameters:     None.                                                   **/
/** Return:         HMI_ENGINE_RESULT.                                      **/
/** Notice:         This function demonstrates how to use the interface and **/
/**                 HMI engine of Simple GUI.                               **/
/*****************************************************************************/
HMI_ENGINE_RESULT InitializeHMIEngineObj(void)
{
    /*----------------------------------*/
    /* Variable Declaration             */
    /*----------------------------------*/
    HMI_ENGINE_RESULT           eProcessResult;
    int                         iIndex;

    /*----------------------------------*/
    /* Initialize                       */
    /*----------------------------------*/
    eProcessResult =            HMI_RET_NORMAL;

    /*----------------------------------*/
    /* Process                          */
    /*----------------------------------*/
    /* Clear structure. */
    SGUI_SystemIF_MemorySet(&g_stDeviceInterface, 0x00, sizeof(SGUI_SCR_DEV));
    SGUI_SystemIF_MemorySet(&g_stDemoEngine, 0x00, sizeof(HMI_ENGINE_OBJECT));
#ifdef _SIMPLE_GUI_IN_VIRTUAL_SDK_
    /* Initialize display size. */
    g_stDeviceInterface.stSize.iWidth = 128;
    g_stDeviceInterface.stSize.iHeight = 64;
    /* Initialize interface object. */
    g_stDeviceInterface.fnSetPixel = SGUI_SDK_SetPixel;
#ifdef SGUI_GET_POINT_FUNC_EN
    g_stDeviceInterface.fnGetPixel = SGUI_SDK_GetPixel;
#endif // SGUI_GET_POINT_FUNC_EN
    //g_stDeviceInterface.fnFillRect = SGUI_SDK_FillRectangle;
    //g_stDeviceInterface.fnClear = SGUI_SDK_ClearDisplay;
    g_stDeviceInterface.fnSyncBuffer = SGUI_SDK_RefreshDisplay;
#else
    #error Add screen device object initialize process here.
#endif
    g_stDeviceInterface.stBuffer.pBuffer = s_pBmpDataBuffer;
    g_stDeviceInterface.stBuffer.sSize = BMP_DATA_BUFFER_SIZE;

    SGUI_Basic_ResetMask(&g_stDeviceInterface);
    do
    {
        /* Prepare HMI engine object. */
        g_stDemoEngine.ScreenCount = sizeof(g_arrpstScreenObjs)/sizeof(*g_arrpstScreenObjs);
        g_stDemoEngine.ScreenObjPtr = g_arrpstScreenObjs;
        g_stDemoEngine.Interface = &g_stDeviceInterface;

        /* Initialize all screen object. */
        if(NULL != g_stDemoEngine.ScreenObjPtr)
        {
            for(iIndex=0; iIndex<g_stDemoEngine.ScreenCount; iIndex++)
            {
                if( (NULL != g_stDemoEngine.ScreenObjPtr[iIndex])
                    && (NULL != g_stDemoEngine.ScreenObjPtr[iIndex]->pstActions)
                    && (NULL != g_stDemoEngine.ScreenObjPtr[iIndex]->pstActions->Initialize)
                    )
                {
                    g_stDemoEngine.ScreenObjPtr[iIndex]->pstActions->Initialize(&g_stDeviceInterface);
                    g_stDemoEngine.ScreenObjPtr[iIndex]->pstPrevious = NULL;
                }
            }
        }
        else
        {

        }
        /* Active engine object. */
        eProcessResult = HMI_ActiveEngine(&g_stDemoEngine, HMI_SCREEN_ID_DEMO_LIST);
        if(HMI_PROCESS_FAILED(eProcessResult))
        {
            /* Active engine failed. */
            break;
        }
        /* Start engine process. */
        eProcessResult = HMI_StartEngine(NULL);
        if(HMI_PROCESS_FAILED(eProcessResult))
        {
            /* Start engine failed. */
            break;
        }
    }while(0);

    return eProcessResult;
}

/*****************************************************************************/
/** Function Name:  DemoMainProcess                                         **/
/** Purpose:        It is a dummy main function for SimpleGUI Virtual SDK,  **/
/**                 or run demo process in demo process.                    **/
/** Parameters:     None.                                                   **/
/** Return:         Terminal code, seam as main function return code.       **/
/** Notice:         None.                                                   **/
/*****************************************************************************/
void DemoMainProcess(void)
{
    /*----------------------------------*/
    /* Initialize                       */
    /*----------------------------------*/
    // Initialize HMI Engine.
    InitializeHMIEngineObj();

    /*----------------------------------*/
    /* Process                          */
    /*----------------------------------*/
    while(SGUI_SDK_IsActive())
    {
        SGUI_SDK_TicksProlog();
        // Check and process heart-beat timer event.
        if(true == SysTickTimerTriggered())
        {
            SysTickTimerEventProc();
        }
        // Check and process key press event.
        if(true == UserEventTriggered())
        {
            KeyPressEventProc();
        }
        // Check and process RTC event.
        if(true == RTCTimerTriggered())
        {
            RTCEventProc();
        }
    }
}

/*****************************************************************************/
/** Function Name:  KeyPressEventProc                                       **/
/** Purpose:        Deal with user key process in demo process.             **/
/** Parameters:     None.                                                   **/
/** Return:         None.                                                   **/
/** Notice:         The button is just abstract, and the message may come   **/
/**                 from a touch screen, a serial port, and so on.          **/
/*****************************************************************************/
void KeyPressEventProc(void)
{
    /*----------------------------------*/
    /* Variable Declaration             */
    /*----------------------------------*/
    KEY_PRESS_EVENT         stEvent;

    /*----------------------------------*/
    /* Initialize                       */
    /*----------------------------------*/
    HMI_EVENT_INIT(stEvent);

    /*----------------------------------*/
    /* Process                          */
    /*----------------------------------*/
    stEvent.Head.iID = EVENT_ID_KEY_PRESS;
#ifdef _SIMPLE_GUI_IN_VIRTUAL_SDK_
    stEvent.Data.uiKeyValue = SGUI_SDK_GetKeyCode();
#else
    #error Add key event data prepare process here.
#endif
    // Post key press event.
    HMI_ProcessEvent((HMI_EVENT_BASE*)(&stEvent));
}

/*****************************************************************************/
/** Function Name:  SysTickTimerEventProc                                   **/
/** Purpose:        Deal with heartbeat timer event in demo process.        **/
/** Parameters:     None.                                                   **/
/** Return:         None.                                                   **/
/** Notice:         It is usually used to simulate ADC or other sensors.    **/
/*****************************************************************************/
void SysTickTimerEventProc(void)
{
    /*----------------------------------*/
    /* Variable Declaration             */
    /*----------------------------------*/
    DATA_EVENT              stEvent;

    /*----------------------------------*/
    /* Initialize                       */
    /*----------------------------------*/
    HMI_EVENT_INIT(stEvent);

    /*----------------------------------*/
    /* Process                          */
    /*----------------------------------*/
    stEvent.Head.iID = EVENT_ID_TIMER;
    stEvent.Data.iValue = simulator_if_get_data();
    // Post timer event.
    HMI_ProcessEvent((HMI_EVENT_BASE*)&stEvent);
}

/*****************************************************************************/
/** Function Name:  RTCEventProc                                            **/
/** Purpose:        Deal with RTC timer event in demo process.              **/
/** Parameters:     None.                                                   **/
/** Return:         None.                                                   **/
/** Notice:         It is usually used to simulate ADC or other sensors.    **/
/*****************************************************************************/
void RTCEventProc(void)
{
    /*----------------------------------*/
    /* Variable Declaration             */
    /*----------------------------------*/
    HMI_GENERAL_EVENT       stEvent;

    /*----------------------------------*/
    /* Initialize                       */
    /*----------------------------------*/
    HMI_EVENT_INIT(stEvent);

    /*----------------------------------*/
    /* Process                          */
    /*----------------------------------*/
    stEvent.Head.iID =      EVENT_ID_RTC;
    // Post RTC update message to a screen.
    HMI_ProcessEvent((HMI_EVENT_BASE*)&stEvent);
}

/*****************************************************************************/
/** Function Name:  SysTickTimerTriggered                                   **/
/** Purpose:        Check sys-tick timer interrupt is triggered.            **/
/** Parameters:     None.                                                   **/
/** Return:         None.                                                   **/
/** Notice:         None.                                                   **/
/*****************************************************************************/
bool SysTickTimerTriggered(void)
{
    /*----------------------------------*/
    /* Process                          */
    /*----------------------------------*/
#ifdef _SIMPLE_GUI_IN_VIRTUAL_SDK_
    return simulator_if_has_data();
#else
    #error Add sys-tick timer trigger process here.
#endif
}

/*****************************************************************************/
/** Function Name:  RTCTimerTriggered                                       **/
/** Purpose:        Check RTC timer interrupt is triggered.                 **/
/** Parameters:     None.                                                   **/
/** Return:         None.                                                   **/
/** Notice:         None.                                                   **/
/*****************************************************************************/
bool RTCTimerTriggered(void)
{
    /*----------------------------------*/
    /* Process                          */
    /*----------------------------------*/
#ifdef _SIMPLE_GUI_IN_VIRTUAL_SDK_
    return false;
#else
    // // Add Dummy RTC trigger process here.
    return false;
#endif
}

/*****************************************************************************/
/** Function Name:  UserEventTriggered                                      **/
/** Purpose:        Check user event is triggered.                          **/
/** Parameters:     None.                                                   **/
/** Return:         None.                                                   **/
/** Notice:         None.                                                   **/
/*****************************************************************************/
bool UserEventTriggered(void)
{
    /*----------------------------------*/
    /* Process                          */
    /*----------------------------------*/
#ifdef _SIMPLE_GUI_IN_VIRTUAL_SDK_
    return SGUI_SDK_HasKey();
#else
    #error Add user event trigger process here.
#endif
}

/*****************************************************************************/
/** Function Name:  SysTickTimerEnable                                      **/
/** Purpose:        Enable or disable sys-tick timer.                       **/
/** Parameters:                                                             **/
/** @ bEnable[in]:  True for enable sys-tick timer, false for disable.      **/
/** Return:         None.                                                   **/
/** Notice:         None.                                                   **/
/*****************************************************************************/
void SysTickTimerEnable(bool bEnable)
{
    /*----------------------------------*/
    /* Process                          */
    /*----------------------------------*/
#ifdef _SIMPLE_GUI_IN_VIRTUAL_SDK_
    // (void)SGUI_SDK_ConfigGeneralTimer(bEnable?DEMO_HEART_BEAT_INTERVAL_MS:0);
#else
    #error Add sys-tick timer enable/disable process here.
#endif
}

/*****************************************************************************/
/** Function Name:  RTCTimerEnable                                          **/
/** Purpose:        Enable or disable RTC timer.                            **/
/** Parameters:                                                             **/
/** @ bEnable[in]:  True for enable RTC timer, false for disable.           **/
/** Return:         None.                                                   **/
/** Notice:         None.                                                   **/
/*****************************************************************************/
void RTCTimerEnable(bool bEnable)
{

    /*----------------------------------*/
    /* Process                          */
    /*----------------------------------*/
#ifdef _SIMPLE_GUI_IN_VIRTUAL_SDK_
    // (void)SGUI_SDK_EnableSecondInterrupt(bEnable);
#endif
}

