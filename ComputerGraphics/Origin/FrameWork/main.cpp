// the main routine makes the window, and then runs an even loop
// until the window is closed
#include <windows.h>
#include <iostream>

#include <FL/Fl_Gl_Window.h>
#include <Fl/Fl.h>
#include <Fl/Fl_Value_Slider.H>
#include <Fl/Fl_Button.h>
#include <Fl/Fl_Choice.h>
#include <Fl/Fl_File_Chooser.H>
#include <FL/Fl_Box.h>
#include "MyGlWindow.h"
#include "RunButton.H"



#include "BVH.h"
#include "Fl_GIF_Image.H"


Fl_Group* widgets;


void load_cb(Fl_Widget*w, Fl_Widget* o)
{	

	MyGlWindow * win = (MyGlWindow *) o;

	
	win->damage(1);
}

static void cb_Auto(Fl_Button*, void*) {
	Fl_Window * x=Fl::first_window();
	x->~Fl_Window();
}

void animate(void* data) {
	((Fl_Widget*)data)->damage();
	((Fl_Widget*)data)->redraw();
	Fl::add_timeout(.2,animate,data);
}



int main()
{


	



	Fl::scheme("plastic") ;// plastic
	int width = 800;
	int height = 800;
	Fl_Double_Window* wind = new Fl_Double_Window(100,100,width,height,"GL 3D FrameWork");

	wind->begin();		// put widgets inside of the window
	MyGlWindow* gl = new MyGlWindow(10,10,width-20,height-50);
	

	
		

	widgets = new Fl_Group(820,5,190,590);
	widgets->begin();


	Fl_Box* resizebox = new Fl_Box(820,595,200,5);
	widgets->resizable(resizebox);

	widgets->end();

	Fl_Button * loadBVH = new Fl_Button(200,height-30,100,20,"LoadBVH");
	loadBVH->callback((Fl_Callback*)load_cb,gl);


	gl->m_slider = new RunSlider(gl,0,400, height-30,190,20);

	gl->time = gl->m_slider;
	wind->resizable(gl);

	Fl_Choice *	stepRate = new Fl_Choice(700,height-30, 100, 20);
	stepRate->down_box(FL_BORDER_BOX);
	stepRate->labelsize(10);
	stepRate->textsize(10);
	stepRate->add("60"  ,0,0,(void*)60);
	stepRate->add("30"  ,0,0,(void*)30);
	stepRate->add("15"  ,0,0,(void*)15);
	stepRate->add("10"  ,0,0,(void*)10);
	stepRate->add("5"   ,0,0,(void*)5);
	stepRate->value(1);

	RunButton* rb = new RunButton(gl->m_slider, stepRate, 600,height-30,80,20);



	wind->end();



	wind->show();	// this actually opens the window


	Fl::run();
	delete wind;

	return 1;
}

