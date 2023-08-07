// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/unicode/parsers.hpp>

namespace cmp {

namespace impl {

// -------------------------------------------------- cmp::impl::number_parser

// Core -----------------------------------------------------------------------

template <
    std::integral Output,
    unicode_string Input
>
Output
number_parser::parse_integer (
    const Input& input,
    const integer_format& format
) {
    std::size_t input_size{string_size(input)};
    if (input_size == 0) {
        throw parse_failed{
            "The input string is empty, there is nothing to parse.",
            parse_failed::type::empty_input
        };
    }

    by_code_point bcp_range{input};
    auto bcp_iterator{bcp_range.crbegin()};

    const auto format_radix{format.get_radix()};
    const auto format_thousands_separator{format.get_thousands_separator()};
    const auto format_sign_status{format.get_sign_status()};

    int current_digit{get_next_digit(*bcp_iterator, format_radix)};
    Output output{static_cast<Output>(current_digit)};

    ++bcp_iterator;
    if (bcp_iterator == bcp_range.crend()) {
        return output;
    }

    bool sign_found{false};
    bool negate{false};
    Output power{1};
    unsigned int digits_counted{1};
    char32_t current_character;

    for (; bcp_iterator != bcp_range.crend(); ++bcp_iterator) {
        current_character = *bcp_iterator;
        if (
            digits_counted == 3
                && format_thousands_separator != thousands_separator::none
        ) {
            digits_counted = 0;
            if (
                check_for_sign(
                    current_character,
                    sign_found,
                    negate,
                    format_sign_status
                )
            ) {
                continue;
            }
            check_for_thousands_separator(
                current_character,
                format_thousands_separator
            );
            continue;
        }
        if (
            check_for_sign(
                current_character,
                sign_found,
                negate,
                format_sign_status
            )
        ) {
            continue;
        } else if (!is_radix_digit(current_character, format_radix)) {
            report_non_digit_character();
        }
        current_digit = get_next_digit(current_character, format_radix);
        prepend_digit(
            power,
            format_radix,
            output,
            current_digit,
            digits_counted
        );
    }
    if (negate) {
        if constexpr (std::is_signed_v<Output>) {
            output = -output;
        } else {
            throw parse_failed{
                "The input string contains a negative "
                "sign but the output type is unsigned.",
                parse_failed::type::negative_unsigned
            };
        }
    }
    return output;
} // function -----------------------------------------------------------------

template <
    std::floating_point Output,
    unicode_string Input
>
Output
number_parser::parse_floating_point (
    const Input& input,
    const floating_point_format& format
) {
    const std::u32string u32_input{to_u32string(input)};
    const auto format_radix_character{format.get_radix_character()};
    const auto format_radix{format.get_radix()};
    auto radix_character_iterator{
        std::find(
            u32_input.cbegin(),
            u32_input.cend(),
            format_radix_character == radix_character::period
                ? '.'
                : ','
        )
    };
    integer_format equivalent_format{
        format_radix,
        format.get_sign_status(),
        format.get_thousands_separator()
    };
    if (radix_character_iterator == u32_input.cend()) {
        return number_parser::parse_integer<long long>(
            u32_input,
            equivalent_format
        );
    } else {
        const auto integral_part_start{u32_input.data()};
        const auto integral_part_size{
            radix_character_iterator - u32_input.cbegin()
        };
        const std::u32string_view integral_part{
            integral_part_start,
            static_cast<std::u32string_view::size_type>(integral_part_size)
        };
        Output output{
            static_cast<Output>(
                parse_integer<long long>(integral_part, equivalent_format)
            )
        };
        ++radix_character_iterator;
        if (radix_character_iterator == u32_input.cend()) {
            if (format.get_radix_place_limit() == radix_place_limit::none) {
                return output;
            } else if (format.get_radix_place_count() > 0) {
                throw parse_failed{
                    "The input string had insufficient "
                    "places after the radix point.",
                    parse_failed::type::wrong_place_limit
                };
            }
        }
        Output root = 1;
        int current_digit;;
        unsigned int digits_counted{0};
        while (radix_character_iterator != u32_input.cend()) {
            current_digit = digit_character_to_integer(
                *radix_character_iterator,
                format_radix
            );
            if (current_digit == -1) {
                throw parse_failed{
                    "The input string didn't have enough "
                    "places after the radix point.",
                    parse_failed::type::wrong_place_limit
                };
            } else {
                append_digit(
                    root,
                    format_radix,
                    output,
                    current_digit,
                    digits_counted
                );
            }
            ++radix_character_iterator;
        }
        return output;
    }
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

template <
    std::integral Output
>
void
number_parser::prepend_digit (
    Output& power,
    unsigned int radix,
    Output& output,
    int current_digit,
    unsigned int& digits_counted
)
noexcept
{
    power *= radix;
    output += current_digit * power;
    ++digits_counted;
} // function -----------------------------------------------------------------

template <
    std::floating_point Output
>
void
number_parser::append_digit (
    Output& root,
    unsigned int radix,
    Output& output,
    int current_digit,
    unsigned int& digits_counted
)
noexcept
{
    root *= radix;
    output += current_digit / root;
    ++digits_counted;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

template <
    unicode_string Input
>
bool
parse_bool (
    Input input,
    const bool_format& format
) {
    if (string_size(input) == 0) {
        throw parse_failed{
            "The input string is empty, there is nothing to parse.",
            parse_failed::type::empty_input
        };
    }
    if constexpr (is_utf8_string_v<Input>) {
        if (input == format.get_true_string()) {
            return true;
        }
        if (input == format.get_false_string()) {
            return false;
        }
    } else {
        std::u8string input_u8string{to_u8string(input)};
        if (input_u8string == format.get_true_string()) {
            return true;
        }
        if (input_u8string == format.get_false_string()) {
            return false;
        }
    }
    throw parse_failed{
        "The input string did not match the format provided. "
        "Specifically, the input string matches neither the "
        "true string nor the false string of the bool format.",
        parse_failed::type::neither_boolean
    };
} // function -----------------------------------------------------------------

template <
    std::integral Output,
    unicode_string Input
>
Output
parse_integer (
    const Input& input,
    const integer_format& format
) {
    return impl::number_parser::parse_integer<Output>(input, format);
} // function -----------------------------------------------------------------

template <
    std::floating_point Output,
    unicode_string Input
>
Output
parse_floating_point (
    const Input& input,
    const floating_point_format& format
) {
    return impl::number_parser::parse_floating_point<Output>(input, format);
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
