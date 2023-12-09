// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_IO_RESOURCE_HPP_INCLUDED
#define CMP_IO_IO_RESOURCE_HPP_INCLUDED

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/input_resource.hpp>
#include <cmp/io/output_resource.hpp>

namespace cmp {

/**
    Description:
        An I/O resource is both a source of
        input and a destination for output.
        It's an object you can read data
        from and write data to.
*/
class CMP_LIBRARY_NAME io_resource
    : public input_resource
    , public output_resource
{
public:
    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs an I/O resource with the given buffer capacity.

        Parameters:
            buffer_capacity:
                The capacity of the I/O buffer. If this is zero,
                the I/O resource is completely unbuffered.
    */
    CMP_CONDITIONAL_INLINE
    explicit
    io_resource (
        std::size_t buffer_capacity
    );

    CMP_CONDITIONAL_INLINE
    ~io_resource ()
    override = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs an <#type>io_resource</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>io_resource</#type>
                to copy from.
    */
    CMP_CONDITIONAL_INLINE
    io_resource (
        const io_resource& other
    )
    = default;

    /**
        Description:
            Copy-assigns an <#type>io_resource</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>io_resource</#type>
                to copy from.
    */
    CMP_CONDITIONAL_INLINE
    io_resource&
    operator = (
        const io_resource& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs an <#type>io_resource</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>io_resource</#type>
                to move from.
    */
    CMP_CONDITIONAL_INLINE
    io_resource (
        io_resource&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns an <#type>io_resource</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>io_resource</#type>
                to move from.
    */
    CMP_CONDITIONAL_INLINE
    io_resource&
    operator = (
        io_resource&& other
    )
    noexcept = default;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#if CMP_CONFIG_HEADER_ONLY == true
#   include <cmp/io/io_resource.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#endif // CMP_IO_IO_RESOURCE_HPP_INCLUDED
