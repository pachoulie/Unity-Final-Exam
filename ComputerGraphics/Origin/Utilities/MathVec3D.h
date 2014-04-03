// File: MathVec3D.h
// Tom Brunet adapted code by Lucas Kovar

#pragma once

#include "Utilities.h"
#include <vector>
#include "Debug.h"

/**
 * \brief A class for a Euclidean 3-vectors.
 *
 * This class provides an encapsulation of Euclidean 2-vectors, with standard 
 * operations like addition, subtraction, dot products, cross products, 
 * distances between to vectors, and projection/orthogonalization supported.
 * All methods are inlined for efficiency, and this class is templated so floats 
 * may be used if large numbers of MathVec3D's must be stored.
 */
template<class T> class MathVec3D {
	public: // CTORS/ Copy
        /**
         * Create a 0 vector.
         */
        MathVec3D( );

        /** Create a vector where all elems are val */
        explicit MathVec3D(T val);

		/** Create a vector (x,y,z). */
		MathVec3D( T x, T y, T z);

        /** Copy a vector from an array. */ 
        MathVec3D( const T *array );

        /** Copy a vector from an array. */ 
        MathVec3D( const std::vector<T>& array );

        /** Copy CTOR. */ 
		MathVec3D( const MathVec3D<T> &rhs );

        /** Swig assignment op. */
		MathVec3D& copy( const MathVec3D<T> &rhs );

#ifndef SWIG
        /**
         * Assignment Op.
         */
        MathVec3D& operator = (const MathVec3D& rhs);

        /**
         * Assign every value of the vector to a given value.
         */
        MathVec3D<T>& operator = (T value);
#endif

        ~MathVec3D();


    public: // Operators
		// =  : copy the given MathVec3D
		// +  : return a new MathVec3D that is the sum with the argument
		// -  : return a new MathVec3D that is the difference from the argument
		// * (scalar) : return a copy, scaled by the given value 
		//				(definition is outside of class; see end of file)
		// / (scalar) : return a copy, scaled by the inverse of the given value
		// * (MathVec3D) : return the dot product
		// ^  : return the cross product
		// [] : return the element at the given array index (0 -> x, 1 -> y, else error)

		/** == : returns true iff each coordinate is equal. */
		bool operator == ( const MathVec3D<T> &vec ) const;
		/** != : returns true iff at least one coordinate is different. */
		bool operator != ( const MathVec3D<T> &vec ) const;

  		/** += : element-wise addition. */
		MathVec3D<T>& operator += ( const MathVec3D<T> &vec );
        /** += : element-wise add offset. */
		MathVec3D<T>& operator += ( const T offset );
        /** Element-wise add a vector to this and return a new vector with the result. */
		MathVec3D<T> operator + ( const MathVec3D<T> &vec ) const;
        /** Element-wise add a scalar and return a new vector with the result. */
        MathVec3D<T> operator + ( double scale ) const;
        /** Element-wise add a scalar and return a new vector with the result. */
        MathVec3D<T> operator + ( float scale ) const;

        /** -= : element-wise subtraction. */
		MathVec3D<T>& operator -= ( const MathVec3D<T> &vec );
        /** -= : element-wise subtract offset. */
		MathVec3D<T>& operator -= ( const T offset );
        /** Subtract a vector from this and return a new vector with the result. */
		MathVec3D<T> operator - ( const MathVec3D<T> &vec ) const;
        /** Element-wise subtract a scalar and return a new vector with the result. */
        MathVec3D<T> operator - ( double scale ) const;
        /** Element-wise subtract a scalar and return a new vector with the result. */
        MathVec3D<T> operator - ( float scale ) const;
        /** Element-wise invert and return a new vector with the result. */
        MathVec3D<T> operator - () const {
            return MathVec3D<T>(-x(), -y(), -z()); }

        /** /= : element-wise division. */
		MathVec3D<T>& operator /= ( const MathVec3D<T> &vec );
		/** /= : scalar: scale each element by the inverse of the given value. */
		MathVec3D<T>& operator /= ( T scale );
        /** Element-wise divide this vector by scale and return a new vector with the result. */
		MathVec3D<T> operator / ( const MathVec3D<T> &vec ) const;
        /** Element-wise divide a scalar and return a new vector with the result. */
		MathVec3D<T> operator / ( double scale ) const;
        /** Element-wise divide a scalar and return a new vector with the result. */
		MathVec3D<T> operator / ( float scale ) const;

        /** *= : element-wise multiplication. */
		MathVec3D<T>& operator *= ( const MathVec3D<T> &vec );
		/** *= : scalar: scale each element by the given value. */
		MathVec3D<T>& operator *= ( T scale );
        /** Element-wise multiply two vectors and return a new vector with the result. */
		MathVec3D<T> operator * ( const MathVec3D<T> &vec ) const;
        /** Element-wise multiply by a scalar and return a new vector with the result. */
        MathVec3D<T> operator * ( double scale ) const;
        /** Element-wise multiply by a scalar and return a new vector with the result. */
        MathVec3D<T> operator * ( float scale ) const;
		
        /** Replace this MathVec3D with the cross product with the given MathVec3D. */
		MathVec3D<T>& operator ^= ( const MathVec3D<T> &vec );
        /** Get the crossproduct of this and another MathVec3D. */
		MathVec3D<T> operator ^ ( const MathVec3D<T> &vec );

    public: // Accessors
        /** Get x. */
		inline T x() const;
        /** Get y. */
		inline T y() const;
        /** Get z. */
        inline T z() const;

        /** Set x. */
		inline void x( T val );
        /** Set y. */
		inline void y( T val );
        /** Set z. */
        inline void z( T val) ;
        /** Set x, y, and z. */
		inline void set( T x, T y, T z );

        /** Return the dimensionality of this object.
         *
         * Useful if using templates, and not sure if you're using a MathVec2d or 3d.
         */
        inline long dimension() const {
            return 3; }
#ifndef SWIG
        /** Retrieve element at a given index. */
		T& operator [] ( int index );
        /** Retrieve element at a given index (const version). */
		const T& operator [] ( int index ) const;
#endif

        /** Return a representation of this MathVec3D as a C-style array. */
		T* asArray();
		/** Return a representation of this MathVec3D as a C-style array. (const version). */
		const T* asArray() const;

    public: // Mutators and Math
        /** Set this vector to the zero vector. */
		void zero();

        /** The length of this vector under Euclidean norm. */
		T magnitude() const;
        /** Square length of this vector under Euclidean norm. */
		T sqrMagnitude() const;

		/**
	     * Make the length of this vector be 1.  If this is (within tolerance) the zero vector, then it is
		 * left unchanged and an error is reported.
         */
		void normalize();

        /** Euclidean distance to the given vec. */
		T distance( const MathVec3D<T> &vec ) const;
        /** Square of the euclidean distance to the given vec. */
		T sqrDist( const MathVec3D<T> &vec ) const;

		/**
		 * Returns the sum of the elements in this MathVec3D.
         */
		T sumOfElements() const;

		/**
		 * Returns the dot product with the given MathVec3D.
         */
		T dotProduct( const MathVec3D<T> &vec ) const;

        /** 
		 * Adjusts this MathVec3D so it is orthogonal to vec.  If vec is the zero vector, then a warning is printed and this
		 * MathVec3D is set to the zero vector.
         */
		void makeOrthogonalTo( const MathVec3D<T> &vec );

		/**
		 * Adjusts this MathVec3D so it is parallel vec.  If vec is the zero vector, then a warning is printed and this
		 * MathVec3D is left unchanged.
         */
		void projectOnto( const MathVec3D<T> &vec );

		void writeToFile(FILE *fp);
		void loadFromFile(FILE *fp);

		

    public: // I/O
        /**
		 * Returns a string representation of this object.  If the argument is true,
		 * then the elements will be layout oud horizontally, separated by commas.
		 * If it is false, then the elements will be arranged vertically, one number
		 * per line.
         */
		std::string toString() const;

	private:
		// Exporting a template type will generate a compiler warning, even though the 
		// code itself is fine.  Turn this warning off for these member declarations.
		#pragma warning( disable: 4251 )
            T m_vec[3];
		#pragma warning( default: 4251 )

    public: // Friends
#ifndef SWIG
        friend inline UTIL_API std::ostream& operator << (std::ostream & stream, const MathVec3D<T>& vec) {
            return stream << "(" << vec.x() << "," << vec.y() << "," << vec.z() << ")";
        }

        /** Element-wise add a scalar and return a new vector with the result. */
        friend inline MathVec3D<T> operator + ( double scale, const MathVec3D<T> &vec ) {
            return MathVec3D<T>(vec) += static_cast<T>(scale); }

        /** Element-wise add a scalar and return a new vector with the result. */
        friend inline MathVec3D<T> operator + ( float scale, const MathVec3D<T> &vec ) {
            return MathVec3D<T>(vec) += scale; }

        /** Element-wise subtract a scalar and return a new vector with the result. */
        friend MathVec3D<T> operator - ( double scale, const MathVec3D<T> &vec ) {
            T s = static_cast<T>(scale);
            return MathVec3D<T>(s-vec.x(), s-vec.y(), s-vec.z());
        }

        /** Element-wise subtract a scalar and return a new vector with the result. */
        friend MathVec3D<T> operator - ( float scale, const MathVec3D<T> &vec ) {
            T s = static_cast<T>(scale);
            return MathVec3D<T>(s-vec.x(), s-vec.y(), s-vec.z());
        }

        /** Element-wise multiply by a scalar and return a new vector with the result. */
        friend MathVec3D<T> operator * ( double scale, const MathVec3D<T> &vec ) {
            return MathVec3D<T>(vec) *= static_cast<T>(scale); }

        /** Element-wise multiply by a scalar and return a new vector with the result. */
        friend MathVec3D<T> operator * ( float scale, const MathVec3D<T> &vec ) {
            return MathVec3D<T>(vec) *= scale; }
#endif
        /**
         * Linear interpolate between two vectors
         *
         * Assumes one and two are the same dimensionality.  If not, returns an empty vector
         * @param param When 1.0, return two.  When 0.0, returns one.  Otherwise, a linear interpolation between.
         */
        friend MathVec3D<T> inline lerp(T param, const MathVec3D<T>& one, const MathVec3D<T>& two) {
            return MathVec3D<T>((1-param)*one.x()+param*two.x(), (1-param)*one.y()+param*two.y(), (1-param)*one.z()+param*two.z());
        }
};

// Include the .cpp, as each method is inlined
#include "MathVec3D.cpp"

typedef MathVec3D<double> Point3D;
typedef std::pair<Point3D, Point3D> Point3DPair;
typedef std::vector<Point3DPair> Point3DPairList;
typedef std::vector<Point3D> Point3DList;

#ifndef SWIG
// These next two lines are necessary for this class to export correctly to a DLL
#pragma warning(push)
#pragma warning(disable:4231)
UTIL_STL_EXPORT(MathVec3D<double>);
UTIL_STL_EXPORT(MathVec3D<float>);
UTIL_STL_EXPORT(std::allocator<Point3DPair>);
UTIL_STL_EXPORT(std::vector<Point3DPair>);
UTIL_STL_EXPORT(std::allocator<Point3D>);
UTIL_STL_EXPORT(std::vector<Point3D>);
#pragma warning(pop)
#endif
