#ifndef __INCLUDE_SDK_INTERFACE__
#define __INCLUDE_SDK_INTERFACE__
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include <stdint.h>
#include <stdbool.h>
#include <SGUI_Typedef.h>
//=======================================================================//
//= Data type definition.											    =//
//=======================================================================//
typedef enum
{
    ENV_FLAG_IDX_SDK_INIT		= 0,
    ENV_FLAG_IDX_SDK_RTC_EN,
    ENV_FLAG_IDX_SDK_RTC_EVENT,
    ENV_FLAG_IDX_SDK_TIM_SET,
    ENV_FLAG_IDX_SDK_TIM_EVENT,
    ENV_FLAG_IDX_SDK_KEY_EVENT,
    ENV_FLAG_IDX_MAX,
} ENV_FLAG_INDEX;

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
void			SGUI_SDK_SetEvnetSyncFlag(ENV_FLAG_INDEX eIndex, bool bValue);
void			SGUI_SDK_SyncKeyEventData(unsigned int uiKeyCode);
unsigned int	SGUI_SDK_GetKeyEventData(void);
bool			SGUI_SDK_GetEventSyncFlag(ENV_FLAG_INDEX eIndex);
bool			SGUI_SDK_Initialize(void);
void			SGUI_SDK_SetPixel(SGUI_INT uiPosX, SGUI_INT uiY, SGUI_COLOR uiPixelValue);
SGUI_COLOR		SGUI_SDK_GetPixel(SGUI_INT uiPosX, SGUI_INT uiY);
void			SGUI_SDK_RefreshDisplay(void);
void			SGUI_SDK_ClearDisplay(void);
bool			SGUI_SDK_ConfigHearBeatTimer(unsigned int uiIntervalMs);
bool			SGUI_SDK_EnableRTCInterrupt(bool bEnabled);
void			SGUI_SDK_SysTickTimerInterrput(void);
void			SGUI_SDK_RTCInterrput(void);
int				SGUI_SDK_DummyMainProc(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif // __INCLUDE_USER_ACTION_INTERFACE__
