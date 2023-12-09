// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_OUTPUT_STREAM_HPP_INCLUDED
#define CMP_IO_OUTPUT_STREAM_HPP_INCLUDED

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/general.hpp>
#include <cmp/io/output_resource.hpp>

namespace cmp {

/**
    Description:
        An output stream is an object that writes data to an output resource.

        There are two kinds of output streams in CCL: data output streams,
        which write binary data to its output resource, and text output
        streams, which write text to its output resource.

        The <#type>output_stream</#type> class template serves as the
        foundation for both data output streams and text output streams.
*/
template <
    typename OutputResource
>
class output_stream {
public:
    // Types ------------------------------------------------------------------

    /**
        Description:
            The type of the referenced output resource.
    */
    using referenced_resource_type = OutputResource;

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
        referenced_resource_type& resource,
        std::endian endianness = std::endian::native
    )
    noexcept;

    virtual
    ~output_stream ();

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs an <#type>output_stream</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>output_stream</#type>
                to copy from.
    */
    output_stream (
        const output_stream& other
    )
    = default;

    /**
        Description:
            Copy-assigns an <#type>output_stream</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>output_stream</#type>
                to copy from.
    */
    output_stream&
    operator = (
        const output_stream& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs an <#type>output_stream</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>output_stream</#type>
                to move from.
    */
    output_stream (
        output_stream&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns an <#type>output_stream</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>output_stream</#type>
                to move from.
    */
    output_stream&
    operator = (
        output_stream&& other
    )
    noexcept = default;

    // Accessors --------------------------------------------------------------

    /**
        Description:
            Returns a non-constant reference to the referenced output resource.
    */
    referenced_resource_type&
    grab_resource ()
    noexcept;

    /**
        Description:
            Returns a constant reference to the referenced output resource.
    */
    const referenced_resource_type&
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
            Returns a pointer to the referenced output resource,
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

// Free Functions -------------------------------------------------------------

/**
    Description:
        Flushes the output stream.

    Parameters:
        stream:
            The output stream to flush.
        flush_v:
            This parameter is only used to indicate that a
            flush is desired, its value is not actually read.
*/
template <
    typename OutputResource
>
output_stream<OutputResource>&
operator << (
    output_stream<OutputResource>& stream,
    flush_t flush_v
);

} // namespace ----------------------------------------------------------------

#include <cmp/io/output_stream.ipp>

#endif // CMP_IO_OUTPUT_STREAM_HPP_INCLUDED
