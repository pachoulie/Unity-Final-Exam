// File: MathVec3D.cpp
// Author: Lucas Kovar

#include "UtilitiesPCH.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MathVec3D definition
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T> inline MathVec3D<T>::MathVec3D() {
	m_vec[0] = 0;
	m_vec[1] = 0;
	m_vec[2] = 0;
}

template<class T> inline MathVec3D<T>::MathVec3D(T val) {
    m_vec[0] = val;
    m_vec[1] = val;
    m_vec[2] = val;
}

template<class T> inline MathVec3D<T>::~MathVec3D() {}

template<class T> inline MathVec3D<T>::MathVec3D( T x, T y, T z ) {
	m_vec[0] = x;
	m_vec[1] = y;
	m_vec[2] = z;
}

template<class T> inline MathVec3D<T>::MathVec3D( const T *array ) {
	m_vec[0] = array[0];
	m_vec[1] = array[1];
	m_vec[2] = array[2];
}

template<class T> inline MathVec3D<T>::MathVec3D( const std::vector<T>& array ) {
    m_vec[0] = array[0];
    m_vec[1] = array[1];
    m_vec[2] = array[2];
}

template<class T> inline MathVec3D<T>::MathVec3D( const MathVec3D<T> &toCopy ) {
	m_vec[0] = toCopy.m_vec[0];
	m_vec[1] = toCopy.m_vec[1];
	m_vec[2] = toCopy.m_vec[2];
}

template<class T> inline MathVec3D<T>& MathVec3D<T>::copy ( const MathVec3D<T> &toCopy ) {
	if( this != &toCopy ) {
		m_vec[0] = toCopy.m_vec[0];
		m_vec[1] = toCopy.m_vec[1];
		m_vec[2] = toCopy.m_vec[2];
	}
	return( *this );
}

template<class T> inline MathVec3D<T>& MathVec3D<T>::operator = ( const MathVec3D<T> &toCopy ) {
	if( this != &toCopy ) {
		m_vec[0] = toCopy.m_vec[0];
		m_vec[1] = toCopy.m_vec[1];
		m_vec[2] = toCopy.m_vec[2];
	}
	return( *this );
}

template<class T> inline MathVec3D<T>& MathVec3D<T>::operator = ( T value ) {
	m_vec[0] = value;
	m_vec[1] = value;
	m_vec[2] = value;

	return( *this );
}

template<class T> inline bool MathVec3D<T>::operator == ( const MathVec3D<T> &vec ) const {
	return( (m_vec[0] == vec.m_vec[0]) && (m_vec[1] == vec.m_vec[1]) && (m_vec[2] == vec.m_vec[2]) );
}

template<class T> inline bool MathVec3D<T>::operator != ( const MathVec3D<T> &vec ) const {
	return( (m_vec[0] != vec.m_vec[0]) || (m_vec[1] != vec.m_vec[1]) || (m_vec[2] != vec.m_vec[2]) );
}


template<class T> inline MathVec3D<T>& MathVec3D<T>::operator += ( const MathVec3D<T> &vec ) {
	m_vec[0] += vec.m_vec[0];
	m_vec[1] += vec.m_vec[1];
	m_vec[2] += vec.m_vec[2];
	return( *this );
}

template<class T> inline MathVec3D<T>& MathVec3D<T>::operator += ( T offset ) {
	m_vec[0] += offset;
	m_vec[1] += offset;
	m_vec[2] += offset;
	return( *this );
}

template<class T> inline MathVec3D<T> MathVec3D<T>::operator + ( const MathVec3D<T> &vec ) const {
    return MathVec3D<T>(x()+vec.x(), y()+vec.y(), z()+vec.z());
}

template<class T> inline MathVec3D<T> MathVec3D<T>::operator + ( double scale ) const {
    return MathVec3D<T>((T)(x()+scale), (T)(y()+scale), (T)(z()+scale));
}

template<class T> inline MathVec3D<T> MathVec3D<T>::operator + ( float scale ) const {
    return MathVec3D<T>((T)(x()+scale), (T)(y()+scale), (T)(z()+scale));
}

template<class T> inline MathVec3D<T>& MathVec3D<T>::operator -= ( const MathVec3D<T> &vec ) {
	m_vec[0] -= vec.m_vec[0];
	m_vec[1] -= vec.m_vec[1];
	m_vec[2] -= vec.m_vec[2];
	return( *this );
}

template<class T> inline MathVec3D<T>& MathVec3D<T>::operator -= ( T offset ) {
	m_vec[0] -= offset;
	m_vec[1] -= offset;
	m_vec[2] -= offset;
	return( *this );
}

template<class T> inline MathVec3D<T> MathVec3D<T>::operator - ( const MathVec3D<T> &vec ) const {
    return MathVec3D<T>(x()-vec.x(), y()-vec.y(), z()-vec.z());
}

template<class T> inline MathVec3D<T> MathVec3D<T>::operator - ( double scale ) const {
    return MathVec3D<T>((T)(x()-scale), (T)(y()-scale), (T)(z()-scale));
}

template<class T> inline MathVec3D<T> MathVec3D<T>::operator - ( float scale ) const {
    return MathVec3D<T>((T)(x()-scale), (T)(y()-scale), (T)(z()-scale));
}

template<class T> inline MathVec3D<T>& MathVec3D<T>::operator *= ( const MathVec3D<T> &vec ) {
	m_vec[0] *= vec.m_vec[0];
	m_vec[1] *= vec.m_vec[1];
	m_vec[2] *= vec.m_vec[2];
	return( *this );
}

template<class T> inline MathVec3D<T>& MathVec3D<T>::operator *= ( T scale ) {
	m_vec[0] *= scale;
	m_vec[1] *= scale;
	m_vec[2] *= scale;
	return( *this );
}

template<class T> inline MathVec3D<T> MathVec3D<T>::operator * ( const MathVec3D<T> &vec ) const {
    return MathVec3D<T>(x()*vec.x(), y()*vec.y(), z()*vec.z());
}

template<class T> inline MathVec3D<T> MathVec3D<T>::operator * ( double scale ) const {
    return MathVec3D<T>((T)(x()*scale), (T)(y()*scale), (T)(z()*scale));
}

template<class T> inline MathVec3D<T> MathVec3D<T>::operator * ( float scale ) const {
    return MathVec3D<T>((T)(x()*scale), (T)(y()*scale), (T)(z()*scale));
}

template<class T> inline MathVec3D<T>& MathVec3D<T>::operator /= ( const MathVec3D<T> &vec ) {
	m_vec[0] /= vec.m_vec[0];
	m_vec[1] /= vec.m_vec[1];
	m_vec[2] /= vec.m_vec[2];
	return( *this );
}

template<class T> inline MathVec3D<T>& MathVec3D<T>::operator /= ( T scale ) {
	m_vec[0] /= scale;
	m_vec[1] /= scale;
	m_vec[2] /= scale;
	return( *this );
}

template<class T> inline MathVec3D<T> MathVec3D<T>::operator / ( const MathVec3D<T> &vec ) const {
    return MathVec3D<T>(x()/vec.x(), y()/vec.y(), z()/vec.z());
}

template<class T> inline MathVec3D<T> MathVec3D<T>::operator / ( double scale ) const {
    return MathVec3D<T>((T)(x()/scale), (T)(y()/scale), (T)(z()/scale));
}

template<class T> inline MathVec3D<T> MathVec3D<T>::operator / ( float scale ) const {
    return MathVec3D<T>((T)(x()/scale), (T)(y()/scale), (T)(z()/scale));
}

template<class T> inline MathVec3D<T>& MathVec3D<T>::operator ^= ( const MathVec3D<T> &vec ) {
	T temp[3] = {m_vec[0], m_vec[1], m_vec[2]};

	temp[0] = m_vec[1]*vec.m_vec[2]-m_vec[2]*vec.m_vec[1];
	temp[1] = m_vec[2]*vec.m_vec[0]-m_vec[0]*vec.m_vec[2];
	temp[2] = m_vec[0]*vec.m_vec[1]-m_vec[1]*vec.m_vec[0];

	m_vec[0] = temp[0];
	m_vec[1] = temp[1];
	m_vec[2] = temp[2];

	return( *this );
}

template<class T> inline MathVec3D<T> MathVec3D<T>::operator ^ ( const MathVec3D<T> &vec ) {
    MathVec3D<T> ret(*this);
    return ret ^= vec;
}

template<class T> inline T MathVec3D<T>::dotProduct( const MathVec3D<T> &vec ) const {
	return( m_vec[0]*vec.m_vec[0] + m_vec[1]*vec.m_vec[1] + m_vec[2]*vec.m_vec[2] );
}

template<class T> inline T& MathVec3D<T>::operator [] ( int index ) {
    switch (index) {
        case 0:
        case 1:
        case 2:
	    	return m_vec[index];
        default:
    	    ERR_WARN_POS("Error: called MathVec3D::operator [] with out-of-bounds argument " << index);
	        return m_vec[0];
    };
}

template<class T> inline const T& MathVec3D<T>::operator [] ( int index ) const {
    switch (index) {
        case 0:
	    	return m_vec[0];
        case 1:
            return m_vec[1];
        case 2:
            return m_vec[2];
        default:
    	    ERR_WARN_POS("Error: called MathVec3D::operator [] with out-of-bounds argument " << index);
	        return m_vec[0];
    };
}

template<class T> inline void MathVec3D<T>::zero() {
	m_vec[0] = 0;
	m_vec[1] = 0;
	m_vec[2] = 0;
}

template<class T> inline T MathVec3D<T>::sumOfElements() const {
    return x()+y()+z();
}



template<class T> inline T MathVec3D<T>::magnitude() const {
	return( sqrt(m_vec[0]*m_vec[0] + m_vec[1]*m_vec[1] + m_vec[2]*m_vec[2]) );
}

template<class T> inline T MathVec3D<T>::sqrMagnitude() const {
	return( m_vec[0]*m_vec[0] + m_vec[1]*m_vec[1] + m_vec[2]*m_vec[2] );
}

template<class T> inline T MathVec3D<T>::distance( const MathVec3D<T> &vec ) const {
	return( sqrt(
		(m_vec[0]-vec.m_vec[0])*(m_vec[0]-vec.m_vec[0]) + (m_vec[1]-vec.m_vec[1])*(m_vec[1]-vec.m_vec[1]) + 
		(m_vec[2]-vec.m_vec[2])*(m_vec[2]-vec.m_vec[2])
	));
}

template<class T> inline T MathVec3D<T>::sqrDist( const MathVec3D<T> &vec ) const {
	return( 
		(m_vec[0]-vec.m_vec[0])*(m_vec[0]-vec.m_vec[0]) + (m_vec[1]-vec.m_vec[1])*(m_vec[1]-vec.m_vec[1]) +
		(m_vec[2]-vec.m_vec[2])*(m_vec[2]-vec.m_vec[2])
	);
}

template<class T> inline void MathVec3D<T>::normalize() {
	T vecLength = magnitude();
	if( vecLength != 0 ) {
		m_vec[0] /= vecLength;
		m_vec[1] /= vecLength;
		m_vec[2] /= vecLength;
	} else {
		ERR_WARN("Warning: called MathVec3D::normalize on the zero vector");
	}
}



template<class T> inline void MathVec3D<T>::makeOrthogonalTo( const MathVec3D<T> &vec ) {
	T length = vec.magnitude();

	if( length == 0 ) {
		ERR_WARN("Warning: called MathVec3D::makeOrthogonalTo with zero vector as the argument.  Doing nothing.");
	} else {
		T scale = (m_vec[0]*vec.m_vec[0] + m_vec[1]*vec.m_vec[1] + m_vec[2]*vec.m_vec[2]) / (length * length);
		m_vec[0] -= scale * vec.m_vec[0];
		m_vec[1] -= scale * vec.m_vec[1];
		m_vec[2] -= scale * vec.m_vec[2];
	}
}

template<class T> inline void MathVec3D<T>::projectOnto( const MathVec3D<T> &vec ) {
	T length = vec.magnitude();
	if( length == 0 ) {
		ERR_WARN("Warning: called MathVec3D::projectOnto with zero vector as the argument.  Doing nothing.");
	} else {
		T scale = (m_vec[0]*vec.m_vec[0] + m_vec[1]*vec.m_vec[1] + m_vec[2]*vec.m_vec[2]) / (length * length);
		m_vec[0] = scale * vec.m_vec[0];
		m_vec[1] = scale * vec.m_vec[1];
		m_vec[2] = scale * vec.m_vec[2];
	}
}

template<class T> inline T* MathVec3D<T>::asArray() {
	return( m_vec );
}

template<class T> inline const T* MathVec3D<T>::asArray() const {
	return( m_vec );
}

template<class T> inline T MathVec3D<T>::x() const {
	return( m_vec[0] );
}

template<class T> inline T MathVec3D<T>::y() const {
	return( m_vec[1] );
}

template<class T> inline T MathVec3D<T>::z() const {
	return( m_vec[2] );
}

template<class T> inline void MathVec3D<T>::x( T val ) {
	m_vec[0] = val;
}

template<class T> inline void MathVec3D<T>::y( T val ) {
	m_vec[1] = val;
}

template<class T> inline void MathVec3D<T>::z( T val ) {
	m_vec[2] = val;
}

template<class T> inline void MathVec3D<T>::set( T x, T y, T z ) {
	m_vec[0] = x;
	m_vec[1] = y;
	m_vec[2] = z;
}

template<class T> inline std::string MathVec3D<T>::toString() const {
	std::ostringstream stringStream;
	stringStream << "(" << m_vec[0] << "," << m_vec[1] << "," << m_vec[2] << ")";
	return( stringStream.str() );
}

/////////////////////////////////added by mksung//////////////////////////////////////

template<class T> inline void MathVec3D<T>::writeToFile(FILE *fp)
{
	fprintf(fp,"%5.3f %5.3f %5.3f ",m_vec[0],m_vec[1],m_vec[2]);
}

template<class T> inline void MathVec3D<T>::loadFromFile(FILE *fp)
{
   float x,y,z;
   fscanf(fp,"%f %f %f ",&x,&y,&z);
   
   set((T )x,(T )y,(T )z);
}