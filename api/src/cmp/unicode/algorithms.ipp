// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/unicode/algorithms.hpp>

namespace cmp {

template <
    unicode_string ContentString,
    unicode_string Substring
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
    unicode_string ContentString,
    unicode_string Substring
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
    writable_raii_unicode_string OutputString
>
void
append_code_point (
    OutputString& s,
    char32_t code_point
) {
    insert_code_point(s, code_point, s.size());
} // function -----------------------------------------------------------------

template <
    writable_raii_unicode_string OutputString
>
void
prepend_code_point (
    OutputString& s,
    char32_t code_point
) {
    insert_code_point(s, code_point, 0);
} // function -----------------------------------------------------------------

template <
    unicode_string InputString
>
std::string
to_string (
    const InputString& s
) {
    std::string result;
    result.reserve(string_size(s));
    for (char32_t current_code_point : by_code_point{s}) {
        result.push_back(static_cast<char>(current_code_point));
    }
    return result;
} // function -----------------------------------------------------------------

template <
    unicode_string InputString
>
std::u8string
to_u8string (
    const InputString& s
) {
    std::u8string result;
    result.reserve(string_size(s));
    for (char32_t current_code_point : by_code_point{s}) {
        append_code_point(result, current_code_point);
    }
    return result;
} // function -----------------------------------------------------------------

template <
    unicode_string InputString
>
std::u16string
to_u16string (
    const InputString& s
) {
    std::u16string result;
    result.reserve(string_size(s));
    for (char32_t current_code_point : by_code_point{s}) {
        append_code_point(result, current_code_point);
    }
    return result;
} // function -----------------------------------------------------------------

template <
    unicode_string InputString
>
std::u32string
to_u32string (
    const InputString& s
) {
    std::u32string result;
    result.reserve(string_size(s));
    for (char32_t current_code_point : by_code_point{s}) {
        append_code_point(result, current_code_point);
    }
    return result;
} // function -----------------------------------------------------------------

template <
    raii_unicode_string OutputString,
    unicode_string InputString
>
OutputString
convert_string (
    const InputString& s
) {
    if constexpr (is_utf8_string_v<OutputString>) {
        return to_u8string(s);
    } else if constexpr (is_utf16_string_v<OutputString>) {
        return to_u16string(s);
    } else if constexpr (is_utf32_string_v<OutputString>) {
        return to_u32string(s);
    }
} // function -----------------------------------------------------------------

template <
    unicode_string InputString
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
