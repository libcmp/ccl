// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_INPUT_STREAM_HPP_INCLUDED
#define CMP_IO_INPUT_STREAM_HPP_INCLUDED

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/exceptions.hpp>
#include <cmp/io/general.hpp>
#include <cmp/io/input_resource.hpp>

namespace cmp {

/**
    Description:
        An input stream is an object that reads data from an input resource.

        There are two kinds of input streams in CCL: data input streams,
        which read binary data from its input resource, and text input
        streams, which read text from its input resource.

        The <#type>input_stream</#type> class template serves as the
        foundation for both data input streams and text input streams.
*/
template <
    typename InputResource
>
class input_stream {
public:
    // Types ------------------------------------------------------------------

    /**
        Description:
            The type of the referenced input resource.
    */
    using referenced_resource_type = InputResource;

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
        referenced_resource_type& resource,
        std::endian endianness = std::endian::native
    )
    noexcept;

    virtual
    ~input_stream ()
    = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs an <#type>input_stream</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>input_stream</#type>
                to copy from.
    */
    input_stream (
        const input_stream& other
    )
    = default;

    /**
        Description:
            Copy-assigns an <#type>input_stream</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>input_stream</#type>
                to copy from.
    */
    input_stream&
    operator = (
        const input_stream& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs an <#type>input_stream</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>input_stream</#type>
                to move from.
    */
    input_stream (
        input_stream&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns an <#type>input_stream</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>input_stream</#type>
                to move from.
    */
    input_stream&
    operator = (
        input_stream&& other
    )
    noexcept = default;

    // Accessors --------------------------------------------------------------

    /**
        Description:
            Returns a non-constant reference to the referenced input resource.
    */
    referenced_resource_type&
    grab_resource ()
    noexcept;

    /**
        Description:
            Returns a constant reference to the referenced input resource.
    */
    const referenced_resource_type&
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
            Returns a pointer to the referenced input resource,
            enabling use of the arrow operator.
    */
    referenced_resource_type*
    operator -> ()
    const noexcept;

private:
    // Private Data -----------------------------------------------------------

    referenced_resource_type& m_resource;
    std::endian m_endianness;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#include <cmp/io/input_stream.ipp>

#endif // CMP_IO_INPUT_STREAM_HPP_INCLUDED
