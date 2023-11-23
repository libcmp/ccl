// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_TEXT_INPUT_STREAM_HPP_INCLUDED
#define CMP_IO_TEXT_INPUT_STREAM_HPP_INCLUDED

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/input_stream.hpp>
#include <cmp/unicode/impl/impl.hpp>
#include <cmp/unicode/algorithms.hpp>
#include <cmp/unicode/parsers.hpp>

namespace cmp {

template <
    typename InputResource
>
class text_input_stream
    : public input_stream<InputResource>
{
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
            Constructs a text input stream from the given input resource
            and with the given encoding form and endianness. The text input
            stream will hold a non-owning reference to the resource, which
            is expected to stay valid when using the text input stream.

        Parameters:
            resource:
                The input resource to read from.
            source_encoding_form:
                The encoding form that the text is expected to be in.
            endianness:
                The endianness that the text is expected to be in.
    */
    text_input_stream (
        wrapped_resource_type& resource,
        encoding_form source_encoding_form,
        std::endian endianness = std::endian::big
    )
    noexcept;

    ~text_input_stream ()
    noexcept = default;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Returns the encoding form associated
            with <#this/> text input stream.
    */
    encoding_form
    get_encoding_form ()
    const noexcept;

    /**
        Description:
            Sets the encoding form associated
            with <#this/> text input stream.

        Parameters:
            new_source_encoding_form:
                The new encoding form to use with <#this/> text input stream.
    */
    void
    set_encoding_form (
        encoding_form new_source_encoding_form
    )
    noexcept;

    /**
        Description:
            Reads a code point in the current encoding form, and if it is
            a valid BOM (byte order mark) then the endianness of <#this/>
            text input stream is adjusted accordingly. Returns the read
            code point.
    */
    char32_t
    read_bom ();

    /**
        Description:
            Reads a line and appends it to the given string object.

        Parameters:
            target:
                The object to append the read line to.
    */
    template <
        writable_raii_text_object TargetString
    >
    void
    append_line (
        TargetString& target
    );

    /**
        Description:
            Reads a line and assigns it to the given string object.

        Parameters:
            target:
                The object to assign the read line to.
    */
    template <
        writable_raii_text_object TargetString
    >
    void
    read_line (
        TargetString& target
    );

    /**
        Description:
            Reads all remaining text and appends it to the given string object.

        Parameters:
            target:
                The object to append the read text to.
    */
    template <
        writable_raii_text_object TargetString
    >
    void
    append_all (
        TargetString& target
    );

    /**
        Description:
            Reads all remaining text and assigns it to the given string object.

        Parameters:
            target:
                The object to assign the read text to.
    */
    template <
        writable_raii_text_object TargetString
    >
    void
    read_all (
        TargetString& target
    );

    // Friends ----------------------------------------------------------------

    template <
        typename InputResource2
    >
    friend
    text_input_stream<InputResource2>&
    operator >> (
        text_input_stream<InputResource2>& stream,
        char32_t& target
    );

private:
    // Private Data -----------------------------------------------------------

    encoding_form m_source_encoding_form;

    // Private Functions ------------------------------------------------------

    bool
    read_utf8_code_unit (
        char8_t& output
    );

    bool
    read_utf16_code_unit (
        char16_t& output
    );

    bool
    read_utf32_code_unit (
        char32_t& output
    );

    char32_t
    finish_utf8_sequence (
        int sequence_length,
        char32_t initial_code_point_value
    );

    char32_t
    finish_utf16_sequence (
        int sequence_length,
        char32_t initial_code_point_value
    );

    char32_t
    read_utf8_code_point ();

    char32_t
    read_utf16_code_point ();

    char32_t
    read_utf32_code_point ();

    char32_t
    read_code_point ();

    char32_t
    read_filtered_code_point ();

    char32_t
    read_utf16_bom ();

    char32_t
    read_utf32_bom ();
}; // class -------------------------------------------------------------------

// Free Functions -------------------------------------------------------------

/**
    Description:
        Reads a code point with the text input stream.

    Parameters:
        stream:
            The text input stream to read with.
        target:
            The object to store the read data in.
*/
template <
    typename InputResource
>
text_input_stream<InputResource>&
operator >> (
    text_input_stream<InputResource>& stream,
    char32_t& target
);

/**
    Description:
        Reads a Unicode string with the text input stream.

    Parameters:
        stream:
            The text input stream to read with.
        target:
            The object to store the read data in.
*/
template <
    typename InputResource,
    writable_raii_text_object T
>
text_input_stream<InputResource>&
operator >> (
    text_input_stream<InputResource>& stream,
    T& target
);

/**
    Description:
        Reads a bool value with the text input stream.

    Parameters:
        stream:
            The text input stream to read with.
        target:
            The object to store the read data in.
*/
template <
    typename InputResource
>
text_input_stream<InputResource>&
operator >> (
    text_input_stream<InputResource>& stream,
    bool& target
);

/**
    Description:
        Reads an integral value with the text input stream.

    Parameters:
        stream:
            The text input stream to read with.
        target:
            The object to store the read data in.
*/
template <
    typename InputResource,
    std::integral T
>
text_input_stream<InputResource>&
operator >> (
    text_input_stream<InputResource>& stream,
    T& target
);

/**
    Description:
        Reads a floating-point value with the text input stream.

    Parameters:
        stream:
            The text input stream to read with.
        target:
            The object to store the read data in.
*/
template <
    typename InputResource,
    std::floating_point T
>
text_input_stream<InputResource>&
operator >> (
    text_input_stream<InputResource>& stream,
    T& target
);

} // namespace ----------------------------------------------------------------

#include <cmp/io/text_input_stream.ipp>

#endif // CMP_IO_TEXT_INPUT_STREAM_HPP_INCLUDED
