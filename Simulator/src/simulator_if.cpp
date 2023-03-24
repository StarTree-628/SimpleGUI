/*************************************************************************/
/** Copyright.															**/
/** FileName: SDKInterface.cpp											**/
/** Author: Polarix														**/
/** Description: SDK swap interface function defines.					**/
/*************************************************************************/
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "simulator_if.h"
#include "DemoProc.h"
#include "DemoActions.h"
#include "simulator.h"
#include "console_log.h"

//=======================================================================//
//= User definition.												    =//
//=======================================================================//
#define LV_HOR_RES_MAX      (128)
#define LV_VER_RES_MAX      (64)

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static unsigned int         SGUI_SDK_ConvKeyScanCode(int iScanCode);

//=======================================================================//
//= Static object declaration.                                          =//
//=======================================================================//
simulator                   s_simulator_obj;

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
/*************************************************************************/
/** Function Name:	SGUI_SDK_SetPixel                                   **/
/** Purpose:		Set virtual device pixel register data.             **/
/** Params:																**/
/**	@ iX[in]:		Pixel x-coordinate on display panel.                **/
/**	@ iY[in]:		Pixel y-coordinate on display panel.                **/
/**	@ uiPixelValue[in]:	Pixel value, 0 for clear, 1 for set.            **/
/** Return:			None.                                               **/
/** Notice:			None.                                               **/
/*************************************************************************/
void SGUI_SDK_SetPixel(int iX, int iY, unsigned int uiColor)
{
    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    if(uiColor)
    {
        s_simulator_obj.window(0).paint_pixel(iX, iY, 0xFF, 0xFF, 0xFF);
    }
    else
    {
        s_simulator_obj.window(0).paint_pixel(iX, iY, 0x00, 0x00, 0x00);
    }
}

/*************************************************************************/
/** Function Name:	SGUI_SDK_GetPixel									**/
/** Purpose:		Get a pixel value form virtual device register.     **/
/** Params:																**/
/**	@ iX[in]:		Pixel x-coordinate on display panel.                **/
/**	@ iY[in]:		Pixel y-coordinate on display panel.                **/
/** Return:			Pixel state, 0 for cleared, 1 for set.              **/
/** Notice:			None.                                               **/
/*************************************************************************/
unsigned int SGUI_SDK_GetPixel(int iX, int iY)
{
    return 0;
}

/*************************************************************************/
/** Function Name:	SGUI_SDK_RefreshDisplay								**/
/** Purpose:		Refresh virtual device display.                     **/
/** Params:			None.                                               **/
/** Return:			None.                                               **/
/** Notice:			None.                                               **/
/*************************************************************************/
void SGUI_SDK_RefreshDisplay(void)
{
    s_simulator_obj.window(0).sync_paint_buffer();
}

/*************************************************************************/
/** Function Name:	SGUI_SDK_ClearDisplay								**/
/** Purpose:		Clear screen display.                               **/
/** Params:			None.                                               **/
/** Return:			None.                                               **/
/** Notice:			None.                                               **/
/*************************************************************************/
void SGUI_SDK_ClearDisplay(void)
{
    s_simulator_obj.window(0).clear_paint();
    s_simulator_obj.window(0).sync_paint_buffer();
}

bool SGUI_SDK_HasKey(void)
{
    return (s_simulator_obj.window(0).key_event().size() > 0);
}

/*************************************************************************/
/** Function Name:	SGUI_SDK_KeyCode                                    **/
/** Purpose:		Convert SDL2 key scan code to demo key code value.  **/
/** Params:                                                             **/
/** [in] iScanCode: Key scan code from SDL engine.                      **/
/** Return:			Simple GUI demo key code value.                     **/
/*************************************************************************/
unsigned int SGUI_SDK_GetKeyCode(void)
{
    unsigned int uiKeyCode = KEY_VALUE_NONE;
    if(!s_simulator_obj.window(0).key_event().empty())
    {
        if(sim_key_release == (s_simulator_obj.window(0).key_event().front().event()))
        {
            uiKeyCode = SGUI_SDK_ConvKeyScanCode(s_simulator_obj.window(0).key_event().front().code());
        }
        s_simulator_obj.window(0).key_event().pop();
    }
    return uiKeyCode;
}

bool simulator_if_has_data(void)
{
    return s_simulator_obj.random().is_update();
}

int simulator_if_get_data(void)
{
    return s_simulator_obj.random().value();
}

bool SGUI_SDK_TicksProlog(void)
{
    return s_simulator_obj.window(0).prolog();
}

bool SGUI_SDK_IsActive(void)
{
    return !(s_simulator_obj.window(0).exit());
}

/*************************************************************************/
/** Function Name:	SGUI_SDK_KeyCode                                    **/
/** Purpose:		Convert SDL2 key scan code to demo key code value.  **/
/** Params:                                                             **/
/** [in] iScanCode: Key scan code from SDL engine.                      **/
/** Return:			Simple GUI demo key code value.                     **/
/*************************************************************************/
unsigned int SGUI_SDK_ConvKeyScanCode(int iScanCode)
{
    uint16_t uiKeyCode = KEY_VALUE_NONE;
    switch(iScanCode)
    {
        case SDL_SCANCODE_UP:
        {
            uiKeyCode = KEY_VALUE_UP;
            break;
        }
        case SDL_SCANCODE_DOWN:
        {
            uiKeyCode = KEY_VALUE_DOWN;
            break;
        }
        case SDL_SCANCODE_LEFT:
        {
            uiKeyCode = KEY_VALUE_LEFT;
            break;
        }
        case SDL_SCANCODE_RIGHT:
        {
            uiKeyCode = KEY_VALUE_RIGHT;
            break;
        }
        case SDL_SCANCODE_RETURN:
        case SDL_SCANCODE_RETURN2:
        {
            uiKeyCode = KEY_VALUE_ENTER;
            break;
        }
        case SDL_SCANCODE_SPACE:
        {
            uiKeyCode = KEY_VALUE_SPACE;
        }
        case SDL_SCANCODE_ESCAPE:
        {
            uiKeyCode = KEY_VALUE_ESC;
        }
        case SDL_SCANCODE_BACKSPACE:
        {
            uiKeyCode = KEY_VALUE_BACKSPACE;
        }
        default:
        {
            /* Do nothing. */
        }
    }

    return uiKeyCode;
}

/*************************************************************************/
/** Function Name:	InitializeSDK.										**/
/** Purpose:		Post initialize event and wait for event sync.		**/
/** Params:			None.                                               **/
/** Return:			None.                                               **/
/** Notice:			Post event to main frame for initialize SDK.		**/
/*************************************************************************/
bool SGUI_SDK_Initialize(void)
{
    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    s_simulator_obj.init();

    return true;
}

/*************************************************************************/
/** Function Name:	SGUI_SDK_Deinitialize.                              **/
/** Purpose:		Deinitialize SDK simulator.                         **/
/** Params:			None.                                               **/
/** Return:			None.                                               **/
/*************************************************************************/
void SGUI_SDK_Deinitialize(void)
{
    s_simulator_obj.deinit();
}

/*************************************************************************/
/** Function Name:	SGUI_SDK_DummyMainProc								**/
/** Purpose:		Main process start interface.						**/
/** Params:			None.                                               **/
/** Return:			return code, 0 for no error.						**/
/** Notice:			This function simulates the main entry function of	**/
/**					the target platform, it will called by main frame	**/
/**					thread helper process.								**/
/*************************************************************************/
int SGUI_SDK_DummyMainProc(void)
{
    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    // Initialize main frame.
    SGUI_SDK_Initialize();
    // Call main process.
    DemoMainProcess();

    SGUI_SDK_Deinitialize();

    return 0;
}

/*************************************************************************/
/** Function Name:	SGUI_SDK_GeneralTimerHandler						**/
/** Purpose:		SDK Dummy General timer interrupt service function.	**/
/** Params:			None.                                               **/
/** Return:			none.												**/
/** Notice:			This function simulates the SysTick timer interrupt	**/
/**					service, add custom processing here if needed.		**/
/*************************************************************************/
void SGUI_SDK_GeneralTimerHandler(void)
{
	// Add your process here.
}

/*************************************************************************/
/** Function Name:	SGUI_SDK_SecondTimerHandler                         **/
/** Purpose:		SDK Dummy second interrupt service function.        **/
/** Params:			None.                                               **/
/** Return:			none.												**/
/** Notice:			This function simulates the RTC interrupt service,	**/
/**					add custom processing here if needed.				**/
/*************************************************************************/
void SGUI_SDK_SecondTimerHandler(void)
{
    // Add your process here.
}

/*************************************************************************/
/** Function Name:	SGUI_SDK_KeyboardHandler                            **/
/** Purpose:		SDK Dummy Key board interrupt service function.     **/
/** Params:			None.                                               **/
/** Return:			none.												**/
/** Notice:			This function simulates the RTC interrupt service,	**/
/**					add custom processing here if needed.				**/
/*************************************************************************/
void SGUI_SDK_KeyboardHandler(void)
{
    // Add your process here.
}
