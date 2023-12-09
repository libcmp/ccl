// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_OUTPUT_RESOURCE_HPP_INCLUDED
#define CMP_IO_OUTPUT_RESOURCE_HPP_INCLUDED

#include <cstddef>

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/transfer_resource.hpp>

namespace cmp {

/**
    Description:
        An output resource is a destination for output.
        It's an object you can write data to.
*/
class CMP_LIBRARY_NAME output_resource
    : public virtual transfer_resource
{
public:
    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs an output resource with the given buffer capacity.

        Parameters:
            buffer_capacity:
                The capacity of the I/O buffer. If this is zero,
                the output resource is completely unbuffered.
    */
    CMP_CONDITIONAL_INLINE
    explicit
    output_resource (
        std::size_t buffer_capacity = io_buffer::default_buffer_capacity
    );

    CMP_CONDITIONAL_INLINE
    ~output_resource ()
    override = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs an <#type>output_resource</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>output_resource</#type>
                to copy from.
    */
    CMP_CONDITIONAL_INLINE
    output_resource (
        const output_resource& other
    )
    = default;

    /**
        Description:
            Copy-assigns an <#type>output_resource</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>output_resource</#type>
                to copy from.
    */
    CMP_CONDITIONAL_INLINE
    output_resource&
    operator = (
        const output_resource& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs an <#type>output_resource</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>output_resource</#type>
                to move from.
    */
    CMP_CONDITIONAL_INLINE
    output_resource (
        output_resource&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns an <#type>output_resource</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>output_resource</#type>
                to move from.
    */
    CMP_CONDITIONAL_INLINE
    output_resource&
    operator = (
        output_resource&& other
    )
    noexcept = default;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Writes <#parameter>byte_count</#parameter> bytes
            from the <#parameter>data</#parameter> array to
            <#this/> output resource.

        Parameters:
            data:
                The array of bytes that will be
                written to <#this/> output resource.
            byte_count:
                The number of bytes to write to <#this/> output resource.
    */
    CMP_CONDITIONAL_INLINE
    virtual
    std::size_t
    write (
        const std::byte* data,
        std::size_t byte_count
    );

    /**
        Description:
            Flushes <#this/> output resource, ensuring that any data that
            has previously been requested to be written out actually
            gets written out.
    */
    CMP_CONDITIONAL_INLINE
    void
    flush ();

protected:
    // Protected Functions ----------------------------------------------------

    /**
        Description:
            Writes <#parameter>byte_count</#parameter> bytes
            from the <#parameter>data</#parameter> array to
            <#this/> output resource.

        Parameters:
            data:
                The array of bytes that will be
                written to <#this/> output resource.
            byte_count:
                The number of bytes to write to <#this/> output resource.
    */
    CMP_CONDITIONAL_INLINE
    virtual
    std::size_t
    write_raw (
        const std::byte* data,
        std::size_t byte_count
    )
    = 0;

private:
    // Private Functions ------------------------------------------------------

    CMP_CONDITIONAL_INLINE
    std::size_t
    write_buffered (
        const std::byte* data,
        std::size_t byte_count
    );
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#if CMP_CONFIG_HEADER_ONLY == true
#   include <cmp/io/output_resource.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#endif // CMP_IO_OUTPUT_RESOURCE_HPP_INCLUDED
