// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_EXCEPTIONS_HPP_INCLUDED
#define CMP_IO_EXCEPTIONS_HPP_INCLUDED

#include <exception>

#include <cmp/io/inclusion_assert.hpp>

namespace cmp {

/**
    Description:
        An exception of this type is thrown by input streams when an
        attempt is made to read past the end of a stream. For example,
        if you read from a file through an input stream and read past
        the file's EOF (end of file) position.
*/
class CMP_LIBRARY_NAME read_past_end
    : public std::exception
{
public:
    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs a <#type>read_past_end</#type>.
    */
    CMP_CONDITIONAL_INLINE
    read_past_end ()
    noexcept = default;

    CMP_CONDITIONAL_INLINE
    ~read_past_end ()
    override = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs a <#type>read_past_end</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>read_past_end</#type>
                to copy from.
    */
    CMP_CONDITIONAL_INLINE
    read_past_end (
        const read_past_end& other
    )
    = default;

    /**
        Description:
            Copy-assigns a <#type>read_past_end</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>read_past_end</#type>
                to copy from.
    */
    CMP_CONDITIONAL_INLINE
    read_past_end&
    operator = (
        const read_past_end& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs a <#type>read_past_end</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>read_past_end</#type>
                to move from.
    */
    CMP_CONDITIONAL_INLINE
    read_past_end (
        read_past_end&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns a <#type>read_past_end</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>read_past_end</#type>
                to move from.
    */
    CMP_CONDITIONAL_INLINE
    read_past_end&
    operator = (
        read_past_end&& other
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
        This exception type indicates that an IO operation was attempted under
        the wrong access mode. For example, trying to write to a file that was
        opened as read-only.
*/
class CMP_LIBRARY_NAME invalid_access_mode
    : public std::exception
{
public:
    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs an <#type>invalid_access_mode</#type>.
    */
    CMP_CONDITIONAL_INLINE
    invalid_access_mode ()
    noexcept = default;

    CMP_CONDITIONAL_INLINE
    ~invalid_access_mode ()
    override = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs an <#type>invalid_access_mode</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>invalid_access_mode</#type>
                to copy from.
    */
    CMP_CONDITIONAL_INLINE
    invalid_access_mode (
        const invalid_access_mode& other
    )
    = default;

    /**
        Description:
            Copy-assigns an <#type>invalid_access_mode</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>invalid_access_mode</#type>
                to copy from.
    */
    CMP_CONDITIONAL_INLINE
    invalid_access_mode&
    operator = (
        const invalid_access_mode& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs an <#type>invalid_access_mode</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>invalid_access_mode</#type>
                to move from.
    */
    CMP_CONDITIONAL_INLINE
    invalid_access_mode (
        invalid_access_mode&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns an <#type>invalid_access_mode</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>invalid_access_mode</#type>
                to move from.
    */
    CMP_CONDITIONAL_INLINE
    invalid_access_mode&
    operator = (
        invalid_access_mode&& other
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
#   include <cmp/io/exceptions.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#endif // CMP_IO_EXCEPTIONS_HPP_INCLUDED
