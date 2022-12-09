// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/data_input_stream.hpp>

namespace cmp {

// ---------------------------------------------------- cmp::data_input_stream

// Constructors and Destructor ------------------------------------------------

template <
    typename InputResource
>
data_input_stream<InputResource>::data_input_stream (
    wrapped_resource_type& resource,
    std::endian endianness
)
noexcept
    : input_stream<InputResource>{resource, endianness}
{
} // function -----------------------------------------------------------------

// Readers --------------------------------------------------------------------

template <
    typename InputResource,
    typename T
>
requires (std::is_fundamental_v<T>)
data_input_stream<InputResource>&
operator >> (
    data_input_stream<InputResource>& stream,
    T& target
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
        Next we fill that array of bytes with raw data read from
        the stream. We also check whether we successfully read
        the desired number of bytes, and if we didn't then we
        report that we tried to read past the end of the stream.
    */
    if (stream.read(data, byte_count) < byte_count) {
        throw read_past_end{};
    }

    /*
        Then we check whether the endianness of the stream matches
        the endianness of the system. If it doesn't, we invert the
        endianness of the data that we just read.
    */
    if (stream.get_endianness() != std::endian::native) {
        invert_endianness(data, byte_count);
    }

    /*
        At this point we have an array of raw bytes that represent the data
        read from the stream, in the correct endianness for this system to
        process. So now we copy those raw bytes to the 'object' argument.
    */
    std::memcpy(&target, data, byte_count);

    return stream;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
