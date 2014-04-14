//
// tinyPhotoShop.cpp
//
// The main driver program for the other parts. We have two major components,
// UI and Doc.
// They do have a link to each other as their member such that they can 
// communicate.
//
 #pragma warning (disable : 4311)
 #pragma warning (disable : 4312)

#include <stdio.h>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Shared_Image.H>

#include "imageUI.h"
#include "imageDoc.h"

ImageUI *impUI;
ImageDoc *impDoc;

int main(int	argc, 
		 char**	argv) 
{

	Fl::scheme("gtk+"); //plastic 
	impDoc = new ImageDoc();

	// Create the UI
	impUI = new ImageUI();

	fl_register_images();

	// Set the impDoc which is used as the bridge between UI and brushes
	impUI->setDocument(impDoc);
	impDoc->setUI(impUI);

	Fl::visual(FL_DOUBLE|FL_INDEX);

	impUI->show();

	return Fl::run();
}
