// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_UNICODE_PARSERS_HPP_INCLUDED
#define CMP_UNICODE_PARSERS_HPP_INCLUDED

#include <cmath>
#include <algorithm>

#include <cmp/unicode/inclusion_assert.hpp>
#include <cmp/core/config.hpp>
#include <cmp/unicode/formats.hpp>
#include <cmp/unicode/concepts.hpp>
#include <cmp/unicode/algorithms.hpp>
#include <cmp/core/general.hpp>

namespace cmp {

namespace impl {

class CMP_LIBRARY_NAME number_parser {
public:
    // Core -------------------------------------------------------------------

    template <
        std::integral Output,
        unicode_string Input
    >
    static
    Output
    parse_integer (
        const Input& input,
        const integer_format& format
    );

    template <
        std::floating_point Output,
        unicode_string Input
    >
    static
    Output
    parse_floating_point (
        const Input& input,
        const floating_point_format& format
    );

private:
    // Private Functions ------------------------------------------------------

    CMP_CONDITIONAL_INLINE
    static
    int
    digit_character_to_integer (
        char32_t character,
        unsigned int radix
    )
    noexcept;

    CMP_CONDITIONAL_INLINE
    static
    void
    report_non_digit_character ();

    CMP_CONDITIONAL_INLINE
    static
    int
    get_next_digit (
        char32_t character,
        unsigned int radix
    );

    CMP_CONDITIONAL_INLINE
    static
    bool
    is_sign_character (
        char32_t character
    )
    noexcept;

    CMP_CONDITIONAL_INLINE
    static
    bool
    check_for_sign (
        char32_t character,
        bool& sign_found,
        bool& negate,
        sign_status format_sign_status
    );

    CMP_CONDITIONAL_INLINE
    static
    void
    check_for_thousands_separator (
        char32_t character,
        thousands_separator format_thousands_separator
    );

    template <
        std::integral Output
    >
    static
    void
    prepend_digit (
        Output& power,
        unsigned int radix,
        Output& output,
        int current_digit,
        unsigned int& digits_counted
    )
    noexcept;

    template <
        std::floating_point Output
    >
    static
    void
    append_digit (
        Output& root,
        unsigned int radix,
        Output& output,
        int current_digit,
        unsigned int& digits_counted
    )
    noexcept;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

class CMP_LIBRARY_NAME parse_failed
    : public std::invalid_argument
{
public:
    // Types ------------------------------------------------------------------

    /**
        Description:
            Indicates the type of failure that was encountered during parsing.
    */
    enum class type {
        empty_input,
        neither_boolean,
        multiple_signs,
        thousands_separator_missing,
        digit_character_expected,
        negative_unsigned,
        wrong_place_limit
    };

    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs a <#type>parse_failed</#type>
            exception with the given message and type.

        Parameters:
            message:
                The message to use with <#this/> exception.
            t:
                The type of failure that was encountered during parsing.
    */
    CMP_CONDITIONAL_INLINE
    parse_failed (
        const char* message,
        type t
    )
    noexcept;

    CMP_CONDITIONAL_INLINE
    ~parse_failed ()
    noexcept override = default;

    // Accessors --------------------------------------------------------------

    /**
        Description:
            Returns the type associated with <#this/> exception.
    */
    CMP_CONDITIONAL_INLINE
    type
    get_type ()
    const noexcept;

private:
    // Private Data -----------------------------------------------------------

    type m_type;
}; // class -------------------------------------------------------------------

/**
    Description:
        Parses the input string and returns the corresponding boolean value.
        The input string is expected to conform to the given bool format. If
        it doesn't, a <#type>parse_failed</#type> exception is thrown.
*/
template <
    unicode_string Input
>
bool
parse_bool (
    Input input,
    const bool_format& format
);

/**
    Description:
        Parses the input string and returns the corresponding integer value.
        The input string is expected to conform to the given integer format.
        If it doesn't, a <#type>parse_failed</#type> exception is thrown.
*/
template <
    std::integral Output,
    unicode_string Input
>
Output
parse_integer (
    const Input& input,
    const integer_format& format
);

/**
    Description:
        Parses the input string and returns the corresponding floating point
        value. The input string is expected to conform to the given floating
        point format. If it doesn't, a <#type>parse_failed</#type> exception
        is thrown.
*/
template <
    std::floating_point Output,
    unicode_string Input
>
Output
parse_floating_point (
    const Input& input,
    const floating_point_format& format
);

} // namespace ----------------------------------------------------------------

#include <cmp/unicode/parsers.ipp>
#if CMP_CONFIG_HEADER_ONLY == true
#   include <cmp/unicode/parsers.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#endif // CMP_UNICODE_PARSERS_HPP_INCLUDED
