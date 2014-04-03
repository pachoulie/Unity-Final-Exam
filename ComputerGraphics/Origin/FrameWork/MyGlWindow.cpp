

#include "MyGlWindow.h"
#include "MathVec3D.h"
#include <iostream>
#include "drawUtils.h"

std::vector<Vec3f *> m_points;
std::vector<Vec3f *> m_triangles;


#include "rply.h"

//**************************************************************************
//
// Implementation of MyGLWindow
//==========================================================================


static double DEFAULT_VIEW_POINT[3] = {30, 30, 30};
static double DEFAULT_VIEW_CENTER[3] = {0, 0, 0};
static double DEFAULT_UP_VECTOR[3] = {0, 1, 0};

MyGlWindow::MyGlWindow(int x, int y, int w, int h) :
  Fl_Gl_Window(x,y,w,h)
//==========================================================================
{
    
    mode( FL_RGB|FL_ALPHA|FL_DOUBLE | FL_STENCIL );
 	
	fieldOfView = 45;

	MathVec3D<double> viewPoint( DEFAULT_VIEW_POINT );
	MathVec3D<double> viewCenter( DEFAULT_VIEW_CENTER );
	MathVec3D<double> upVector( DEFAULT_UP_VECTOR );
	double aspect = ( w /  h);
	m_viewer = new Viewer( viewPoint, viewCenter, upVector, 45, aspect );
	
	
	m_bvh = 0;

}


  void MyGlWindow::setupLight()
  {
	  // set up the lighting
	  GLfloat lightPosition[] = {50, 200.0, 50, 1.0};
	 
	  GLfloat lightPosition2[] = {-100.0, 10.0, -150.0, 1.0};
	  GLfloat lightPosition3[] = {0, -200, 0, 1.0};
	  GLfloat violetLight[] = {0.5f, 0.1f, .5f, 1.0};
	  GLfloat yellowishLight[] = {1, 1, 1, 1.0};
	  GLfloat blueLight[] = {.1f,.1f,.3f,1.0};


	  glEnable(GL_COLOR_MATERIAL);
	  glEnable(GL_DEPTH_TEST);
	  glEnable(GL_LIGHTING);
	  glEnable(GL_LIGHT0);
	  glEnable(GL_LIGHT1);
	  glEnable(GL_LIGHT2);
	  glEnable(GL_DEPTH);

	  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	  glLightfv(GL_LIGHT0, GL_DIFFUSE, yellowishLight);

	  glLightfv(GL_LIGHT1, GL_POSITION, lightPosition2);
	  glLightfv(GL_LIGHT1, GL_DIFFUSE, yellowishLight);

	  glLightfv(GL_LIGHT2, GL_POSITION, lightPosition3);
	  glLightfv(GL_LIGHT2, GL_DIFFUSE, blueLight);  

	  glEnable (GL_BLEND); 
	 // glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
  }



   int vertex_cb(p_ply_argument argument) {
	  long eol;
	  static int index = 0;
	  static double p[3];
	  static double t;
	  
	  ply_get_argument_user_data(argument, NULL, &eol);
	  t = ply_get_argument_value(argument);
	  printf("%g", ply_get_argument_value(argument));
	  p[index] = t;
	  index++;

	  if (eol) { 
		  printf("  %d   \n ",index);
		  Vec3f * v = new Vec3f(p[0],p[1],p[2]);
		  m_points.push_back(v)		;
		  index = 0;
		  
	  }
	  else printf(" ");
	  return 1;
  }

  int face_cb(p_ply_argument argument) {
	  long length, value_index;
	  static int index = 0;
	  static double p[3];
	  static double t;

	  ply_get_argument_property(argument, NULL, &length, &value_index);
	  switch (value_index) {
		case 0:
		case 1:
			{
				printf("%g ", ply_get_argument_value(argument));
				t = ply_get_argument_value(argument);
				p[index] = t;
				index++;
			}
			break;
		case 2:
			{
				printf("%g\n", ply_get_argument_value(argument));
				t = ply_get_argument_value(argument);
				p[index] = t;
				index++;
				Vec3f * v = new Vec3f(p[0],p[1],p[2]);
				m_triangles.push_back(v);
				index = 0;
			}
			
			break;
		default: 
			break;
	  }
	  return 1;
  }

int MyGlWindow::loadply()
{

	p_ply ply = ply_open("roof.ply", NULL, 0, NULL);
	if (!ply) return 1;
	if (!ply_read_header(ply)) return 1;

	int nvertices = ply_set_read_cb(ply, "vertex", "x", vertex_cb, NULL, 0);
	ply_set_read_cb(ply, "vertex", "y", vertex_cb, NULL, 0);
	ply_set_read_cb(ply, "vertex", "z", vertex_cb, NULL, 1);
	int ntriangles = ply_set_read_cb(ply, "face", "vertex_indices", face_cb, NULL, 0);
	printf("%ld\n%ld\n", nvertices, ntriangles);
	if (!ply_read(ply)) return 1;
	ply_close(ply);

	std::cout << m_points.size() << std::endl;
}


void MyGlWindow::drawStuff()
{


}

//==========================================================================
void MyGlWindow::draw()
//==========================================================================
{

  glViewport(0,0,w(),h());

	// clear the window, be sure to clear the Z-Buffer too
  glClearColor(0.2f,0.2f,.2f,0);		// background should be blue


  glClearStencil(0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glEnable(GL_DEPTH);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  
  // now draw the ground plane
  setProjection();
  setupFloor();

  glPushMatrix();
  drawFloor(50,32);
  glPopMatrix();

  // now to draw the shadows



  setupLight();


  // Add a sphere to the scene.
  glBegin(GL_LINES);
  glColor3f(1,0,0);
  glVertex3f(0,0,0);
  glVertex3f(0,100,0);
  glColor3f(0,1,0);
  glVertex3f(0,0,0);
  glVertex3f(100,0,0);
  glColor3f(0,0,1);
  glVertex3f(0,0,0);
  glVertex3f(0,0,100);
  glEnd();


 
 

  setupShadows();
  drawStuff();
  unsetupShadows();


  drawStuff();


}

void MyGlWindow::setProjection(int clearProjection)
//==========================================================================
{
  glMatrixMode(GL_PROJECTION);
  glViewport(0,0,w(),h());
  if (clearProjection)
	glLoadIdentity();
  // compute the aspect ratio so we don't distort things
  double aspect = ((double) w()) / ((double) h());
  gluPerspective(fieldOfView, aspect, 1, 1000);

  // put the camera where we want it to be
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  // use the transformation in the ArcBall

  gluLookAt( 
	  m_viewer->getViewPoint().x(), m_viewer->getViewPoint().y(), m_viewer->getViewPoint().z(), 
	  m_viewer->getViewCenter().x(), m_viewer->getViewCenter().y(), m_viewer->getViewCenter().z(), 
	  m_viewer->getUpVector().x(), m_viewer->getUpVector().y(), m_viewer->getUpVector().z()
	  );
  
  glDisable (GL_BLEND); 
}

static int last_push;
int m_pressedMouseButton;
int m_lastMouseX;
int m_lastMouseY;

int MyGlWindow::handle(int e)
//==========================================================================
{

  switch(e) {
  case FL_SHOW:		// you must handle this, or not be seen!
	  show();
	  return 1;
  case FL_PUSH:
	  {
		 
		  m_pressedMouseButton = Fl::event_button();

	//	  m_viewer->setAspectRatio( static_cast<double>(this->w()) / static_cast<double>(this->h()) );

		  m_lastMouseX = Fl::event_x();
		  m_lastMouseY = Fl::event_y();
	  }
	  damage(1);
	  return 1;
  case FL_RELEASE:
	  m_pressedMouseButton = -1;
	  damage(1);
	  return 1;
  case FL_DRAG: // if the user drags the mouse
	  {

		  double fractionChangeX = static_cast<double>(Fl::event_x() - m_lastMouseX) / static_cast<double>(this->w());
		  double fractionChangeY = static_cast<double>(m_lastMouseY - Fl::event_y()) / static_cast<double>(this->h());

		  if( m_pressedMouseButton == 1 ) {
			  m_viewer->rotate( fractionChangeX, fractionChangeY );
		  } else if( m_pressedMouseButton == 2 ) {
			  m_viewer->zoom( fractionChangeY );
		  } else if( m_pressedMouseButton == 3 ) {
			  m_viewer->translate( -fractionChangeX, -fractionChangeY, (Fl::event_key(FL_Shift_L) == 0) || (Fl::event_key(FL_Shift_R) == 0));
		  } else {
			  std::cout << "Warning: dragging with unknown mouse button!  Nothing will be done" << std::endl;
		  }

		  m_lastMouseX = Fl::event_x();
		  m_lastMouseY = Fl::event_y();
		  redraw();
	  }
	 
	  return 1;
  
  case FL_KEYBOARD:
	  return 0;

  default:
	return 0;
  }
}


//
// get the mouse in NDC
//==========================================================================
void MyGlWindow::getMouseNDC(float& x, float& y)
//==========================================================================
{
	// notice, we put everything into doubles so we can do the math
	  float mx = (float) Fl::event_x();	// remeber where the mouse went down
	  float my = (float) Fl::event_y();

	  // we will assume that the viewport is the same as the window size
	  float wd = (float) w();
	  float hd = (float) h();

	  // remember that FlTk has Y going the wrong way!
	  my = hd-my;
	
	  x = (mx / wd) * 2.0f - 1.f;
	  y = (my / hd) * 2.0f - 1.f;
}

