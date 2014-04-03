// File: Quaternion.h
// Author: Lucas Kovar

#pragma once

class Quaternion;
enum eulerAngleSetT;


#include "Utilities.h"
#include "MathVec3D.h"



#ifndef SWIG
/**
	An enumeration of supported euler angle sets (for example, 
	EULER_ANGLES_ZXY indicates that a Quaternion can be constructed from and converted 
	into ZXY euler angles).
 */
enum eulerAngleSetT {
	EULER_ANGLES_ZXY,
	EULER_ANGLES_XYZ
};
#endif
/**
 * \brief A class for quaternion.
 * This represents quaternions, provides many methods of creating 
 * quaternions that satisfy various criteria, allows basic operations on quaternions,
 * and provides several utility functions (filtering, averaging, slerp, and finding 
 * quaternions that are "closest" to a given quaternion under various restrictions).
 */

class UTIL_API Quaternion {
	public:		// Constructors
		/** Create an identity Quaternion. */
		Quaternion();

		/** Copy an existing Quaternion. */
		Quaternion( const Quaternion &q );

		/** Directly set the coordinates {w, (x,y,z)}. */
		Quaternion( double w, double x, double y, double z );


		// Creating a quaternion
		// -------------------------------------------------------------------------------
		// A quaternion can be created to satisfy a variety of conditions.  In most cases,
		// one can either replace the coordinates of an existing Quaternion or create
		// a new Quaternion; the former use the naming convention setFrom[METHOD] and the
		// latter are static methods using the naming convention from[METHOD].
		//
		/** Create an identity quaternion. */
		void identity();
		bool isIdentity();

		/** Copy the coordinates of a given Quaternion q. */
		void copy( const Quaternion &q );
#ifndef SWIG
		Quaternion& operator = (const Quaternion &q);
#endif
		/** Directly set the coordinates of a quaternion. */
		void setCoords( double w, double x, double y, double z );

#ifndef SWIG
		/** 
		 * Create a quaternion from euler angles (specified in radians).
		 * The order of the euler angles is determined by the first argument.
     */
		void setFromEulers( eulerAngleSetT eulerType, const double *eulerAngles );
		void setFromEulers( eulerAngleSetT eulerType, const MathVec3D<double> &eulerAngles );
		static Quaternion fromEulers( eulerAngleSetT eulerType, const double *eulerAngles );
		static Quaternion fromEulers( eulerAngleSetT eulerType, const MathVec3D<double> &eulerAngles );
#endif
		/**
		 * Create a quaternion from a 3x3 matrix.
	 	 * The matrix is represented as an array of nine elements, with the first row in 
	   * elements 0-2, the second row in elements 3-5, and the third row in elments 
		 * 6-8.  This method has a different name because there is a separate overload of
		 * setCoords that takes as input a single array of doubles (namely, the one that 
		 * makes a Quaternion from a 3-vector representing a log map).
     */
		void setFromMatrix( const double *matrix );
		static Quaternion fromMatrix( const double *matrix );

		/** 
		 * Create a quaternion corresponding to a rotation by [angle] radians about a 
		 *  specified axis.
		 *
		 * The axis may be specified either as an array of three numbers or as one of the 
		 * characters 'x', 'y', or 'z' (lower case or upper case).  If an illegal 
		 * character is used, then an error is printed and the quaternion is set to the
		 * identity.
     */
		void setFromAxisAngle( const double *axis, double angle );
		void setFromAxisAngle( const MathVec3D<double> &axis, double angle );
		void setFromAxisAngle( char axis, double angle );
		static Quaternion fromAxisAngle( const double *axis, double angle );
		static Quaternion fromAxisAngle( const MathVec3D<double> &axis, double angle );
		static Quaternion fromAxisAngle( char axis, double angle );

		/** 
		 * Create a quaternion that will rotate a 3-vector [vec1] such that it faces 
		 *  the same direction as a 3-vector [vec2].
		 *
		 * The input vectors do not need to be unit length.  If one or both of the 
		 * vectors is/are (within tolerance) the zero vector, then the identity rotation 
		 * is created.  If the vectors point along the same line but in opposite directions, 
		 * then the rotation can be about an arbitrary axis.
     */
		void setFromVecAlign( const double *vec1, const double *vec2 );
		void setFromVecAlign( const MathVec3D<double> &vec1, const MathVec3D<double> &vec2 );
		static Quaternion fromVecAlign( const double *vec1, const double *vec2 );
		static Quaternion fromVecAlign( const MathVec3D<double> &vec1, const MathVec3D<double> &vec2 );

		/** 
		 * Create a quaternion that a) is a rotation about the axis [rotAxis] and b) 
		 * when applied to the 3-vector [vec1] makes it point as much as possible in the 
		 * direction of the 3-vector [vec2] (i.e., maximizes the dot product).
		 *
		 * The input vectors do not need to be unit length.  If one or both of the 
		 * vectors is (within tolerance) the zero vector, then the identity rotation is created. 
     */
		void setFromVecAlignAboutAxis( const double *vec1, const double *vec2, const double *rotAxis );
		void setFromVecAlignAboutAxis( const MathVec3D<double> &vec1, const MathVec3D<double> &vec2, const MathVec3D<double> &rotAxis );
		static Quaternion fromVecAlignAboutAxis( const double *vec1, const double *vec2, const double *rotAxis );
		static Quaternion fromVecAlignAboutAxis( const MathVec3D<double> &vec1, const MathVec3D<double> &vec2, const MathVec3D<double> &rotAxis );

		/** 
		 * Create a quaternion that a) is a rotation about the axis [rotAxis] and b) 
		 * is as close as possible to the reference Quaternion [quatToMatch] (i.e., 
		 * minimizes great-arc distance).
     */
		void setFromAxisConstraint( const Quaternion &quatToMatch, const double *rotAxis );
		void setFromAxisConstraint( const Quaternion &quatToMatch, const MathVec3D<double> &rotAxis );
		static Quaternion fromAxisConstraint( const Quaternion &quatToMatch, const double *rotAxis );
		static Quaternion fromAxisConstraint( const Quaternion &quatToMatch, const MathVec3D<double> &rotAxis );

		/** Create a quaternion from a 3-vector representing the log map. */
		void setFromLogMap( const double *logMap );
		void setFromLogMap( const MathVec3D<double> &logMap );
		static Quaternion fromLogMap( const double *logMap );
		static Quaternion fromLogMap( const MathVec3D<double> &logMap );

		/** 
		 * Create a zero quaternion.
		 * While this no longer represents a rotation, it can be useful for orientation 
		 * blending.  There is no equivalent constructor.
     */
		void zero();

		// Manipulating quaternions
		// -------------------------------------------------------------------------------

    /** Convert this quaternion into its inverse. */
		void inverse();
    /** Return the inverse of this quaternion (don't change this one). */
		Quaternion copyAndInvert() const;


		/**	
		 * Multiplies this quaternion by q.  
		 * If the third argument is true, [this]*q is computed; otherwise q*[this] is computed.
		*/
		void multiply( const Quaternion &q, bool rightMultiply);

		/** 
		 * Identical to multiply(const Quaternion &q, bool rightMultiply), 
		 * but q is defined by an axis identifier ('x', 'y', or 'z' - upper 
		 * case or lower case) and angle (in radians).
		*/
		void multiply( char axis, double angle, bool rightMultiply );

		/**
		 * Identical to multiply(const Quaternion &q, bool rightMultiply)
		 * with the second argument true.
		 */
		Quaternion& operator *= ( const Quaternion &q );

		/**
		 * Identical to multiply(const Quaternion &q, bool rightMultiply)
		 * with the second argument true, but the result 
		 * is returned as a new Quaternion.
		 */
		Quaternion operator * ( const Quaternion &q ) const;

		
		/**
		 * These methods apply the appropriate operations with each Quaternion treated 
		 * as a euclidean 4-vector.  Note that the result is in general not unit length 
		 * and hence not a valid rotation.
		*/
		Quaternion& operator += ( const Quaternion &q );
		Quaternion operator + ( const Quaternion &q ) const;
		Quaternion& operator -= ( const Quaternion &q );
		Quaternion operator - ( const Quaternion &q ) const;
		Quaternion& operator *= ( double scale );
		Quaternion operator * ( double scale ) const;
		Quaternion& operator /= ( double scale );
		Quaternion operator / ( double scale ) const;

		/**
		 * Applies the rotation represented by this Quaternion to the given vector.  The 
		 * first method will behave properly if the two arguments point to the same block 
		 * of memory.  The second method returns the result as a temporary variable.
		*/
		void vecMult( const double *vec, double *result ) const;
		MathVec3D<double> vecMult( const MathVec3D<double> &vec ) const;

		/** Extracts the equivalent 4x4 column major matrix for use by openGL. */
		void glMatrix( double mat[16] ) const;

		/**
		 * Computes the equivalent axis-angle representation and stores it in the given 
		 * arguments.  The angle is given in radians.
		 */
		void axisAngle( double *axis, double &angle ) const;
		void axisAngle( MathVec3D<double> &axis, double &angle ) const;

		/**
		 * Returns the equivalent 3x3 rotation matrix.  The results are stored in a 
		 * user-supplied vector of nine elements where the first three elements 
		 * correspond to the first row, the next three to the second row, and the final
		 * three to the third row
		*/
		void rotMatrix( double *result ) const;

		/** Computes the log map representation of this quarternion */
		void logMap( double *result ) const;
		MathVec3D<double> logMap() const;


#ifndef SWIG
   /**
    * Computes equivalent ZXY euler angles; that is, the first, second, and 
    * third elements in the given array will respectively hold the Z, X, and Y 
    * rotations.  The results are given in radians.
    */
		void eulers( eulerAngleSetT eulerType, double *result ) const;
		MathVec3D<double> eulers( eulerAngleSetT eulerType ) const;
#endif

		/**
		 * Replaces this quaternion with its antipode if the latter is closer (in the 
		 * great-arc sense) to [quat].
		*/
		void pickClosest( const Quaternion &quat );

		/**
		 * Returns the dot product with the given quaternion.  This is typically useful 
		 * for determining if a Quaternion should be replaced with its antipode.
		*/
		double dotProduct( const Quaternion &quat ) const;

		/**
		 * Performs spherical linear interpolation between this quaternion and the 
		 * identity quaternion.  If u = 0, this quaternion is set to the identity; if 
		 * u = 1, it is unchanged.
		*/
		void damp( double u );

		/** Returns the great-arc distance to the given quaternion. */
		double distance( const Quaternion &quat ) const;

		/** Returns the magnitude of the rotation corresponding to this quaternion. */
		double magnitude() const;

		/**
		 * Scales this quaternion to have unit length.  If the quaternion is the zero 
		 * vector, then it is left unchanged and an error is printed.
		*/
		void normalize();

		/** 
		 * Returns a representation of this Quaternion as a 4-vector 
		 * w, x, y, z = [angle, axis]
		*/
		double *asArray();
		const double *asArray() const;

		/** Returns/sets the value of the given coordinate. */
		double w() const;
		void w( double val );
		double x() const;
		void x( double val );
		double y() const;
		void y( double val );
		double z() const;
		void z( double val );

		
		/** 
		 * Return the element at the given array index (0 -> w, 1 -> x, 
		 * 2 -> y, 3 ->z ).  If [index] > 3, an error is printed to cerr.
		*/
#ifndef SWIG
		double& operator [] ( int index );
		const double& operator [] ( int index ) const;
#endif
		// Utility methods
		// -------------------------------------------------------------------------------
		/** 
		 * Performs spherical linear interpolation on q1 and q2.  If u = 0, this returns 
		 * q1; if u = 1 this returns q2.
		 */
		static Quaternion slerp( const Quaternion &q1, const Quaternion &q2, double u );

		/** 
		 * Performs the exp of the quaternion (cite from Jehee Lee's Quaternion class)
		 */
		static Quaternion exp(MathVec3D <double>& w);

		/** 
		 * Performs the ln of the quaternion (cite from Jehee Lee's Quaternion class) :
		 * This is same as 2 * logmap() in this class
		 */
		static MathVec3D<double> ln(Quaternion & q);

		/**
		 * Modifies the given sequence (array) of Quaternions so element i is on the same 
		 * side of the 4-sphere as element i-1. That is, this eliminates numerical 
		 * discontinuities that stem from antipode equivalence.
		 */
		static void selectAntipodesForContinuity( Quaternion *rotations, int numPts );
		static void selectAntipodesForContinuity( std::vector<Quaternion> &rotations );

		/**
		 * Modifies the given sequence (array) of angles (2D rotations) so the distance 
		 * between element i and element i-1 is always <= PI.
		*/
		static void selectAnglesForContinuity( double *rotations, int numRots );
		static void selectAnglesForContinuity( std::vector<double> &rotations );

		/**
		 * Convolves the given signal with the supplied kernel.  At boundaries the 
		 * first/last point is repeated.  If the kernel is of even width, then the extra 
		 * tap is placed at the end, rather than the beginning.  The input signal is 
		 * first run through selectAntipodesForContinuity to eliminate spurious numerical
		 * differences (i.e., individual Quaternions may change numerically, but they
		 * are guaranteed to represent the same orientation).
		 *
		 * signal, numPts: the original signal and its length
		 * kernel, kernelWidth: the filter kernel and its width.
		 * result: An array of at least numPts elements, which must NOT be the same as 
			  the first argument.
		*/
		static void filterRotations( Quaternion *signal, int numPts, const double *kernel, int kernelWidth, Quaternion *result );
		static void filterRotations( std::vector<Quaternion> &signal, const std::vector<double> &kernel, std::vector<Quaternion> &result );

		/**
		 * Computes the average orientation of the given array of numOrients orientations 
		 * and stores the result in the final argument.  The input signal is first run 
		 * through selectAntipodesForContinuity to eliminate spurious numerical 
		 * differences (i.e., individual Quaternions may change numerically, but they are
		 * guaranteed to represent the same orientation).
		*/
		static Quaternion average( Quaternion *orients, int numOrients );
		static Quaternion average( std::vector<Quaternion> &orients );

		/**
		 * Computes the average value of [orients[i] * orients[i-1]^(-1)] over the given 
		 * array of numOrients orientations and stores the logarithmic map of the result 
		 * in the final argument. This is the average angular velocity in the event that 
		 * the spacing between samples is a unit of time; otherwise the average angular 
		 * velocity can be obtained by scaling the result by the inverse of the time 
		 * between samples.
		*/
		static void averageVelocity( const Quaternion *orients, int numVals, double *result );
		static MathVec3D<double> averageVelocity( const std::vector<Quaternion> &orients );
		
		/**
		 * Spline Interpolation
		 *
		 *	Get the quaternion at time t [0:1] given the quaternions at time 0 (pt1) 
		 *	and time 1 (pt2), i.e. the location of the end points, and the angular 
		 *	velocities at time 0 (w1) and time 1 (w2), i.e. the angular velocities of 
		 *	the end points
		*/
		static Quaternion hermite(const Quaternion pt1, const Quaternion pt2, const MathVec3D<double> w1, const MathVec3D<double> w2, double t);

		/** Returns a string containing the coordinates of this quaternion. */
		std::string toString() const;

		/** Returns a string containing the axis/angle representation of this quaternion. */
		std::string toAxisAngleString() const;

#ifndef SWIG
        friend inline std::ostream& operator << (std::ostream& stream, const Quaternion& quat) {
            return stream << "(" << quat.m_coords[0] << "," << quat.m_coords[1] << "," << quat.m_coords[2] << "," << quat.m_coords[3] << ")";
        }
#endif
	private:

		double m_coords[4];	// w, x, y, z = [scalar, 3-vector]

		// mult
		//
		// Low-level method for quaternion multiplication.
		void mult( const double *otherQuat, bool rightMultiply );
};

// The default constructor and copy routines are inlined for efficiency

inline Quaternion::Quaternion() {
	m_coords[0] = 1;
	m_coords[1] = 0;
	m_coords[2] = 0;
	m_coords[3] = 0;
}

inline Quaternion::Quaternion( const Quaternion &q ) {
	memcpy( m_coords, q.m_coords, sizeof(m_coords) );
}

inline void Quaternion::copy( const Quaternion &quat ) {
	memcpy( m_coords, quat.m_coords, sizeof(m_coords) );
}

inline Quaternion& Quaternion::operator=( const Quaternion &quat ) {
	if( this != &quat ) {
		memcpy( m_coords, quat.m_coords, sizeof(m_coords) );
	}
	return *this;
}
