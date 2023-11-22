// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/data_output_stream.hpp>

namespace cmp {

// ----------------------------------- cmp::data_output_stream<OutputResource>

// Constructors and Destructor ------------------------------------------------

template <
    typename OutputResource
>
data_output_stream<OutputResource>::data_output_stream (
    wrapped_resource_type& resource,
    std::endian endianness
)
noexcept
    : output_stream<OutputResource>{resource, endianness}
{
} // function -----------------------------------------------------------------

// Free Functions -------------------------------------------------------------

template <
    typename OutputResource,
    typename T
>
requires (std::is_fundamental_v<T>)
data_output_stream<OutputResource>&
operator << (
    data_output_stream<OutputResource>& stream,
    T& source
) {
    /*
        We calculate the number of bytes in
        a *T* object with the sizeof operator.
    */
    constexpr std::size_t byte_count{sizeof (T)};

    /*
        We allocate an array with enough bytes to store a *T* object.
    */
    std::byte data[byte_count];

    /*
        Next we copy the data of the source object to the array of bytes.
    */
    std::memcpy(data, &source, byte_count);

    /*
        Next we write that array of bytes to the stream. If the endianness
        of the stream matches the endianness of the system then we simply
        write out the bytes, but if the endianness of the stream does not
        match the endianness of the system then we reverse the bytes before
        writing them.
    */
    if (stream.get_endianness() == std::endian::native) {
        stream.write(data, byte_count);
    } else {
        stream.reverse_write(data, byte_count);
    }

    return stream;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------