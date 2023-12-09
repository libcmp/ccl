// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_INPUT_RESOURCE_HPP_INCLUDED
#define CMP_IO_INPUT_RESOURCE_HPP_INCLUDED

#include <cstddef>

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/general.hpp>
#include <cmp/io/output_resource.hpp>

namespace cmp {

/**
    Description:
        An input resource is a source of input.
        It's an object you can read data from.
*/
class CMP_LIBRARY_NAME input_resource
    : public virtual transfer_resource
{
public:
    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs an input resource with the given buffer capacity.

        Parameters:
            buffer_capacity:
                The capacity of the I/O buffer. If this is zero,
                the input resource is completely unbuffered.
    */
    CMP_CONDITIONAL_INLINE
    explicit
    input_resource (
        std::size_t buffer_capacity = io_buffer::default_buffer_capacity
    );

    CMP_CONDITIONAL_INLINE
    ~input_resource ()
    override = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs an <#type>input_resource</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>input_resource</#type>
                to copy from.
    */
    CMP_CONDITIONAL_INLINE
    input_resource (
        const input_resource& other
    )
    = default;

    /**
        Description:
            Copy-assigns an <#type>input_resource</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>input_resource</#type>
                to copy from.
    */
    CMP_CONDITIONAL_INLINE
    input_resource&
    operator = (
        const input_resource& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs an <#type>input_resource</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>input_resource</#type>
                to move from.
    */
    CMP_CONDITIONAL_INLINE
    input_resource (
        input_resource&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns an <#type>input_resource</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>input_resource</#type>
                to move from.
    */
    CMP_CONDITIONAL_INLINE
    input_resource&
    operator = (
        input_resource&& other
    )
    noexcept = default;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Reads <#parameter>byte_count</#parameter> bytes
            from <#this/> input resource and places them in the
            provided <#parameter>data</#parameter> array.

        Parameters:
            data:
                The array into which the read bytes will be placed.
            byte_count:
                The number of bytes to read from <#this/> input resource.
    */
    CMP_CONDITIONAL_INLINE
    virtual
    std::size_t
    read (
        std::byte* data,
        std::size_t byte_count
    );

    /**
        Description:
            Ties the given output resource to <#this/> input resource.
            The tied output resource is flushed when <#this/> input
            resource is read from.
    */
    CMP_CONDITIONAL_INLINE
    void
    tie (
        output_resource& resource
    )
    noexcept;

protected:
    // Protected Functions ----------------------------------------------------

    /**
        Description:
            Reads <#parameter>byte_count</#parameter> bytes
            from <#this/> input resource and places them in
            the provided <#parameter>data</#parameter> array.

        Parameters:
            data:
                The array into which the read bytes will be placed.
            byte_count:
                The number of bytes to read from <#this/> input resource.
            rr:
                The kind of read request that is
                being issued to <#this/> input resource.
    */
    CMP_CONDITIONAL_INLINE
    virtual
    std::size_t
    read_raw (
        std::byte* data,
        std::size_t byte_count,
        read_request rr
    )
    = 0;

    /**
        Description:
            Fills the buffer and returns the number of bytes read.
    */
    CMP_CONDITIONAL_INLINE
    std::size_t
    fill ();

private:
    // Private Data -----------------------------------------------------------

    output_resource* m_tied_resource;

    // Private Functions ------------------------------------------------------

    CMP_CONDITIONAL_INLINE
    std::size_t
    read_buffered (
        std::byte* data,
        std::size_t byte_count
    );
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#if CMP_CONFIG_HEADER_ONLY == true
#   include <cmp/io/input_resource.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#endif // CMP_IO_INPUT_RESOURCE_HPP_INCLUDED
