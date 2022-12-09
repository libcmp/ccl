// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_UNICODE_EXCEPTIONS_HPP_INCLUDED
#define CMP_UNICODE_EXCEPTIONS_HPP_INCLUDED

#include <exception>

#include <cmp/core/config.hpp>

namespace cmp {

/**
    Description:
        This exception type indicates that a code point is
        not a valid Unicode code point. This check is done
        with the <#function>is_code_point_valid</#function>
        function.
*/
class CMP_LIBRARY_NAME invalid_code_point
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

/**
    Description:
        This exception type indicates that the data read from a stream or
        string is not valid UTF-8 or UTF-16. UTF-32 is not affected because
        it is not a variable length encoding.
*/
class CMP_LIBRARY_NAME invalid_unicode_encoding
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

class CMP_LIBRARY_NAME iterated_past_end
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
#   include <cmp/unicode/exceptions.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#endif // CMP_UNICODE_EXCEPTIONS_HPP_INCLUDED
