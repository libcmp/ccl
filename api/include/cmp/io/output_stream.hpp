// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_OUTPUT_STREAM_HPP_INCLUDED
#define CMP_IO_OUTPUT_STREAM_HPP_INCLUDED

#include <bit>

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/general.hpp>
#include <cmp/io/output_resource.hpp>

namespace cmp {

template <
    typename OutputResource
>
class output_stream {
public:
    // Types ------------------------------------------------------------------

    /**
        Description:
            The type of the wrapped output resource.
    */
    using wrapped_resource_type = OutputResource;

    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs an output stream with the
            given output resource and endianness.

        Parameters:
            resource:
                The output resource this stream will write to.
            endianness:
                The endianness to write the data in.
    */
    explicit
    output_stream (
        wrapped_resource_type& resource,
        std::endian endianness = std::endian::native
    )
    noexcept;

    virtual
    ~output_stream ();

    // Accessors --------------------------------------------------------------

    /**
        Description:
            Returns a non-constant reference to the wrapped output resource.
    */
    wrapped_resource_type&
    grab_resource ()
    noexcept;

    /**
        Description:
            Returns a constant reference to the wrapped output resource.
    */
    const wrapped_resource_type&
    grab_resource ()
    const noexcept;

    /**
        Description:
            Returns the endianness associated with <#this/> output stream.
    */
    std::endian
    get_endianness ()
    const noexcept;

    /**
        Description:
            Sets the endianness associated with <#this/> output stream.

        Parameters:
            new_endianness:
                The new endianness to use with <#this/> output stream.
    */
    void
    set_endianness (
        std::endian new_endianness
    )
    noexcept;

    /**
        Description:
            Tells whether this stream's output resource is at its end.
    */
    bool
    is_at_end ()
    const noexcept;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Writes <#parameter>byte_count</#parameter>
            bytes from the <#parameter>data</#parameter>
            array to <#this/> stream's output resource.

        Parameters:
            data:
                The array of bytes that will be written
                to <#this/> stream's output resource.
            byte_count:
                The number of bytes to write to
                <#this/> stream's output resource.
    */
    std::size_t
    write (
        const std::byte* data,
        std::size_t byte_count
    );

    /**
        Description:
            Reverses the order of the bytes in the
            <#parameter>data</#parameter> array and
            then writes them to this stream's output
            resource.

        Parameters:
            data:
                The bytes that will be reversed and
                written to this stream's output resource.
            byte_count:
                The number of bytes to reverse and
                write to this stream's output resource.
    */
    std::size_t
    reverse_write (
        std::byte* data,
        std::size_t byte_count
    );

    /**
        Description:
            Flushes the stream's output resource, ensuring that any data
            that has previously been requested to be written out actually
            gets written out.
    */
    void
    flush ();

    // Operator Overloads -----------------------------------------------------

    /**
        Description:
            Returns a pointer to the wrapped output resource,
            enabling use of the arrow operator.
    */
    wrapped_resource_type*
    operator -> ()
    const noexcept;

private:
    // Private Data -----------------------------------------------------------

    wrapped_resource_type& m_resource;
    std::endian m_endianness;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#include <cmp/io/output_stream.ipp>

#endif // CMP_IO_OUTPUT_STREAM_HPP_INCLUDED
