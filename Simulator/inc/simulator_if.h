#ifndef __INCLUDE_SIMULATOR_INTERFACE__
#define __INCLUDE_SIMULATOR_INTERFACE__
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

//=======================================================================//
//= Data type definition.											    =//
//=======================================================================//
typedef enum
{
    ENV_FLAG_IDX_SDK_INIT		= 0,
    ENV_FLAG_IDX_SDK_SEC_EN,
    ENV_FLAG_IDX_SDK_SEC_EVENT,
    ENV_FLAG_IDX_SDK_TIM_SET,
    ENV_FLAG_IDX_SDK_TIM_EVENT,
    ENV_FLAG_IDX_SDK_KEY_EVENT,
    ENV_FLAG_IDX_MAX,
} ENV_FLAG_INDEX;

typedef struct
{
    uint32_t    iKeyCode;
    bool        bShift;
    bool        bCtrl;
    bool        bAlt;
}SDK_KB_EVENT;

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
bool			    SGUI_SDK_Initialize(void);
void			    SGUI_SDK_Deinitialize(void);
bool                SGUI_SDK_HasKey(void);
unsigned int        SGUI_SDK_GetKeyCode(void);
bool                simulator_if_has_data(void);
int                 simulator_if_get_data(void);
bool			    SGUI_SDK_TicksProlog(void);
bool			    SGUI_SDK_IsActive(void);
void			    SGUI_SDK_SetPixel(int iX, int iY, unsigned int uiColor);
unsigned int        SGUI_SDK_GetPixel(int iX, int iY);
void			    SGUI_SDK_RefreshDisplay(void);
void			    SGUI_SDK_ClearDisplay(void);

int				    SGUI_SDK_DummyMainProc(void);
void			    SGUI_SDK_GeneralTimerHandler(void);
void			    SGUI_SDK_SecondTimerHandler(void);
void			    SGUI_SDK_KeyboardHandler(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif // __INCLUDE_SIMULATOR_INTERFACE__
