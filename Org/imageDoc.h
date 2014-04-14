// 
// imageDoc.h
//
// header file for Doc 
//

#ifndef __ImageDoc_h
#define __ImageDoc_h

#include "tinyPhotoShop.h"
#include "bitmap.h"
#include "TargaImage.h"
#include "Matrix.hpp"




class ImageUI;



class Point 
{
public:
	Point() {};
	Point(int xx, int yy) { x = xx; y = yy; };

	int x, y;
};


class ImageDoc 
{
public:
	ImageDoc();

	void	setUI(ImageUI* ui);		// Assign the UI to use

	int		loadImage(char *iname);			// called by the UI to load image
	int		saveImage(char *iname);			// called by the UI to save image
	int     resize();
	int     copy();
	int     convolution();


	void resizeWindow(float scale);
	int     clearCanvas();                  // called by the UI to clear the drawing canvas
	char*	 getImageName();					// get the current image name

	

// Attributes
public:
	// Dimensions of original window.
	int				m_nWidth, 
					m_nHeight;
	// Dimensions of the paint window.
	int				m_nPaintWidth, 
					m_nPaintHeight;	
	// Bitmaps for original image and painting.
	unsigned char*	m_ucBitmap;
	unsigned char*	m_ucPainting;

	//# of bits per pixel
	int		m_nDepth;  

	//UI class pointer
	ImageUI*	m_pUI;

	//bmp = 0, targa = 1
	int m_fileType;
	TargaImage *m_img;   //contains the TargaImage class instance
 
// Operations
public:
	
	GLubyte* GetOriginalPixel( int x, int y );   
	GLubyte* GetOriginalPixel( const Point p );


private:
	char			m_imageName[256];

};



#endif
