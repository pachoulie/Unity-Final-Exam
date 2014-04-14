/************************************************************************
     File:        TargaImage.h

     Author:     
                  Steven J. Chenney, schenney@cs.wisc.edu
     Modifier
                  Yu-Chi Lai, yu-chi@cs.wisc.edu
     
     Comment:     Class to handle the targa image
   
     Platform:    Visio Studio.Net 2003
*************************************************************************/

#ifndef TARGA_IMAGE_H_
#define TARGA_IMAGE_H_

#include <Fl/Fl.h>
#include <Fl/Fl_Widget.h>
#include <stdio.h>

class TargaImage
{
	// methods
	public:
		// Constructor and destructor
		TargaImage(void);
		TargaImage(int, int, unsigned char*);
		~TargaImage(void);

		// Convert the image to RGB format,
		unsigned char*	To_RGB(void);	   
		// Save the image to a file
		 bool Save_Image(char*);    

		// Load a file and return a pointer to a new TargaImage object.  Returns NULL on failure
		static TargaImage* Load_Image(char*);  

	private:
		// helper function for format conversion
		void RGBA_To_RGB(unsigned char *data, unsigned char *rgb);          
    // reverse the rows of the image, some targas are stored bottom to top
		TargaImage* Reverse_Rows(void);                                      

	// members
	public:
		int		         width;	    // width of the image in pixels
		int		         height;	    // height of the image in pixels
		unsigned char	*data;	    // pixel data for the image, assumed to be in pre-multiplied RGBA format.

};


#endif


