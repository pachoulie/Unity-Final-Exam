#ifndef BARY_H
#define BARY_H

#include <vector>
#include <tr1/array>
#include <assert.h>
#include <math.h>
#include <limits>

using namespace std;

typedef std::tr1::array<double,2>  Point2D;
typedef std::tr1::array<double,3>  Point3D;

////////////////////////////////////////////////////////////////////////////////

int  mean_value_coordinates( const vector<Point2D> &cageCoords,
                              const Point2D &queryCoord,
                              vector<double> &baryCoords);

int  green_coordinates( const vector<Point2D> &cageCoords, 
                       const Point2D    &queryCoord,
                       vector<double>   &phi, vector<double> &psi);


void setGreenBary2GlobalCoords( const vector<Vertex*> &cageNodes, 
                                const vector<double>  &orgseglen, 
                                const vector<double>  &newseglen, 
                                const vector<Point2D> &cageNormals,
                                Vertex *anyNode ); 

void setBary2GlobalCoords( const vector<Vertex*> &cageNodes, Vertex *anyNode ); 

void GreenCoordinates( const vector<Vertex*>    & modelNodes,
                       const vector<Vertex*>    & cageNodes , bool genfield = 0);

void MeanValueCoordinates(const vector<Vertex*> & modelNodes,
                          const vector<Vertex*> & cageNodes, bool genfield = 0 );

void HarmonicCoordinates(const vector<Vertex*>   & modelNodes,
                         const vector<Vertex*>   & cageNodes, bool genfield = 1);

#endif
