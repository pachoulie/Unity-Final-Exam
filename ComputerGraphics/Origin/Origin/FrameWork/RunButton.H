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

#ifndef RUNBUTTON_H
#define RUNBUTTON_H


#include <Fl/Fl_Value_Slider.H>
#include <Fl/Fl_Light_Button.H>
#include <Fl/Fl_Choice.H>

// the time slider
// the only thing it does is create itself. all of its work happens
// in a callback it installs
class RunSlider  : public Fl_Value_Slider {
public:
	RunSlider(Fl_Widget* draw,		// what needs to be told to redraw
				  int length,			// how many frames is the animation
				  int x, int y, int w,int h);			// standard slider parameters

  };

// the run button - advances the slider periodically
// note: this is hard coded to 30 frames per second
class RunButton : public Fl_Light_Button {
public:
	RunButton(Fl_Slider* time, Fl_Choice * choice,		// what to advance
			  int x, int y, int w, int h);
	~RunButton();					// remove the idle function

	Fl_Slider* slider;				// need to remember this
	Fl_Choice * choice;
	long lastRedraw;				// time of last redraw
};

#endif
