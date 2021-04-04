/*************************************************************************/
/** Copyright.															**/
/** FileName: SGUI_Basic.c												**/
/** Author: XuYulin,Jerry   											**/
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
/**	@ pstDeviceIF[in]: Device driver object pointer.					**/
/**	@ iPosX[in]:    X coordinate of point by pixels.                    **/
/**	@ iPosY[in]:    Y coordinate of point by pixels.                    **/
/**	@ eColor[in]:		Point color, GUI_COLOR_BKGCLR means clear pix, 	**/
/**						GUI_COLOR_FRGCLR means set pix.					**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_Basic_DrawPoint(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iPosX, SGUI_INT iPosY, SGUI_COLOR eColor)
{
    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    if((NULL != pstDeviceIF) && (iPosX < RECT_WIDTH(pstDeviceIF->stSize)) && (iPosY < RECT_HEIGHT(pstDeviceIF->stSize)))
    {
    	if(NULL == pstDeviceIF->fnSetPixel)
		{
			/* Action function is unspecified, no actions. */
		}
        else
        {
            pstDeviceIF->fnSetPixel(iPosX,iPosY,eColor);
        }
    }
}

/*************************************************************************/
/** Function Name:	SGUI_Basic_GetPoint									**/
/** Purpose:		Get a pixel color .									**/
/** Params:																**/
/**	@ pstDeviceIF[in]: SimpleGUI object pointer.                        **/
/**	@ iPosX[in]:	X coordinate of point by pixels.				    **/
/**	@ iPosY[in]:    Y coordinate of point by pixels.				    **/
/** Return:			SGUI_COLOR type enumerated for point color.			**/
/** Notice:			None.												**/
/*************************************************************************/
SGUI_COLOR SGUI_Basic_GetPoint(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iPosX, SGUI_INT iPosY)
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
    if((NULL != pstDeviceIF) && (iPosX < RECT_WIDTH(pstDeviceIF->stSize)) && (iPosY < RECT_HEIGHT(pstDeviceIF->stSize)))
    {
    	if(NULL == pstDeviceIF->fnSetPixel)
		{
			/* Action function is unspecified, no actions. */
		}
		else
		{
			eColor = pstDeviceIF->fnGetPixel(iPosX, iPosY);
        }
    }

    return eColor;
}

/*************************************************************************/
/** Function Name:	SGUI_Basic_ClearScreen								**/
/** Purpose:		Clean LCD screen display.							**/
/** Params:																**/
/**	@ pstDeviceIF[in]: Device driver object pointer.					**/
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
/**	@ pstDeviceIF[in]: Device driver object pointer.					**/
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
/** Function Name:	SGUI_Basic_DrawHorizontalLine						**/
/** Purpose:		Draw a horizontal line by the Bresenham algorithm.  **/
/** Params:																**/
/**	@ pstDeviceIF[in]:  SimpleGUI object pointer.						**/
/**	@ iStartX[in]:		X coordinate of start point of line.			**/
/**	@ iEndX[in]:		X coordinate of end point of line.				**/
/**	@ iY[in]:           Y coordinate of the line.                       **/
/**	@ eColor[in]:		Line color.										**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_Basic_DrawHorizontalLine(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iStartX, SGUI_INT iEndX, SGUI_INT iY, SGUI_COLOR eColor)
{
    /*----------------------------------*/
    /* Variable Declaration				*/
    /*----------------------------------*/
    SGUI_INT                iPointX;

    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    for(iPointX=iStartX; iPointX<=iEndX; iPointX++)
    {
        SGUI_Basic_DrawPoint(pstDeviceIF, iPointX, iY, eColor);
    }
}

/*************************************************************************/
/** Function Name:	SGUI_Basic_DrawVerticalLine                         **/
/** Purpose:		Draw a vertical line by the Bresenham algorithm.    **/
/** Params:																**/
/**	@ pstDeviceIF[in]: Device driver object pointer.					**/
/**	@ iX[in]:       X coordinate of the line.                           **/
/**	@ iStartY[in]:  Y coordinate of start point of line.                **/
/**	@ iEndY[in]:	Y coordinate of end point of line.			    	**/
/**	@ eColor[in]:	Line color.											**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_Basic_DrawVerticalLine(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iX, SGUI_INT iStartY, SGUI_INT iEndY, SGUI_COLOR eColor)
{
    /*----------------------------------*/
    /* Variable Declaration				*/
    /*----------------------------------*/
    SGUI_INT                iPointY;

    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    for(iPointY=iStartY; iPointY<=iEndY; iPointY++)
    {
        SGUI_Basic_DrawPoint(pstDeviceIF, iX, iPointY, eColor);
    }
}

/*************************************************************************/
/** Function Name:	SGUI_Basic_DrawLine									**/
/** Purpose:		Draw a line by the Bresenham algorithm.				**/
/** Params:																**/
/**	@ pstDeviceIF[in]: Device driver object pointer.					**/
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
/**	@ pstDeviceIF[in]: Device driver object pointer.					**/
/**	@ iStartX[in]:		X coordinate of the upper-left corner.			**/
/**	@ iStartY[in]:		Y coordinate of the upper-left corner.			**/
/**	@ iWidth[in]: .	Width of rectangle.								    **/
/**	@ iHeight[in]:		Height of rectangle.							**/
/**	@ eEdgeColor[in]:	Edge color.										**/
/**	@ eFillColor[in]:	Fill color.										**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_Basic_DrawRectangle(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iStartX, SGUI_INT iStartY, SGUI_INT iWidth, SGUI_INT iHeight, SGUI_COLOR eEdgeColor, SGUI_COLOR eFillColor)
{
    /*----------------------------------*/
    /* Variable Declaration				*/
    /*----------------------------------*/
    SGUI_INT					iColumnIndex;

    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    if((iWidth > 0) && (iHeight > 0))
    {
        if((iWidth == 1) && (iHeight == 1))
        {
            SGUI_Basic_DrawPoint(pstDeviceIF, iStartX, iStartY, eEdgeColor);
        }
        else if(iWidth == 1)
        {
            SGUI_Basic_DrawVerticalLine(pstDeviceIF, iStartX, iStartY, iStartY+iHeight-1, eEdgeColor);
        }
        else if(iHeight == 1)
        {
            SGUI_Basic_DrawHorizontalLine(pstDeviceIF, iStartX, iStartX+iWidth-1, iStartY, eEdgeColor);
        }
        else
        {
            // Draw edge.
            // Check and set changed page and column index is in edge display action.
            // Top edge
            SGUI_Basic_DrawHorizontalLine(pstDeviceIF, iStartX, iStartX+iWidth-1, iStartY, eEdgeColor);
            // Bottom edge
            SGUI_Basic_DrawHorizontalLine(pstDeviceIF, iStartX, iStartX+iWidth-1, iStartY+iHeight-1, eEdgeColor);
            // Left edge
            SGUI_Basic_DrawVerticalLine(pstDeviceIF, iStartX, iStartY+1, iStartY+iHeight-2, eEdgeColor);
            // Right edge
            SGUI_Basic_DrawVerticalLine(pstDeviceIF, iStartX+iWidth-1, iStartY+1, iStartY+iHeight-2, eEdgeColor);
            // Fill area.
            if((eFillColor != SGUI_COLOR_TRANS) && (iWidth > 2) && (iHeight > 2))
            {
                for(iColumnIndex=(iStartX+1); iColumnIndex<(iStartX+iWidth-1); iColumnIndex++)
                {
                    SGUI_Basic_DrawVerticalLine(pstDeviceIF, iColumnIndex, iStartY+1, iStartY+iHeight-2, eFillColor);
                }
            }
        }
    }
}

/*************************************************************************/
/** Function Name:	SGUI_Basic_DrawCircle								**/
/** Purpose:		Draw a circle by center coordinate and radius.		**/
/** Params:																**/
/**	@ pstDeviceIF[in]:	SimpleGUI object pointer.                       **/
/**	@ iCx[in]:			Circle center X coordinate.						**/
/**	@ iCy[in]:			Circle center Y coordinate.						**/
/**	@ iRadius[in]:		Circle radius.									**/
/**	@ eEdgeColor[in]:	Edge color.										**/
/**	@ eFillColor[in]:	Fill color.										**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_Basic_DrawCircle(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iCx, SGUI_INT iCy, SGUI_INT iRadius, SGUI_COLOR eEdgeColor, SGUI_COLOR eFillColor)
{
    /*----------------------------------*/
    /* Variable Declaration				*/
    /*----------------------------------*/
    SGUI_INT                iPosXOffset = iRadius;
    SGUI_INT                iPosYOffset = 0;
    SGUI_INT                iPosXOffset_Old = -1;
    SGUI_INT                iPosYOffset_Old = -1;
    SGUI_INT                iXChange = 1 - (iRadius<<1); /* iRadius*2 */
    SGUI_INT                iYChange = 1;
    SGUI_INT                iRadiusError = 0;

    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    if(iRadius < 1)
    {
        SGUI_Basic_DrawPoint(pstDeviceIF, iCx, iCy, eEdgeColor);
    }
    else
    {
        while(iPosXOffset >= iPosYOffset)
        {
            if((iPosXOffset_Old != iPosXOffset) || (iPosYOffset_Old != iPosYOffset) )
            {
                // Fill the circle
                if((iRadius > 1) && (eFillColor != SGUI_COLOR_TRANS) && (iPosXOffset_Old != iPosXOffset))
                {

                    SGUI_Basic_DrawLine(pstDeviceIF, iCx-iPosXOffset, iCy-iPosYOffset+1, iCx-iPosXOffset, iCy+iPosYOffset-1, eFillColor);
                    SGUI_Basic_DrawLine(pstDeviceIF, iCx+iPosXOffset, iCy-iPosYOffset+1, iCx+iPosXOffset, iCy+iPosYOffset-1, eFillColor);

                }
                SGUI_Basic_DrawLine(pstDeviceIF, iCx-iPosYOffset, iCy-iPosXOffset+1, iCx-iPosYOffset, iCy+iPosXOffset-1, eFillColor);
                SGUI_Basic_DrawLine(pstDeviceIF, iCx+iPosYOffset, iCy-iPosXOffset+1, iCx+iPosYOffset, iCy+iPosXOffset-1, eFillColor);

                // Draw edge.
                SGUI_Basic_DrawPoint(pstDeviceIF, iCx+iPosXOffset, iCy+iPosYOffset, eEdgeColor);
                SGUI_Basic_DrawPoint(pstDeviceIF, iCx-iPosXOffset, iCy+iPosYOffset, eEdgeColor);
                SGUI_Basic_DrawPoint(pstDeviceIF, iCx-iPosXOffset, iCy-iPosYOffset, eEdgeColor);
                SGUI_Basic_DrawPoint(pstDeviceIF, iCx+iPosXOffset, iCy-iPosYOffset, eEdgeColor);
                SGUI_Basic_DrawPoint(pstDeviceIF, iCx+iPosYOffset, iCy+iPosXOffset, eEdgeColor);
                SGUI_Basic_DrawPoint(pstDeviceIF, iCx-iPosYOffset, iCy+iPosXOffset, eEdgeColor);
                SGUI_Basic_DrawPoint(pstDeviceIF, iCx-iPosYOffset, iCy-iPosXOffset, eEdgeColor);
                SGUI_Basic_DrawPoint(pstDeviceIF, iCx+iPosYOffset, iCy-iPosXOffset, eEdgeColor);

                iPosYOffset_Old = iPosYOffset;
                iPosXOffset_Old = iPosXOffset;
            }
            iPosYOffset++;
            iRadiusError += iYChange;
            iYChange += 2;
            if ((2 * iRadiusError + iXChange) > 0)
            {
                iPosXOffset--;
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
/**	@ pstDeviceIF[in]:vSimpleGUI object pointer.						**/
/**	@ iStartX[in]:	X coordinate of the upper-left corner.				**/
/**	@ iStartY[in]:	Y coordinate of the upper-left corner.				**/
/**	@ iWidth[in]:	Width of rectangle.									**/
/**	@ iHeight[in]:	Height of rectangle.								**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_Basic_ReverseBlockColor(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iStartX, SGUI_INT iStartY, SGUI_INT iWidth, SGUI_INT iHeight)
{
    /*----------------------------------*/
    /* Variable Declaration				*/
    /*----------------------------------*/
    SGUI_INT					iIdxW, iIdxH;
    SGUI_COLOR 					eColor;

    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    for(iIdxW=0; iIdxW<iWidth; iIdxW++)
    {
        for(iIdxH=0; iIdxH<iHeight; iIdxH++)
        {
            eColor=SGUI_Basic_GetPoint(pstDeviceIF, iStartX+iIdxW, iStartY+iIdxH);
            #ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
            eColor=SGUI_Basic_GetReverseColor(pstDeviceIF->uiDepthBits,eColor);
            #else
            eColor=SGUI_Basic_GetReverseColor(SGUI_CONF_GRAYSCALE_DEPTH_BITS,eColor);
            #endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
			SGUI_Basic_DrawPoint(pstDeviceIF, iStartX + iIdxW, iStartY + iIdxH, eColor);
        }
    }
}
/*************************************************************************/
/** Function Name:	SGUI_Basic_DrawAlphaBitMap							**/
/** Purpose:		Draw a rectangular area alpha bit map on LCD screen.**/
/** Params:																**/
/**	@ pstDeviceIF[in]:	 Device driver object pointer.					**/
/**	@ pstDisplayArea[in]: Display area position and size.				**/
/**	@ pstInnerPos[in]:	Data area size and display offset.				**/
/**	@ pstBitmapData[in]: Bitmap object, include size, depth and data.	**/
/**	@ eTargetColor[in]:	Target color, which will be render with         **/
/**                     background.	                                    **/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_Basic_DrawAlphaBitMap(SGUI_SCR_DEV* pstDeviceIF, SGUI_RECT* pstDisplayArea,SGUI_POINT* pstInnerPos, const SGUI_BMP_RES* pstBitmapData, SGUI_COLOR eTargetColor)
{
    /*----------------------------------*/
    /* Variable Declaration				*/
    /*----------------------------------*/
    SGUI_INT					iDrawPixX, iDrawPixY;
    SGUI_INT					iBmpPixX, iBmpPixY;
    SGUI_UINT					uiDrawnWidthIndex, uiDrawnHeightIndex;
    SGUI_COLOR                  eAlpha,eColor,eMaxColor;

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
            #ifdef SGUI_GRAYSCALE_COLOR_MAPPING_ENABLED
            eMaxColor = SGUI_MAXCOLOR(pstDeviceIF->uiDepthBits);
            #else
            eMaxColor = SGUI_MAXCOLOR(SGUI_CONF_GRAYSCALE_DEPTH_BITS);
            #endif
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
                        eAlpha = pstBitmapData->fnGetPixel(pstBitmapData,iBmpPixX,iBmpPixY);
                    }
                    else
                    {
                        eAlpha = SGUI_Basic_BitMapScanDVPV(pstBitmapData,iBmpPixX,iBmpPixY);
                    }
                    #ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
                    if(pstDeviceIF->uiDepthBits != pstBitmapData->uiDepthBits)
                    {
                        eAlpha = SGUI_Basic_MapColor(pstBitmapData->uiDepthBits,eAlpha,pstDeviceIF->uiDepthBits);
                    }
                    #endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
                    eColor = SGUI_Basic_GetPoint(pstDeviceIF,iDrawPixX,iDrawPixY);

                    // calculate the mixed color

                    eColor = (eTargetColor * eAlpha + (eMaxColor - eAlpha)*eColor)/eMaxColor;

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
/** Function Name:	SGUI_Basic_DrawBitMap								**/
/** Purpose:		Draw a rectangular area bit map on LCD screen.		**/
/** Params:																**/
/**	@ pstDeviceIF[in]: Device driver object pointer.					**/
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
	SGUI_INT					iDrawnWidthIndex, iDrawnHeightIndex;
	SGUI_COLOR                  eColor;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	iDrawnWidthIndex			= 0;
	iDrawnHeightIndex			= 0;

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
			iDrawnWidthIndex = iBmpPixX;
			// Loop for x coordinate;
			while((iDrawnWidthIndex<RECT_WIDTH(*pstBitmapData)) && (iDrawPixX<=RECT_X_END(*pstDisplayArea)) && (iDrawPixX<RECT_WIDTH(pstDeviceIF->stSize)))
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
				iDrawnHeightIndex = iBmpPixY;
				// Loop for y coordinate;
				while((iDrawnHeightIndex<RECT_HEIGHT(*pstBitmapData)) && (iDrawPixY<=RECT_Y_END(*pstDisplayArea)) && (iDrawPixY<RECT_HEIGHT(pstDeviceIF->stSize)))
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
					    #ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
						eColor = SGUI_Basic_GetReverseColor(pstBitmapData->uiDepthBits,eColor);
						#else
						eColor = SGUI_Basic_GetReverseColor(SGUI_CONF_GRAYSCALE_DEPTH_BITS,eColor);
						#endif
					}
					#ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
					if(pstDeviceIF->uiDepthBits != pstBitmapData->uiDepthBits)
					{
						eColor = SGUI_Basic_MapColor(pstBitmapData->uiDepthBits,eColor,pstDeviceIF->uiDepthBits);
					}
					#endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
					SGUI_Basic_DrawPoint(pstDeviceIF,iDrawPixX,iDrawPixY,eColor);
					iDrawnHeightIndex ++;
					iDrawPixY ++;
					iBmpPixY ++;
				}
				iDrawnWidthIndex ++;
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
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_COLOR          eColor;
	SGUI_UINT8          uiBytesPerRow;
	SGUI_CBYTE*         pData;
	SGUI_BYTE           cTemp;
	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	#ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
        #define DEPTH_BITS (pstBitmapData->uiDepthBits)
	#else
        #define DEPTH_BITS  SGUI_CONF_GRAYSCALE_DEPTH_BITS
	#endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
	eColor              = 0;
	uiBytesPerRow       = (pstBitmapData->iWidth * DEPTH_BITS + 7)/8;
	pData               = pstBitmapData->pData;
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if( DEPTH_BITS == 1 || DEPTH_BITS == 2 ||
        DEPTH_BITS == 4 || DEPTH_BITS == 8 )
	{
        pData += uiBytesPerRow * uiY + (uiX*DEPTH_BITS)/8;
        cTemp  = (*pData)>>((uiX*DEPTH_BITS)%8);
        eColor = cTemp & ((0x1<<DEPTH_BITS)-1);
	}
	#undef DEPTH_BITS
	return eColor;
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
	#ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
        #define DEPTH_BITS (pstBitmapData->uiDepthBits)
    #else
        #define DEPTH_BITS  SGUI_CONF_GRAYSCALE_DEPTH_BITS
    #endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
	eColor              = 0;
	pData               = pstBitmapData->pData;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if( DEPTH_BITS == 1 || DEPTH_BITS == 2 ||
        DEPTH_BITS == 4 || DEPTH_BITS == 8 )
	{
		uiPixelPerByte      = 8 / DEPTH_BITS;
		uiByteRow           = uiY / uiPixelPerByte;
		pData              += uiByteRow * pstBitmapData->iWidth + uiX;
		cTemp               = (*pData)>>(uiY%uiPixelPerByte*DEPTH_BITS);
		eColor             |= cTemp & ((0x1<<DEPTH_BITS)-1);
	}
	#undef DEPTH_BITS
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
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_COLOR          eColor;
	SGUI_UINT8          uiPixelPerByte;
	SGUI_UINT8          uiByteColumn;
	SGUI_CBYTE*         pData;
	SGUI_BYTE           cTemp;
	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	#ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
        #define DEPTH_BITS (pstBitmapData->uiDepthBits)
    #else
        #define DEPTH_BITS  SGUI_CONF_GRAYSCALE_DEPTH_BITS
    #endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
	eColor              = 0;
	pData               = pstBitmapData->pData;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if( DEPTH_BITS == 1 || DEPTH_BITS == 2 ||
        DEPTH_BITS == 4 || DEPTH_BITS == 8 )
	{
		uiPixelPerByte      = 8 / DEPTH_BITS;
		uiByteColumn        = uiX / uiPixelPerByte;
		pData              += uiByteColumn * pstBitmapData->iHeight + uiY;
		cTemp               = (*pData)>>(uiX%uiPixelPerByte*DEPTH_BITS);
		eColor             |= cTemp & ((0x1<<DEPTH_BITS)-1);
	}
    #undef DEPTH_BITS
	return eColor;
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
	SGUI_COLOR          eColor;
	SGUI_UINT8          uiBytesPerColomn;
	SGUI_CBYTE*         pData;
	SGUI_BYTE           cTemp;

	/*----------------------------------*/
	/* Initialize       				*/
	/*----------------------------------*/
	#ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
        #define DEPTH_BITS (pstBitmapData->uiDepthBits)
    #else
        #define DEPTH_BITS  SGUI_CONF_GRAYSCALE_DEPTH_BITS
    #endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
	eColor = 0;
	uiBytesPerColomn    = (DEPTH_BITS * pstBitmapData->iHeight + 7)/8;
	pData               = pstBitmapData->pData;
	/*----------------------------------*/
	/* Process          				*/
	/*----------------------------------*/
	if( DEPTH_BITS == 1 || DEPTH_BITS == 2 ||
	    DEPTH_BITS == 4 || DEPTH_BITS == 8 )
	{
	    pData += uiBytesPerColomn * uiX + (uiY*DEPTH_BITS)/8;
	    cTemp  = (*pData) >> ((uiY*DEPTH_BITS)%8);
	    eColor = cTemp & ((0x01 << DEPTH_BITS)-1);
	}
	#undef DEPTH_BITS
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
/*************************************************************************/
/** Function Name:	SGUI_Basic_DrawRoundedRectangle                     **/
/** Purpose:		Draw a rounded rectangle.                           **/
/** Params:																**/
/**	@ pstDeviceIF[in]: Device driver object pointer.					**/
/**	@ iStartX[in]:  X coordinate of the upper-left corner.              **/
/**	@ iStartY[in]:  Y coordinate of the upper-left corner.              **/
/**	@ iWidth[in]:   Width of rectangle.								    **/
/**	@ iHeight[in]:  Height of rectangle.							    **/
/**	@ iFillet[in]:  Fillet radius.           						    **/
/**	@ eEdgeColor[in]: Edge color.										**/
/**	@ eFillColor[in]: Fill color.										**/
/** Return:			None.												**/
/** Notice:			The width and height of the rectangle must greater  **/
/**                 then double fillet radius.                          **/
/*************************************************************************/
void SGUI_Basic_DrawRoundedRectangle(SGUI_SCR_DEV* pstDeviceIF, SGUI_INT iStartX, SGUI_INT iStartY, SGUI_INT iWidth, SGUI_INT iHeight, SGUI_INT iFillet, SGUI_COLOR eEdgeColor, SGUI_COLOR eFillColor)
{
    /*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_INT				iPosXOffset = iFillet;
	SGUI_INT                iPosYOffset = 0;
    SGUI_INT                iYOffset_Old = -1;
    SGUI_INT                iXOffset_Old = -1;
    SGUI_INT				iXChange = 1 - (iFillet << 1); /* iFillet*2 */
    SGUI_INT                iYChange = 1;
    SGUI_INT                iRadiusError = 0;
    SGUI_INT                iFillIdx;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/

	if((iWidth > (iFillet<<1)) && (iHeight > (iFillet<<1)))
    {
        // Paint first horizontal line for edge.
        SGUI_Basic_DrawLine(pstDeviceIF, iStartX+iFillet, iStartY, iStartX+iWidth-1-iFillet, iStartY, eEdgeColor);
        // Paint last horizontal line for edge.
        SGUI_Basic_DrawLine(pstDeviceIF, iStartX+iFillet, iStartY+iHeight-1, iStartX+iWidth-1-iFillet, iStartY+iHeight-1, eEdgeColor);
        // Paint Arc
        while(iPosXOffset >= iPosYOffset)
        {
            if((iXOffset_Old != iPosXOffset) || (iYOffset_Old != iPosYOffset))
            {
                // Fill
                if(eFillColor != SGUI_COLOR_TRANS)
                {
                    if(iPosXOffset != iPosYOffset)
                    {
                        SGUI_Basic_DrawHorizontalLine(pstDeviceIF, iStartX+iFillet-iPosXOffset+1, iStartX+iWidth-iFillet+iPosXOffset-2, iStartY+iFillet-iPosYOffset, eFillColor);
                    }
                    if((iPosXOffset != iFillet) && (iXOffset_Old != iPosXOffset))
                    {
                        SGUI_Basic_DrawHorizontalLine(pstDeviceIF, iStartX+iFillet-iPosYOffset+1, iStartX+iWidth-iFillet+iPosYOffset-2, iStartY+iFillet-iPosXOffset, eFillColor);
                    }
                    pstDeviceIF->fnSyncBuffer();
                }
                // Draw arc edge for 2nd quadrant(Left top arc).
                SGUI_Basic_DrawPoint(pstDeviceIF, iStartX+iFillet-iPosXOffset, iStartY+iFillet-iPosYOffset, eEdgeColor);
                SGUI_Basic_DrawPoint(pstDeviceIF, iStartX+iFillet-iPosYOffset, iStartY+iFillet-iPosXOffset, eEdgeColor);
                // Draw arc edge for 1st quadrant(Right top arc).
                SGUI_Basic_DrawPoint(pstDeviceIF, iStartX+iWidth-iFillet+iPosXOffset-1, iStartY+iFillet-iPosYOffset, eEdgeColor);
                SGUI_Basic_DrawPoint(pstDeviceIF, iStartX+iWidth-iFillet+iPosYOffset-1, iStartY+iFillet-iPosXOffset, eEdgeColor);
                // Fill
                if(eFillColor != SGUI_COLOR_TRANS)
                {
                    if(iPosXOffset != iPosYOffset)
                    {
                        SGUI_Basic_DrawHorizontalLine(pstDeviceIF, iStartX+iFillet-iPosXOffset+1, iStartX+iWidth-iFillet+iPosXOffset-2, iStartY+iHeight-iFillet+iPosYOffset-1, eFillColor);
                    }
                    if((iPosXOffset != iFillet) && (iXOffset_Old != iPosXOffset))
                    {
                        SGUI_Basic_DrawHorizontalLine(pstDeviceIF, iStartX+iFillet-iPosYOffset+1, iStartX+iWidth-iFillet+iPosYOffset-2, iStartY+iHeight-iFillet+iPosXOffset-1, eFillColor);
                    }
                }
                // Draw arc edge for 3rd quadrant(Left bottom arc).
                SGUI_Basic_DrawPoint(pstDeviceIF, iStartX+iFillet-iPosXOffset, iStartY+iHeight-iFillet+iPosYOffset-1, eEdgeColor);
                SGUI_Basic_DrawPoint(pstDeviceIF, iStartX+iFillet-iPosYOffset, iStartY+iHeight-iFillet+iPosXOffset-1, eEdgeColor);
                // Draw arc edge for 4th quadrant(Right bottom arc).
                SGUI_Basic_DrawPoint(pstDeviceIF, iStartX+iWidth-iFillet+iPosXOffset-1, iStartY+iHeight-iFillet+iPosYOffset-1, eEdgeColor);
                SGUI_Basic_DrawPoint(pstDeviceIF, iStartX+iWidth-iFillet+iPosYOffset-1, iStartY+iHeight-iFillet+iPosXOffset-1, eEdgeColor);

                iYOffset_Old = iPosYOffset;
                iXOffset_Old = iPosXOffset;

            }
            iPosYOffset++;
            iRadiusError += iYChange;
            iYChange += 2;
            if ((2 * iRadiusError + iXChange) > 0)
            {
                iPosXOffset--;
                iRadiusError += iXChange;
                iXChange += 2;
            }
        }

        // Draw left vertical edge
        SGUI_Basic_DrawLine(pstDeviceIF, iStartX, iStartY+iFillet, iStartX, iStartY+iHeight-iFillet-1, eEdgeColor);
        // Draw right vertical edge
        SGUI_Basic_DrawLine(pstDeviceIF, iStartX+iWidth-1, iStartY+iFillet, iStartX+iWidth-1, iStartY+iHeight-iFillet-1, eEdgeColor);
        // Fill center.
        if(eFillColor != SGUI_COLOR_TRANS)
        {
            for(iFillIdx=iStartY+iFillet+1; iFillIdx<iStartY+iHeight-iFillet-1; iFillIdx++)
            {
                SGUI_Basic_DrawHorizontalLine(pstDeviceIF, iStartX+1, iStartX+iWidth-2, iFillIdx, eFillColor);
            }
        }
    }
}
