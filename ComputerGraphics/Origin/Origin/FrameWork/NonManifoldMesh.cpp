#include "NonManifoldMesh.h"
#include <iostream>

int Vertex::global_id = 0;

////////////////////////////////////////////////////////////////////////////////

struct CutNode {
    CutNode() {}

    CutNode( Point2D &p, double s, int side) {
        point = p;
        t     = s;
        faceside = side;
    }

    bool operator < ( const CutNode &rhs) const {
        return t < rhs.t;
    }

    double t;
    double faceside;
    Point2D point;
};

////////////////////////////////////////////////////////////////////////////////

BoundingBox Edge :: getBoundingBox() const
{
    vector<Point2D> points(2);
    points[0] = connect[0]->getCoords();
    points[1] = connect[1]->getCoords();
    BoundingBox box(points);
    return box;
}

///////////////////////////////////////////////////////////////////////////////

BoundingBox Face :: getBoundingBox() const
{
    int nSize = connect.size();
    vector<Point2D> points(nSize);

    for( int i = 0; i < nSize; i++)
        points[i] = connect[i]->getCoords();

    BoundingBox box(points);
    return box;
}
///////////////////////////////////////////////////////////////////////////////

BoundingBox GeomCurve :: getBoundingBox() const
{
    int nSize = edges.size();
    vector<Point2D> points(2*nSize);

    list<Edge*>::const_iterator it;
    int index = 0;
    for( it = edges.begin(); it != edges.end(); ++it) {
        Edge *e = *it;
        points[index++] = e->getNodeAt(0)->getCoords();
        points[index++] = e->getNodeAt(1)->getCoords();
    }

    BoundingBox box(points);
    return box;
}
///////////////////////////////////////////////////////////////////////////////

bool intersect ( const BoundingBox &box1, const BoundingBox &box2)
{
    if( box1.minCorner[0] > box2.maxCorner[0] ) return 0;
    if( box1.minCorner[1] > box2.maxCorner[1] ) return 0;

    if( box2.minCorner[0] > box1.maxCorner[0] ) return 0;
    if( box2.minCorner[1] > box1.maxCorner[1] ) return 0;

    return 1;
}
///////////////////////////////////////////////////////////////////////////////

void
inverse22(const long double *inmat, long double *omat)
{
    long double a = inmat[0];
    long double b = inmat[1];
    long double c = inmat[2];
    long double d = inmat[3];

    long double det = a * d - b*c;
    assert(fabs(det) > 0.0);

    long double multby = 1.0/det;

    omat[0] = d*multby;
    omat[1] = -b*multby;
    omat[2] = -c*multby;
    omat[3] = a*multby;
}
///////////////////////////////////////////////////////////////////////////////

bool
intersect(double *a, double *b, double *c, double *d)
{
    double abc = orient2d(a, b, c);
    double abd = orient2d(a, b, d);
    double cda = orient2d(c, d, a);
    double cdb = orient2d(c, d, b);

    if (abc == 0 && abd == 0) return 0;

    if (abc * abd > 0) return 0;
    if (cda * cdb > 0) return 0;

    return 1;
}
///////////////////////////////////////////////////////////////////////////////

int
intersect(const Edge *seg1, const Edge *seg2, Point2D &point, double &sab, double &scd)
{
    double a[2], b[2], c[2], d[2], e[2], f[2];

    long double s, t;
    long double m[4], im[4];

    const Point2D  &pa =  seg1->getNodeAt(0)->getCoords();
    const Point2D  &pb =  seg1->getNodeAt(1)->getCoords();

    const Point2D  &pc =  seg2->getNodeAt(0)->getCoords();
    const Point2D  &pd =  seg2->getNodeAt(1)->getCoords();

    a[0] = pa[0];
    a[1] = pa[1];
    b[0] = pb[0];
    b[1] = pb[1];
    c[0] = pc[0];
    c[1] = pc[1];
    d[0] = pd[0];
    d[1] = pd[1];

    if (intersect(a, b, c, d)) {
        m[0] = b[0] - a[0];
        m[1] = c[0] - d[0];
        m[2] = b[1] - a[1];
        m[3] = c[1] - d[1];
        inverse22(m, im);
        s = im[0]*(c[0] - a[0]) + im[1]*(c[1] - a[1]);
        if (s < 0.0 || s > 1.0) return 0;

        t = im[2]*(c[0] - a[0]) + im[3]*(c[1] - a[1]);
        if (t < 0.0 || t > 1.0) return 0;

        sab      = (double)s;
        scd      = (double)t;
        point[0] = (double)( (long double) a[0] + s * m[0] );
        point[1] = (double)( (long double) a[1] + s * m[2] );

        if( s < std::numeric_limits<double>::min() ) return 1;
        if( (1.0 - s) < std::numeric_limits<double>::min() ) return 2;

        return 3;
    }
    return 0;
}


///////////////////////////////////////////////////////////////////////////////

void intersect( const Face *face, const Edge *cutedge,
                vector<int> &faceSides, vector<Vertex*> &newnodes)
{
    //////////////////////////////////////////////////////////////////////////
    // Input:   polygon ( Any "N" sided polygon (convex or concave ))
    //          cutedge ( any straight line edge )
    //
    // Output:  faceSide: edges which are intersected with the cutedge.
    //          newnodes: new intersection nodes on the polygon.
    //          	  These nodes are ordered in the ascending order of
    //                    parametric value along the "cutedge".
    //////////////////////////////////////////////////////////////////////////

    double sab;  // Parametric value of the cut at the I  edge;
    double tcd;  // Parametric value of the cut at the II edge;

    faceSides.clear();
    newnodes.clear();

    int numSegments = face->getSize(0);

    Point2D point;

    vector<CutNode> cutnodes;

    cutnodes.reserve( numSegments );

    for (int i = 0; i < numSegments; i++) {
        const Vertex *v0 =  face->getNodeAt( (i+0)%numSegments);
        const Vertex *v1 =  face->getNodeAt( (i+1)%numSegments);
        Edge  faceedge(v0,v1);
        if( intersect( &faceedge, cutedge, point, sab, tcd) ) {
            cutnodes.push_back( CutNode( point, tcd, i));
        }
    }

    sort( cutnodes.begin(), cutnodes.end(), std::less<CutNode>() );

    for( int i = 0; i < cutnodes.size(); i++) {
        Vertex *v = new Vertex;
        v->setPristine(0);
        v->setCoords( cutnodes[i].point );
        faceSides.push_back(cutnodes[i].faceside);
        newnodes.push_back(v);
    }
}

///////////////////////////////////////////////////////////////////////////////

bool GeomCurve :: isChain() const
{
    // Checks if the nodes on the curve form a linear chain.
    list<Edge*>::const_iterator it;

    const Vertex *prev_end_vertex;

    int index = 0;
    for( it = edges.begin(); it != edges.end(); ++it) {
        const Edge *e = *it;
        if( index++ == 0 ) {
            prev_end_vertex = e->getNodeAt(1);
        } else {
            if( e->getNodeAt(0) != prev_end_vertex ) return 0;
            prev_end_vertex = e->getNodeAt(1);
        }
    }
    return 1;
}

///////////////////////////////////////////////////////////////////////////////

Edge* GeomCurve :: splitAt( Edge *edge, Vertex *vmid)
{
    //
    // Whenever an edge on the list is dividing, the list is modified i.e
    // if the edge( v0, v1) is divided at vmid, then (v0,vmid) U ( vmid,v1)
    // is created. We modify the original edge to (v0, vmid) and return
    // a new edge ( vmid,v1).
    //

    list<Edge*>::iterator it;
    for( it = edges.begin(); it != edges.end(); ++it)
        if( *it == edge ) break;

    assert( it != edges.end() );

    const Vertex *v0 = edge->getNodeAt(0);
    const Vertex *v1 = edge->getNodeAt(1);

    edge->setNodes( vmid, v1 );

    Edge *newedge = new Edge(v0, vmid);
    edges.insert(it, newedge);

    splitNodes.push_back(vmid);

    assert( isChain() );
}

///////////////////////////////////////////////////////////////////////////////

void GeomCurve ::linear_refine(int ntimes )
{
    vector<Edge*>  curredges;

    Point2D  pm;
    for( int i = 0; i < ntimes; i++) {
        size_t numEdges = edges.size();
        curredges.resize( numEdges );
        copy( edges.begin(), edges.end(), curredges.begin() );

        for( int j = 0; j < numEdges; j++) {
            Edge *edge = curredges[i];
            const Point2D &p0 = edge->getNodeAt(0)->getCoords();
            const Point2D &p1 = edge->getNodeAt(1)->getCoords();
            Vertex *vm = new Vertex;
            pm[0] = 0.5*( p0[0] + p1[0] );
            pm[1] = 0.5*( p0[1] + p1[1] );
            vm->setCoords(pm);
            splitAt( edge, vm);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
bool Face::contains(Point2D &pnew) const
{
    double  ori[3];
    assert( connect.size() == 3 );

    Point2D &pa = connect[0]->xyCoords;
    Point2D &pb = connect[1]->xyCoords;
    Point2D &pc = connect[2]->xyCoords;

    ori[0]  = orient2d( &pb[0], &pc[0], &pnew[0] );
    ori[1]  = orient2d( &pc[0], &pa[0], &pnew[0] );
    ori[2]  = orient2d( &pa[0], &pb[0], &pnew[0] );

    int side = 0;
    for(int i = 0; i < 3; i++)
        if( ori[i] < 0) side = 1;

    if( side == 0)  return 1;

    return 0;
}

///////////////////////////////////////////////////////////////////////////////

Face *FaceMesh::contains( const Vertex *v) const
{
    assert(v);
    size_t numFaces = faces.size();

    Point2D xyCoord = v->xyCoords;
    for( size_t i = 0; i < numFaces; i++)
        if( faces[i]->contains(xyCoord) ) return faces[i];

    return NULL;
}

///////////////////////////////////////////////////////////////////////////////

void FaceMesh :: build_relations( int src, int dst )
{
    if( src == 0 && dst == 0) build_relations00();
    if( src == 0 && dst == 2) build_relations02();
    if( src == 2 && dst == 2) build_relations22();
}

///////////////////////////////////////////////////////////////////////////////

void FaceMesh :: build_relations00()
{
    size_t numfaces = faces.size();
    for( int i = 0; i < numfaces; i++) {
        Face *face = faces[i];
        int nnodes = face->getSize(0);
        for( int j = 0; j < nnodes; j++) {
            Vertex *v = face->getNodeAt(j);
            v->clearRelations(0);
        }
    }

    for( int i = 0; i < numfaces; i++) {
        Face *face = faces[i];
        int nnodes = face->getSize(0);
        for( int j = 0; j < nnodes; j++) {
            Vertex *v0 = face->getNodeAt((j+0)%nnodes);
            Vertex *v1 = face->getNodeAt((j+1)%nnodes);
            v0->addRelation(v1);
            v1->addRelation(v0);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

void FaceMesh :: build_relations02()
{
    size_t numfaces = faces.size();

    for( int i = 0; i < numfaces; i++) {
        Face *face = faces[i];
        int nnodes = face->getSize(0);
        for( int j = 0; j < nnodes; j++) {
            Vertex *v = face->getNodeAt(j);
            v->clearRelations(2);
        }
    }

    for( int i = 0; i < numfaces; i++) {
        Face *face = faces[i];
        int nnodes = face->getSize(0);
        for( int j = 0; j < nnodes; j++) {
            Vertex *v0 = face->getNodeAt(j);
            v0->addRelation(face);
        }
    }
}
///////////////////////////////////////////////////////////////////////////////

vector<Edge*>  FaceMesh :: getEdges()
{
     build_relations00();

     vector<Edge*>  meshedges;

     size_t numnodes =  getSize(0);
     meshedges.reserve( 3* numnodes );
     for( int i = 0; i < numnodes; i++) {
          Vertex *src = nodes[i];
          const vector<Vertex*> &neighs = src->getRelations0();
          for( int j = 0; j < neighs.size(); j++) {
               Vertex *dst = neighs[j];
               if( src < dst ) {
                   Edge *newedge = new Edge( src, dst );
                   meshedges.push_back(newedge);
               }
         }
     }
     return meshedges;
}

///////////////////////////////////////////////////////////////////////////////

vector<Face*> FaceMesh :: getRelations112( const Vertex *v0, const Vertex *v1)
{
    const vector<Face*> &v0faces = v0->getRelations2();
    const vector<Face*> &v1faces = v1->getRelations2();

    assert( !v0faces.empty()  && !v1faces.empty() );

    vector<Face*> faceneighs;

    set_intersection(v0faces.begin(), v0faces.end(), v1faces.begin(),
                     v1faces.end(), back_inserter(faceneighs));
    return faceneighs;
}

///////////////////////////////////////////////////////////////////////////////

void FaceMesh :: build_relations22()
{
    build_relations02();

    size_t numfaces = faces.size();
    for( int i = 0; i < numfaces; i++) {
        Face *face = faces[i];
        face->clearRelations(2);
    }

    vector<Face*> faceneighs;
    for( int i = 0; i < numfaces; i++) {
        Face *face = faces[i];
        int nnodes = face->getSize(0);
        for( int j = 0; j < nnodes; j++) {
            Vertex *v0 = face->getNodeAt((j+0)%nnodes);
            Vertex *v1 = face->getNodeAt((j+1)%nnodes);
            faceneighs = getRelations112( v0, v1);
            for( int k = 0; k < faceneighs.size(); k++) {
                if( faceneighs[k] != face )
                    face->addRelation( faceneighs[k] );
            }
        }
    }

    // Self is not allowed ...
    for( int i = 0; i < numfaces; i++) {
        Face *face = faces[i];
        assert( face->getNumRelations(2) ) ;
        assert( !face->hasRelation( face ) );
   }

}

///////////////////////////////////////////////////////////////////////////////

int NonManifoldMesh2D :: readEmbeddedTriMesh( const string &filename)
{
    ifstream infile( filename.c_str(), ios::in);
    if( infile.fail() ) return 1;

    mesh = new FaceMesh;
    string str;
    infile >> str;
    assert( str == "OFF");

    size_t numNodes, numFaces,  numEdges;
    infile >> numNodes >> numFaces >> numEdges;

    mesh->nodes.resize( numNodes );
    mesh->faces.resize( numFaces );

    Vertex::global_id = 0;
    double z;
    Point2D p;
    for( size_t i = 0; i < numNodes; i++) {
        infile >> p[0] >> p[1] >> z;
        Vertex *v = new Vertex;
        v->setPristine(1);
        v->setID(Vertex::global_id++);
        v->setCoords(p);
        mesh->nodes[i] = v;
    }

    int n0, n1, n2, nSides;
    vector<Vertex*> connect(3);
    int minid = std::numeric_limits<int>::max();
    for( size_t i = 0; i < numFaces; i++) {
        infile >> nSides >> n0 >> n1 >> n2;
        assert( nSides == 3 );
        Face *face = new Face;
        connect[0] = mesh->nodes[n0];
        connect[1] = mesh->nodes[n1];
        connect[2] = mesh->nodes[n2];
        face->setNodes( connect );
        face->setID(i);
        mesh->faces[i] = face;
    }

    return 0;
}

///////////////////////////////////////////////////////////////////////////////
int NonManifoldMesh2D :: addEmbeddedTriMesh ( const vector<Face*> &faces)
{
    mesh = new FaceMesh;
    mesh->faces = faces;
    return 0;
}

///////////////////////////////////////////////////////////////////////////////

GeomCurve* NonManifoldMesh2D :: addCutCurve( vector<Vertex*> &nodes,
        int closedCurve)
{
    Vertex *v0, *v1;
    Edge  *segment;

    GeomCurve *curve = new GeomCurve;
    size_t numNodes = nodes.size();
    /*
        for( size_t i = 0; i < numNodes; i++)  {
             nodes[i]->setID( Vertex::global_id++);
             cout << "CurveID " << nodes[i]->getID() << endl;
        }
    */
    for( size_t i = 0; i < numNodes-1; i++) {
        v0 = nodes[i];
        v1 = nodes[i+1];
        segment = new Edge( v0, v1);
        curve->edges.push_back(segment);
    }

    if( closedCurve) {
        v0 = nodes.back();
        v1 = nodes.front();
        segment = new Edge( v0, v1);
        curve->edges.push_back(segment);
    }

    cutCurves.push_back( curve );

    return curve;
}

///////////////////////////////////////////////////////////////////////////////

int NonManifoldMesh2D :: readCutCurves( const string &filename)
{
    ifstream infile( filename.c_str(), ios::in);
    if( infile.fail() ) return 1;

    int numCurves;
    infile >> numCurves;

    Point2D p;
    size_t numNodes, closedCurve;
    Vertex *v0, *v1;
    Edge  *segment;
    int id = 0;
    vector<Vertex*> nodes;
    for( int j = 0; j < numCurves; j++) {
        GeomCurve *curve = new GeomCurve;
        infile >> numNodes >> closedCurve;
        nodes.resize(numNodes);
        for( size_t i = 0; i < numNodes; i++) {
            infile >> p[0] >> p[1];
            Vertex *v = new Vertex;
            v->setPristine(1);
            v->setCoords( p );
            nodes[i] = v;
        }
        addCutCurve( nodes, closedCurve );
    }

    return 0;
}

///////////////////////////////////////////////////////////////////////////////

GeomCurve* NonManifoldMesh2D :: addCutCurve( vector<Point2D> &v, int closedCurve)
{
    vector<Vertex*>  nodes;
    for( int i = 0; i < v.size(); i++)
        nodes[i] = new Vertex;
    return addCutCurve( nodes, closedCurve );
}

///////////////////////////////////////////////////////////////////////////////

int NonManifoldMesh2D :: cutTriMesh( GeomCurve *curve)
{
    Face *face = NULL;
    Edge *edge = NULL;

    list<Edge*>::const_iterator it;
    for( it = curve->edges.begin(); it != curve->edges.end(); ++it) {
        edge = *it;
        face  = mesh->contains( edge->getNodeAt(0) );
        if( face ) break;
    }
    if( face == NULL ) return 1;

//CSV
    vector<int>  face_sides;
    vector<Vertex*>  newnodes;
    while( it != curve->edges.end() ) {
        edge = *it;
        cout << edge->getNodeAt(0)->getID() << " " << edge->getNodeAt(1)->getID() << endl;
        getchar();
        intersect( face, edge, face_sides, newnodes);
        if( newnodes.size() ) {
            cout << " Intersect Now " << Vertex::global_id << endl;
            for( int i = 0; i < newnodes.size(); i++) {
                newnodes[i]->setID( Vertex::global_id++);
                cout << newnodes[i]->getID() << endl;
                curve->splitAt( edge, newnodes[i] );
            }
        } else
            ++it;
    }
}

///////////////////////////////////////////////////////////////////////////////
int NonManifoldMesh2D :: cutTriMesh()
{
    int nCurves = cutCurves.size();
    for( int i = 0; i <  nCurves; i++) {
        int err = cutTriMesh( cutCurves[i] );
        if( err ) return 1;
    }
    return 0;
}

///////////////////////////////////////////////////////////////////////////////

/*
void Face::percolate_down( const Face *face, vector<Face*> &leafnodes)
{
   if( children.empty() ) {
         leafnodes.push_back(face);
         return;
   }

   vector<Face*> &children = face->getChildren();
   for( int i = 0; i < children.size(); i++)
        percolate_down( children[i], leafnodes)
}
///////////////////////////////////////////////////////////////////////////////

vector<Face*> Face::getLeafs() const
{
     vector<Face*> leafs;
     percolate_down( this, leafs);
     return leafs;
}

*/
///////////////////////////////////////////////////////////////////////////////

FaceMesh* NonManifoldMesh2D :: getDuplicatedMesh() const
{
    /*
        FaceMesh *dupmesh = new FaceMesh;

        size_t numFaces = trimesh->getSize(2);
        for( size_t i = 0; i < numFaces; i++)  {
             Face *face = mesh->faces[i];
             vector<Face*>  faces = face->getLeafs();
             for( size_t j = 0; faces.size(); j++)
                  dupmesh->addFace( faces[i] );
        }
    */
}

///////////////////////////////////////////////////////////////////////////////

void NonManifoldMesh2D :: enumerate()
{
    int numCurves = cutCurves.size();
    Vertex *vertex;
    list<Edge*>::iterator it;

    for( int i = 0; i < numCurves; i++) {
        GeomCurve *curve = cutCurves[i];
        int numEdges = curve->getNumSegments();
        for( it = curve->edges.begin(); it != curve->edges.end(); ++it) {
            Edge *edge = *it;
            for( int j = 0; j < 2; j++) {
                vertex  = edge->getNodeAt(j);
                vertex->visitMark = 0;
            }
        }
    }

    int numFaces = mesh->faces.size();
    for( int i = 0; i < numFaces; i++) {
        Face *face = mesh->faces[i];
        for( int j = 0; j < 3; j++) {
            vertex = face->getNodeAt(j);
            vertex->visitMark = 0;
        }
    }

    int index = 0;
    for( int i = 0; i < numFaces; i++) {
        Face *face = mesh->faces[i];
        for( int j = 0; j < 3; j++) {
            vertex  = face->getNodeAt(j);
            if( !vertex->visitMark ) {
                vertex->setID( index++);
                vertex->visitMark = 1;
            }
        }
    }

    for( int i = 0; i < numCurves; i++) {
        GeomCurve *curve = cutCurves[i];
        int numEdges = curve->getNumSegments();
        for( it = curve->edges.begin(); it != curve->edges.end(); ++it) {
            Edge *edge = *it;
            for( int j = 0; j < 2; j++) {
                vertex  = edge->getNodeAt(j);
                if( !vertex->visitMark ) {
                    vertex->setID( index++);
                    vertex->visitMark = 1;
                }
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

void NonManifoldMesh2D :: saveAs( const string &filename)
{
    ofstream  ofile(filename.c_str(), ios::out);
    if( ofile.fail() ) return;

    FaceMesh *dupmesh = getDuplicatedMesh();

    size_t numNodes = dupmesh->getSize(0);
    for( int i = 0; i < numNodes; i++) {
        const Point2D &xyCoords = mesh->nodes[i]->xyCoords;
        ofile << xyCoords[0] << " " << xyCoords[1] << endl;
    }

    size_t numFaces = dupmesh->getSize(2);
    for( int i = 0; i < numFaces; i++) {
        Face *face = dupmesh->faces[i];
        int nfnodes = face->getSize(0);
        ofile << nfnodes << endl;
        for( int j = 0; j < nfnodes; j++)
            ofile << face->getNodeAt(j)->getID() << " ";
        ofile << endl;
    }
}
///////////////////////////////////////////////////////////////////////////////
