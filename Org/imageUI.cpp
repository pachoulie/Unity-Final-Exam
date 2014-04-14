//
// imageUI.cpp
//
// The user interface part for the program.
//

#pragma warning (disable : 4312)
#pragma warning (disable : 4311)

#include <FL/fl_ask.H>

#include <algorithm>

#include <math.h>

#include "imageUI.h"
#include "imageDoc.h"

ImageUI* ImageUI::whoami(Fl_Menu_* o)	
{
	return ( (ImageUI*)(o->parent()->user_data()) );
}


//--------------------------------- Callback Functions --------------------------------------------

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImageUI::cb_load_image(Fl_Menu_* o, void* v) 
{
	ImageDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp\t*.tga", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->loadImage(newfile);
	}
}


//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImageUI::cb_save_image(Fl_Menu_* o, void* v) 
{
	ImageDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Save File?", "*.bmp", "save.bmp" );
	if (newfile != NULL) {
		pDoc->saveImage(newfile);
	}
}


//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImageUI::cb_clear_canvas(Fl_Menu_* o, void* v)
{
	ImageDoc* pDoc=whoami(o)->getDocument();

	pDoc->clearCanvas();
}

//------------------------------------------------------------
// Causes the tinyPhotoShop program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImageUI::cb_exit(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_mainWindow->hide();


}



//-----------------------------------------------------------
// Brings up an about dialog box
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImageUI::cb_about(Fl_Menu_* o, void* v) 
{
	fl_message("Tiny Photo Shop");
}




//---------------------------------- per instance functions --------------------------------------

//------------------------------------------------
// Return the imageDoc used
//------------------------------------------------
ImageDoc* ImageUI::getDocument()
{
	return m_pDoc;
}

//------------------------------------------------
// Draw the main window
//------------------------------------------------
void ImageUI::show() {
	m_mainWindow->show();
	m_paintView->show();
	m_origView->show();
}

//------------------------------------------------
// Change the paint and original window sizes to 
// w by h
//------------------------------------------------
void ImageUI::resize_windows(int w, int h) {
	m_paintView->size(w,h);
	m_origView->size(w,h);
}

//------------------------------------------------ 
// Set the ImageDoc used by the UI to 
// communicate with the brushes 
//------------------------------------------------
void ImageUI::setDocument(ImageDoc* doc)
{
	m_pDoc = doc;

	m_origView->m_pDoc = doc;
	m_paintView->m_pDoc = doc;
}




// Main menu definition
Fl_Menu_Item ImageUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Load Image...",	FL_ALT + 'l', (Fl_Callback *)ImageUI::cb_load_image },
		{ "&Save Image...",	FL_ALT + 's', (Fl_Callback *)ImageUI::cb_save_image },

		{ "&Clear Canvas", FL_ALT + 'c', (Fl_Callback *)ImageUI::cb_clear_canvas, 0, FL_MENU_DIVIDER },
		
		{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImageUI::cb_exit },
		{ 0 },

	{ "&Process",		0, 0, 0, FL_SUBMENU },
	{ 0 },

	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImageUI::cb_about },
		{ 0 },

	{ 0 }
};

// Brush choice menu definition
// Fl_Menu_Item ImageUI::brushTypeMenu[NUM_BRUSH_TYPE+1] = {
//   {"Points",			FL_ALT+'p', (Fl_Callback *)ImageUI::cb_brushChoice, (void *)BRUSH_POINTS},
//   {"Lines",				FL_ALT+'l', (Fl_Callback *)ImageUI::cb_brushChoice, (void *)BRUSH_LINES},
//   {"Circles",			FL_ALT+'c', (Fl_Callback *)ImageUI::cb_brushChoice, (void *)BRUSH_CIRCLES},
//   {"Scattered Points",	FL_ALT+'q', (Fl_Callback *)ImageUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POINTS},
//   {"Scattered Lines",	FL_ALT+'m', (Fl_Callback *)ImageUI::cb_brushChoice, (void *)BRUSH_SCATTERED_LINES},
//   {"Scattered Circles",	FL_ALT+'d', (Fl_Callback *)ImageUI::cb_brushChoice, (void *)BRUSH_SCATTERED_CIRCLES},
//   {0}
// };



//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImageUI::ImageUI() {
	// Create the main window
	m_mainWindow = new Fl_Window(600, 300, "TinyPhotoShop");
		m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
		// install menu bar
		m_menubar = new Fl_Menu_Bar(0, 0, 600, 25);
		m_menubar->menu(menuitems);
		

		// Create a group that will hold two sub windows inside the main
		// window
		
	//
		
	Fl_Group* group = new Fl_Group(0, 25, 600, 275);
		// install original view window
			m_origView = new OriginalView(0, 25, 300, 275, "This is the orig view");//300jon
			m_origView->box(FL_DOWN_FRAME);
			m_origView->deactivate();

		

			// install paint view window
			m_paintView = new PaintView(300, 25, 300, 275, "This is the paint view");//0jon
			m_paintView->box(FL_DOWN_FRAME);
			m_paintView->resizable();
		

	group->end();
	//Fl_Group::current()->resizable(group);
    m_mainWindow->end();

	// init values


}

ImageUI::~ImageUI()
{
}
