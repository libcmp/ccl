// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_INPUT_STREAM_HPP_INCLUDED
#define CMP_IO_INPUT_STREAM_HPP_INCLUDED

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/general.hpp>
#include <cmp/io/input_resource.hpp>
#include <cmp/io/exceptions.hpp>

namespace cmp {

template <
    typename InputResource
>
class input_stream {
public:
    // Types ------------------------------------------------------------------

    /**
        Description:
            The type of the wrapped input resource.
    */
    using wrapped_resource_type = InputResource;

    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs an input stream with the
            given input resource and endianness.

        Parameters:
            resource:
                The input resource this stream will read from.
            endianness:
                The endianness the data is expected to be in.
    */
    explicit
    input_stream (
        wrapped_resource_type& resource,
        std::endian endianness = std::endian::native
    )
    noexcept;

    ~input_stream ()
    noexcept = default;

    // Accessors --------------------------------------------------------------

    /**
        Description:
            Returns a non-constant reference to the wrapped input resource.
    */
    wrapped_resource_type&
    grab_resource ()
    noexcept;

    /**
        Description:
            Returns a constant reference to the wrapped input resource.
    */
    const wrapped_resource_type&
    grab_resource ()
    const noexcept;

    /**
        Description:
            Returns the endianness associated with <#this/> input stream.
    */
    std::endian
    get_endianness ()
    const noexcept;

    /**
        Description:
            Sets the endianness associated with <#this/> input stream.

        Parameters:
            new_endianness:
                The new endianness to use with <#this/> input stream.
    */
    void
    set_endianness (
        std::endian new_endianness
    )
    noexcept;

    /**
        Description:
            Tells whether this stream's input resource is at its end.
    */
    bool
    is_at_end ()
    const noexcept;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Reads <#parameter>byte_count</#parameter> bytes from
            <#this/> stream's input resource and places them in
            the provided <#parameter>data</#parameter> array.

        Parameters:
            data:
                The array into which the read bytes will be placed.
            byte_count:
                The number of bytes to read from
                <#this/> stream's input resource.
    */
    std::size_t
    read (
        std::byte* data,
        std::size_t byte_count
    );

    // Operator Overloads -----------------------------------------------------

    /**
        Description:
            Returns a pointer to the wrapped input resource,
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

#include <cmp/io/input_stream.ipp>

#endif // CMP_IO_INPUT_STREAM_HPP_INCLUDED
