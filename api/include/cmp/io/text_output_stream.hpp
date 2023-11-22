// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_TEXT_OUTPUT_STREAM_HPP_INCLUDED
#define CMP_IO_TEXT_OUTPUT_STREAM_HPP_INCLUDED

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/output_stream.hpp>
#include <cmp/unicode/algorithms.hpp>
#include <cmp/unicode/formatters.hpp>

namespace cmp {

template <
    typename OutputResource
>
class text_output_stream
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
            Constructs a text output stream from the given output resource
            and with the given encoding form and endianness. The text output
            stream will hold a non-owning reference to the resource, which
            is expected to stay valid when using the text output stream.

        Parameters:
            resource:
                The output resource to write to.
            target_encoding_form:
                The encoding form that the text is going to be in.
            endianness:
                The endianness that the text is going to be in.
    */
    text_output_stream (
        wrapped_resource_type& resource,
        encoding_form target_encoding_form,
        std::endian endianness = std::endian::big
    )
    noexcept;

    ~text_output_stream ()
    noexcept = default;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Returns the encoding form associated
            with <#this/> text output stream.
    */
    encoding_form
    get_encoding_form ()
    const noexcept;

    /**
        Description:
            Sets the encoding form associated
            with <#this/> text output stream.

        Parameters:
            new_target_encoding_form:
                The new encoding form to use with <#this/> text output stream.
    */
    void
    set_encoding_form (
        encoding_form new_target_encoding_form
    )
    noexcept;

    /**
        Description:
            Writes a BOM (byte order mark) for the current
            endianness in the current encoding form.
    */
    void
    write_bom ();

    // Friends ----------------------------------------------------------------

    template <
        typename OutputResource2
    >
    friend
    text_output_stream<OutputResource2>&
    operator << (
        text_output_stream<OutputResource2>& stream,
        char source
    );

    template <
        typename OutputResource2
    >
    friend
    text_output_stream<OutputResource2>&
    operator << (
        text_output_stream<OutputResource2>& stream,
        char32_t source
    );

    template <
        typename OutputResource2
    >
    friend
    text_output_stream<OutputResource2>&
    operator << (
        text_output_stream<OutputResource2>& stream,
        const std::string_view& source
    );

    template <
        typename OutputResource2
    >
    friend
    text_output_stream<OutputResource2>&
    operator << (
        text_output_stream<OutputResource2>& stream,
        const std::u8string_view& source
    );

    template <
        typename OutputResource2
    >
    friend
    text_output_stream<OutputResource2>&
    operator << (
        text_output_stream<OutputResource2>& stream,
        const std::u16string_view& source
    );

    template <
        typename OutputResource2
    >
    friend
    text_output_stream<OutputResource2>&
    operator << (
        text_output_stream<OutputResource2>& stream,
        const std::u32string_view& source
    );

    template <
        typename OutputResource2
    >
    friend
    text_output_stream<OutputResource2>&
    operator << (
        text_output_stream<OutputResource2>& stream,
        const std::wstring_view& source
    );

    friend class stdout_stream_t;

private:
    // Private Data -----------------------------------------------------------

    encoding_form m_target_encoding_form;

    // Private Functions ------------------------------------------------------

    void
    write_code_point_in_utf8 (
        char32_t code_point
    );

    void
    write_code_point_in_utf16 (
        char32_t code_point
    );

    void
    write_code_point_in_utf32 (
        char32_t code_point
    );

    void
    write_code_point (
        char32_t code_point
    );
}; // class -------------------------------------------------------------------

// Free Functions -------------------------------------------------------------

/**
    Description:
        Writes a char value with the text output stream.

    Parameters:
        stream:
            The text output stream to write with.
        source:
            The object to write.
*/
template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    char source
);

/**
    Description:
        Writes a code point with the text output stream.

    Parameters:
        stream:
            The text output stream to write with.
        source:
            The object to write.
*/
template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    char32_t source
);

/**
    Description:
        Writes a string with the text output stream.

    Parameters:
        stream:
            The text output stream to write with.
        source:
            The object to write.
*/
template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    const char* source
);

/**
    Description:
        Writes a string with the text output stream.

    Parameters:
        stream:
            The text output stream to write with.
        source:
            The object to write.
*/
template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    const std::string_view& source
);

/**
    Description:
        Writes a UTF-8 code unit with the text output stream.

    Parameters:
        stream:
            The text output stream to write with.
        source:
            The object to write.
*/
template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    const char8_t* source
);

/**
    Description:
        Writes a UTF-8 string with the text output stream.

    Parameters:
        stream:
            The text output stream to write with.
        source:
            The object to write.
*/
template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    const std::u8string_view& source
);

/**
    Description:
        Writes a UTF-16 code unit with the text output stream.

    Parameters:
        stream:
            The text output stream to write with.
        source:
            The object to write.
*/
template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    const char16_t* source
);

/**
    Description:
        Writes a UTF-16 string with the text output stream.

    Parameters:
        stream:
            The text output stream to write with.
        source:
            The object to write.
*/
template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    const std::u16string_view& source
);

/**
    Description:
        Writes a UTF-32 code unit with the text output stream.

    Parameters:
        stream:
            The text output stream to write with.
        source:
            The object to write.
*/
template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    const char32_t* source
);

/**
    Description:
        Writes a UTF-32 string with the text output stream.

    Parameters:
        stream:
            The text output stream to write with.
        source:
            The object to write.
*/
template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    const std::u32string_view& source
);

/**
    Description:
        Writes a wide code unit with the text output stream.

    Parameters:
        stream:
            The text output stream to write with.
        source:
            The object to write.
*/
template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    const wchar_t* source
);

/**
    Description:
        Writes a wide string with the text output stream.

    Parameters:
        stream:
            The text output stream to write with.
        source:
            The object to write.
*/
template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    const std::wstring_view& source
);

/**
    Description:
        Writes bool value with the text output stream.

    Parameters:
        stream:
            The text output stream to write with.
        source:
            The object to write.
*/
template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    bool source
);

/**
    Description:
        Writes an integral value with the text output stream.

    Parameters:
        stream:
            The text output stream to write with.
        source:
            The object to write.
*/
template <
    typename OutputResource,
    std::integral T
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    T source
);

/**
    Description:
        Writes a floating-point value with the text output stream.

    Parameters:
        stream:
            The text output stream to write with.
        source:
            The object to write.
*/
template <
    typename OutputResource,
    std::floating_point T
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    T source
);

} // namespace ----------------------------------------------------------------

#include <cmp/io/text_output_stream.ipp>

#endif // CMP_IO_TEXT_OUTPUT_STREAM_HPP_INCLUDED
