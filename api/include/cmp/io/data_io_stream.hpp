// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_DATA_IO_STREAM_HPP_INCLUDED
#define CMP_IO_DATA_IO_STREAM_HPP_INCLUDED

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/data_input_stream.hpp>
#include <cmp/io/data_output_stream.hpp>
#include <cmp/io/io_resource.hpp>

namespace cmp {

template <
    typename IOResource
>
class data_io_stream
    : public data_input_stream<IOResource>
    , public data_output_stream<IOResource>
{
public:
    // Types ------------------------------------------------------------------

    /**
        Description:
            The type of the wrapped I/O resource.
    */
    using wrapped_resource_type = IOResource;

    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs a data I/O stream from the given I/O resource
            and with the given endianness. The data I/O stream will hold
            a non-owning reference to the resource, which is expected to
            stay valid when using the data I/O stream.

        Parameters:
            resource:
                The I/O resource to read from and write to.
            endianness:
                The endianness that the data is expected to be in.
    */
    explicit
    data_io_stream (
        wrapped_resource_type& resource,
        std::endian endianness = std::endian::big
    )
    noexcept;

    ~data_io_stream ()
    noexcept = default;

    // Operator Overloads -----------------------------------------------------

    /**
        Description:
            Returns a pointer to the wrapped I/O resource,
            enabling use of the arrow operator.
    */
    wrapped_resource_type*
    operator -> ()
    const noexcept;

private:
    // Private Data -----------------------------------------------------------

    wrapped_resource_type& m_resource;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#include <cmp/io/data_io_stream.ipp>

#endif // CMP_IO_DATA_IO_STREAM_HPP_INCLUDED
