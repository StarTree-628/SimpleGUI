#ifndef __INCLUDE_COMMON_H__
#define __INCLUDE_COMMON_H__
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include <stddef.h>
#include <stdint.h>

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define _TRANS_TEXT(STR)								_(STR)

#define LCD_COLOR_OBJ_PIX						    	(0xFF5B805A)
#define LCD_COLOR_OBJ_BKG						    	(0xFFF9ECE4)
#define LCD_COLOR_OBJ_GRID						    	(0xFF383834)

#define PARAM_DEFAULT_PIXEL_NUM_H                       (128)
#define PARAM_DEFAULT_PIXEL_NUM_V                       (64)
#define PARAM_DEFAULT_PIXEL_WIDTH					    (3)
#define PARAM_DEFAULT_PIXEL_HEIGHT					    (3)
#define PARAM_DEFAULT_GRID_ENABLE                       (true)
#define PARAM_DEFAULT_GRID_DISABLE                      (false)

//=======================================================================//
//= Data type declaration.											    =//
//=======================================================================//
typedef struct
{
	size_t					HorizontalPixelNumber;
    size_t					VerticalPixelNumber;
    size_t					PixelUnitWidth;
    size_t					PixelUnitHeight;
    bool					EnableGrid;
	unsigned int			PanelColor;
	unsigned int			PixelColor;
	unsigned int			GridColor;
}PixelPanelParameter;

//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
extern PixelPanelParameter			g_stParameters;

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
void SetDefaultParameterData(PixelPanelParameter* pstParameter);

#endif // __INCLUDE_LCD_COMMON_H__
