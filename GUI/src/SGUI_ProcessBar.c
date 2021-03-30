/*************************************************************************/
/** Copyright.															**/
/** FileName: SGUI_ProcessBar.c											**/
/** Author: XuYulin,Jerry												**/
/** Description: Process bar display interface.							**/
/*************************************************************************/

//=======================================================================//
//= Include files.														=//
//=======================================================================//
#include "SGUI_ProcessBar.h"

//=======================================================================//
//= Function define.													=//
//=======================================================================//
/*************************************************************************/
/** Function Name:	SGUI_RefreshProcessBar								**/
/** Purpose:		Display or update a process bar.					**/
/** Resources:		Process bar data structure.							**/
/** Params:																**/
/**	@ pstDeviceIF[in]:	SimpleGUI object pointer.							**/
/**	@ pstProcessBarData[in]: Process bar data whitch will update on		**/
/**					screen.												**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_ProcessBar_Repaint(SGUI_SCR_DEV* pstDeviceIF, SGUI_PROCBAR_STRUCT *pstProcessBarData)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_UINT16					uiProcessBlockStartX, uiProcessBlockStartY;
	SGUI_UINT16					uiProcessBlockWidth, uiProcessBlockHeight;
	SGUI_COLOR					eBackColor, eFillColor;
	SGUI_PROCBAR_PALETTE*		pstPalette;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	pstPalette = &pstProcessBarData->stParameter.stPalette;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstProcessBarData)
	{

		if((pstProcessBarData->stParameter.stLayout.iWidth > 3) && (pstProcessBarData->stParameter.stLayout.iHeight > 3))
		{
			// Check value must be less then PROCBAR_VALUE_MAX.
			if(pstProcessBarData->stData.sValue > pstProcessBarData->stParameter.sMaxValue)
			{
				pstProcessBarData->stData.sValue = pstProcessBarData->stParameter.sMaxValue;
			}
			#ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
			// Mapping Color
			if(pstPalette->uiDepthBits != pstDeviceIF->uiDepthBits)
			{
				pstPalette->eBackgroundColor	= SGUI_Basic_MapColor(pstPalette->uiDepthBits,pstPalette->eBackgroundColor,pstDeviceIF->uiDepthBits);
				pstPalette->eProcessBarColor	= SGUI_Basic_MapColor(pstPalette->uiDepthBits,pstPalette->eProcessBarColor,pstDeviceIF->uiDepthBits);
				pstPalette->eEdgeColor		  = SGUI_Basic_MapColor(pstPalette->uiDepthBits,pstPalette->eEdgeColor,pstDeviceIF->uiDepthBits);
				pstPalette->uiDepthBits		 = pstDeviceIF->uiDepthBits;
			}
			#endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
			// Update process bar data.
			switch(pstProcessBarData->stParameter.eDirection)
			{
				case SGUI_PROCBAR_DOWN:	// Process from up to down.
				{
					uiProcessBlockStartX	= pstProcessBarData->stParameter.stLayout.iX + 1;
					uiProcessBlockStartY	= pstProcessBarData->stParameter.stLayout.iY + 1;
					uiProcessBlockWidth		= pstProcessBarData->stParameter.stLayout.iWidth - 2;
					uiProcessBlockHeight	= (pstProcessBarData->stParameter.stLayout.iHeight - 2) * (pstProcessBarData->stData.sValue) / pstProcessBarData->stParameter.sMaxValue;
					eBackColor = pstPalette->eBackgroundColor;
					eFillColor = pstPalette->eProcessBarColor;
					break;
				}
				case SGUI_PROCBAR_LEFT:	// Process from right to left.
				{
					uiProcessBlockStartX	= pstProcessBarData->stParameter.stLayout.iX + 1;
					uiProcessBlockStartY	= pstProcessBarData->stParameter.stLayout.iY + 1;
					uiProcessBlockWidth		= (pstProcessBarData->stParameter.stLayout.iWidth - 2) * (pstProcessBarData->stParameter.sMaxValue - pstProcessBarData->stData.sValue) / pstProcessBarData->stParameter.sMaxValue;
					uiProcessBlockHeight	= pstProcessBarData->stParameter.stLayout.iHeight - 2;
					eBackColor = pstPalette->eProcessBarColor;
					eFillColor = pstPalette->eBackgroundColor;
					break;
				}
				case SGUI_PROCBAR_RIGHT:	// Process from left to right.
				{
					uiProcessBlockStartX	= pstProcessBarData->stParameter.stLayout.iX + 1;
					uiProcessBlockStartY	= pstProcessBarData->stParameter.stLayout.iY + 1;
					uiProcessBlockWidth		= (pstProcessBarData->stParameter.stLayout.iWidth - 2) * (pstProcessBarData->stData.sValue) / pstProcessBarData->stParameter.sMaxValue;
					uiProcessBlockHeight	= pstProcessBarData->stParameter.stLayout.iHeight - 2;
					eBackColor = pstPalette->eBackgroundColor;
					eFillColor = pstPalette->eProcessBarColor;
					break;
				}
				case SGUI_PROCBAR_UP:	// Process from down to up.
				default:
				{
					uiProcessBlockStartX	= pstProcessBarData->stParameter.stLayout.iX + 1;
					uiProcessBlockStartY	= pstProcessBarData->stParameter.stLayout.iY + 1;
					uiProcessBlockWidth		= pstProcessBarData->stParameter.stLayout.iWidth - 2;
					uiProcessBlockHeight	= (pstProcessBarData->stParameter.stLayout.iHeight - 2) * (pstProcessBarData->stParameter.sMaxValue - pstProcessBarData->stData.sValue) / pstProcessBarData->stParameter.sMaxValue;
					eBackColor = pstPalette->eProcessBarColor;
					eFillColor = pstPalette->eBackgroundColor;
				}
			}
			// Redraw edge and clean up area.
			SGUI_Basic_DrawRectangle(pstDeviceIF,
							pstProcessBarData->stParameter.stLayout.iX, pstProcessBarData->stParameter.stLayout.iY,
							pstProcessBarData->stParameter.stLayout.iWidth, pstProcessBarData->stParameter.stLayout.iHeight,
							pstPalette->eEdgeColor, eBackColor);
			// Draw process block.
			SGUI_Basic_DrawRectangle(pstDeviceIF, uiProcessBlockStartX, uiProcessBlockStartY, uiProcessBlockWidth, uiProcessBlockHeight, eFillColor, eFillColor);
		}
	}
}
