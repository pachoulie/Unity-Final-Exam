#pragma once

#include <iostream>

// Define the macro for DLL exports
#ifndef SWIG
#	ifdef WIN32
#		ifdef UTILITIES_EXPORTS
#			define UTIL_API __declspec(dllexport)
#			define UTIL_API_STL
#		else
#			define UTIL_API __declspec(dllimport)
#			define UTIL_API_STL extern
#			ifdef  _DEBUG
#				pragma comment(lib, "Utilities_dd.lib")
#			else
#				pragma comment(lib, "Utilities_r.lib")
#			endif
#		endif
#	else
#		ifdef _MSC_VER	// -hupp
#			error	"You don't have WIN32 defined, but you're using Visual Studio.  Things will probably break."
#		else
#			define UTIL_API
#			define UTIL_API_STL
#		endif
#	endif
#else // SWIG
#	define UTIL_API
#	define UTIL_API_STL
#endif

#define UTIL_STL_EXPORT(arg) UTIL_API_STL template class UTIL_API arg;
