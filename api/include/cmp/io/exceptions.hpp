// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_EXCEPTIONS_HPP_INCLUDED
#define CMP_IO_EXCEPTIONS_HPP_INCLUDED

#include <cmp/io/inclusion_assert.hpp>

namespace cmp {

/**
    Description:
        This exception is thrown by input streams when an attempt is
        made to read past the end of a stream. For example, if you
        read from a file through an input stream and read past the
        file's EOF (end of file) position, you'll get this exception.
*/
class CMP_LIBRARY_NAME read_past_end
    : public std::exception
{
public:
    // Core -------------------------------------------------------------------

    /**
        Description:
            Returns the explanatory string.
    */
    const char*
    what ()
    const noexcept override;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#if CMP_CONFIG_HEADER_ONLY == true
#   include <cmp/io/exceptions.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#endif // CMP_IO_EXCEPTIONS_HPP_INCLUDED
