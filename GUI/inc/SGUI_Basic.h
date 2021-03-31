#ifndef __INCLUDE_GUI_BASIC__
#define __INCLUDE_GUI_BASIC__
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Common.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define     SGUI_USED_BYTE(V)               (((V-1)/8)+1)
//Bitmap(include font) data bit operation
#define     SGUI_SET_PAGE_BIT(PAGE, Bit)	((PAGE) = (PAGE) | (0x01 << (Bit)))
#define     SGUI_CLR_PAGE_BIT(PAGE, Bit)	((PAGE) = (PAGE) & (~(0x01 << (Bit))))
#define     SGUI_GET_PAGE_BIT(PAGE, Bit)	((((PAGE) & (0x01 << (Bit)))>0)?1:0)

#define     SGUI_BMP_SCAN_MODE_DHPH              SGUI_Basic_BitMapScanDHPH
#define     SGUI_BMP_SCAN_MODE_DHPV              SGUI_Basic_BitMapScanDHPV
#define     SGUI_BMP_SCAN_MODE_DVPH              SGUI_Basic_BitMapScanDVPH
#define     SGUI_BMP_SCAN_MODE_DVPV              SGUI_Basic_BitMapScanDVPV

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
void		SGUI_Basic_ClearScreen(SGUI_SCR_DEV* pstDeviceIF);
void		SGUI_Basic_DrawPoint(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iPosX, SGUI_INT iPosY, SGUI_COLOR eColor);
void		SGUI_Basic_DrawLine(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iStartX, SGUI_INT iStartY, SGUI_INT iEndX, SGUI_INT iEndY, SGUI_COLOR eColor);
void        SGUI_Basic_DrawHorizontalLine(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iStartX, SGUI_INT iEndX, SGUI_INT iY, SGUI_COLOR eColor);
void        SGUI_Basic_DrawVerticalLine(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iX, SGUI_INT iStartY, SGUI_INT iEndY, SGUI_COLOR eColor);
void		SGUI_Basic_DrawLineInArea(SGUI_SCR_DEV* pstDeviceIF, SGUI_POINT* pstStartPoint, SGUI_POINT* pstEndPoint, const SGUI_RECT* pcstArea, SGUI_COLOR eColor);
void		SGUI_Basic_DrawRectangle(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iStartX, SGUI_INT iStartY, SGUI_INT iWidth, SGUI_INT iHeight, SGUI_COLOR eEdgeColor, SGUI_COLOR eFillColor);
void        SGUI_Basic_DrawRoundedRectangle(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iStartX, SGUI_INT iStartY, SGUI_INT iWidth, SGUI_INT iHeight, SGUI_INT iFillet, SGUI_COLOR eEdgeColor, SGUI_COLOR eFillColor);
void		SGUI_Basic_DrawCircle(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iCx, SGUI_INT iCy, SGUI_INT iRadius, SGUI_COLOR eEdgeColor, SGUI_COLOR eFillColor);
void		SGUI_Basic_ReverseBlockColor(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iStartX, SGUI_INT iStartY, SGUI_INT iWidth, SGUI_INT iHeight);
void		SGUI_Basic_DrawBitMap(SGUI_SCR_DEV* pstDeviceIF, SGUI_RECT* pstDisplayArea, SGUI_POINT* pstInnerPos, const SGUI_BMP_RES* pstBitmapData, SGUI_DRAW_MODE eDrawMode);
void        SGUI_Basic_DrawAlphaBitMap(SGUI_SCR_DEV* pstDeviceIF, SGUI_RECT* pstDisplayArea, SGUI_POINT* pstInnerPos, const SGUI_BMP_RES* pstBitmapData, SGUI_COLOR eTargetColor);
SGUI_COLOR  SGUI_Basic_BitMapScanDHPH(const SGUI_BMP_RES* pstBitmapData,SGUI_UINT8 uiX,SGUI_UINT8 uiY);
SGUI_COLOR  SGUI_Basic_BitMapScanDHPV(const SGUI_BMP_RES* pstBitmapData,SGUI_UINT8 uiX,SGUI_UINT8 uiY);
SGUI_COLOR  SGUI_Basic_BitMapScanDVPH(const SGUI_BMP_RES* pstBitmapData,SGUI_UINT8 uiX,SGUI_UINT8 uiY);
SGUI_COLOR  SGUI_Basic_BitMapScanDVPV(const SGUI_BMP_RES* pstBitmapData,SGUI_UINT8 uiX,SGUI_UINT8 uiY);
SGUI_COLOR	SGUI_Basic_GetPoint(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iPosX, SGUI_INT iPosY);
SGUI_BOOL	SGUI_Basic_PointIsInArea(const SGUI_RECT* pstArea, const SGUI_POINT* pstPoint);
SGUI_COLOR  SGUI_Basic_GetReverseColor(const SGUI_UINT8 uiDepthBits,SGUI_COLOR eOriginColor);
SGUI_COLOR  SGUI_Basic_MapColor(const SGUI_UINT8 uiOriginDepthBits,const SGUI_COLOR eOriginColor,const SGUI_UINT8 uiTargetDepthBits);

#endif
