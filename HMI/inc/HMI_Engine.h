#ifndef HMI_PROCESS_H_INCLUDED
#define HMI_PROCESS_H_INCLUDED
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "VirtualDeviceInterface.h"
#include "SGUI_Typedef.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
// GoBack history size
#define		HMI_SCREEN_HISTORY_MAX		    				(20)
#define     HMI_SCREEN_LIST_MAX                             (20)
#define     HMI_EVENT_KEY_VALUE_LENGTH_MAX                  (4)
// Parameter post label.
#define		HMI_SCREEN_ID_ANY								(-1)	// This label means parameter will posted to every screen.

#define		HMI_PROCESS_SUCCESSFUL(RESULT)					(RESULT >= 0)

// Start screen definition
#define		HMI_SCREEN_START								(0)

//=======================================================================//
//= Data type definition.											    =//
//=======================================================================//
// HMI process result
typedef enum
{
    // Abnormal.
    HMI_RET_ERROR =                 -1,
    HMI_RET_INVALID_DATA =          -2,
    HMI_RET_NO_SPACE =              -3,
    HMI_RET_MEMORY_ERR =            -4,
    HMI_RET_UNDEFINED_ACTION =      -5,
    HMI_RET_ERROR_STATE =           -6,
    // Normal.
    HMI_RET_NORMAL =                0,
    HMI_RET_INITIALIZE,
    HMI_RET_CONFIRM,
    HMI_RET_CANCEL,
    HMI_RET_FOLLOWUP,
    HMI_RET_FALLBACK,
    HMI_RET_NOACTION,
    HMI_RET_INPROCESS,
}HMI_ENGINE_RESULT;

// HMI engine state.
typedef enum
{
    HMI_ENGINE_STATE_UNINIT =       0,
    HMI_ENGINE_STATE_READY,
    HMI_ENGINE_STATE_INPROCESS,
    HMI_ENGINE_STATE_ERROR,
}HMI_ENGINE_STATE;

// HMI event type.
typedef enum
{
    HMI_ENGINE_EVENT_BASE =         0,
    HMI_ENGINE_EVENT_UNKNOW =       HMI_ENGINE_EVENT_BASE,
    HMI_ENGINE_EVENT_ENTER,         // Turn to a new screen.
    HMI_ENGINE_EVENT_REFRESH,       // Refresh screen display.
    HMI_ENGINE_EVENT_UPDATE,        // Data in display need update.
    HMI_ENGINE_EVENT_INTERRUPT,     // System interrupt need process.
    // Append new engine event here.

    // Add new engine event above here.
    // User defined screen event
    HMI_ENGINE_EVENT_USER,
}HMI_EVENT_TYPE;

typedef struct
{
    HMI_EVENT_TYPE                  Type;
    SGUI_UINT16                     KeyValue[HMI_EVENT_KEY_VALUE_LENGTH_MAX];
}HMI_EVENT;

// Screen action interface function pointer structure.
typedef struct
{
    HMI_ENGINE_RESULT               (*Initialize)(void); // Initialize screen data and parameter.
	HMI_ENGINE_RESULT               (*Prepare)(const void* pstParameters); // Do some thing before current screen display.
	HMI_ENGINE_RESULT               (*Repaint)(const void* pstParameters); // Repaint screen if needed.
	HMI_ENGINE_RESULT               (*ProcessEvent)(HMI_EVENT_TYPE eEvent, const void* pstParameters); // Process event.
	HMI_ENGINE_RESULT               (*PostProcess)(SGUI_INT iActionResult);
	//void*                           (*InstanceData)(void); // Get current screen instance data pointer.
}HMI_SCREEN_ACTION;
// Screen data structure.
typedef struct
{
	SGUI_INT						ScreenID;
	HMI_SCREEN_ACTION*  			Actions;
}HMI_SCREEN_OBJECT;

typedef struct
{
    SGUI_INT                        TopIndex;
#if (_SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_ > 0)
    HMI_SCREEN_OBJECT*              Item[HMI_SCREEN_HISTORY_MAX];
#else
    HMI_SCREEN_OBJECT**             Item;
#endif
}HMI_HISTORY_STACK;

typedef struct
{
#if (_SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_ > 0)
    HMI_SCREEN_OBJECT**             Screen;
#else
    HMI_SCREEN_OBJECT*              Screen[HMI_SCREEN_LIST_MAX];
#endif
    SGUI_INT                        ScreenCount;
    HMI_SCREEN_OBJECT*              CurrentScreenObject;
    HMI_HISTORY_STACK               History;
    HMI_ENGINE_STATE                State;
}HMI_ENGINE_OBJECT;

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
HMI_ENGINE_RESULT   HMI_PrepareEngine(HMI_ENGINE_OBJECT* pstHMIEngineObject);
HMI_ENGINE_RESULT   HMI_AddScreen(HMI_ENGINE_OBJECT* pstHMIEngineObject, HMI_SCREEN_OBJECT* pstScreenObject);
HMI_ENGINE_RESULT   HMI_ActiveEngine(HMI_ENGINE_OBJECT* pstHMIEngineObject, SGUI_INT iScreenID);
HMI_ENGINE_RESULT   HMI_StartEngine(const void* pstParameters);
HMI_ENGINE_RESULT   HMI_ProcessEvent(HMI_EVENT_TYPE eEvent, const void* pstParameters);
HMI_ENGINE_RESULT   HMI_Goto(SGUI_INT iDestScreenID, const void* pstParameters);
HMI_ENGINE_RESULT   HMI_GoBack(const void* pstParameters);
#endif // HMI_PROCESS_H_INCLUDED
