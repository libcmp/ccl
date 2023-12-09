// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_DATA_OUTPUT_STREAM_HPP_INCLUDED
#define CMP_IO_DATA_OUTPUT_STREAM_HPP_INCLUDED

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/output_stream.hpp>

namespace cmp {

/**
    Description:
        A data output stream is an object that allows
        you to write binary data to an output resource.
*/
template <
    typename OutputResource
>
class data_output_stream
    : public output_stream<OutputResource>
{
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
            Constructs a data output stream from the given output resource
            and with the given endianness. The data output stream will hold
            a non-owning reference to the resource, which is expected to
            stay valid when using the data output stream.

        Parameters:
            resource:
                The output resource to write to.
            endianness:
                The endianness that the data is going to be in.
    */
    explicit
    data_output_stream (
        referenced_resource_type& resource,
        std::endian endianness = std::endian::big
    )
    noexcept;

    ~data_output_stream ()
    override = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs a <#type>data_output_stream</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>data_output_stream</#type>
                to copy from.
    */
    data_output_stream (
        const data_output_stream& other
    )
    = default;

    /**
        Description:
            Copy-assigns a <#type>data_output_stream</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>data_output_stream</#type>
                to copy from.
    */
    data_output_stream&
    operator = (
        const data_output_stream& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs a <#type>data_output_stream</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>data_output_stream</#type>
                to move from.
    */
    data_output_stream (
        data_output_stream&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns a <#type>data_output_stream</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>data_output_stream</#type>
                to move from.
    */
    data_output_stream&
    operator = (
        data_output_stream&& other
    )
    noexcept = default;
}; // class -------------------------------------------------------------------

// Free Functions -------------------------------------------------------------

/**
    Description:
        Writes an object of fundamental type with the data output stream.

    Parameters:
        stream:
            The data output stream to write with.
        source:
            The object to write.
*/
template <
    typename OutputResource,
    typename T
>
requires (std::is_fundamental_v<T>)
data_output_stream<OutputResource>&
operator << (
    data_output_stream<OutputResource>& stream,
    T& source
);

} // namespace ----------------------------------------------------------------

#include <cmp/io/data_output_stream.ipp>

#endif // CMP_IO_DATA_OUTPUT_STREAM_HPP_INCLUDED
