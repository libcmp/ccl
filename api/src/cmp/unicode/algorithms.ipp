// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/unicode/algorithms.hpp>

namespace cmp {

// Free Functions -------------------------------------------------------------

template <
    text_object ContentString,
    text_object Substring
>
bool
starts_with (
    const ContentString& content,
    const Substring& substring
)
noexcept
{
    cmp::by_code_point content_range{content};
    cmp::by_code_point substring_range{substring};
    auto content_iterator{content_range.cbegin()};
    auto substring_iterator{substring_range.cbegin()};
    do {
        if (substring_iterator == substring_range.cend()) {
            return true;
        }
        if (content_iterator == content_range.cend()) {
            return false;
        }
    } while (*(content_iterator++) == *(substring_iterator++));
    return false;
} // function -----------------------------------------------------------------

template <
    text_object ContentString,
    text_object Substring
>
bool
ends_with (
    const ContentString& content,
    const Substring& substring
)
noexcept
{
    cmp::by_code_point content_range{content};
    cmp::by_code_point substring_range{substring};
    auto content_iterator{content_range.crbegin()};
    auto substring_iterator{substring_range.crbegin()};
    do {
        if (substring_iterator == substring_range.crend()) {
            return true;
        }
        if (content_iterator == content_range.crend()) {
            return false;
        }
    } while (*(content_iterator++) == *(substring_iterator++));
    return false;
} // function -----------------------------------------------------------------

template <
    writable_raii_text_object TargetString
>
void
insert_code_point (
    TargetString& s,
    char32_t code_point,
    typename TargetString::size_type index
) {
    if constexpr (std::is_same_v<TargetString, std::string>) {
        s.insert(index, 1, static_cast<char>(code_point));
    } else if constexpr (std::is_same_v<TargetString, std::u8string>) {
        if (!is_code_point_valid(code_point)) {
            throw invalid_code_point{};
        }
        if (fits_in_7_bits(code_point)) {
            s.insert(index, 1, static_cast<char8_t>(code_point));
        } else if (code_point <= 0b0111'1111'1111) {
            s.insert(
                index++,
                1,
                static_cast<char8_t>(
                    (code_point >> 6) | 0b1100'0000
                )
            );
            s.insert(
                index,
                1,
                static_cast<char8_t>(
                    (code_point & 0b0011'1111) | 0b1000'0000
                )
            );
        } else if (code_point <= 0b1111'1111'1111'1111) {
            s.insert(
                index++,
                1,
                static_cast<char8_t>(
                    (code_point >> 12) | 0b1110'0000
                )
            );
            s.insert(
                index++,
                1,
                static_cast<char8_t>(
                    ((code_point >> 6) & 0b0011'1111) | 0b1000'0000
                )
            );
            s.insert(
                index,
                1,
                static_cast<char8_t>(
                    (code_point & 0b0011'1111) | 0b1000'0000
                )
            );
        } else {
            s.insert(
                index++,
                1,
                static_cast<char8_t>(
                    (code_point >> 18) | 0b1111'0000
                )
            );
            s.insert(
                index++,
                1,
                static_cast<char8_t>(
                    ((code_point >> 12) & 0b0011'1111) | 0b1000'0000
                )
            );
            s.insert(
                index++,
                1,
                static_cast<char8_t>(
                    ((code_point >> 6) & 0b0011'1111) | 0b1000'0000
                )
            );
            s.insert(
                index,
                1,
                static_cast<char8_t>(
                    (code_point & 0b0011'1111) | 0b1000'0000
                )
            );
        }
    } else if constexpr (
        std::is_same_v<TargetString, std::u16string>
            || (
                   std::is_same_v<TargetString, std::wstring>
                       && sizeof (wchar_t) == 2
               )
    ) {
        if (
            !is_surrogate(code_point)
                && code_point <= maximum_bmp_code_point
        ) {
            s.insert(index, 1, static_cast<char16_t>(code_point));
        } else {
            code_point -= 0x10000;
            s.insert(
                index++,
                1,
                static_cast<char16_t>(
                    ((0b1111'1111'1100'0000'0000 & code_point) >> 10)
                        + leading_surrogate_minimum_value
                )
            );
            s.insert(
                index,
                1,
                static_cast<char16_t>(
                    (0b0000'0000'0011'1111'1111 & code_point)
                        + trailing_surrogate_minimum_value
                )
            );
        }
    } else if constexpr (
        std::is_same_v<TargetString, std::u32string>
            || (
                   std::is_same_v<TargetString, std::wstring>
                       && sizeof (wchar_t) == 4
               )
    ) {
        s.insert(index, 1, code_point);
    }
} // function -----------------------------------------------------------------

template <
    writable_raii_text_object TargetString
>
void
append_code_point (
    TargetString& s,
    char32_t code_point
) {
    insert_code_point(s, code_point, s.size());
} // function -----------------------------------------------------------------

template <
    writable_raii_text_object TargetString
>
void
prepend_code_point (
    TargetString& s,
    char32_t code_point
) {
    insert_code_point(s, code_point, 0);
} // function -----------------------------------------------------------------

template <
    writable_raii_text_object OutputString,
    text_object InputString
>
OutputString
convert_string (
    const InputString& s
) {
    OutputString result;
    result.reserve(string_size(s));
    for (char32_t current_code_point : by_code_point{s}) {
        append_code_point(result, current_code_point);
    }
    return result;
} // function -----------------------------------------------------------------

template <
    text_object InputString
>
std::string
to_string (
    const InputString& s
) {
    return convert_string<std::string>(s);
} // function -----------------------------------------------------------------

template <
    text_object InputString
>
std::u8string
to_u8string (
    const InputString& s
) {
    return convert_string<std::u8string>(s);
} // function -----------------------------------------------------------------

template <
    text_object InputString
>
std::u16string
to_u16string (
    const InputString& s
) {
    return convert_string<std::u16string>(s);
} // function -----------------------------------------------------------------

template <
    text_object InputString
>
std::u32string
to_u32string (
    const InputString& s
) {
    return convert_string<std::u32string>(s);
} // function -----------------------------------------------------------------

template <
    text_object InputString
>
std::wstring
to_wstring (
    const InputString& s
) {
    return convert_string<std::wstring>(s);
} // function -----------------------------------------------------------------

template <
    text_object InputString
>
typename by_code_point<value_type_t<InputString>>::const_iterator
validate_string (
    const InputString& s
)
noexcept
{
    auto bcp_range{by_code_point(s)};
    auto bcp_range_end{std::cend(bcp_range)};
    auto bcp_iterator{std::cbegin(bcp_range)};
    try {
        while (bcp_iterator != bcp_range_end) {
            if (*bcp_iterator > maximum_code_point) {
                return bcp_iterator;
            }
            ++bcp_iterator;
        }
    } catch (const invalid_unicode_encoding& ex) {
    } catch (const iterated_past_end& ex) {
    }
    return bcp_iterator;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
