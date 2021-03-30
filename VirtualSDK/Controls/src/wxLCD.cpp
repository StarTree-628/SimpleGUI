/*************************************************************************/
/** Copyright.															**/
/** FileName: wxLCD.cpp													**/
/** Author: Polarix														**/
/** Description: LCD display panel in wxWidgets frame.					**/
/*************************************************************************/
//=======================================================================//
//= Include files.														=//
//=======================================================================//
#include "wxLCD.h"
#include "SGUI_Common.h"
#include <math.h>
#include <wx/log.h>
//=======================================================================//
//= Function define.													=//
//=======================================================================//
wxLCD::wxLCD(wxWindow *pclsParent, wxWindowID iWinID, const wxPoint& clsPosition, const wxSize& clsSizeInPixel):
wxLCDBase(pclsParent, iWinID, clsPosition, clsSizeInPixel)
{
	m_clsPixelLColour.Set(0x00000000);
	m_clsPixelHColour.Set(0x00000000);
	m_clsPixelPalette=NULL;
}

wxLCD::~wxLCD(void)
{

}

void wxLCD::SetPanelColour(const wxColour& clsPanelColour, bool bRefreshNow)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Replace old panel color.
	ReplaceColour(m_clsPixelLColour, clsPanelColour);
	// Set new panel color.
	m_clsPixelLColour = clsPanelColour;
	// Refresh display.
	if(true == bRefreshNow)
	{
		RefreshDisplay();
	}
}

void wxLCD::SetPixelColour(const wxColour& clsPixelColour, bool bRefreshNow)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Replace old pixel color.
	ReplaceColour(m_clsPixelHColour, clsPixelColour);
	// Set new pixel color.
	m_clsPixelHColour = clsPixelColour;
	// Refresh display.
	if(true == bRefreshNow)
	{
		RefreshDisplay();
	}
}

void wxLCD::SetPixelDepth(const int depth)
{
	this->m_iPixelDepth=depth;
	if(this->m_clsPixelPalette != NULL)
	{
		free(m_clsPixelPalette);
		m_clsPixelPalette=NULL;
	}
	// Generate a scaled Palette bettween the BackgroundColor and PixelColor
	m_clsPixelPalette = new wxColor[depth];
	wxLogDebug("调色板初始化中...");
	unsigned char ucRH=this->m_clsPixelHColour.Red();
	unsigned char ucGH=this->m_clsPixelHColour.Green();
	unsigned char ucBH=this->m_clsPixelHColour.Blue();
	wxLogDebug("颜色边界A(%d,%d,%d)",ucRH,ucGH,ucBH);
	unsigned char ucRL=m_clsPixelLColour.Red();
	unsigned char ucGL=m_clsPixelLColour.Green();
	unsigned char ucBL=m_clsPixelLColour.Blue();
	wxLogDebug("颜色边界B(%d,%d,%d)",ucRL,ucGL,ucBL);
	double dbRDiff=(ucRH-ucRL)*1.0/(depth-1);
	double dbGDiff=(ucGH-ucGL)*1.0/(depth-1);
	double dbBDiff=(ucBH-ucBL)*1.0/(depth-1);
	wxLogDebug("色差(%.2f,%.2f,%.2f)",dbRDiff,dbGDiff,dbBDiff);
	double dbR=(int)ucRL*1.0;
	double dbG=(int)ucGL*1.0;
	double dbB=(int)ucBL*1.0;

	for(int i=0; i<depth; i++)
	{
		wxLogDebug("颜色0x%02X被映射为(%d,%d,%d)",i,(unsigned char)floor(dbR+0.5),(unsigned char)floor(dbG+0.5),(unsigned char)floor(dbB+0.5));
		m_clsPixelPalette[i]=wxColor((unsigned char)floor(dbR+0.5),(unsigned char)floor(dbG+0.5),(unsigned char)floor(dbB+0.5));
		dbR+=dbRDiff;
		dbG+=dbGDiff;
		dbB+=dbBDiff;
	}
}
int wxLCD::GetPixel(const int iX, const int iY)
{
	int				iReturn=-1;
	int			 iLeft=0;
	int			 iRight=m_iPixelDepth-1;
	int			 iMid=(iLeft+iRight)/2;
	wxColor		 clsLeftColor,clsRightColor;
	wxColor		 clsTargetColor=GetPixelUnitColor(iX, iY);
	wxColor		 clsMidColor;

	while(iLeft<iRight)
	{
		iMid=(iLeft+iRight)/2;
		clsLeftColor=m_clsPixelPalette[iLeft];
		clsMidColor=m_clsPixelPalette[iMid];
		clsRightColor=m_clsPixelPalette[iRight];
		// use Red to search
		if((clsLeftColor.Red()<=clsTargetColor.Red() && clsTargetColor.Red()<clsMidColor.Red()) ||
				(clsLeftColor.Red()>=clsTargetColor.Red() && clsTargetColor.Red()>clsMidColor.Red()))
		{
			iRight=iMid-1;
			continue;
		}
		else if((clsRightColor.Red()>=clsTargetColor.Red() && clsTargetColor.Red()>clsMidColor.Red())||
				(clsRightColor.Red()<=clsTargetColor.Red() && clsTargetColor.Red()<clsMidColor.Red()))
		{
			iLeft=iMid+1;
			continue;
		}
		// use Green to search
		if((clsLeftColor.Green()<=clsTargetColor.Green() && clsTargetColor.Green()<clsMidColor.Green()) ||
				(clsLeftColor.Green()>=clsTargetColor.Green() && clsTargetColor.Green()>clsMidColor.Green()))
		{
			iRight=iMid-1;
			continue;
		}
		else if((clsRightColor.Green()>=clsTargetColor.Green() && clsTargetColor.Green()>clsMidColor.Green())||
				(clsRightColor.Green()<=clsTargetColor.Green() && clsTargetColor.Green()<clsMidColor.Green()))
		{
			iLeft=iMid+1;
			continue;
		}
		// use Blue to search
		if((clsLeftColor.Blue()<=clsTargetColor.Blue() && clsTargetColor.Blue()<clsMidColor.Blue()) ||
				(clsLeftColor.Blue()>=clsTargetColor.Blue() && clsTargetColor.Blue()>clsMidColor.Blue()))
		{
			iRight=iMid-1;
			continue;
		}
		else if((clsRightColor.Blue()>=clsTargetColor.Blue() && clsTargetColor.Blue()>clsMidColor.Blue())||
				(clsRightColor.Blue()<=clsTargetColor.Blue() && clsTargetColor.Blue()<clsMidColor.Blue()))
		{
			iLeft=iMid+1;
			continue;
		}
		// iMid is the target color
		iReturn=iMid;
		break;
	}
	if(iReturn==-1 && iLeft==iRight)
		iReturn=iLeft;
	return iReturn;
}

void wxLCD::SetPixel(const int iX, const int iY, const int iValue)
{
	int iCheckedValue;
	iCheckedValue = SGUI_MIN_OF(iValue,m_iPixelDepth-1);
	iCheckedValue = SGUI_MAX_OF(iCheckedValue,0);

	SetPixelUnitColor(iX,iY,m_clsPixelPalette[iCheckedValue]);
}

void wxLCD::CleanScreen(void)
{
	SetDisplayBuffer(m_clsPixelLColour);
}

void wxLCD::SetParameter(PixelPanelParameter* pstPanelParameter)
{
	if(NULL != pstPanelParameter)
	{
		SetPixelUnitSize(wxSize(pstPanelParameter->PixelUnitWidth, pstPanelParameter->PixelUnitHeight));
		SetGridVisibled(pstPanelParameter->EnableGrid);
		SetPixelNumber(pstPanelParameter->HorizontalPixelNumber, pstPanelParameter->VerticalPixelNumber);
		SetBorderWidth(pstPanelParameter->BorderWidth);

		SetPixelColour(wxColor(pstPanelParameter->PixelColor), false);
		SetPanelColour(wxColor(pstPanelParameter->PanelColor), false);
		SetGridColor(wxColor(pstPanelParameter->GridColor));
		SetPixelDepth(pstPanelParameter->PixelUnitDepth);

		Layout();
	}
}
