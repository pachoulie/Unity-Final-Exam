/// GraphicsTown2006 - CS559 Sample Code
// written by Michael Gleicher - originally written Fall, 2000
// updated Fall, 2005
//
//#include "GrTown_PCH.H"

#include "GL/glew.h"
//#include "glee.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include "DrawUtils.H"
#include "MMatrix.H"

// texture coords...
static float tco[4][2] = {
  {0,0}, {1,0}, {1,1}, {0,1}
};

// Use this for debugging - it is helpful to see if your polys are
// oriented correctly
// we give it texture coordinate, but no promises. basically, they are
// only right if you are drawing squares. That are clockwise
// #define DRAW_POLYGON_NORMALS
void polygon(int nv, ...)
{
#ifdef DRAW_POLYGON_NORMALS
  double cx=0,cy=0,cz=0;
#endif
  
  float ccw = 1;
  if (nv < 0) {
	nv = -nv;
	ccw = -1;
  } else glFrontFace(GL_CW);


  if (nv<3) {
	printf("too few vertices in polygon!\n");
	return;
  }
	
  va_list ap;
  va_start(ap,nv);

  // first 3 points are special...
  double p1[3],p2[3],p3[3];
  p1[0] = va_arg(ap,double); 
  p1[1] = va_arg(ap,double);
  p1[2] = va_arg(ap,double);
  p2[0] = va_arg(ap,double); 
  p2[1] = va_arg(ap,double);
  p2[2] = va_arg(ap,double);
  p3[0] = va_arg(ap,double); 
  p3[1] = va_arg(ap,double);
  p3[2] = va_arg(ap,double);

#ifdef DRAW_POLYGON_NORMALS
  cx = p1[0] + p2[0] + p3[0];
  cy = p1[1] + p2[1] + p3[1];
  cz = p1[2] + p2[2] + p3[2];
#endif

  // compute the normal
  float d1[3], d2[3];
  float n[3];
  d1[0] = (float) (p2[0] - p1[0]);
  d1[1] = (float) (p2[1] - p1[1]);
  d1[2] = (float) (p2[2] - p1[2]);
  d2[0] = (float) (p2[0] - p3[0]);
  d2[1] = (float) (p2[1] - p3[1]);
  d2[2] = (float) (p2[2] - p3[2]);
  cross(d1[0],d1[1],d1[2],d2[0],d2[1],d2[2],n[0],n[1],n[2]);
  normalize(n);
  if (ccw<0) 
	scale(n,-1);

  glNormal3f( n[0], n[1], n[2] );

  /*  printf("(%g %g %g) (%g %g %g) (%g %g %g) -> (%g %g %g)\n",
	  p1[0], p1[1], p1[2],
	  p2[0], p2[1], p2[2],
	  p3[0], p3[1], p3[2],
	  n[0],n[1],n[2]);
  */
  int tv = 0;
  glBegin(GL_POLYGON);
  glTexCoord2fv(tco[(tv++)%4]);
  glVertex3dv(p1);
  glTexCoord2fv(tco[(tv++)%4]);
  glVertex3dv(p2);
  glTexCoord2fv(tco[(tv++)%4]);
  glVertex3dv(p3);

  for(int i=3; i<nv; i++) {
	p3[0] = va_arg(ap,double); 
	p3[1] = va_arg(ap,double);
	p3[2] = va_arg(ap,double);
#ifdef DRAW_POLYGON_NORMALS
	cx += p3[0];
	cy += p3[1];
	cz += p3[2];
#endif
	glTexCoord2fv(tco[(tv++)%4]);
	glVertex3dv(p3);
  }
  glEnd();


#ifdef DRAW_POLYGON_NORMALS
  // draw a little normal vector
  cx /= ((double) nv);
  cy/= ((double) nv);
  cz/= ((double) nv);
  glColor3f(1,1,1);
  glLineWidth(3);
  glBegin(GL_LINES);
  glVertex3d(cx,cy,cz);
  glVertex3d(cx+8*n[0],cy+8*n[1],cz+8*n[2]);
  glEnd();
#endif

  va_end(ap);
  glFrontFace(GL_CCW);
}
void polygoni(int nv, ...)
{
#ifdef DRAW_POLYGON_NORMALS
  double cx=0,cy=0,cz=0;
#endif
  float ccw = 1;
  if (nv < 0) {
	nv = -nv;
	ccw = -1;
  } else glFrontFace(GL_CW);


  if (nv<3) {
	printf("too few vertices in polygon!\n");
	return;
  }
	
  va_list ap;
  va_start(ap,nv);

  // first 3 points are special...
  double p1[3],p2[3],p3[3];
  p1[0] = va_arg(ap,int); 
  p1[1] = va_arg(ap,int);
  p1[2] = va_arg(ap,int);
  p2[0] = va_arg(ap,int); 
  p2[1] = va_arg(ap,int);
  p2[2] = va_arg(ap,int);
  p3[0] = va_arg(ap,int); 
  p3[1] = va_arg(ap,int);
  p3[2] = va_arg(ap,int);

  // compute the normal
  float d1[3], d2[3];
  float n[3];
  int tv = 0;
  d1[0] = (float) (p2[0] - p1[0]);
  d1[1] = (float) (p2[1] - p1[1]);
  d1[2] = (float) (p2[2] - p1[2]);
  d2[0] = (float) (p2[0] - p3[0]);
  d2[1] = (float) (p2[1] - p3[1]);
  d2[2] = (float) (p2[2] - p3[2]);
  cross(d1[0],d1[1],d1[2],d2[0],d2[1],d2[2],n[0],n[1],n[2]);
  normalize(n);
  if (ccw<0) 
	scale(n,-1);

#ifdef DRAW_POLYGON_NORMALS
  cx = p1[0] + p2[0] + p3[0];
  cy = p1[1] + p2[1] + p3[1];
  cz = p1[2] + p2[2] + p3[2];
#endif
  glNormal3f( n[0], n[1], n[2] );

  /*  printf("(%g %g %g) (%g %g %g) (%g %g %g) -> (%g %g %g)\n",
	  p1[0], p1[1], p1[2],
	  p2[0], p2[1], p2[2],
	  p3[0], p3[1], p3[2],
	  n[0],n[1],n[2]);
  */
  glBegin(GL_POLYGON);
  glTexCoord2fv(tco[(tv++)%4]);
  glVertex3dv(p1);
  glTexCoord2fv(tco[(tv++)%4]);
  glVertex3dv(p2);
  glTexCoord2fv(tco[(tv++)%4]);
  glVertex3dv(p3);

  for(int i=3; i<nv; i++) {
	p3[0] = va_arg(ap,int); 
	p3[1] = va_arg(ap,int);
	p3[2] = va_arg(ap,int);
#ifdef DRAW_POLYGON_NORMALS
	cx += p3[0];
	cy += p3[1];
	cz += p3[2];
#endif
	glTexCoord2fv(tco[(tv++)%4]);
	glVertex3dv(p3);
  }
  glEnd();

#ifdef DRAW_POLYGON_NORMALS
  // draw a little normal vector
  glColor3f(1,1,1);
  glLineWidth(3);
  glBegin(GL_LINES);
  cx /= ((double) nv);
  cy/= ((double) nv);
  cz/= ((double) nv);
  glVertex3d(cx,cy,cz);
  glVertex3d(cx+8*n[0],cy+8*n[1],cz+8*n[2]);
  glEnd();
#endif
  va_end(ap);
  glFrontFace(GL_CCW);
}


void polygonf(int nv, ...)
{
#ifdef DRAW_POLYGON_NORMALS
  double cx=0,cy=0,cz=0;
#endif
  float ccw = 1;
  if (nv < 0) {
	nv = -nv;
	ccw = -1;
  } else glFrontFace(GL_CW);


  if (nv<3) {
	printf("too few vertices in polygon!\n");
	return;
  }
	
  va_list ap;
  va_start(ap,nv);

  // first 3 points are special...
  double p1[3],p2[3],p3[3];
  p1[0] = va_arg(ap,double); 
  p1[1] = va_arg(ap,double);
  p1[2] = va_arg(ap,double);
  p2[0] = va_arg(ap,double); 
  p2[1] = va_arg(ap,double);
  p2[2] = va_arg(ap,double);
  p3[0] = va_arg(ap,double); 
  p3[1] = va_arg(ap,double);
  p3[2] = va_arg(ap,double);

  // compute the normal
  float d1[3], d2[3];
  float n[3];
  int tv = 0;
  d1[0] = (float) (p2[0] - p1[0]);
  d1[1] = (float) (p2[1] - p1[1]);
  d1[2] = (float) (p2[2] - p1[2]);
  d2[0] = (float) (p2[0] - p3[0]);
  d2[1] = (float) (p2[1] - p3[1]);
  d2[2] = (float) (p2[2] - p3[2]);
  cross(d1[0],d1[1],d1[2],d2[0],d2[1],d2[2],n[0],n[1],n[2]);
  normalize(n);
  if (ccw<0) 
	scale(n,-1);

#ifdef DRAW_POLYGON_NORMALS
  cx = p1[0] + p2[0] + p3[0];
  cy = p1[1] + p2[1] + p3[1];
  cz = p1[2] + p2[2] + p3[2];
#endif
  glNormal3f( n[0], n[1], n[2] );

  /*  printf("(%g %g %g) (%g %g %g) (%g %g %g) -> (%g %g %g)\n",
	  p1[0], p1[1], p1[2],
	  p2[0], p2[1], p2[2],
	  p3[0], p3[1], p3[2],
	  n[0],n[1],n[2]);
  */
  glBegin(GL_POLYGON);
  glTexCoord2fv(tco[(tv++)%4]);
  glVertex3dv(p1);
  glTexCoord2fv(tco[(tv++)%4]);
  glVertex3dv(p2);
  glTexCoord2fv(tco[(tv++)%4]);
  glVertex3dv(p3);

  for(int i=3; i<nv; i++) {
	p3[0] = va_arg(ap,double); 
	p3[1] = va_arg(ap,double);
	p3[2] = va_arg(ap,double);
#ifdef DRAW_POLYGON_NORMALS
	cx += p3[0];
	cy += p3[1];
	cz += p3[2];
#endif
	glTexCoord2fv(tco[(tv++)%4]);
	glVertex3dv(p3);
  }
  glEnd();

#ifdef DRAW_POLYGON_NORMALS
  // draw a little normal vector
  glColor3f(1,1,1);
  glLineWidth(3);
  glBegin(GL_LINES);
  cx /= ((double) nv);
  cy/= ((double) nv);
  cz/= ((double) nv);
  glVertex3d(cx,cy,cz);
  glVertex3d(cx+8*n[0],cy+8*n[1],cz+8*n[2]);
  glEnd();
#endif
  va_end(ap);
  glFrontFace(GL_CCW);
}



// draw a little cube
void cube(double x, double y, double z, double e)
{

	double s = e/2;
	polygon( 4,x-s,y-s,z-s, x+s,y-s,z-s, x+s,y+s,z-s, x-s,y+s,z-s);
	polygon(-4,x-s,y-s,z+s, x+s,y-s,z+s, x+s,y+s,z+s, x-s,y+s,z+s);

	polygon(-4,x-s,y-s,z-s, x-s,y-s,z+s, x-s,y+s,z+s, x-s,y+s,z-s);
	polygon( 4,x+s,y-s,z-s, x+s,y-s,z+s, x+s,y+s,z+s, x+s,y+s,z-s);

	polygon( 4,x-s,y-s,z-s, x-s,y-s,z+s, x+s,y-s,z+s, x+s,y-s,z-s);
	polygon(-4,x-s,y+s,z-s, x-s,y+s,z+s, x+s,y+s,z+s, x+s,y+s,z-s);

}


// draw a little cube
void cube2(double x, double y, double z, double e,double e1,double e2)
{

	double s = e/2;
	double s1 = e1/2;
	double s2 = e2/2;

	polygon( 4,x-s,y-s1,z-s2, x+s,y-s1,z-s2, x+s,y+s1,z-s2, x-s,y+s1,z-s2);
	polygon(-4,x-s,y-s1,z+s2, x+s,y-s1,z+s2, x+s,y+s1,z+s2, x-s,y+s1,z+s2);

	polygon(-4,x-s,y-s1,z-s2, x-s,y-s1,z+s2, x-s,y+s1,z+s2, x-s,y+s1,z-s2);
	polygon( 4,x+s,y-s1,z-s2, x+s,y-s1,z+s2, x+s,y+s1,z+s2, x+s,y+s1,z-s2);

	polygon( 4,x-s,y-s1,z-s2, x-s,y-s1,z+s2, x+s,y-s1,z+s2, x+s,y-s1,z-s2);
	polygon(-4,x-s,y+s1,z-s2, x-s,y+s1,z+s2, x+s,y+s1,z+s2, x+s,y+s1,z-s2);

}

//**********************************************************************//
Color::Color(float R, float G, float B, float A)
{
  if (R>1) r = R/255.0f; else r=R;
  if (G>1) g = G/255.0f; else g=G;
  if (B>1) b = B/255.0f; else b=B;
  if (A>1) a = A/255.0f; else a=A;
}
Color::Color(Color& color)
{
  r = color.r;
  g = color.g;
  b = color.b;
  a = color.a;
}
void Color::operator() (float R, float G, float B, float A)
{
  if (R>1) r = R/255.0f; else r=R;
  if (G>1) g = G/255.0f; else g=G;
  if (B>1) b = B/255.0f; else b=B;
  if (A>1) a = A/255.0f; else a=A;
}
void Color::operator ()(int* c)
{
	r = ((float)c[0])/255.f;
	g = ((float)c[1])/255.f;
	b = ((float)c[2])/255.f;
}

//////////////////////////////////////////////////////////////
void lookatMatrix(float ex, float ey, float ez, 
				  float ax, float ay, float az, Matrix r)
{
  glPushMatrix();
  glLoadIdentity();
  gluLookAt(ex,ey,ez,ax,ay,az,0,1,0);
  glGetFloatv(GL_MODELVIEW_MATRIX,(float*) &r[0][0]);
  glPopMatrix();
}

void  drawBone( double x0, double y0, double z0, double x1, double y1, double z1 )
{

 GLdouble  dir_x = x1 - x0;
 GLdouble  dir_y = y1 - y0;
 GLdouble  dir_z = z1 - z0;
 double ax = (x0+x1)*0.5f;
 double ay = (y0+y1)*0.5f;
 double az = (z0+z1)*0.5f;

 GLdouble  bone_length = sqrt( dir_x*dir_x + dir_y*dir_y + dir_z*dir_z );
 
 static GLUquadricObj *  quad_obj = NULL;
 if ( quad_obj == NULL )
  quad_obj = gluNewQuadric();
  gluQuadricDrawStyle( quad_obj, GLU_FILL );
  gluQuadricNormals( quad_obj, GLU_SMOOTH );
 glPushMatrix();

 glTranslated( x0, y0, z0 );

 double  length;
 length = sqrt( dir_x*dir_x + dir_y*dir_y + dir_z*dir_z );
 if ( length < 0.0001 ) { 
  dir_x = 0.0; dir_y = 0.0; dir_z = 1.0;  length = 1.0;
 }
 dir_x /= length;  dir_y /= length;  dir_z /= length;

 GLdouble  up_x, up_y, up_z;
 up_x = 0.0;
 up_y = 1.0;
 up_z = 0.0;

 double  side_x, side_y, side_z;
 side_x = up_y * dir_z - up_z * dir_y;
 side_y = up_z * dir_x - up_x * dir_z;
 side_z = up_x * dir_y - up_y * dir_x;

 length = sqrt( side_x*side_x + side_y*side_y + side_z*side_z );
 if ( length < 0.0001 ) {
  side_x = 1.0; side_y = 0.0; side_z = 0.0;  length = 1.0;
 }
 side_x /= length;  side_y /= length;  side_z /= length;

 up_x = dir_y * side_z - dir_z * side_y;
 up_y = dir_z * side_x - dir_x * side_z;
 up_z = dir_x * side_y - dir_y * side_x;

 GLdouble  m[16] = { side_x, side_y, side_z, 0.0,
					 up_x,   up_y,   up_z,   0.0,
					 dir_x,  dir_y,  dir_z,  0.0,
					 0.0,    0.0,    0.0,    1.0 };
 glMultMatrixd( m );
GLdouble radius= 0.2f; 

 int slices = 8; 
 int stack = 3;  
 gluCylinder( quad_obj, radius, radius, bone_length, slices, stack ); 
 glPopMatrix();
}