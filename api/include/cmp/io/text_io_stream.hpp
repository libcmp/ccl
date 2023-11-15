// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_TEXT_IO_STREAM_HPP_INCLUDED
#define CMP_IO_TEXT_IO_STREAM_HPP_INCLUDED

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/text_input_stream.hpp>
#include <cmp/io/text_output_stream.hpp>

namespace cmp {

template <
    typename IOResource
>
class text_io_stream
    : public text_input_stream<IOResource>
    , public text_output_stream<IOResource>
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
            Constructs a text I/O stream from the given I/O resource and
            with the given encoding form and endianness. The text I/O
            stream will hold a non-owning reference to the resource,
            which is expected to stay valid when using the text I/O
            stream.

        Parameters:
            resource:
                The I/O resource to read from and write to.
            ef:
                The encoding form that the text is expected to be in.
            endianness:
                The endianness that the text is expected to be in.
    */
    text_io_stream (
        wrapped_resource_type& resource,
        encoding_form ef,
        std::endian endianness = std::endian::big
    )
    noexcept;

    ~text_io_stream ()
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

#include <cmp/io/text_io_stream.ipp>

#endif // CMP_IO_TEXT_IO_STREAM_HPP_INCLUDED
