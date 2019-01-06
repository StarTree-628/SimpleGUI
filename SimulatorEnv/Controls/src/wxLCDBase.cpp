//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include <wx/msgdlg.h>
#include <wx/clipbrd.h>
#include "wxLCDBase.h"

//=======================================================================//
//= Marco declare.                                                      =//
//=======================================================================//
#define	wxLCD_ERROR_STOP_PROC_P(P, R, V)		{if(NULL == P){R=V; break;}}

const wxSize	wxDefaultSizeInPixel(128, 64);

//=======================================================================//
//= Event table.													    =//
//=======================================================================//
BEGIN_EVENT_TABLE(wxLCDBase,wxWindow)
	EVT_PAINT		        (wxLCDBase::OnPaint)
	EVT_ERASE_BACKGROUND    (wxLCDBase::OnEraseBackGround)
	EVT_KEY_DOWN			(wxLCDBase::OnKeyDown)
END_EVENT_TABLE()

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
wxLCDBase::wxLCDBase(wxWindow *pclsParent, wxWindowID iWinID, const wxPoint& clsPosition, const wxSize& clsSizeInPixel):
wxWindow(pclsParent, iWinID, clsPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxNO_BORDER, wxPanelNameStr),
m_clsCDC(this)
{
	/*----------------------------------*/
	/* Initialize member.				*/
	/*----------------------------------*/
	// Initialize panel size.
	if(wxDefaultSize == clsSizeInPixel)
	{
		m_clsSizeInPixel.Set(WX_LCD_DEFAULT_WIDTH_PIX, WX_LCD_DEFAULT_HEIGHT_PIX);
	}
	else
	{
		m_clsSizeInPixel = clsSizeInPixel;
	}
	// Initialize paint buffer and function pointer.
	m_ppuiDisplayBuffer = nullptr;
	m_pfDrawPoint = nullptr;
	// Process initialize.
	m_bIsOK = _initialize();
}

wxLCDBase::~wxLCDBase()
{
	_freeDisplayBuffer(m_ppuiDisplayBuffer);
}

bool wxLCDBase::_initialize(void)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	bool					bReturn;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	bReturn =				true;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
    do
	{
		// Create display buffer.
		m_ppuiDisplayBuffer = _createNewDisplayBuffer(m_clsSizeInPixel.GetWidth(), m_clsSizeInPixel.GetHeight());
		wxLCD_ERROR_STOP_PROC_P(m_ppuiDisplayBuffer, bReturn, false);
		// Set pixel size.
		SetPixelSize(WX_LCD_DEFAULT_PIX_SIZE);
		// Set grid visible.
		SetGridVisibled(WX_LCD_DEFAULT_GRID_VISIBLE);
	}while(0);

	return bReturn;
}

void wxLCDBase::_getBestSize(wxSize& clsBestSize) const
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	bool					bGridIsVisible;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	bGridIsVisible =		GetGridVisibled();

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Set size object value.
	clsBestSize.SetWidth(m_clsSizeInPixel.GetWidth()*m_iPixelSize+(bGridIsVisible?1:0));
	clsBestSize.SetHeight(m_clsSizeInPixel.GetHeight()*m_iPixelSize+(bGridIsVisible?1:0));
}

void wxLCDBase::SetPixelNumber(int iHorizontalPixelNumber, int iVerticalPixelNumber)
{
    /*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	unsigned int**			ppuiNewDisplayBuffer;
	int                		iCopiedRowNumber;
	int						iCopiedColumnNumber;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	ppuiNewDisplayBuffer =  NULL;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((iHorizontalPixelNumber > 0) && (iVerticalPixelNumber > 0))
    {
        // Create a new display buffer
        ppuiNewDisplayBuffer = _createNewDisplayBuffer(iHorizontalPixelNumber, iVerticalPixelNumber);
        if(NULL != ppuiNewDisplayBuffer)
        {
            iCopiedRowNumber = m_clsSizeInPixel.GetHeight()<iVerticalPixelNumber?m_clsSizeInPixel.GetHeight():iVerticalPixelNumber;
            iCopiedColumnNumber = m_clsSizeInPixel.GetWidth()<iHorizontalPixelNumber?m_clsSizeInPixel.GetWidth():iHorizontalPixelNumber;
            // Copy old buffer content to new buffer;
            for(int iIdxV=0; iIdxV<iCopiedRowNumber; iIdxV++)
            {
                memcpy(*(ppuiNewDisplayBuffer+iIdxV), *(m_ppuiDisplayBuffer+iIdxV), sizeof(unsigned int)*iCopiedColumnNumber);
            }
            // Free current buffer.
            _freeDisplayBuffer(m_ppuiDisplayBuffer);
            m_ppuiDisplayBuffer = ppuiNewDisplayBuffer;
            m_clsSizeInPixel.Set(iHorizontalPixelNumber, iVerticalPixelNumber);
        }
    }
}

void wxLCDBase::GetPixelNumber(int* piHorizontalPixelNumber, int* piVerticalPixelNumber)
{
    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != piHorizontalPixelNumber)
	{
		*piHorizontalPixelNumber = m_clsSizeInPixel.GetWidth();
	}

	if(NULL != piVerticalPixelNumber)
	{
		*piVerticalPixelNumber = m_clsSizeInPixel.GetHeight();
	}
}

void wxLCDBase::SetPixelSize(int iPixelSize)
{
    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Save the pixel size value.
    m_iPixelSize = iPixelSize;

    // If pixel size is 0, the pixel drawing function will set to invalid.
	if(0 == m_iPixelSize)
	{
		m_pfDrawPoint = NULL;
		m_bIsOK = false;
	}
	// If pixel size is 1, the pixel drawing function will set to draw pixel unit by point.
	else if(1 == m_iPixelSize)
	{
		m_pfDrawPoint = &_drawPointSinglePixel;
	}
	else
	{
		if(true == GetGridVisibled())
		{
			m_pfDrawPoint = &_drawPointMultiplePixelWithGrid;
		}
		else
        {
            m_pfDrawPoint = &_drawPointMultiplePixel;
        }
	}
}

void wxLCDBase::SetGridVisibled(bool bGridVisible, bool bRefreshNow)
{
    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Save the grid visible value set.
    m_bGridVisible = bGridVisible;

    if(m_iPixelSize < WX_LCD_PIX_SIZE_MIN_WITH_GRID)
	{
		m_bGridVisible = false;
	}
	else
	{
		if(true == m_bGridVisible)
		{
			m_pfDrawPoint = &_drawPointMultiplePixelWithGrid;
		}
		else
		{
			m_pfDrawPoint = &_drawPointMultiplePixel;
		}
	}
	if(true == bRefreshNow)
	{
		RefreshDisplay();
	}
}

bool wxLCDBase::GetGridVisibled(void) const
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	bool				bGridVisible;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(m_iPixelSize < WX_LCD_PIX_SIZE_MIN_WITH_GRID)
	{
		bGridVisible = false;
	}
	else
	{
		bGridVisible = m_bGridVisible;
	}

	return bGridVisible;
}

void wxLCDBase::_cleanDisplayBuffer(void)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	for(int iIdxV=0; iIdxV<m_clsSizeInPixel.GetHeight(); iIdxV++)
    {
        memset(*(m_ppuiDisplayBuffer+iIdxV), 0x00, sizeof(unsigned int)*m_clsSizeInPixel.GetWidth());
    }
	RefreshDisplay();
}

void wxLCDBase::SetDisplayBuffer(wxColour& clsPanelColour)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != m_pfDrawPoint) && (m_iPixelSize > 0))
	{
		// Cleanup display and set display buffer .
		for(int iIdxV=0; iIdxV<m_clsSizeInPixel.GetHeight(); iIdxV++)
		{
			for(int iIdxH=0; iIdxH<m_clsSizeInPixel.GetWidth(); iIdxH++)
			{
				*(*(m_ppuiDisplayBuffer+iIdxV)+iIdxH) = clsPanelColour.GetRGBA();
			}
		}
	}
}

void wxLCDBase::ReplaceColour(const wxColour& clsOldColour, const wxColour& clsNewColour)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != m_pfDrawPoint) && (m_iPixelSize > 0))
	{
		// Cleanup display and set display buffer .
		for(int iIdxV=0; iIdxV<m_clsSizeInPixel.GetHeight(); iIdxV++)
		{
			for(int iIdxH=0; iIdxH<m_clsSizeInPixel.GetWidth(); iIdxH++)
			{
				if(*(*(m_ppuiDisplayBuffer+iIdxV)+iIdxH) == clsOldColour.GetRGBA())
				{
					*(*(m_ppuiDisplayBuffer+iIdxV)+iIdxH) = clsNewColour.GetRGBA();
				}
			}
		}
	}
}

void wxLCDBase::SetGridColor(const wxColor& clsColor)
{
    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	m_clsGridColor = clsColor;
}

wxColor& wxLCDBase::GetGridColor(void)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
    return m_clsGridColor;
}

void wxLCDBase::OnPaint(wxPaintEvent &clsEvent)
{
    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	RefreshDisplay();
}

void wxLCDBase::OnKeyDown(wxKeyEvent& clsEvent)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	clsEvent.ResumePropagation(1);
	clsEvent.Skip();
}

void wxLCDBase::_drawPointSinglePixel(wxDC& clsDCObject, int iPosX, int iPosY, int iPixelSize)
{
    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	clsDCObject.DrawPoint(wxPoint(iPosX, iPosY));
}

void wxLCDBase::_drawPointMultiplePixel(wxDC& clsDCObject, int iPosX, int iPosY, int iPixelSize)
{
    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	clsDCObject.DrawRectangle(wxPoint(iPosX*iPixelSize, iPosY*iPixelSize), wxSize(iPixelSize, iPixelSize));
}

void wxLCDBase::_drawPointMultiplePixelWithGrid(wxDC& clsDCObject, int iPosX, int iPosY, int iPixelSize)
{
    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	clsDCObject.DrawRectangle(wxPoint(iPosX*iPixelSize+1, iPosY*iPixelSize+1), wxSize(iPixelSize-1, iPixelSize-1));
}

/*************************************************************************/
/** Function Name:	SetPixelUnitColor                                   **/
/** Purpose:		Set a pixel RGBA color value.                       **/
/** Params:																**/
/**	@ iPosX[in]:		X-Coordinate of pixel.                          **/
/**	@ iPosY[in]:		Y-Coordinate of pixel.                          **/
/**	@ clsColor[in]:     Color data object.                              **/
/**	@ bRefreshNow[in]:  Refresh display at once, default to false.      **/
/** Return:			None.                                               **/
/** Notice:			This function only change the pixel color register  **/
/**                 if bRefreshNow is false(default), and when the      **/
/**                 parameter bRefreshNow is true, all pixel blocks of  **/
/**                 LCD screen panel will be repaint. if need to draw   **/
/**                 only one pixel, please use the DrawPixel function   **/
/**                 directly.                                           **/
/*************************************************************************/
void wxLCDBase::SetPixelUnitColor(int iPosX, int iPosY, const wxColor& clsColor, bool bRefreshNow)
{
    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((iPosX < m_clsSizeInPixel.GetWidth()) && (iPosY < m_clsSizeInPixel.GetHeight()))
	{
		if(nullptr != m_ppuiDisplayBuffer)
		{
		    *(*(m_ppuiDisplayBuffer+iPosY)+iPosX) = clsColor.GetRGBA();
		}
		if(true == bRefreshNow)
		{
			RefreshDisplay();
		}
	}
}

/*************************************************************************/
/** Function Name:	GetPixelUnitColor                                   **/
/** Purpose:		Get color of a pixel unit.                          **/
/** Params:																**/
/**	@ uiPosX[in]:       X-Coordinate of pixel.                          **/
/**	@ uiPosY[in]:       Y-Coordinate of pixel.                          **/
/** Return:			RGBA color value of the pixel unit.                 **/
/** Notice:			None.                                               **/
/*************************************************************************/
unsigned int wxLCDBase::GetPixelUnitColor(int iPosX, int iPosY)
{
    /*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	uint32_t		uiReturnValue = 0x00;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((iPosX < m_clsSizeInPixel.GetWidth()) && (iPosY < m_clsSizeInPixel.GetHeight()))
	{
		if(nullptr != m_ppuiDisplayBuffer)
		{
			uiReturnValue = *(*(m_ppuiDisplayBuffer+iPosY)+iPosX);
		}
	}

	return uiReturnValue;
}

/*************************************************************************/
/** Function Name:	DrawPixel                                           **/
/** Purpose:		Draw a pixel.                                       **/
/** Params:																**/
/**	@ iPosX[in]:		X-Coordinate of pixel.                          **/
/**	@ iPosY[in]:		Y-Coordinate of pixel.                          **/
/**	@ clsColor[in]:     Color data object.                              **/
/** Return:			None.                                               **/
/** Notice:			Draw only one pixel directly.                       **/
/*************************************************************************/
void wxLCDBase::DrawPixel(int iPosX, int iPosY, wxColor& clsColor)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((iPosX < m_clsSizeInPixel.GetWidth()) && (iPosY < m_clsSizeInPixel.GetHeight()) && (m_iPixelSize != 0))
	{
		_setDCColor(clsColor);
		_prepareDC(m_clsCDC);
		if(nullptr != m_pfDrawPoint)
		{
			(this->*m_pfDrawPoint)(m_clsCDC, iPosX, iPosY, m_iPixelSize);
		}
		if(nullptr != m_ppuiDisplayBuffer)
        {
            *(*(m_ppuiDisplayBuffer+iPosY)+iPosX) = clsColor.GetRGBA();
        }
		SetPixelUnitColor(iPosX, iPosY, clsColor);
		_releaseDC(m_clsCDC);
	}
}

/*************************************************************************/
/** Function Name:	RefreshDisplay                                      **/
/** Class:			wxLCDBase											**/
/** Accessibility:	Public.												**/
/** Purpose:		Repaint LCD screen panel.                           **/
/** Params:			None.                                               **/
/** Return:			None.                                               **/
/** Notice:			Call this function after the SetPixelColor called,  **/
/**                 all pixels of the LCD panel will be repaint by the  **/
/**                 pixels's RGBA value register array.                 **/
/*************************************************************************/
void wxLCDBase::RefreshDisplay(void)
{
    /*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	int					iPaintSizeWidth, iPaintSizeHeight;
	bool				bGridVisible;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	iPaintSizeWidth =	m_clsSizeInPixel.GetWidth()*m_iPixelSize;
	iPaintSizeHeight =	m_clsSizeInPixel.GetHeight()*m_iPixelSize;
	bGridVisible = GetGridVisibled();

	// Set buffer size.
	if(true == bGridVisible)
	{
		iPaintSizeWidth++;
		iPaintSizeHeight++;
	}
	// Create buffer image and DC object.
	wxBitmap			clsBufferImage(iPaintSizeWidth, iPaintSizeHeight);
	wxBufferedDC		clsBufferedDC(&m_clsCDC, clsBufferImage);

	// Clear background for grid line.
	if(true == bGridVisible)
	{
		_setDCColor(m_clsGridColor);
		_prepareDC(clsBufferedDC);
		clsBufferedDC.DrawRectangle(wxPoint(0, 0),
							wxSize(	m_clsSizeInPixel.GetWidth()*m_iPixelSize+1,
									m_clsSizeInPixel.GetHeight()*m_iPixelSize+1));
	}

	// Paint pixel.
	if(nullptr != m_pfDrawPoint)
	{
		// Refresh each pixel on screen.
		for(int i_H=0; i_H<m_clsSizeInPixel.GetHeight(); i_H++)
		{
			for(int i_W=0; i_W<m_clsSizeInPixel.GetWidth(); i_W++)
			{
				_setDCColor(wxColor(*(*(m_ppuiDisplayBuffer+i_H)+i_W)));
				_prepareDC(clsBufferedDC);
				(this->*m_pfDrawPoint)(clsBufferedDC, i_W, i_H, m_iPixelSize);
			}
		}
	}
}

/*************************************************************************/
/** Function Name:	SaveScreenImageToFile                               **/
/** Class:			wxLCDBase											**/
/** Accessibility:	Public.												**/
/** Purpose:		Save current panel image to a jpeg file.            **/
/** Params:			                                                    **/
/**	@ strFilePath[in]:  Save file path.                                 **/
/** Return:                                                             **/
/** @ true:             Save successfully.                              **/
/** @ false:            Save failed.                                    **/
/** Notice:			To support jpeg format, need add wxWidgets jpeg     **/
/**                 format handler in initialize(OnInit) function of    **/
/**                 the wxApp Object.                                   **/
/**                 wxImage::AddHandler(new wxJPEGHandler)              **/
/*************************************************************************/
bool wxLCDBase::SaveScreenImageToFile(const wxString& strFilePath)
{
    /*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	wxBitmap*               pclsBitMap;
	wxMemoryDC*             pclsMemoryDC;
	bool                    bReturn;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	bReturn =               false;
	pclsMemoryDC =			nullptr;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Create bitmap buffer.
	pclsBitMap = new wxBitmap(GetSize(), wxBITMAP_SCREEN_DEPTH);
	if(nullptr != pclsBitMap)
    {
        pclsMemoryDC = new wxMemoryDC(*pclsBitMap);
        if(nullptr != pclsMemoryDC)
        {
            bReturn = pclsMemoryDC->Blit(wxPoint(0, 0), GetSize(), &m_clsCDC, wxPoint(0, 0));
            if(true == bReturn)
            {
                bReturn = pclsBitMap->SaveFile(strFilePath, wxBITMAP_TYPE_JPEG);
            }
        }
    }
    //
    delete pclsBitMap;
    delete pclsMemoryDC;

	return bReturn;
}

/*************************************************************************/
/** Function Name:	CopyScreenImageToClipBoard                          **/
/** Class:			wxLCDBase											**/
/** Accessibility:	Public.												**/
/** Purpose:		Copy current screen image to clip board.            **/
/** Params:			None.                                               **/
/** Return:                                                             **/
/** @ true:             Copy successfully.                              **/
/** @ false:            Copy failed.                                    **/
/** Notice:			None.                                               **/
/*************************************************************************/
bool wxLCDBase::CopyScreenImageToClipBoard(void)
{
    /*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	uint32_t                uiPictureWidth, uiPictureHeight;
	wxBitmap*               pclsDCBufferBitmap;
	wxMemoryDC*             pclsDCBuffer;
	bool                    bReturn;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	uiPictureWidth =        GetSize().GetX();
	uiPictureHeight =       GetSize().GetY();
	pclsDCBufferBitmap =    new wxBitmap(uiPictureWidth, uiPictureHeight, wxBITMAP_SCREEN_DEPTH);
	pclsDCBuffer =          new wxMemoryDC(*pclsDCBufferBitmap);
	bReturn =               true;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((nullptr != pclsDCBufferBitmap) && (nullptr != pclsDCBuffer))
    {
        if(true == wxTheClipboard->Open())
        {
            pclsDCBuffer->Blit(0, 0, uiPictureWidth, uiPictureHeight, &m_clsCDC, 0, 0);
            wxTheClipboard->SetData(new wxBitmapDataObject(*pclsDCBufferBitmap));
            wxTheClipboard->Flush();
            wxTheClipboard->Close();
        }
        else
        {
            bReturn = false;
        }
    }

    delete pclsDCBufferBitmap;
    delete pclsDCBuffer;

	return bReturn;
}

/*************************************************************************/
/** Function Name:	_freeDisplayBuffer									**/
/** Class:			wxLCDBase											**/
/** Accessibility:	Private.											**/
/** Purpose:		Release display buffer memory resource.				**/
/** Resources:		None.												**/
/** Params:																**/
/** @ ppuiDisplayBuffer: Display buffer pointer.						**/
/** Return:			None.												**/
/** Notice:			Private function, called when need to release a 	**/
/**					existed display buffer. just like object destroy or **/
/**					size in pixel changed.								**/
/*************************************************************************/
void wxLCDBase::_freeDisplayBuffer(uint32_t** ppuiDisplayBuffer)
{
    if(nullptr != ppuiDisplayBuffer)
	{
	    for(int iIdxV=0; iIdxV<m_clsSizeInPixel.GetHeight(); iIdxV++)
        {
            free(*(ppuiDisplayBuffer+iIdxV));
        }
        free(ppuiDisplayBuffer);
	}
}

/*************************************************************************/
/** Function Name:	_createNewDisplayBuffer								**/
/** Class:			wxLCDBase											**/
/** Accessibility:	Private.											**/
/** Purpose:		Allocate new display buffer.						**/
/** Resources:		None.												**/
/** Params:																**/
/** @ iHorizontalPixelNumber: The number of pixels in the horizontal	**/
/**					direction.											**/
/** @ iVerticalPixelNumber: The number of pixels in the vertical		**/
/**					direction.											**/
/** Return:			New display buffer heap memory pointer.				**/
/** Notice:			Private function, called when need to create new 	**/
/**					display buffer. just like object create or size in	**/
/**					pixel changed.										**/
/*************************************************************************/
unsigned int** wxLCDBase::_createNewDisplayBuffer(int iHorizontalPixelNumber, int iVerticalPixelNumber)
{
    /*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	unsigned int**			ppuiNewDisplayBuffer;
	unsigned int*			puiNewHorizontalPixelBuffer;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	ppuiNewDisplayBuffer =  nullptr;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/

	if((iHorizontalPixelNumber > 0) && (iVerticalPixelNumber > 0))
    {
        ppuiNewDisplayBuffer = (unsigned int**)malloc(sizeof(unsigned int*)*iVerticalPixelNumber);
        if(nullptr != ppuiNewDisplayBuffer)
        {
            memset(ppuiNewDisplayBuffer, 0x00, sizeof(unsigned int*)*iVerticalPixelNumber);
            for(int iIdxV=0; iIdxV<iVerticalPixelNumber; iIdxV++)
            {
                puiNewHorizontalPixelBuffer = (unsigned int*)malloc(sizeof(unsigned int)*iHorizontalPixelNumber);
                if(nullptr != puiNewHorizontalPixelBuffer)
                {
                    memset(puiNewHorizontalPixelBuffer, 0x00, sizeof(unsigned int)*iHorizontalPixelNumber);
                    *(ppuiNewDisplayBuffer+iIdxV) = puiNewHorizontalPixelBuffer;
                }
                else
                {
                    _freeDisplayBuffer(ppuiNewDisplayBuffer);
                    ppuiNewDisplayBuffer = nullptr;
                    break;
                }
            }
        }
    }

    return ppuiNewDisplayBuffer;
}

/*************************************************************************/
/** Function Name:	DoGetBestClientSize									**/
/** Class:			wxLCDBase											**/
/** Accessibility:	Protected.											**/
/** Purpose:		Get best display size with current size in pixel	**/
/**					unit size, called by base class function.			**/
/** Resources:		None.												**/
/** Params:			None.												**/
/** Return:			Size object.										**/
/** Notice:			This function will be call when user call base		**/
/**					class function GetBestSize.							**/
/*************************************************************************/
wxSize wxLCDBase::DoGetBestClientSize(void) const
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	wxSize					clsBestSize;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	_getBestSize(clsBestSize);

	return clsBestSize;
}
