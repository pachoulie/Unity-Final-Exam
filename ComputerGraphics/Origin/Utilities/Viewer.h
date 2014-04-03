 // File: Viewer.h
 // Author: Lucas Kovar
#pragma warning( disable : 4312 )
#pragma warning( disable : 4311 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4275 )
#pragma warning( disable : 4251 )
#pragma once
#include "Utilities.h"

class Viewer;


#include "MathVec3D.h"
/**
 * \brief A class to control the viewing parameters.
 *
 * This class maintains and provides access to parameters of a simple viewing model, 
 * and it supports basic viewing operations like translation, rotation, and zooming.
 * The view parameters are:
 *		- The view point (where the camera is located)
 *		- The view center (a point that is being looked at; the closer it is to the
 *		   view point, the greater the degree of zooming)
 *		- The up vector (defines the global vertical axis; typically this is the y axis)
 *		- The field of view (defined as the vertical angular span of the viewing
 *		   frustrum in radians
 *		- The aspect ratio (the ratio width/height for the resultant image)
*/
class UTIL_API  Viewer {
	public:

		/** Constructor */
		Viewer( 
			const MathVec3D<double> &viewPoint, const MathVec3D<double> &viewCenter, const MathVec3D<double> &upVector, 
			double fieldOfView, double aspectRatio
		);

		/** The worldspace location of the center of focus */
		MathVec3D<double> getViewPoint() const;
		/** This corresponds to the worldspace location of  OpenGL's "look at" point */
		MathVec3D<double> getViewCenter() const;
		/**	The up vector in worldspace coordinates */
		MathVec3D<double> getUpVector() const;
		double getFieldOfView() const;
		double getAspectRatio() const;

		/** The (normalized) worldspace vector from the viewpoint	to the view center */
		MathVec3D<double> getViewDir() const;

		/** The worldspace direction (i.e., normalized vector) of the horizontal image axis */
		MathVec3D<double> getImagePlaneHorizDir() const;

		/** The worldspace direction (i.e., normalized vector) of the vertical image axis	*/
		MathVec3D<double> getImagePlaneVertDir() const;

		/** 
		 * Translate
		 *
		 * These methods alter the view based on mouse movement.  The arguments
		 * changeHoriz and changeVert specify, respectively, the amount
		 * the mouse has moved horizontally/vertically as a fraction of the
		 * total screen width/height.
		 *
		 * translate: The final argument determines whether the translation is
		 * parallel to the view plane; if not, then only the vertical mouse 
		 * movement (second argument) is used.  The actual amount of 
		 * translation is determined by the distance between the view center 
		 * and the view point.
		 *
		*/
		void translate( double changeHoriz, double changeVert, bool parallelToViewPlane );

		/** 
		 * Zoom
		 *
		 * These methods alter the view based on mouse movement.  The arguments
		 * changeHoriz and changeVert specify, respectively, the amount
		 * the mouse has moved horizontally/vertically as a fraction of the
		 * total screen width/height.
		 *
		 * zoom: Zoom in or out by changing the distance between the view
		 * center and the viewpoint; the view center is held fixed.  The 
		 * distance is changed by a fraction 2.0 ^ (m_zoomFraction*changeVert)
		 * of the current distance; m_zoomFraction can be altered to adjust
		 * zoom speed.
		 *
		*/
		void zoom( double changeVert );

		/** 
		 * Rotate
		 *
		 * These methods alter the view based on mouse movement.  The arguments
		 * changeHoriz and changeVert specify, respectively, the amount
		 * the mouse has moved horizontally/vertically as a fraction of the
		 * total screen width/height.
		 *
		 *
		 * rotate: Rotate about the view plane axes; the first argument is for 
		 * rotation about the vertical view axis and the second is for
		 * rotation about the horizontal view axis.  The amount of rotation
		 * is controlled by m_rotateSpeed.
		*/
		void rotate( double changeHoriz, double changeVert );

		/** 
		 * Center at
		 *
		 * These methods alter the view based on mouse movement.  The arguments
		 * changeHoriz and changeVert specify, respectively, the amount
		 * the mouse has moved horizontally/vertically as a fraction of the
		 * total screen width/height.
		 *
		 * centerAt: Centers the view at the given location without changing the
		 * global orientation or scaling.
		*/
		void centerAt( const MathVec3D<double> &pos );

		/** 
		 * Look From
		 *
		*/
		void lookFrom( const MathVec3D<double> &pos );

		/** Set the field of view*/
		void setFieldOfView( double fieldOfView );
		/** Set up the aspect ratio*/
		void setAspectRatio( double aspectRatio );
		/** Set up the translate speed */
		void setTranslateSpeed( double translateSpeed );
		/** Set up the zoom factor*/
		void setZoomFraction( double zoomFraction );
		/** Set up the roation speed */
		void setRotateSpeed( double rotateSpeed );

	private:

		MathVec3D<double> m_viewPoint;
		MathVec3D<double> m_viewCenter;
		MathVec3D<double> m_upVector;
		double m_fieldOfView;
		double m_aspectRatio;

		double m_translateSpeed;
		double m_zoomFraction;
		double m_rotateSpeed;

		MathVec3D<double> m_viewDir;
		MathVec3D<double> m_imagePlaneHorizDir;
		MathVec3D<double> m_imagePlaneVertDir;

		/**
		 * These member variables hold the width and height of the plane that
		 * a) is parallel to the clipping planes, b) passes through the
		 * the view center, and c) is clipped by the frustrum boundaries.
		 * This is useful for converting mouse input into view transformations
		 * of an appropriate magnitude.
		 */

		double m_displayWidth;
		double m_displayHeight;

		/** These are used for tracking */

		double m_lastDesired[3];

		/**
		 * The following values contain the geometry of our viewing volume: the
		 * field of view, the aspect ratio, the height and width of view plane 
		 * containing the center of projection, the world-coordinate directions
		 * of the image x and y axes, and the dimensions of the viewport.
		 */
		void getFrustrumInfo();
};
