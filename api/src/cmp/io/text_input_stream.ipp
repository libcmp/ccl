// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/text_input_stream.hpp>

namespace cmp {

// ---------------------------------------------------- cmp::text_input_stream

// Constructors and Destructor ------------------------------------------------

template <
    typename InputResource
>
text_input_stream<InputResource>::text_input_stream (
    wrapped_resource_type& resource,
    encoding_form source_encoding_form,
    std::endian endianness
)
noexcept
    : input_stream<InputResource>{resource, endianness}
    , m_source_encoding_form{source_encoding_form}
{
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

template <
    typename InputResource
>
encoding_form
text_input_stream<InputResource>::get_encoding_form ()
const noexcept
{
    return m_source_encoding_form;
} // function -----------------------------------------------------------------

template <
    typename InputResource
>
void
text_input_stream<InputResource>::set_encoding_form (
    encoding_form new_source_encoding_form
)
noexcept
{
    m_source_encoding_form = new_source_encoding_form;
} // function -----------------------------------------------------------------

template <
    typename InputResource
>
char32_t
text_input_stream<InputResource>::read_bom ()
{
    switch (m_source_encoding_form) {
        case utf8:
            return read_code_point();
        case utf16:
            return read_utf16_bom();
        case utf32:
            return read_utf32_bom();
    }
} // function -----------------------------------------------------------------

template <
    typename InputResource
>
template <
    writable_unicode_string TargetString
>
void
text_input_stream<InputResource>::append_line (
    TargetString& target
) {
    char32_t code_point;
    while (!this->is_at_end()) {
        code_point = read_filtered_code_point();
        if (code_point == '\n') {
            break;
        }
        append_code_point(target, code_point);
    }
} // function -----------------------------------------------------------------

template <
    typename InputResource
>
template <
    writable_unicode_string TargetString
>
void
text_input_stream<InputResource>::read_line (
    TargetString& target
) {
    target.clear();
    append_line(target);
} // function -----------------------------------------------------------------

template <
    typename InputResource
>
template <
    writable_unicode_string TargetString
>
void
text_input_stream<InputResource>::append_all (
    TargetString& target
) {
    while (!this->is_at_end()) {
        append_code_point(target, read_filtered_code_point());
    }
} // function -----------------------------------------------------------------

template <
    typename InputResource
>
template <
    writable_unicode_string TargetString
>
void
text_input_stream<InputResource>::read_all (
    TargetString& target
) {
    target.clear();
    append_all(target);
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

template <
    typename InputResource
>
bool
text_input_stream<InputResource>::read_utf8_code_unit (
    char8_t& output
) {
    std::byte data;
    if (this->read(&data, 1) < 1) {
        return false;
    }
    output = static_cast<char8_t>(data);
    return true;
} // function -----------------------------------------------------------------

template <
    typename InputResource
>
bool
text_input_stream<InputResource>::read_utf16_code_unit (
    char16_t& output
) {
    std::byte data[2];
    if (this->read(data, 2) < 2) {
        return false;
    }
    std::memcpy(&output, data, 2);
    return true;
} // function -----------------------------------------------------------------

template <
    typename InputResource
>
bool
text_input_stream<InputResource>::read_utf32_code_unit (
    char32_t& output
) {
    std::byte data[4];
    if (this->read(data, 4) < 4) {
        return false;
    }
    std::memcpy(&output, data, 4);
    return true;
} // function -----------------------------------------------------------------

template <
    typename InputResource
>
char32_t
text_input_stream<InputResource>::finish_utf8_sequence (
    int sequence_length,
    char32_t initial_code_point_value
) {
    char8_t code_unit;
    char32_t result{initial_code_point_value};
    while (--sequence_length > 0) {
        if (!read_utf8_code_unit(code_unit)) {
            throw read_past_end{};
        }
        if (!is_trailing_byte(code_unit)) {
            throw invalid_unicode_encoding{};
        }
        result <<= 6;
        result |= code_unit & 0b0011'1111;
    }
    return result;
} // function -----------------------------------------------------------------

template <
    typename InputResource
>
char32_t
text_input_stream<InputResource>::finish_utf16_sequence (
    int sequence_length,
    char32_t initial_code_point_value
) {
    if (sequence_length == 2) {
        char16_t code_unit;
        if (!read_utf16_code_unit(code_unit)) {
            throw read_past_end{};
        }
        if (!is_trailing_surrogate(code_unit)) {
            throw invalid_unicode_encoding{};
        }
        return initial_code_point_value + (code_unit - 0xDC00) + 0x10000;
    } else {
        return initial_code_point_value;
    }
} // function -----------------------------------------------------------------

template <
    typename InputResource
>
char32_t
text_input_stream<InputResource>::read_utf8_code_point ()
{
    char8_t code_unit;
    if (!read_utf8_code_unit(code_unit)) {
        throw read_past_end{};
    }
    char32_t result;
    int sequence_length{impl::initialize_utf8_sequence(code_unit, result)};
    result = finish_utf8_sequence(sequence_length, result);
    return result;
} // function -----------------------------------------------------------------

template <
    typename InputResource
>
char32_t
text_input_stream<InputResource>::read_utf16_code_point ()
{
    char16_t code_unit;
    if (!read_utf16_code_unit(code_unit)) {
        throw read_past_end{};
    }
    char32_t result;
    int sequence_length{impl::initialize_utf16_sequence(code_unit, result)};
    result = finish_utf16_sequence(sequence_length, result);
    return result;
} // function -----------------------------------------------------------------

template <
    typename InputResource
>
char32_t
text_input_stream<InputResource>::read_utf32_code_point ()
{
    char32_t code_unit;
    if (!read_utf32_code_unit(code_unit)) {
        throw read_past_end{};
    }
    return code_unit;
} // function -----------------------------------------------------------------

template <
    typename InputResource
>
char32_t
text_input_stream<InputResource>::read_code_point ()
{
    switch (m_source_encoding_form) {
        case utf8:
            return read_utf8_code_point();
        case utf16:
            return read_utf16_code_point();
        case utf32:
            return read_utf32_code_point();
    }
} // function -----------------------------------------------------------------

template <
    typename InputResource
>
char32_t
text_input_stream<InputResource>::read_filtered_code_point ()
{
    char32_t code_point{read_code_point()};
    if (code_point == '\r' && !this->is_at_end()) {
        code_point = read_code_point();
    }
    return code_point;
} // function -----------------------------------------------------------------

template <
    typename InputResource
>
char32_t
text_input_stream<InputResource>::read_utf16_bom ()
{
    std::byte first_byte;
    std::byte second_byte;
    if (this->read(&first_byte, 1) < 1) {
        throw read_past_end{};
    }
    if (this->read(&second_byte, 1) < 1) {
        throw read_past_end{};
    }
    if (
        static_cast<int>(first_byte) == 0xFE
            && static_cast<int>(second_byte) == 0xFF
    ) {
        this->set_endianness(std::endian::big);
        return bom;
    } else if (
        static_cast<int>(first_byte) == 0xFF
            && static_cast<int>(second_byte) == 0xFE
    ) {
        this->set_endianness(std::endian::little);
        return bom;
    } else {
        char16_t code_unit;
        if (this->get_endianness() == std::endian::big) {
            code_unit
                = static_cast<int>(first_byte << 8)
                    | static_cast<int>(second_byte);
        } else {
            code_unit
                = static_cast<int>(second_byte << 8)
                    | static_cast<int>(first_byte);
        }
        char32_t result;
        int sequence_length{
            impl::initialize_utf16_sequence(code_unit, result)
        };
        result = finish_utf16_sequence(sequence_length, result);
        return result;
    }
} // function -----------------------------------------------------------------

template <
    typename InputResource
>
char32_t
text_input_stream<InputResource>::read_utf32_bom ()
{
    std::byte first_byte;
    std::byte second_byte;
    std::byte third_byte;
    std::byte fourth_byte;
    if (this->read(&first_byte, 1) < 1) {
        throw read_past_end{};
    }
    if (this->read(&second_byte, 1) < 1) {
        throw read_past_end{};
    }
    if (this->read(&third_byte, 1) < 1) {
        throw read_past_end{};
    }
    if (this->read(&fourth_byte, 1) < 1) {
        throw read_past_end{};
    }
    if (
        static_cast<int>(first_byte) == 0
            && static_cast<int>(second_byte) == 0
            && static_cast<int>(third_byte) == 0xFE
            && static_cast<int>(fourth_byte) == 0xFF
    ) {
        this->set_endianness(std::endian::big);
        return bom;
    } else if (
        static_cast<int>(first_byte) == 0xFF
            && static_cast<int>(second_byte) == 0xFE
            && static_cast<int>(third_byte) == 0
            && static_cast<int>(fourth_byte) == 0
    ) {
        this->set_endianness(std::endian::little);
        return bom;
    } else {
        char32_t result;
        if (this->get_endianness() == std::endian::big) {
            result
                = static_cast<int>(first_byte << 24)
                    | static_cast<int>(second_byte << 16)
                    | static_cast<int>(third_byte << 8)
                    | static_cast<int>(fourth_byte);
        } else {
            result
                = static_cast<int>(fourth_byte << 24)
                    | static_cast<int>(third_byte << 16)
                    | static_cast<int>(second_byte << 8)
                    | static_cast<int>(first_byte);
        }
        return result;
    }
} // function -----------------------------------------------------------------

// Readers --------------------------------------------------------------------

template <
    typename InputResource
>
text_input_stream<InputResource>&
operator >> (
    text_input_stream<InputResource>& stream,
    char32_t& target
) {
    target = stream.read_filtered_code_point();
    return stream;
} // function -----------------------------------------------------------------

template <
    typename InputResource,
    writable_unicode_string T
>
text_input_stream<InputResource>&
operator >> (
    text_input_stream<InputResource>& stream,
    T& target
) {
    char32_t code_point;

    /*
        First we skip all whitespace characters in the stream.
    */
    while (!stream.is_at_end()) {
        stream >> code_point;
        if (!is_whitespace(code_point)) {
            /*
                As soon as we find a non-whitespace character,
                we consume it and break out of the loop.
            */
            append_code_point(target, code_point);
            break;
        }
    }

    /*
        Then we consume all remaining non-whitespace characters.
    */
    while (!stream.is_at_end()) {
        stream >> code_point;
        if (is_whitespace(code_point)) {
            /*
                As soon as we find a whitespace character we break out of
                the loop. Notice how this algorithm does consume the first
                whitespace character after the non-whitespace characters.
            */
            break;
        }
        append_code_point(target, code_point);
    }

    return stream;
} // function -----------------------------------------------------------------

template <
    typename InputResource
>
text_input_stream<InputResource>&
operator >> (
    text_input_stream<InputResource>& stream,
    bool& target
) {
    std::u8string input;
    stream >> input;
    target = parse_bool(input, bool_format{});
    return stream;
} // function -----------------------------------------------------------------

template <
    typename InputResource,
    std::integral T
>
text_input_stream<InputResource>&
operator >> (
    text_input_stream<InputResource>& stream,
    T& target
) {
    std::u8string input;
    stream >> input;
    target = parse_integer<T>(input, integer_format{});
    return stream;
} // function -----------------------------------------------------------------

template <
    typename InputResource,
    std::floating_point T
>
text_input_stream<InputResource>&
operator >> (
    text_input_stream<InputResource>& stream,
    T& target
) {
    std::u8string input;
    stream >> input;
    target = parse_floating_point<T>(input, floating_point_format{});
    return stream;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
