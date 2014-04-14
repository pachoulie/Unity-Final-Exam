//
// paintview.cpp
//
// The code maintaining the painting view of the input images
//
#pragma warning (disable : 4312)
#pragma warning (disable : 4311)


#include "imageDoc.h"
#include "imageUI.h"
#include "paintView.h"



#define LEFT_MOUSE_DOWN		1
#define LEFT_MOUSE_DRAG		2
#define LEFT_MOUSE_UP		3
#define RIGHT_MOUSE_DOWN	4
#define RIGHT_MOUSE_DRAG	5
#define RIGHT_MOUSE_UP		6


#ifndef WIN32
#define min(a, b)	( ( (a)<(b) ) ? (a) : (b) )
#define max(a, b)	( ( (a)>(b) ) ? (a) : (b) )
#endif

static int		eventToDo;
static int		isAnEvent=0;
static Point	coord;

PaintView::PaintView(int			x, 
					 int			y, 
					 int			w, 
					 int			h, 
					 const char*	l)
						: Fl_Gl_Window(x,y,w,h,l)
{
	m_nWindowWidth	= w;
	m_nWindowHeight	= h;

}


void PaintView::draw()
{

	if(!valid())
	{
		glClearColor(0.7f, 0.7f, 0.7f, 1.0);

		// We're only using 2-D, so turn off depth 
		glDisable( GL_DEPTH_TEST );

		// Tell openGL to read from the front buffer when capturing
		// out paint strokes 
		glReadBuffer( GL_FRONT );
		ortho();

	}

	glClear( GL_COLOR_BUFFER_BIT );

	if ( m_pDoc->m_ucPainting ) 
	{
		// note that both OpenGL pixel storage and the Windows BMP format
		// store pixels left-to-right, BOTTOM-to-TOP!!  thus all the fiddling
		// around with startrow.

		m_nWindowWidth=w();
		m_nWindowHeight=h();

		int drawWidth, drawHeight;
		GLvoid* bitstart;

		// we are not using a scrollable window, so ignore it
		Point scrollpos;	// = GetScrollPosition();
		scrollpos.x=scrollpos.y=0;

// 		drawWidth	= min( m_nWindowWidth, m_pDoc->m_nWidth );
// 		drawHeight	= min( m_nWindowHeight, m_pDoc->m_nHeight );

		drawWidth	= m_nWindowWidth;
		drawHeight	= m_nWindowHeight;

		//int	startrow	= m_pDoc->m_nHeight - (scrollpos.y + drawHeight);
		int	startrow	= 0;
	//	int	startrow	= m_pDoc->m_nPaintHeight - (scrollpos.y + drawHeight);

		if ( startrow < 0 ) 
			startrow = 0;


		bitstart = m_pDoc->m_ucPainting + m_pDoc->m_nDepth * ((m_pDoc->m_nWidth * startrow) + scrollpos.x);
		bitstart = m_pDoc->m_ucPainting;

		if (m_pDoc->m_fileType == 0) {

			// just copy image to GLwindow conceptually
			glRasterPos2i( 0, m_nWindowHeight - drawHeight );
			glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
			glPixelStorei( GL_UNPACK_ROW_LENGTH, m_pDoc->m_nWidth );
			glDrawBuffer( GL_BACK );
			glDrawPixels( drawWidth, drawHeight, GL_RGB, GL_UNSIGNED_BYTE, bitstart );

			glFlush();

		}

		else {


			// just copy image to GLwindow conceptually
			glRasterPos2i( 0, m_nWindowHeight - drawHeight );
			glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
			glPixelStorei( GL_UNPACK_ROW_LENGTH, m_pDoc->m_nPaintWidth);
			glDrawBuffer( GL_BACK );
			glDrawPixels( drawWidth, drawHeight, GL_RGBA, GL_UNSIGNED_BYTE, bitstart );

			glFlush();


		}
	}

}


int PaintView::handle(int event)
{


	return 1;
}

void PaintView::refresh()
{
	redraw();
}

void PaintView::resizeWindow(int width, int height)
{
	int cx = x();
	int cy = y();
	resize(cx, cy, width, height);
}


