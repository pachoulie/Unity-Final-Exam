// 
// imageDoc.cpp
//
// It basically maintain the bitmap for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//
 #pragma warning (disable : 4312)
 #pragma warning (disable : 4311)

#include <iostream>

#include <FL/fl_ask.H>

#include <algorithm>

#include "imageDoc.h"
#include "imageUI.h"

#include "Matrix.hpp"


template<typename T>
inline T constrain(T val, T min, T max)
{
	if (val < min)
		return min;
	else if (val > max)
		return max;
	return val;
}




ImageDoc::ImageDoc() 
{
	// Set NULL image name as init. 
	m_imageName[0]	='\0';	

	m_nWidth		= -1;
	m_ucBitmap		= NULL;
	m_ucPainting	= NULL;
	m_img = 0;
	m_nDepth = 0;

}


//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void ImageDoc::setUI(ImageUI* ui) 
{
	m_pUI	= ui;
}

//---------------------------------------------------------
// Returns the active picture/painting name
//---------------------------------------------------------
char* ImageDoc::getImageName() 
{
	return m_imageName;
}



//---------------------------------------------------------
// Returns the size of the brush.
//---------------------------------------------------------

//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImageDoc::loadImage(char *iname) 
{
	// try to open the image to read
	unsigned char*	data;
	int				width, 
					height;


	
	if ( (data=readBMP(iname, width, height))==NULL ) 
	{
	
		if ((m_img = TargaImage::Load_Image(iname)) == NULL)  {
				fl_alert("Can't load bitmap file");	
				return 0;
		}

		else {
		
			data = m_img->data;
			width = m_img->width;
			height = m_img->height;
			m_fileType = 1;
			m_nDepth = 4;
		}
	}
	else {
			m_fileType = 0;
			m_nDepth = 3;
	}



	// reflect the fact of loading the new image
	m_nWidth		= width;
	m_nPaintWidth	= width;
	m_nHeight		= height;
	m_nPaintHeight	= height;

	// release old storage
	delete [] m_ucBitmap;
	delete [] m_ucPainting;


	m_ucBitmap		= data;


	// allocate space for draw view
	m_ucPainting		= new unsigned char [width*height*m_nDepth];

	memset(m_ucPainting, 0, width*height*m_nDepth);


	

	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(), 
								m_pUI->m_mainWindow->y(), 
								width*2, 
								height+25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);	
	m_pUI->m_origView->refresh();
		

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);	
	m_pUI->m_paintView->refresh();
	m_pUI->m_paintView->position(width,25);


	m_pUI->m_menubar->resize(0,0,width*2,25);
	return 1;
}

void  ImageDoc::resizeWindow(float scale)
{
	m_pUI->m_paintView->resizeWindow(m_nPaintWidth, m_nPaintHeight);	
	if (m_nPaintHeight > m_nHeight) {
		m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(), 
			m_pUI->m_mainWindow->y(), 
			m_nPaintWidth+m_nWidth, 
			m_nPaintHeight+25);
	}
	else {
		m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(), 
			m_pUI->m_mainWindow->y(), 
			m_nPaintWidth+m_nWidth, 
			m_nHeight+25);
	}

	m_pUI->m_paintView->position(m_nWidth,25);
	m_pUI->m_menubar->resize(0,0,m_nPaintWidth+m_nWidth,25);
}





//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is 
// pressed.
//----------------------------------------------------------------
int ImageDoc::saveImage(char *iname) 
{
	if (m_fileType == 0)
		writeBMP(iname, m_nPaintWidth, m_nPaintHeight, m_ucPainting);
 	else 
		m_img->Save_Image(iname);

	return 1;
}

//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImageDoc::clearCanvas() 
{

	// Release old storage
	if ( m_ucPainting ) 
	{
		delete [] m_ucPainting;

		// allocate space for draw view
		
		m_ucPainting	= new unsigned char [m_nPaintWidth*m_nPaintHeight*m_nDepth];
		memset(m_ucPainting, 0, m_nPaintWidth*m_nPaintHeight*m_nDepth);
		
		// refresh paint view as well	
		m_pUI->m_paintView->refresh();
	}
	
	return 0;
}




//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImageDoc::GetOriginalPixel( int x, int y )
{
	if ( x < 0 ) 
		x = 0;
	else if ( x >= m_nWidth ) 
		x = m_nWidth-1;

	if ( y < 0 ) 
		y = 0;
	else if ( y >= m_nHeight ) 
		y = m_nHeight-1;


	return (GLubyte*)(m_ucBitmap + m_nDepth * (y*m_nWidth + x));
	
}

//----------------------------------------------------------------
//Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImageDoc::GetOriginalPixel( const Point p )
{
	return GetOriginalPixel( p.x, p.y );
}



