// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/text_output_stream.hpp>

namespace cmp {

// --------------------------------------------------- cmp::text_output_stream

// Constructors and Destructor ------------------------------------------------

template <
    typename OutputResource
>
text_output_stream<OutputResource>::text_output_stream (
    wrapped_resource_type& resource,
    encoding_form target_encoding_form,
    std::endian endianness
)
noexcept
    : output_stream<OutputResource>{resource, endianness}
    , m_target_encoding_form{target_encoding_form}
{
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

template <
    typename OutputResource
>
encoding_form
text_output_stream<OutputResource>::get_encoding_form ()
const noexcept
{
    return m_target_encoding_form;
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
void
text_output_stream<OutputResource>::set_encoding_form (
    encoding_form new_target_encoding_form
)
noexcept
{
    m_target_encoding_form = new_target_encoding_form;
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
void
text_output_stream<OutputResource>::write_bom ()
{
    write_code_point(bom);
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

template <
    typename OutputResource
>
void
text_output_stream<OutputResource>::write_code_point_in_utf8 (
    char32_t code_point
) {
    std::u8string data;
    append_code_point(data, code_point);
    this->write(
        reinterpret_cast<const std::byte*>(data.data()),
        data.size()
    );
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
void
text_output_stream<OutputResource>::write_code_point_in_utf16 (
    char32_t code_point
) {
    std::u16string data;
    append_code_point(data, code_point);
    if (this->get_endianness() == std::endian::native) {
        this->write(
            reinterpret_cast<const std::byte*>(data.data()),
            data.size() * sizeof (char16_t)
        );
    } else {
        this->reverse_write(
            reinterpret_cast<std::byte*>(data.data()),
            sizeof (char16_t)
        );
        if (data.size() > 1) {
            this->reverse_write(
                reinterpret_cast<std::byte*>(data.data() + 1),
                sizeof (char16_t)
            );
        }
    }
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
void
text_output_stream<OutputResource>::write_code_point_in_utf32 (
    char32_t code_point
) {
    if (this->get_endianness() == std::endian::native) {
        this->write(
            reinterpret_cast<const std::byte*>(&code_point),
            sizeof (char32_t)
        );
    } else {
        this->reverse_write(
            reinterpret_cast<std::byte*>(&code_point),
            sizeof (char32_t)
        );
    }
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
void
text_output_stream<OutputResource>::write_code_point (
    char32_t code_point
) {
    switch (m_target_encoding_form) {
        case utf8:
            write_code_point_in_utf8(code_point);
            break;
        case utf16:
            write_code_point_in_utf16(code_point);
            break;
        case utf32:
            write_code_point_in_utf32(code_point);
            break;
    }
} // function -----------------------------------------------------------------

// Writers --------------------------------------------------------------------

template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    char source
) {
    stream.write_code_point(source);
    return stream;
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    char32_t source
) {
    stream.write_code_point(source);
    return stream;
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    const char* source
) {
    return stream << std::string_view{source};
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    const std::string_view& source
) {
    switch (stream.get_encoding_form()) {
        case utf8:
            stream.write(
                reinterpret_cast<const std::byte*>(std::data(source)),
                std::size(source)
            );
            break;
        case utf16:
            for (char current_code_point : source) {
                stream.write_code_point_in_utf16(current_code_point);
            }
            break;
        case utf32:
            for (char current_code_point : source) {
                stream.write_code_point_in_utf32(current_code_point);
            }
            break;
    }
    return stream;
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    const char8_t* source
) {
    return stream << std::u8string_view{source};
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    const std::u8string_view& source
) {
    switch (stream.get_encoding_form()) {
        case utf8:
            stream.write(
                reinterpret_cast<const std::byte*>(std::data(source)),
                std::size(source)
            );
            break;
        case utf16:
            for (char32_t current_code_point : by_code_point{source}) {
                stream.write_code_point_in_utf16(current_code_point);
            }
            break;
        case utf32:
            for (char32_t current_code_point : by_code_point{source}) {
                stream.write_code_point_in_utf32(current_code_point);
            }
            break;
    }
    return stream;
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    const char16_t* source
) {
    return stream << std::u16string_view{source};
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    const std::u16string_view& source
) {
    switch (stream.get_encoding_form()) {
        case utf8:
            for (char32_t current_code_point : by_code_point{source}) {
                stream.write_code_point_in_utf8(current_code_point);
            }
            break;
        case utf16:
            if (stream.get_endianness() == std::endian::native) {
                stream.write(
                    reinterpret_cast<const std::byte*>(std::data(source)),
                    std::size(source) * sizeof (char16_t)
                );
            } else {
                for (char32_t current_code_point : by_code_point{source}) {
                    stream.write_code_point_in_utf16(current_code_point);
                }
            }
            break;
        case utf32:
            for (char32_t current_code_point : by_code_point{source}) {
                stream.write_code_point_in_utf32(current_code_point);
            }
            break;
    }
    return stream;
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    const char32_t* source
) {
    return stream << std::u32string_view{source};
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    const std::u32string_view& source
) {
    switch (stream.get_encoding_form()) {
        case utf8:
            for (char32_t current_code_point : by_code_point{source}) {
                stream.write_code_point_in_utf8(current_code_point);
            }
            break;
        case utf16:
            for (char32_t current_code_point : by_code_point{source}) {
                stream.write_code_point_in_utf16(current_code_point);
            }
            break;
        case utf32:
            if (stream.get_endianness() == std::endian::native) {
                stream.write(
                    reinterpret_cast<const std::byte*>(std::data(source)),
                    std::size(source) * sizeof (char32_t)
                );
            } else {
                for (char32_t current_code_point : by_code_point{source}) {
                    stream.write_code_point_in_utf32(current_code_point);
                }
            }
            break;
    }
    return stream;
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    const wchar_t* source
) {
    return stream << std::wstring_view{source};
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    const std::wstring_view& source
) {
    switch (stream.get_encoding_form()) {
        case utf8:
            for (char32_t current_code_point : by_code_point{source}) {
                stream.write_code_point_in_utf8(current_code_point);
            }
            break;
        case utf16:
            if constexpr (sizeof (wchar_t) == 2) {
                if (stream.get_endianness() == std::endian::native) {
                    stream.write(
                        reinterpret_cast<const std::byte*>(std::data(source)),
                        std::size(source) * sizeof (wchar_t)
                    );
                } else {
                    for (char32_t current_code_point : by_code_point{source}) {
                        stream.write_code_point_in_utf16(current_code_point);
                    }
                }
            } else {
                for (char32_t current_code_point : by_code_point{source}) {
                    stream.write_code_point_in_utf16(current_code_point);
                }
            }
            break;
        case utf32:
            if constexpr (sizeof (wchar_t) == 2) {
                for (char32_t current_code_point : by_code_point{source}) {
                    stream.write_code_point_in_utf32(current_code_point);
                }
            } else {
                if (stream.get_endianness() == std::endian::native) {
                    stream.write(
                        reinterpret_cast<const std::byte*>(std::data(source)),
                        std::size(source) * sizeof (wchar_t)
                    );
                } else {
                    for (char32_t current_code_point : by_code_point{source}) {
                        stream.write_code_point_in_utf32(current_code_point);
                    }
                }
            }
            break;
    }
    return stream;
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    bool source
) {
    switch (stream.get_encoding_form()) {
        case utf8:
            stream << format_bool<std::u8string>(source, bool_format{});
            break;
        case utf16:
            stream << format_bool<std::u16string>(source, bool_format{});
            break;
        case utf32:
            stream << format_bool<std::u32string>(source, bool_format{});
            break;
    }
    return stream;
} // function -----------------------------------------------------------------

template <
    typename OutputResource,
    std::integral T
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    T source
) {
    switch (stream.get_encoding_form()) {
        case utf8:
            stream << format_integer<std::u8string>(source, integer_format{});
            break;
        case utf16:
            stream << format_integer<std::u16string>(source, integer_format{});
            break;
        case utf32:
            stream << format_integer<std::u32string>(source, integer_format{});
            break;
    }
    return stream;
} // function -----------------------------------------------------------------

template <
    typename OutputResource,
    std::floating_point T
>
text_output_stream<OutputResource>&
operator << (
    text_output_stream<OutputResource>& stream,
    T source
) {
    switch (stream.get_encoding_form()) {
        case utf8:
            stream << format_floating_point<std::u8string>(
                source,
                floating_point_format{}
            );
            break;
        case utf16:
            stream << format_floating_point<std::u16string>(
                source,
                floating_point_format{}
            );
            break;
        case utf32:
            stream << format_floating_point<std::u32string>(
                source,
                floating_point_format{}
            );
            break;
    }
    return stream;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
