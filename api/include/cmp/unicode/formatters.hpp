// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_UNICODE_FORMATTERS_HPP_INCLUDED
#define CMP_UNICODE_FORMATTERS_HPP_INCLUDED

#include <cmath>

#include <cmp/unicode/inclusion_assert.hpp>
#include <cmp/core/config.hpp>
#include <cmp/unicode/formats.hpp>
#include <cmp/unicode/concepts.hpp>
#include <cmp/unicode/algorithms.hpp>

namespace cmp {

namespace impl {

class number_formatter {
public:
    // Core -------------------------------------------------------------------

    template <
        writable_raii_text_object Output,
        std::integral Input
    >
    static
    Output
    format_integer (
        Input input,
        const integer_format& format
    );

    template <
        writable_raii_text_object Output,
        std::floating_point Input
    >
    static
    Output
    format_floating_point (
        Input input,
        const floating_point_format& format
    );
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

/**
    Description:
        Formats the given bool value with the given
        bool format and returns the formatted string.
*/
template <
    writable_raii_text_object Output
>
Output
format_bool (
    bool input,
    const bool_format& format
);

/**
    Description:
        Formats the given integer value with the given
        integer format and returns the formatted string.
*/
template <
    writable_raii_text_object Output,
    std::integral Input
>
Output
format_integer (
    Input input,
    const integer_format& format
);

/**
    Description:
        Formats the given floating point value with the given
        floating point format and returns the formatted string.
*/
template <
    writable_raii_text_object Output,
    std::floating_point Input
>
Output
format_floating_point (
    Input input,
    const floating_point_format& format
);

} // namespace ----------------------------------------------------------------

#include <cmp/unicode/formatters.ipp>

#endif // CMP_UNICODE_FORMATTERS_HPP_INCLUDED
