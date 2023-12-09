// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_DATA_INPUT_STREAM_HPP_INCLUDED
#define CMP_IO_DATA_INPUT_STREAM_HPP_INCLUDED

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/input_stream.hpp>

namespace cmp {

/**
    Description:
        A data input stream is an object that allows
        you to read binary data from an input resource.
*/
template <
    typename InputResource
>
class data_input_stream
    : public input_stream<InputResource>
{
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
            Constructs a data input stream from the given input resource
            and with the given endianness. The data input stream will hold
            a non-owning reference to the resource, which is expected to
            stay valid when using the data input stream.

        Parameters:
            resource:
                The input resource to read from.
            endianness:
                The endianness that the data is expected to be in.
    */
    explicit
    data_input_stream (
        referenced_resource_type& resource,
        std::endian endianness = std::endian::big
    )
    noexcept;

    ~data_input_stream ()
    override = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs a <#type>data_input_stream</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>data_input_stream</#type>
                to copy from.
    */
    data_input_stream (
        const data_input_stream& other
    )
    = default;

    /**
        Description:
            Copy-assigns a <#type>data_input_stream</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>data_input_stream</#type>
                to copy from.
    */
    data_input_stream&
    operator = (
        const data_input_stream& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs a <#type>data_input_stream</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>data_input_stream</#type>
                to move from.
    */
    data_input_stream (
        data_input_stream&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns a <#type>data_input_stream</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>data_input_stream</#type>
                to move from.
    */
    data_input_stream&
    operator = (
        data_input_stream&& other
    )
    noexcept = default;
}; // class -------------------------------------------------------------------

// Free Functions -------------------------------------------------------------

/**
    Description:
        Reads an object of fundamental type with the data input stream.

    Parameters:
        stream:
            The data input stream to read with.
        target:
            The object to store the read data in.
*/
template <
    typename InputResource,
    typename T
>
requires (std::is_fundamental_v<T>)
data_input_stream<InputResource>&
operator >> (
    data_input_stream<InputResource>& stream,
    T& target
);

} // namespace ----------------------------------------------------------------

#include <cmp/io/data_input_stream.ipp>

#endif // CMP_IO_DATA_INPUT_STREAM_HPP_INCLUDED
