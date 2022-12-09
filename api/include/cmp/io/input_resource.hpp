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
    explicit
    input_resource (
        std::size_t buffer_capacity = io_buffer::default_buffer_capacity
    );

    virtual
    ~input_resource ()
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
    std::size_t
    fill ();

private:
    // Private Data -----------------------------------------------------------

    output_resource* m_tied_resource;

    // Private Functions ------------------------------------------------------

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
