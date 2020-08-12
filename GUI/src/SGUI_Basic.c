/*************************************************************************/
/** Copyright.															**/
/** FileName: SGUI_Basic.c												**/
/** Author: XuYulin														**/
/** Description: Simple GUI basic drawing operating interface.			**/
/*************************************************************************/
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Basic.h"
#include "math.h"
//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define SGUI_MIN_VAL(A, B)			(((A)>(B)?(B):(A)))
#define SGUI_MAX_VAL(A, B)			(((A)<(B)?(B):(A)))

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
/*************************************************************************/
/** Function Name:	SGUI_Basic_DrawPoint								**/
/** Purpose:		Set a pixel color or draw a point.					**/
/** Params:																**/
/**	@ pstDeviceIF[in]:	SimpleGUI object pointer.						**/
/**	@ uiCoordinateX[in]: X coordinate of point by pixels.				**/
/**	@ uiCoordinateY[in]: Y coordinate of point by pixels.				**/
/**	@ eColor[in]:		Point color, GUI_COLOR_BKGCLR means clear pix, 	**/
/**						GUI_COLOR_FRGCLR means set pix.					**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_Basic_DrawPoint(SGUI_SCR_DEV* pstDeviceIF, SGUI_UINT uiCoordinateX, SGUI_UINT uiCoordinateY, SGUI_COLOR eColor)
{
    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    if((NULL != pstDeviceIF) && (uiCoordinateX < RECT_WIDTH(pstDeviceIF->stSize)) && (uiCoordinateY < RECT_HEIGHT(pstDeviceIF->stSize)))
    {
    	if(NULL == pstDeviceIF->fnSetPixel)
		{
			/* Action function is unspecified, no actions. */
		}
        else
        {
            pstDeviceIF->fnSetPixel(uiCoordinateX,uiCoordinateY,eColor);
        }
    }
}

/*************************************************************************/
/** Function Name:	SGUI_Basic_GetPoint									**/
/** Purpose:		Get a pixel color .									**/
/** Params:																**/
/**	@ pstDeviceIF[in]:	SimpleGUI object pointer.						**/
/**	@ uiCoordinateX[in]: X coordinate of point by pixels.				**/
/**	@ uiCoordinateY[in]: Y coordinate of point by pixels.				**/
/** Return:			SGUI_COLOR type enumerated for point color.			**/
/** Notice:			None.												**/
/*************************************************************************/
SGUI_COLOR SGUI_Basic_GetPoint(SGUI_SCR_DEV* pstDeviceIF, SGUI_UINT uiCoordinateX, SGUI_UINT uiCoordinateY)
{
    /*----------------------------------*/
    /* Variable Declaration				*/
    /*----------------------------------*/
    SGUI_COLOR					eColor;

    /*----------------------------------*/
    /* Initialize						*/
    /*----------------------------------*/
    eColor =					SGUI_COLOR_BKGCLR;

    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    if((NULL != pstDeviceIF) && (uiCoordinateX < RECT_WIDTH(pstDeviceIF->stSize)) && (uiCoordinateY < RECT_HEIGHT(pstDeviceIF->stSize)))
    {
    	if(NULL == pstDeviceIF->fnSetPixel)
		{
			/* Action function is unspecified, no actions. */
		}
		else
		{
			eColor = pstDeviceIF->fnGetPixel(uiCoordinateX, uiCoordinateY);
        }
    }

    return eColor;
}

/*************************************************************************/
/** Function Name:	SGUI_Basic_ClearScreen								**/
/** Purpose:		Clean LCD screen display.							**/
/** Params:																**/
/**	@ pstDeviceIF[in]:	SimpleGUI object pointer.						**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_Basic_ClearScreen(SGUI_SCR_DEV* pstDeviceIF)
{
    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    if(NULL != pstDeviceIF)
	{
		/* Clear screen. */
        if((NULL != pstDeviceIF->fnClear) && (NULL != pstDeviceIF->fnSyncBuffer))
		{
			pstDeviceIF->fnClear();
		}
		else
		{
		    /* Draw a blank rectangle for clean screen when clean function is not supposed. */
			SGUI_Basic_DrawRectangle(pstDeviceIF, 0, 0, RECT_WIDTH(pstDeviceIF->stSize), RECT_HEIGHT(pstDeviceIF->stSize), SGUI_COLOR_BKGCLR, SGUI_COLOR_BKGCLR);
		}
	}
}

/*************************************************************************/
/** Function Name:	SGUI_Basic_DrawLine									**/
/** Purpose:		Draw a line by the Bresenham algorithm.				**/
/** Params:																**/
/**	@ pstDeviceIF[in]:	SimpleGUI object pointer.						**/
/**	@ iStartX[in]:		X coordinate of start point of line.			**/
/**	@ iStartY[in]:		Y coordinate of start point of line.			**/
/**	@ iEndX[in]:		X coordinate of end point of line.				**/
/**	@ iEndY[in]:		Y coordinate of end point of line.				**/
/**	@ eColor[in]:		Line color.										**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_Basic_DrawLine(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iStartX, SGUI_INT iStartY, SGUI_INT iEndX, SGUI_INT iEndY, SGUI_COLOR eColor)
{
    /*----------------------------------*/
    /* Variable Declaration				*/
    /*----------------------------------*/
    SGUI_INT					iDx, iDy;
    SGUI_INT					iIncX, iIncY;
    SGUI_INT					iErrX = 0, iErrY = 0;
    SGUI_INT					i, iDs;
    SGUI_INT					iCurrentPosX, iCurrentPosY;

    /*----------------------------------*/
    /* Initialize						*/
    /*----------------------------------*/
    iErrX = 0;
    iErrY = 0;
    iDx = iEndX - iStartX;
    iDy = iEndY - iStartY;
    iCurrentPosX = iStartX;
    iCurrentPosY = iStartY;

    if(iDx > 0)
    {
        iIncX = 1;
    }
    else
    {
        if(iDx == 0)
        {
            iIncX = 0;
        }
        else
        {
            iIncX = -1;
            iDx = -iDx;
        }
    }

    if(iDy > 0)
    {
        iIncY = 1;
    }
    else
    {
        if(iDy == 0)
        {
            iIncY = 0;
        }
        else
        {
            iIncY = -1;
            iDy = -iDy;
        }
    }

    if(iDx > iDy)
    {
        iDs = iDx;
    }
    else
    {
        iDs = iDy;
    }

    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    for(i = 0; i <= iDs+1; i++)
    {
        SGUI_Basic_DrawPoint(pstDeviceIF, iCurrentPosX,iCurrentPosY, eColor);
        iErrX += iDx;
        if(iErrX > iDs)
        {
            iErrX -= iDs;
            iCurrentPosX += iIncX;
        }
        iErrY += iDy;
        if(iErrY > iDs)
        {
            iErrY -= iDs;
            iCurrentPosY += iIncY;
        }
    }
}

/*************************************************************************/
/** Function Name:	SGUI_Basic_DrawLine									**/
/** Purpose:		Draw a line by the Bresenham algorithm.				**/
/** Params:																**/
/**	@ pstDeviceIF[in]:	SimpleGUI object pointer.						**/
/**	@ pstStartPoint[in]: Start point coordinate.						**/
/**	@ pstEndPoint[in]: End point coordinate.							**/
/**	@ pcstArea[in]:	Visible area.										**/
/**	@ eColor[in]:	Line color.											**/
/** Return:			None.												**/
/** Notice:			Only paint in visible area order by pcstArea, point	**/
/**					out of range will be ignore.						**/
/*************************************************************************/
void SGUI_Basic_DrawLineInArea(SGUI_SCR_DEV* pstDeviceIF, SGUI_POINT* pstStartPoint, SGUI_POINT* pstEndPoint, const SGUI_RECT* pcstArea, SGUI_COLOR eColor)
{
	/*----------------------------------*/
    /* Variable Declaration				*/
    /*----------------------------------*/
    SGUI_INT					iDx, iDy;
    SGUI_INT					iIncX, iIncY;
    SGUI_INT					iErrX = 0, iErrY = 0;
    SGUI_INT					i, iDs;
    SGUI_INT					iCurrentPosX, iCurrentPosY;

    /*----------------------------------*/
    /* Initialize						*/
    /*----------------------------------*/
    iErrX = 0;
    iErrY = 0;
    iDx = pstEndPoint->iX - pstStartPoint->iX;
    iDy = pstEndPoint->iY - pstStartPoint->iY;
    iCurrentPosX = pstStartPoint->iX;
    iCurrentPosY = pstStartPoint->iY;

    if(iDx > 0)
    {
        iIncX = 1;
    }
    else
    {
        if(iDx == 0)
        {
            iIncX = 0;
        }
        else
        {
            iIncX = -1;
            iDx = -iDx;
        }
    }

    if(iDy > 0)
    {
        iIncY = 1;
    }
    else
    {
        if(iDy == 0)
        {
            iIncY = 0;
        }
        else
        {
            iIncY = -1;
            iDy = -iDy;
        }
    }

    if(iDx > iDy)
    {
        iDs = iDx;
    }
    else
    {
        iDs = iDy;
    }

    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    for(i = 0; i <= iDs+1; i++)
    {
    	/* Only paint in visible area. */
    	if(	(iCurrentPosX >= RECT_X_START(*pcstArea)) &&
			(iCurrentPosX <= RECT_X_END(*pcstArea)) &&
			(iCurrentPosY >= RECT_Y_START(*pcstArea)) &&
			(iCurrentPosY <= RECT_Y_END(*pcstArea)))
		{
			SGUI_Basic_DrawPoint(pstDeviceIF, iCurrentPosX,iCurrentPosY, eColor);
		}
        iErrX += iDx;
        if(iErrX > iDs)
        {
            iErrX -= iDs;
            iCurrentPosX += iIncX;
        }
        iErrY += iDy;
        if(iErrY > iDs)
        {
            iErrY -= iDs;
            iCurrentPosY += iIncY;
        }
    }
}

/*************************************************************************/
/** Function Name:	SGUI_Basic_DrawRectangle							**/
/** Purpose:		Draw a rectangle on screen. 						**/
/** Params:																**/
/**	@ pstDeviceIF[in]:	SimpleGUI object pointer.						**/
/**	@ uiStartX[in]:		X coordinate of the upper-left corner.			**/
/**	@ uiStartY[in]:		Y coordinate of the upper-left corner.			**/
/**	@ uiWidth[in]: .	Width of rectangle.								**/
/**	@ uiHeight[in]:		Height of rectangle.							**/
/**	@ eEdgeColor[in]:	Edge color.										**/
/**	@ eFillColor[in]:	Fill color.										**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_Basic_DrawRectangle(SGUI_SCR_DEV* pstDeviceIF, SGUI_UINT uiStartX, SGUI_UINT uiStartY, SGUI_UINT uiWidth, SGUI_UINT uiHeight, SGUI_COLOR eEdgeColor, SGUI_COLOR eFillColor)
{
    /*----------------------------------*/
    /* Variable Declaration				*/
    /*----------------------------------*/
    SGUI_UINT					uiColumnIndex;

    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    if((uiWidth > 0) && (uiHeight > 0))
    {
        if((uiWidth == 1) && (uiHeight == 1))
        {
            SGUI_Basic_DrawPoint(pstDeviceIF, uiStartX, uiStartY, eEdgeColor);
        }
        else if(uiWidth == 1)
        {
            SGUI_Basic_DrawLine(pstDeviceIF, uiStartX, uiStartY, uiStartX, uiStartY+uiHeight-1, eEdgeColor);
        }
        else if(uiHeight == 1)
        {
            SGUI_Basic_DrawLine(pstDeviceIF, uiStartX, uiStartY, uiStartX+uiWidth-1, uiStartY, eEdgeColor);
        }
        else
        {
            // Draw edge.
            // Check and set changed page and column index is in edge display action.
            SGUI_Basic_DrawLine(pstDeviceIF, uiStartX, uiStartY, uiStartX, uiStartY+uiHeight-1, eEdgeColor);
            SGUI_Basic_DrawLine(pstDeviceIF, uiStartX+uiWidth-1, uiStartY, uiStartX+uiWidth-1, uiStartY+uiHeight-1, eEdgeColor);
            SGUI_Basic_DrawLine(pstDeviceIF, uiStartX, uiStartY, uiStartX+uiWidth-1, uiStartY, eEdgeColor);
            SGUI_Basic_DrawLine(pstDeviceIF, uiStartX, uiStartY+uiHeight-1, uiStartX+uiWidth-1, uiStartY+uiHeight-1, eEdgeColor);
            // Fill area.
            if((eFillColor != SGUI_COLOR_TRANS) && (uiWidth > 2) && (uiHeight > 2))
            {
                for(uiColumnIndex=(uiStartX+1); uiColumnIndex<(uiStartX+uiWidth-1); uiColumnIndex++)
                {
                    SGUI_Basic_DrawLine(pstDeviceIF, uiColumnIndex, uiStartY+1, uiColumnIndex, uiStartY+uiHeight-2, eFillColor);
                }
            }
        }
    }
}

/*************************************************************************/
/** Function Name:	SGUI_Basic_DrawCircle								**/
/** Purpose:		Draw a circle by center coordinate and radius.		**/
/** Params:																**/
/**	@ pstDeviceIF[in]:	SimpleGUI object pointer.							**/
/**	@ uiCx[in]:			Circle center X coordinate.						**/
/**	@ uiCy[in]:			Circle center Y coordinate.						**/
/**	@ uiRadius[in]:		Circle radius.									**/
/**	@ eEdgeColor[in]:	Edge color.										**/
/**	@ eFillColor[in]:	Fill color.										**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_Basic_DrawCircle(SGUI_SCR_DEV* pstDeviceIF, SGUI_UINT uiCx, SGUI_UINT uiCy, SGUI_UINT uiRadius, SGUI_COLOR eEdgeColor, SGUI_COLOR eFillColor)
{
    /*----------------------------------*/
    /* Variable Declaration				*/
    /*----------------------------------*/
    SGUI_UINT					uiPosXOffset, uiYOffset;
    SGUI_UINT					uiPosXOffset_Old, uiYOffset_Old;
    SGUI_INT					iXChange, iYChange, iRadiusError;

    /*----------------------------------*/
    /* Initialize						*/
    /*----------------------------------*/
    uiPosXOffset				= uiRadius;
    uiYOffset				= 0;
    uiPosXOffset_Old			= 0xFFFF;
    uiYOffset_Old			= 0xFFFF;
    iXChange					= 1 - 2 * uiRadius;
    iYChange					= 1;
    iRadiusError				= 0;

    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    if(uiRadius < 1)
    {
        SGUI_Basic_DrawPoint(pstDeviceIF, uiCx, uiCy, eEdgeColor);
    }
    else
    {
        while(uiPosXOffset >= uiYOffset)
        {
            if((uiPosXOffset_Old != uiPosXOffset) || (uiYOffset_Old != uiYOffset) )
            {
                // Fill the circle
                if((uiRadius > 1) && (eFillColor != SGUI_COLOR_TRANS) && (uiPosXOffset_Old != uiPosXOffset))
                {
                    SGUI_Basic_DrawLine(pstDeviceIF, uiCx-uiPosXOffset, uiCy-uiYOffset+1, uiCx-uiPosXOffset, uiCy+uiYOffset-1, eFillColor);
                    SGUI_Basic_DrawLine(pstDeviceIF, uiCx+uiPosXOffset, uiCy-uiYOffset+1, uiCx+uiPosXOffset, uiCy+uiYOffset-1, eFillColor);
                    uiPosXOffset_Old = uiPosXOffset;
                }
				if ((uiRadius > 1) && (eFillColor != SGUI_COLOR_TRANS) && (uiYOffset_Old != uiYOffset))
				{
                    SGUI_Basic_DrawLine(pstDeviceIF, uiCx-uiYOffset, uiCy-uiPosXOffset+1, uiCx-uiYOffset, uiCy+uiPosXOffset-1, eFillColor);
                    SGUI_Basic_DrawLine(pstDeviceIF, uiCx+uiYOffset, uiCy-uiPosXOffset+1, uiCx+uiYOffset, uiCy+uiPosXOffset-1, eFillColor);
                    uiYOffset_Old = uiYOffset;
                }
                // Draw edge.
                SGUI_Basic_DrawPoint(pstDeviceIF, uiCx+uiPosXOffset, uiCy+uiYOffset, eEdgeColor);
                SGUI_Basic_DrawPoint(pstDeviceIF, uiCx-uiPosXOffset, uiCy+uiYOffset, eEdgeColor);
                SGUI_Basic_DrawPoint(pstDeviceIF, uiCx-uiPosXOffset, uiCy-uiYOffset, eEdgeColor);
                SGUI_Basic_DrawPoint(pstDeviceIF, uiCx+uiPosXOffset, uiCy-uiYOffset, eEdgeColor);
                SGUI_Basic_DrawPoint(pstDeviceIF, uiCx+uiYOffset, uiCy+uiPosXOffset, eEdgeColor);
                SGUI_Basic_DrawPoint(pstDeviceIF, uiCx-uiYOffset, uiCy+uiPosXOffset, eEdgeColor);
                SGUI_Basic_DrawPoint(pstDeviceIF, uiCx-uiYOffset, uiCy-uiPosXOffset, eEdgeColor);
                SGUI_Basic_DrawPoint(pstDeviceIF, uiCx+uiYOffset, uiCy-uiPosXOffset, eEdgeColor);
            }
            uiYOffset++;
            iRadiusError += iYChange;
            iYChange += 2;
            if ((2 * iRadiusError + iXChange) > 0)
            {
                uiPosXOffset--;
                iRadiusError += iXChange;
                iXChange += 2;
            }
        }
    }
}

/*************************************************************************/
/** Function Name:	SGUI_Basic_ReverseBlockColor						**/
/** Purpose:		Reverse all pixel color in a rectangle area.		**/
/** Params:																**/
/**	@ pstDeviceIF[in]:	SimpleGUI object pointer.							**/
/**	@ uiStartX[in]:		X coordinate of the upper-left corner.			**/
/**	@ uiStartY[in]:		Y coordinate of the upper-left corner.			**/
/**	@ uiWidth[in]: .	Width of rectangle.								**/
/**	@ uiHeight[in]:		Height of rectangle.							**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_Basic_ReverseBlockColor(SGUI_SCR_DEV* pstDeviceIF, SGUI_UINT uiStartX, SGUI_UINT uiStartY, SGUI_UINT uiWidth, SGUI_UINT uiHeight)
{
    /*----------------------------------*/
    /* Variable Declaration				*/
    /*----------------------------------*/
    SGUI_UINT					i_W, i_H;
    SGUI_COLOR 					eColor;

    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    for(i_W=0; i_W<uiWidth; i_W++)
    {
        for(i_H=0; i_H<uiHeight; i_H++)
        {
            eColor=SGUI_Basic_GetPoint(pstDeviceIF, uiStartX+i_W, uiStartY+i_H);
            eColor=SGUI_Basic_GetReverseColor(pstDeviceIF->uiDepthBits,eColor);
			SGUI_Basic_DrawPoint(pstDeviceIF, uiStartX + i_W, uiStartY + i_H, eColor);
        }
    }
}

/*************************************************************************/
/** Function Name:	SGUI_Basic_DrawBitMap								**/
/** Purpose:		Draw a rectangular area bit map on LCD screen.		**/
/** Params:																**/
/**	@ pstDeviceIF[in]:	SimpleGUI object pointer.						**/
/**	@ pstDisplayArea[in]: Display area position and size.				**/
/**	@ pstInnerPos[in]:	Data area size and display offset.				**/
/**	@ pstBitmapData[in]: Bitmap object, include size, depth and data.	**/
/**	@ eDrawMode[in]		Bit map display mode(normal or reverse color).	**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_Basic_DrawBitMap(SGUI_SCR_DEV* pstDeviceIF, SGUI_RECT* pstDisplayArea, SGUI_POINT* pstInnerPos, const SGUI_BMP_RES* pstBitmapData, SGUI_DRAW_MODE eDrawMode)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_INT					iDrawPixX, iDrawPixY;
	SGUI_INT					iBmpPixX, iBmpPixY;
	SGUI_UINT					uiDrawnWidthIndex, uiDrawnHeightIndex;
	SGUI_COLOR                  eColor;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	uiDrawnWidthIndex			= 0;
	uiDrawnHeightIndex			= 0;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Only draw in visible area of screen.
	if(	(RECT_X_START(*pstDisplayArea) < RECT_WIDTH(pstDeviceIF->stSize)) && (RECT_Y_START(*pstDisplayArea) < RECT_HEIGHT(pstDeviceIF->stSize)) &&
		(RECT_X_END(*pstDisplayArea) > 0) && (RECT_Y_END(*pstDisplayArea) > 0))
	{
		// Adapt text display area and data area.
        SGUI_Common_AdaptDisplayInfo(pstDisplayArea, pstInnerPos);
		// Only process drawing when valid display data existed
		if((RECT_VALID_WIDTH(*pstBitmapData, *pstInnerPos) > 0) && (RECT_VALID_HEIGHT(*pstBitmapData, *pstInnerPos) > 0))
		{
			// Set loop start parameter of x coordinate
			iDrawPixX = RECT_X_START(*pstDisplayArea);
			iBmpPixX = 0;
			if(RECT_X_START(*pstInnerPos) > 0)
			{
				iDrawPixX += RECT_X_START(*pstInnerPos);
			}
			else
			{
				iBmpPixX -= RECT_X_START(*pstInnerPos);
			}
			uiDrawnWidthIndex = iBmpPixX;
			// Loop for x coordinate;
			while((uiDrawnWidthIndex<RECT_WIDTH(*pstBitmapData)) && (iDrawPixX<=RECT_X_END(*pstDisplayArea)) && (iDrawPixX<RECT_WIDTH(pstDeviceIF->stSize)))
			{
				// Set loop start parameter of y coordinate
				iDrawPixY = RECT_Y_START(*pstDisplayArea);
				iBmpPixY = 0;
				if(RECT_Y_START(*pstInnerPos) > 0)
				{
					iDrawPixY += RECT_Y_START(*pstInnerPos);
				}
				else
				{
					iBmpPixY -= RECT_Y_START(*pstInnerPos);
				}
				uiDrawnHeightIndex = iBmpPixY;
				// Loop for y coordinate;
				while((uiDrawnHeightIndex<RECT_HEIGHT(*pstBitmapData)) && (iDrawPixY<=RECT_Y_END(*pstDisplayArea)) && (iDrawPixY<RECT_HEIGHT(pstDeviceIF->stSize)))
				{
					if(pstBitmapData->fnGetPixel!=NULL)
					{
						eColor = pstBitmapData->fnGetPixel(pstBitmapData,iBmpPixX,iBmpPixY);
					}
					else
					{
						eColor = SGUI_Basic_BitMapScanDVPV(pstBitmapData,iBmpPixX,iBmpPixY);
					}

					if(eDrawMode == SGUI_DRAW_REVERSE)
					{
						eColor = SGUI_Basic_GetReverseColor(pstBitmapData->iDepthBits,eColor);
					}
					if(pstDeviceIF->uiDepthBits != pstBitmapData->iDepthBits)
					{
						eColor = SGUI_Basic_MapColor(pstBitmapData->iDepthBits,eColor,pstDeviceIF->uiDepthBits);
					}
					SGUI_Basic_DrawPoint(pstDeviceIF,iDrawPixX,iDrawPixY,eColor);
					uiDrawnHeightIndex ++;
					iDrawPixY ++;
					iBmpPixY ++;
				}
				uiDrawnWidthIndex ++;
				iDrawPixX ++;
				iBmpPixX ++;
			}
		}
	}
}

/*************************************************************************/
/** Function Name:	SGUI_Basic_BitMapScanDHPH   						**/
/** Purpose:		Scan the BitMap data by Data Horizontally and Pixel	**/
/**                 Horizontally and return the Pixel Data              **/
/** Params:																**/
/**	@ pDataBuffer[in]:  the raw BitMap data.						    **/
/**	@ uiDepth[in]:      the pixel depth.                				**/
/**	@ uiX[in]:	        the coordinate X of BitMap.                     **/
/**	@ uiY[in]:	        the coordinate Y of BitMap.                     **/
/** Return:			the Pixel Color at (uiX,uiY).				        **/
/** Notice:			None.												**/
/*************************************************************************/
SGUI_COLOR   SGUI_Basic_BitMapScanDHPH(const SGUI_BMP_RES* pstBitmapData,SGUI_UINT8 uiX,SGUI_UINT8 uiY)
{
	// TODO
	return SGUI_COLOR_BKGCLR;
}

/*************************************************************************/
/** Function Name:	SGUI_Basic_BitMapScanDHPV   						**/
/** Purpose:		Scan the BitMap data by Data Horizontally and Pixel	**/
/**                 Vertically and return the Pixel Data                **/
/** Params:																**/
/**	@ pDataBuffer[in]:  the raw BitMap data.						    **/
/**	@ uiDepth[in]:      the pixel depth.                				**/
/**	@ uiX[in]:	        the coordinate X of BitMap.                     **/
/**	@ uiY[in]:	        the coordinate Y of BitMap.                     **/
/** Return:			the Pixel Color at (uiX,uiY).				        **/
/** Notice:			None.												**/
/*************************************************************************/
SGUI_COLOR   SGUI_Basic_BitMapScanDHPV(const SGUI_BMP_RES* pstBitmapData,SGUI_UINT8 uiX,SGUI_UINT8 uiY)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_COLOR          eColor;
	SGUI_UINT8          uiPixelPerByte;
	SGUI_UINT8          uiByteRow;
	SGUI_CBYTE*         pData;
	SGUI_BYTE           cTemp;
	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	eColor              = 0;
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if( pstBitmapData->iDepthBits == 1 ||
	        pstBitmapData->iDepthBits == 2 ||
	        pstBitmapData->iDepthBits == 4 ||
	        pstBitmapData->iDepthBits == 8 )
	{
		uiPixelPerByte      = 8 / pstBitmapData->iDepthBits;
		uiByteRow           = uiY / uiPixelPerByte;
		pData               = pstBitmapData->pData + uiByteRow * pstBitmapData->iWidth + uiX;
		cTemp               = (*pData)>>(uiY%8*pstBitmapData->iDepthBits);
		eColor             |= cTemp & ((0x1<<pstBitmapData->iDepthBits)-1);
	}
	return eColor;
}

/*************************************************************************/
/** Function Name:	SGUI_Basic_BitMapScanDVPH   						**/
/** Purpose:		Scan the BitMap data by Data Vertically and Pixel   **/
/**                 Horizontally and return the Pixel Data              **/
/** Params:																**/
/**	@ pDataBuffer[in]:  the raw BitMap data.						    **/
/**	@ uiDepth[in]:      the pixel depth.                				**/
/**	@ uiX[in]:	        the coordinate X of BitMap.                     **/
/**	@ uiY[in]:	        the coordinate Y of BitMap.                     **/
/** Return:			the Pixel Color at (uiX,uiY).				        **/
/** Notice:			None.												**/
/*************************************************************************/
SGUI_COLOR   SGUI_Basic_BitMapScanDVPH(const SGUI_BMP_RES* pstBitmapData,SGUI_UINT8 uiX,SGUI_UINT8 uiY)
{
	// TODO
	return SGUI_COLOR_BKGCLR;
}

/*************************************************************************/
/** Function Name:	SGUI_Basic_BitMapScanDVPV   						**/
/** Purpose:		Scan the BitMap data by Data Vertically and Pixel	**/
/**                 Vertically and return the Pixel Data                **/
/** Params:																**/
/**	@ pDataBuffer[in]:  the raw BitMap data.						    **/
/**	@ uiDepth[in]:      the pixel depth.                				**/
/**	@ uiX[in]:	        the coordinate X of BitMap.                     **/
/**	@ uiY[in]:	        the coordinate Y of BitMap.                     **/
/** Return:			the Pixel Color at (uiX,uiY).				        **/
/** Notice:			None.												**/
/*************************************************************************/
SGUI_COLOR   SGUI_Basic_BitMapScanDVPV(const SGUI_BMP_RES* pstBitmapData,SGUI_UINT8 uiX,SGUI_UINT8 uiY)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_UINT8          uiBytesPerColomn;
	SGUI_UINT16         uiBitIndex;
	SGUI_UINT16         uiByteOffset;
	SGUI_COLOR          eColor;
	const SGUI_BYTE*    pData;
	SGUI_BYTE           ucTemp;
	SGUI_UINT8          i;

	/*----------------------------------*/
	/* Initialize       				*/
	/*----------------------------------*/
	eColor = 0;
	/*----------------------------------*/
	/* Process          				*/
	/*----------------------------------*/
	uiBytesPerColomn    = (pstBitmapData->iDepthBits * pstBitmapData->iHeight + 7)/8;
	uiBitIndex          = pstBitmapData->iDepthBits *  uiY;
	uiByteOffset        = uiBytesPerColomn*uiX+uiBitIndex / 8;
	uiBitIndex          = uiBitIndex % 8;
	pData               = pstBitmapData->pData+uiByteOffset;
	ucTemp              = ((*pData) << uiBitIndex) & 0xFF;
	for(i=0; i<pstBitmapData->iDepthBits; i++)
	{
		eColor <<= 1;
		eColor |=  (ucTemp & 0x80) ? 0x1 : 0x0;

		ucTemp <<= 1;
		uiBitIndex += 1;
		if(uiBitIndex == 8 )
		{
			pData++;
			ucTemp=*pData;
			uiBitIndex = 0;
		}
	}
	return eColor;
}

/*************************************************************************/
/** Function Name:	SGUI_Basic_PointIsInArea							**/
/** Purpose:		Judge point is in the specified rectangular area.	**/
/** Params:																**/
/**	@ pstArea[in]:	Specified rectangular area.							**/
/**	@ pstPoint[in]:	Point coordinate.									**/
/** Return:			SGUI_TRUE for the point is in the rectangular area.	**/
/**					SGUI_FALSE for the point is out of range.			**/
/** Notice:			None.												**/
/*************************************************************************/
SGUI_BOOL SGUI_Basic_PointIsInArea(const SGUI_RECT* pstArea, const SGUI_POINT* pstPoint)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_BOOL					bReturn;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	bReturn						= SGUI_TRUE;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL == pstArea) || (NULL == pstPoint))
	{
		bReturn = SGUI_FALSE;
	}
	else
	{
        if(	(pstPoint->iX < RECT_X_START(*pstArea)) ||
			(pstPoint->iX > RECT_X_END(*pstArea)) ||
			(pstPoint->iY < RECT_Y_START(*pstArea)) ||
			(pstPoint->iY > RECT_Y_END(*pstArea)))
		{
			bReturn = SGUI_FALSE;
		}
	}
	return bReturn;
}
/*************************************************************************/
/** Function Name:	SGUI_Basic_GetReverseColor							**/
/** Purpose:		Calculate the reverse color of eOriginColor when 	**/
/**                 there is uiDepthBits bits is used to present depth  **/
/** Params:																**/
/**	@ uiDepthBits[in]:	Specified current depth bit count.  			**/
/**	@ eOriginColor[in]:	Specified the origin color which will be        **/
/**                     reverted.									    **/
/** Return:			The revert color of eOriginColor                	**/
/** Notice:			Author:Jerry    									**/
/*************************************************************************/
SGUI_COLOR SGUI_Basic_GetReverseColor(const SGUI_UINT8 uiDepthBits,SGUI_COLOR eOriginColor)
{
	return (1<<uiDepthBits)-1-eOriginColor;
}
/*************************************************************************/
/** Function Name:	SGUI_Basic_MapColor     							**/
/** Purpose:		Calculate the mapped color in uiTargetDepthBits     **/
/**                 color space of eOriginColor in uiOriginDepthBits    **/
/**                 color space.                                        **/
/** Params:																**/
/**	@ uiOriginDepthBits[in]:    Origin color space depth bit count.		**/
/**	@ eOriginColor[in]:         Origin color.                    		**/
/**	@ uiTargetDepthBits[in]:	Target color space depth bit count.     **/
/** Return:			The target color of eOriginColor                	**/
/** Notice:			Author:Jerry    									**/
/*************************************************************************/
SGUI_COLOR SGUI_Basic_MapColor(const SGUI_UINT8 uiOriginDepthBits,const SGUI_COLOR eOriginColor,const SGUI_UINT8 uiTargetDepthBits)
{
	SGUI_UINT16 uiOriginSpace=(1<<uiOriginDepthBits)-1;
	SGUI_UINT16 uiTargetSpace=(1<<uiTargetDepthBits)-1;
	return (SGUI_COLOR)(eOriginColor*1.0/uiOriginSpace*uiTargetSpace);
}
