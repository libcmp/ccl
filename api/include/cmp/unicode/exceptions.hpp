// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_UNICODE_EXCEPTIONS_HPP_INCLUDED
#define CMP_UNICODE_EXCEPTIONS_HPP_INCLUDED

#include <exception>

#include <cmp/unicode/inclusion_assert.hpp>

namespace cmp {

/**
    Description:
        This exception type indicates that a code
        point is not a valid Unicode code point.
*/
class CMP_LIBRARY_NAME invalid_code_point
    : public std::exception
{
public:
    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs an <#type>invalid_code_point</#type>.
    */
    invalid_code_point ()
    noexcept = default;

    ~invalid_code_point ()
    override = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs an <#type>invalid_code_point</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>invalid_code_point</#type>
                to copy from.
    */
    CMP_CONDITIONAL_INLINE
    invalid_code_point (
        const invalid_code_point& other
    )
    = default;

    /**
        Description:
            Copy-assigns an <#type>invalid_code_point</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>invalid_code_point</#type>
                to copy from.
    */
    CMP_CONDITIONAL_INLINE
    invalid_code_point&
    operator = (
        const invalid_code_point& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs an <#type>invalid_code_point</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>invalid_code_point</#type>
                to move from.
    */
    CMP_CONDITIONAL_INLINE
    invalid_code_point (
        invalid_code_point&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns an <#type>invalid_code_point</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>invalid_code_point</#type>
                to move from.
    */
    CMP_CONDITIONAL_INLINE
    invalid_code_point&
    operator = (
        invalid_code_point&& other
    )
    noexcept = default;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Returns the explanatory string.
    */
    CMP_CONDITIONAL_INLINE
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
    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs an <#type>invalid_unicode_encoding</#type>.
    */
    invalid_unicode_encoding ()
    noexcept = default;

    ~invalid_unicode_encoding ()
    override = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs an <#type>invalid_unicode_encoding</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>invalid_unicode_encoding</#type>
                to copy from.
    */
    CMP_CONDITIONAL_INLINE
    invalid_unicode_encoding (
        const invalid_unicode_encoding& other
    )
    = default;

    /**
        Description:
            Copy-assigns an <#type>invalid_unicode_encoding</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>invalid_unicode_encoding</#type>
                to copy from.
    */
    CMP_CONDITIONAL_INLINE
    invalid_unicode_encoding&
    operator = (
        const invalid_unicode_encoding& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs an <#type>invalid_unicode_encoding</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>invalid_unicode_encoding</#type>
                to move from.
    */
    CMP_CONDITIONAL_INLINE
    invalid_unicode_encoding (
        invalid_unicode_encoding&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns an <#type>invalid_unicode_encoding</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>invalid_unicode_encoding</#type>
                to move from.
    */
    CMP_CONDITIONAL_INLINE
    invalid_unicode_encoding&
    operator = (
        invalid_unicode_encoding&& other
    )
    noexcept = default;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Returns the explanatory string.
    */
    CMP_CONDITIONAL_INLINE
    const char*
    what ()
    const noexcept override;
}; // class -------------------------------------------------------------------

/**
    Description:
        This exception type indicates that you tried to iterate past the end
        of a string. This can occur if the string you are iterating over is
        malformed and ends with a code unit that indicates that there is more
        to read when really there isn't.
*/
class CMP_LIBRARY_NAME iterated_past_end
    : public std::exception
{
public:
    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs an <#type>iterated_past_end</#type>.
    */
    iterated_past_end ()
    noexcept = default;

    ~iterated_past_end ()
    override = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs an <#type>iterated_past_end</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>iterated_past_end</#type>
                to copy from.
    */
    CMP_CONDITIONAL_INLINE
    iterated_past_end (
        const iterated_past_end& other
    )
    = default;

    /**
        Description:
            Copy-assigns an <#type>iterated_past_end</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>iterated_past_end</#type>
                to copy from.
    */
    CMP_CONDITIONAL_INLINE
    iterated_past_end&
    operator = (
        const iterated_past_end& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs an <#type>iterated_past_end</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>iterated_past_end</#type>
                to move from.
    */
    CMP_CONDITIONAL_INLINE
    iterated_past_end (
        iterated_past_end&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns an <#type>iterated_past_end</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>iterated_past_end</#type>
                to move from.
    */
    CMP_CONDITIONAL_INLINE
    iterated_past_end&
    operator = (
        iterated_past_end&& other
    )
    noexcept = default;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Returns the explanatory string.
    */
    CMP_CONDITIONAL_INLINE
    const char*
    what ()
    const noexcept override;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#if CMP_CONFIG_HEADER_ONLY == true
#   include <cmp/unicode/exceptions.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#endif // CMP_UNICODE_EXCEPTIONS_HPP_INCLUDED
