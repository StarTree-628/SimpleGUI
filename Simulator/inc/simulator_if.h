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
bool			    simulator_init(void);
void			    simulator_deinit(void);
bool			    simulator_ticks_prolog(void);
bool			    simulator_is_active(void);
bool                simulator_if_has_key_event(void);
unsigned int        simulator_if_read_key(void);
bool                simulator_if_has_data(void);
int                 simulator_if_get_data(void);
void			    simulator_if_paint_pixel(int iX, int iY, unsigned int uiColor);
unsigned int        simulator_if_read_pixel(int iX, int iY);
void			    simulator_if_flush_screen(void);
void			    simulator_if_clear_screen(void);
int				    SGUI_SDK_DummyMainProc(void);
void			    SGUI_SDK_GeneralTimerHandler(void);
void			    SGUI_SDK_SecondTimerHandler(void);
void			    SGUI_SDK_KeyboardHandler(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif // __INCLUDE_SIMULATOR_INTERFACE__
