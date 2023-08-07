// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/unicode/formatters.hpp>

namespace cmp {

namespace impl {

// ----------------------------------------------- cmp::impl::number_formatter

// Core -----------------------------------------------------------------------

template <
    raii_unicode_string Output,
    std::integral Input
>
Output
number_formatter::format_integer (
    Input input,
    const integer_format& format
) {
    Output output;
    if (input == 0) {
        append_code_point(output, '0');
        return output;
    }
    unsigned int format_radix{format.get_radix()};
    unsigned int digits_counted{0};
    char sign_character{' '};
    if (input < 0) {
        sign_character = '-';
    } else if (format.get_sign_status() == sign_status::always_show) {
        sign_character = '+';
    }
    if constexpr (std::is_signed_v<Input>) {
        input = std::abs(input);
    }
    while (input != 0) {
        char character{static_cast<char>(input % format_radix)};
        if (character <= 9) {
            character += '0';
        } else {
            character += 'A' - 10;
        }
        prepend_code_point(output, character);
        input /= format_radix;
        ++digits_counted;
        if (digits_counted == 3) {
            digits_counted = 0;
            if (input != 0) {
                switch (format.get_thousands_separator()) {
                    case thousands_separator::comma:
                        prepend_code_point(output, ',');
                        break;
                    case thousands_separator::period:
                        prepend_code_point(output, '.');
                        break;
                    case thousands_separator::none:
                        continue;
                }
            }
        }
    }
    if (sign_character != ' ') {
        prepend_code_point(output, sign_character);
    }

    return output;
} // function -----------------------------------------------------------------

template <
    raii_unicode_string Output,
    std::floating_point Input
>
Output
number_formatter::format_floating_point (
    Input input,
    const floating_point_format& format
) {
    integer_format equivalent_format{
        format.get_radix(),
        format.get_sign_status(),
        format.get_thousands_separator()
    };
    Output output{
        number_formatter::format_integer<Output>(
            static_cast<long long>(std::floor(input)),
            equivalent_format
        )
    };
    if (input < 0) {
        input = -input;
    }
    Input fractional_part{input - std::floor(input)};
    if (fractional_part == 0) {
        return output;
    }
    Output fractional_part_string;
    unsigned int digits_counted{0};
    unsigned int radix_places_counted{0};
    while (fractional_part != 0) {
        fractional_part *= format.get_radix();
        char character{static_cast<char>(std::floor(fractional_part))};
        fractional_part -= std::floor(fractional_part);
        if (character <= 9) {
            character += '0';
        } else {
            character += 'A' - 10;
        }
        if (
            format.get_radix_place_limit() != radix_place_limit::none
                && (radix_places_counted++) == format.get_radix_place_count()
        ) {
            break;
        }
        append_code_point(fractional_part_string, character);
        ++digits_counted;
        if (digits_counted == 3) {
            digits_counted = 0;
            switch (format.get_thousands_separator()) {
                case thousands_separator::comma:
                    append_code_point(fractional_part_string, ',');
                    break;
                case thousands_separator::period:
                    append_code_point(fractional_part_string, '.');
                    break;
                case thousands_separator::none:
                    continue;
            }
        }
    }
    if (format.get_radix_place_limit() == radix_place_limit::exactly_equal) {
        while ((radix_places_counted++) < format.get_radix_place_count()) {
            append_code_point(fractional_part_string, '0');
        }
    }
    append_code_point(
        output,
        format.get_radix_character() == radix_character::period ? '.' : ','
    );
    output += fractional_part_string;

    return output;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

template <
    raii_unicode_string Output
>
Output
format_bool (
    bool input,
    const bool_format& format
) {
    return convert_string<Output>(
        input ? format.get_true_string() : format.get_false_string()
    );
} // function -----------------------------------------------------------------

template <
    raii_unicode_string Output,
    std::integral Input
>
Output
format_integer (
    Input input,
    const integer_format& format
) {
    return impl::number_formatter::format_integer<Output>(input, format);
} // function -----------------------------------------------------------------

template <
    raii_unicode_string Output,
    std::floating_point Input
>
Output
format_floating_point (
    Input input,
    const floating_point_format& format
) {
    return impl::number_formatter::format_floating_point<Output>(
        input,
        format
    );
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
