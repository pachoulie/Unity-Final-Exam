// File: Utility.h
// Author: Lucas Kovar

#pragma once

class Utility;

#include "Utilities.h"

/**
 * \brief mathematic functions.
 *
 * This class contains low-level general-purpose functions that don't
 * obviously belong to any other class
*/
class UTIL_API Utility {
	public:
		
		/**
		  Given the full path name of a file, this returns a string representing
		  the local filename.  For example, if the input is "C:\users\kovar\foo.txt",
		  then this would return "foo.txt".
		*/
		static std::string findFilename( std::string &fullFilePath );

};