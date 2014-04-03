/************************************************************************
     File:        simple4.cpp

     Author:     
                  Michael L Gleicher, gleicher@cs.wisc.edu
     Modifier
                  Yu-Chi Lai, yu-chi@cs.wisc.edu
     
     Comment:     written 10/16/99, Michael L Gleicher
		              This provides a utility routine to help with animation
									This file implements a "play" button. The idea is that you creat a 
									window that	does your drawing. When redrawing, this window looks at a 
									slider to see what time it is, so it knows what part of the animation to 
									draw.

									The slider must call the window's redraw function whenever the time changes.

									The play button, when pressed, advances the slider forward a timestep continually.
									In order to do this, it installs itself in the FlTk "Idle" loop so it gets called
									periodically.
   
     Platform:    Visio Studio.Net 2003
*************************************************************************/

#include <iostream>
#include "RunButton.H"
#include <Fl/Fl.h>
#include <time.h>

#include "MyGlWindow.h"

// the guts of the slider - 
void runSliderCB(Fl_Widget*, Fl_Widget* o)
{
	o->damage(1);
	
}

// the slider constructor
RunSlider::RunSlider(Fl_Widget* dr, int length,
					 int x, int y, int w, int h) : Fl_Value_Slider(x,y,w,h)
{
	// set up slider parameters
	value(0);
	range(0,length);
	step(1);
	type(5);				// horizontal, "nice"
	when(FL_WHEN_CHANGED);	// update whenever it changes

	callback((Fl_Callback*) runSliderCB, dr);
}

//
// this callback function is the "guts" of the RunButton -
// notice that it is an "idle" callback, not a widget callback
//
// another nice problem to have - most likely, we'll be too fast
// don't draw more than 30 times per second
void runButtonCB(RunButton* b)
{
	if (b->value()) {	// only advance time if appropriate
		
		const char* rc = b->choice->text(b->choice->value());
		int r = atoi(rc);

		if (clock() - b->lastRedraw > CLOCKS_PER_SEC/(float)r) {
			b->lastRedraw = clock();
			int t = (int) b->slider->value();
			int m = (int) b->slider->maximum();
			t++;
			if (t>=m) t=0;	// wrap around
			b->slider->value(t);
				// note: FlTk doesn't have the slider call its callback
			// when the value is changed internally
			(b->slider->callback())(b->slider,b->slider->user_data());

			MyGlWindow * win = (MyGlWindow *) b->slider->user_data();
			win->run = 1;
			
		}
	} 
	else {
		MyGlWindow * win = (MyGlWindow *) b->slider->user_data();
		win->run = 0;
	}

}

// create the run button - the main thing it does is install the idle
// handler
RunButton::RunButton(Fl_Slider* time,  Fl_Choice * choice,
					 int x, int y, int w, int h) : Fl_Light_Button(x,y,w,h,"Play")
{
	Fl::add_idle((void (*)(void*))runButtonCB,this);
	slider = time;
	this->choice = choice;
	lastRedraw = 0;
}
RunButton::~RunButton()
{
	Fl::remove_idle((void (*)(void*))runButtonCB,this);
}
