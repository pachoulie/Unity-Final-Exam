//
// imageUI.h
//
// The header file for the UI part
//

#ifndef ImageUI_h
#define ImageUI_h

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_File_Chooser.H>		// FLTK file chooser
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Color_Chooser.H>


#include "originalView.h"
#include "paintView.h"




class ImageUI {
public:
	ImageUI();
	~ImageUI();

	// The FLTK widgets
	Fl_Window*			m_mainWindow;
	Fl_Menu_Bar*		m_menubar;
								
	PaintView*			m_paintView;
	OriginalView*		m_origView;


	// Member functions
	void				setDocument(ImageDoc* doc);
	ImageDoc*	getDocument();

	void				show();
	void				resize_windows(int w, int h);

	// Interface to get attribute


	void				setSize(int size);




private:
	ImageDoc*	m_pDoc;		// pointer to document to communicate with the document



	// Static class members
	static Fl_Menu_Item		menuitems[];

	static ImageUI*	whoami(Fl_Menu_* o);

	// All callbacks here.  Callbacks are declared 
	// static
	static void	cb_load_image(Fl_Menu_* o, void* v);
	static void	cb_save_image(Fl_Menu_* o, void* v);

	static void	cb_clear_canvas(Fl_Menu_* o, void* v);
	static void	cb_exit(Fl_Menu_* o, void* v);
	static void	cb_about(Fl_Menu_* o, void* v);

	static void	cb_resize(Fl_Menu_* o, void* v);
	static void	cb_copy(Fl_Menu_* o, void* v);
	static void	cb_convolution(Fl_Menu_* o, void* v);
};

#endif

