// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_DATA_OUTPUT_STREAM_HPP_INCLUDED
#define CMP_IO_DATA_OUTPUT_STREAM_HPP_INCLUDED

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/output_stream.hpp>

namespace cmp {

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
            The type of the wrapped output resource.
    */
    using wrapped_resource_type = OutputResource;

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
        wrapped_resource_type& resource,
        std::endian endianness = std::endian::big
    )
    noexcept;

    ~data_output_stream ()
    noexcept = default;
}; // class -------------------------------------------------------------------

// Writers --------------------------------------------------------------------

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
