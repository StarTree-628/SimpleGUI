#ifndef __INCLUDE_GUI_BASIC__
#define __INCLUDE_GUI_BASIC__
//=======================================================================//
//= Include files.                                                      =//
//=======================================================================//
#include "SGUI_Common.h"

//=======================================================================//
//= Macro definition.                                                   =//
//=======================================================================//
#define     SGUI_USED_BYTE(V)               (((V-1)/8)+1)
//Bitmap(include font) data bit operation
#define     SGUI_SET_PAGE_BIT(PAGE, Bit)    ((PAGE) = (PAGE) | (0x01 << (Bit)))
#define     SGUI_CLR_PAGE_BIT(PAGE, Bit)    ((PAGE) = (PAGE) & (~(0x01 << (Bit))))
#define     SGUI_GET_PAGE_BIT(PAGE, Bit)    ((((PAGE) & (0x01 << (Bit)))>0)?1:0)

//=======================================================================//
//= Public function declaration.                                        =//
//=======================================================================//
#ifdef __cplusplus
extern "C"{
#endif
void        SGUI_Basic_ResetMask(SGUI_SCR_DEV* pstDeviceIF);
void        SGUI_Basic_SetMask1(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iStartX, SGUI_INT iStartY, SGUI_INT iEndX, SGUI_INT iEndY);
void        SGUI_Basic_SetMask2(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iX, SGUI_INT iY, SGUI_INT iWidth, SGUI_INT iHeight);
void        SGUI_Basic_SetMask3(SGUI_SCR_DEV* pstDeviceIF, const SGUI_PAINT_MASK* pstMask);
void        SGUI_Basic_SetMask4(SGUI_SCR_DEV* pstDeviceIF, const SGUI_RECT* pstRect);
void        SGUI_Basic_ClearScreen(SGUI_SCR_DEV* pstDeviceIF);
void        SGUI_Basic_DrawPoint(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iPosX, SGUI_INT iPosY, SGUI_COLOR eColor);
void        SGUI_Basic_DrawLine(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iStartX, SGUI_INT iStartY, SGUI_INT iEndX, SGUI_INT iEndY, SGUI_COLOR eColor);
#ifdef SGUI_GET_POINT_FUNC_EN
SGUI_COLOR  SGUI_Basic_GetPoint(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iPosX, SGUI_INT iPosY);
#endif // SGUI_GET_POINT_FUNC_EN
void        SGUI_Basic_DrawHorizontalLine(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iStartX, SGUI_INT iEndX, SGUI_INT iY, SGUI_COLOR eColor);
void        SGUI_Basic_DrawVerticalLine(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iX, SGUI_INT iStartY, SGUI_INT iEndY, SGUI_COLOR eColor);
void        SGUI_Basic_DrawRectangle(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iStartX, SGUI_INT iStartY, SGUI_INT iWidth, SGUI_INT iHeight, SGUI_COLOR eEdgeColor, SGUI_COLOR eFillColor);
void        SGUI_Basic_DrawRoundedRectangle(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iStartX, SGUI_INT iStartY, SGUI_INT iWidth, SGUI_INT iHeight, SGUI_INT iFillet, SGUI_COLOR eEdgeColor, SGUI_COLOR eFillColor);
void        SGUI_Basic_DrawCircle(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iCx, SGUI_INT iCy, SGUI_INT iRadius, SGUI_COLOR eEdgeColor, SGUI_COLOR eFillColor);
#ifdef SGUI_REVERSE_FUNC_EN
void        SGUI_Basic_ReverseBlockColor(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iStartX, SGUI_INT iStartY, SGUI_INT iWidth, SGUI_INT iHeight);
#endif // SGUI_REVERSE_FUNC_EN
void        SGUI_Basic_FillRectangleArea(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iStartX, SGUI_INT iStartY, SGUI_INT iWidth, SGUI_INT iHeight, SGUI_COLOR eFillColor);
void        SGUI_Basic_DrawBitMap(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iX, SGUI_INT iY, const SGUI_BMP_RES* pstBitmapData, SGUI_DRAW_MODE eDrawMode);
SGUI_BOOL   SGUI_Basic_PointIsInArea(const SGUI_RECT* pstArea, SGUI_INT iPosX, SGUI_INT iPosY);
#ifdef __cplusplus
}
#endif

#endif
