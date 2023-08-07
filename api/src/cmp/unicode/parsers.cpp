// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/unicode/parsers.hpp>

namespace cmp {

namespace impl {

// -------------------------------------------------- cmp::impl::number_parser

// Private Functions ----------------------------------------------------------

int
number_parser::digit_character_to_integer (
    char32_t character,
    unsigned int radix
)
noexcept
{
    if (!is_radix_digit(character, radix)) {
        return -1;
    }
    if (character >= '0' && character <= '9') {
        return character - '0';
    } else if (character >= 'a' && character <= 'z') {
        return character - 'a' + 10;
    } else if (character >= 'A' && character <= 'Z') {
        return character - 'A' + 10;
    }
} // function -----------------------------------------------------------------

void
number_parser::report_non_digit_character ()
{
    throw parse_failed{
        "The input string contains a non-digit character "
        "where a digit character was expected.",
        parse_failed::type::digit_character_expected
    };
} // function -----------------------------------------------------------------

int
number_parser::get_next_digit (
    char32_t character,
    unsigned int radix
) {
    int digit = digit_character_to_integer(
        character,
        radix
    );
    if (digit == -1) {
        report_non_digit_character();
    }
    return digit;
} // function -----------------------------------------------------------------

bool
number_parser::is_sign_character (
    char32_t character
)
noexcept
{
    return character == '-' || character == '+';
} // function -----------------------------------------------------------------

bool
number_parser::check_for_sign (
    char32_t character,
    bool& sign_found,
    bool& negate,
    sign_status format_sign_status
) {
    if (is_sign_character(character)) {
        if (sign_found) {
            throw parse_failed{
                "The input string contains multiple "
                "signs but only one is allowed.",
                parse_failed::type::multiple_signs
            };
        }
        if (
            format_sign_status == sign_status::always_show
                || character == '-'
        ) {
            sign_found = true;
            if (character == '-') {
                negate = true;
            }
            return true;
        }
    }
    return false;
} // function -----------------------------------------------------------------

void
number_parser::check_for_thousands_separator (
    char32_t character,
    thousands_separator format_thousands_separator
) {
    if (
        (format_thousands_separator
            == thousands_separator::comma && character != ',')
        || (format_thousands_separator
            == thousands_separator::period && character != '.')
    ) {
        throw parse_failed{
            "The input string did not have a thousands "
            "separator where one was expected.",
            parse_failed::type::thousands_separator_missing
        };
    }
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// --------------------------------------------------------- cmp::parse_failed

// Constructors and Destructor ------------------------------------------------

parse_failed::parse_failed (
    const char* message,
    type t
)
noexcept
    : std::invalid_argument{message}
    , m_type{t}
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

parse_failed::type
parse_failed::get_type ()
const noexcept
{
    return m_type;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
