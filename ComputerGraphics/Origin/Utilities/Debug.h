#pragma once

#include "Utilities.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

/**
 * \brief Series of macros and an exception to aid in debugging.  
 *
 * Macros for debugging and error messages.
 *
 * Usage:
 * // Warns in the debugOut stream
 * ERR_WARN("Warning: bad value for foo:" << foo);
 *
 * // Throws exception
 * ERR_THROW("Warning: bad value for foo:" << foo);
 *
 * // Warns in the debugOut stream and reports file and line information
 * ERR_WARN_POS("Warning: bad value for foo:" << foo);
 *
 * // Throws exception with file and line information
 * ERR_THROW_POS("Warning: bad value for foo:" << foo);
 */

//BU_STL_EXPORT(std::runtime_error);
#pragma warning(push)
#pragma warning(disable:4231)
//UTIL_STL_EXPORT(std::allocator<char>);
//UTIL_STL_EXPORT(std::basic_string<char>);
#pragma warning(pop)

/**
 * Basic Exception class.  Really just an STL exception 
 */
class UTIL_API BasicException {
public:
    BasicException(const std::string& msg) : m_err(msg) {
        // Put a breakpoint here to see where the exception originated from
    }
    virtual ~BasicException() {}
    virtual const char *what() const {
        return m_err.c_str(); }

    static std::ostringstream* streamToStringConverter;
    static std::ostream* debugOut;
private:
	// Exporting a template type will generate a compiler warning, even though the 
	// code itself is fine.  Turn this warning off for these member declarations.
	#pragma warning( disable: 4251 )
        std::string m_err;
	#pragma warning( default: 4251 )
};

/*
    The STREAM_TO_STRING macro converts a set of stream operations into a string,
    e.g STREAM_TO_STRING("Hello" << ", " << str
    */
#define ERR_STREAM_TO_STRING(arg) static_cast<std::ostringstream&>(	BasicException::streamToStringConverter->str(""), \
																	(*BasicException::streamToStringConverter) << arg).str()

#define ERR_THROW(arg)	    throw BasicException(ERR_STREAM_TO_STRING(arg))
#define ERR_THROW_POS(arg)	throw BasicException(ERR_STREAM_TO_STRING(__FILE__ << "(" << __LINE__ << "): " << arg))
#define ERR_PRINT(arg)	    (*BasicException::debugOut) << arg << std::endl
#ifdef NO_WARN
    #define ERR_WARN(arg)
#else
    #define ERR_WARN(arg)   (*BasicException::debugOut) << arg << std::endl
#endif

#ifdef NO_WARN
    #define ERR_WARN(arg)
#else
    #define ERR_WARN_POS(arg)   (*BasicException::debugOut) << __FILE__ << "(" << __LINE__ << "): " << arg << std::endl
#endif
// A common warning
#define ERR_NOTIMPL(str) ERR_WARN_POS((str) << "not implemented.")
#define ERR_NOTIMPLTHROW(str) ERR_WARN_POS((str) << "not implemented."); ERR_THROW_POS((str) << "not implemented.")
